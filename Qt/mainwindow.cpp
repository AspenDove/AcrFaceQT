#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <ctime>

//时间戳转换为日期格式
void timestampToTime(char* timeStamp, char* dateTime, int dateTimeSize)
{
	time_t tTimeStamp = atoll(timeStamp);
	struct tm* pTm = gmtime(&tTimeStamp);
	strftime(dateTime, dateTimeSize, "%Y-%m-%d %H:%M:%S", pTm);
}

//图像颜色格式转换
int ColorSpaceConversion(MInt32 width, MInt32 height, MInt32 format, MUInt8* imgData, ASVLOFFSCREEN& offscreen)
{
	offscreen.u32PixelArrayFormat = static_cast<unsigned int>(format);
	offscreen.i32Width = width;
	offscreen.i32Height = height;

	switch (offscreen.u32PixelArrayFormat)
	{
	case ASVL_PAF_RGB24_B8G8R8:
		offscreen.pi32Pitch[0] = offscreen.i32Width * 3;
		offscreen.ppu8Plane[0] = imgData;
		break;
	case ASVL_PAF_I420:
		offscreen.pi32Pitch[0] = width;
		offscreen.pi32Pitch[1] = width >> 1;
		offscreen.pi32Pitch[2] = width >> 1;
		offscreen.ppu8Plane[0] = imgData;
		offscreen.ppu8Plane[1] = offscreen.ppu8Plane[0] + offscreen.i32Height*offscreen.i32Width;
		offscreen.ppu8Plane[2] = offscreen.ppu8Plane[0] + offscreen.i32Height*offscreen.i32Width * 5 / 4;
		break;
	case ASVL_PAF_NV12:
	case ASVL_PAF_NV21:
		offscreen.pi32Pitch[0] = offscreen.i32Width;
		offscreen.pi32Pitch[1] = offscreen.pi32Pitch[0];
		offscreen.ppu8Plane[0] = imgData;
		offscreen.ppu8Plane[1] = offscreen.ppu8Plane[0] + offscreen.pi32Pitch[0] * offscreen.i32Height;
		break;
	case ASVL_PAF_YUYV:
	case ASVL_PAF_DEPTH_U16:
		offscreen.pi32Pitch[0] = offscreen.i32Width * 2;
		offscreen.ppu8Plane[0] = imgData;
		break;
	case ASVL_PAF_GRAY:
		offscreen.pi32Pitch[0] = offscreen.i32Width;
		offscreen.ppu8Plane[0] = imgData;
		break;
	default:
		return 0;
	}
	return 1;
}


mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	(void)connect(&theTimer, &QTimer::timeout, this, &mainwindow::updateImage);
	(void)connect(ui.actChooseVideo, &QAction::triggered, this, &mainwindow::openFile);
	(void)connect(ui.actExit, &QAction::triggered, this, &mainwindow::close);
	(void)connect(ui.actOpenCam, &QAction::triggered, this, &mainwindow::openCam);
	(void)connect(ui.actChooseImg, &QAction::triggered, this, &mainwindow::openImg);
	(void)connect(&theTimer, &QTimer::timeout, this, &mainwindow::updateDurationInfo);
	(void)connect(ui.slrContent, &QSlider::sliderPressed, &theTimer, &QTimer::stop);
	(void)connect(ui.slrContent, &QSlider::sliderMoved, this, &mainwindow::positionChanged);
	(void)connect(ui.slrContent, &QSlider::sliderReleased, &theTimer, static_cast<void (QTimer::*)()>(&QTimer::start));
	(void)connect(ui.btnInput, &QPushButton::clicked, this, &mainwindow::onInput);

	MRESULT res = MOK;
	ASF_ActiveFileInfo activeFileInfo = { 0 };
	res = ASFGetActiveFileInfo(&activeFileInfo);
	if (res != MOK)
	{
		QMessageBox::information(this,
			tr(u8"错误"),
			tr(u8"ASFGetActiveFileInfo fail: %1").arg(res));
	}
	else
	{
		//这里仅获取了有效期时间，还需要其他信息直接打印即可
		char startDateTime[32];
		timestampToTime(activeFileInfo.startTime, startDateTime, 32);
		//printf("startTime: %s\n", startDateTime);
		char endDateTime[32];
		timestampToTime(activeFileInfo.endTime, endDateTime, 32);
		//printf("endTime: %s\n", endDateTime);
	}

	//SDK版本信息
	const ASF_VERSION version = ASFGetVersion();
	//printf("\nVersion:%s\n", version.Version);
	//printf("BuildDate:%s\n", version.BuildDate);
	//printf("CopyRight:%s\n", version.CopyRight);

	//printf("\n************* Face Recognition *****************\n");

	res = ASFOnlineActivation(APPID, SDKKEY);
	if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res)
		QMessageBox::information(this,
			tr(u8"错误"),
			tr(u8"ASFOnlineActivation fail: %1").arg(res));

	//初始化引擎
	MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION | ASF_AGE | ASF_GENDER | ASF_FACE3DANGLE | ASF_LIVENESS | ASF_IR_LIVENESS;
	res = ASFInitEngine(ASF_DETECT_MODE_IMAGE,
		ASF_OP_0_ONLY,
		NSCALE,
		FACENUM,
		mask,
		&handle);
	if (res != MOK)
		QMessageBox::information(this,
			tr(u8"错误"),
			tr(u8"ASFInitEngine fail: %1").arg(res));
}

mainwindow::~mainwindow()
{
	videoCap.release();
}

void mainwindow::openCam()
{
	//从摄像头捕获视频
	if (videoCap.open(0))
	{
		fileName.clear();
		srcImage = cv::Mat::zeros(imageSize, CV_8UC3);
		ui.slrContent->setVisible(false);
		theTimer.start(1);
	}
	else
	{
		QMessageBox::information(this,
			tr(u8"错误"),
			tr(u8"打开摄像头失败!"));
	}
}
void mainwindow::openFile()
{
	const QString file =
		QFileDialog::getOpenFileName(this,
			tr(u8"选择视频"),
			"",
			tr("Videos (*.avi *.mp4)"));
	if (file.isEmpty())
	{
		return;
	}
	else
	{
		fileName = file;
		if (videoCap.open(file.toStdString()))
		{
			srcImage = cv::Mat::zeros(imageSize, CV_8UC3);
			const int frame_count = int(videoCap.get(CV_CAP_PROP_FRAME_COUNT));
			const double fps = videoCap.get(CV_CAP_PROP_FPS);
			cDuration = frame_count / fps;
			ui.slrContent->setMaximum(frame_count);
			ui.slrContent->setVisible(true);
			theTimer.start(1);
		}
		else
		{
			QMessageBox::information(this,
				tr(u8"错误"),
				tr(u8"打开视频失败!"));
		}
	}
}
void mainwindow::openImg()
{
	const QString file =
		QFileDialog::getOpenFileName(this,
			tr(u8"选择图像"),
			"",
			tr("Images (*.png *.bmp *.jpg *.tif *.gif)"));
	if (file.isEmpty())return;

	fileName = file;
	srcImage = cv::imread(file.toStdString());
	if (!srcImage.empty())
	{
		currImage = srcImage.clone();
		videoCap.release();
		ui.slrContent->setVisible(false);
		theTimer.stop();
		updateImage();
	}
	else
	{
		QMessageBox::information(this,
			tr(u8"错误"),
			tr(u8"打开图像失败!"));
	}
}

void mainwindow::onInput()
{
	const QString strName = ui.editName->text();
	MRESULT res = MOK;
	if (strName.isEmpty())
	{
		QMessageBox::information(this,
			tr(u8"错误"),
			tr(u8"姓名为空"));
		return;
	}

	auto pos = 
	std::find_if(vPeople.begin(), vPeople.end(), [&](const nameinfoPack& x) {return x.first == strName; });
	if (pos != vPeople.end())
	{
		QMessageBox::information(this,
			tr(u8"错误"),
			tr(u8"该信息已存在"));
		////////////TODO:replace or discard?
		return;
	}
	else
	{
		theTimer.stop();
		ASF_SingleFaceInfo SingleDetectedFace = { 0 };
		ASF_FaceFeature feature = { 0 };
		SingleDetectedFace.faceRect = detectedFaces.faceRect[0];
		SingleDetectedFace.faceOrient = detectedFaces.faceOrient[0];

		res = ASFFaceFeatureExtractEx(handle, &offscreen, &SingleDetectedFace, &feature);
		if (res != MOK)
		{
			QMessageBox::information(this,
				tr(u8"错误"),
				tr(u8"ASFFaceFeatureExtractEx 1 fail: %1").arg(res));
			return;
		}
		else
		{
			//拷贝feature，否则第二次进行特征提取，会覆盖第一次特征提取的数据，导致比对的结果为1
			person_info this_person;
			this_person.feature.featureSize = feature.featureSize;
			this_person.feature.feature = static_cast<MByte*>(malloc(feature.featureSize));
			//memset(this_person.feature.feature, 0, feature1.featureSize);
			memcpy(this_person.feature.feature, feature.feature, feature.featureSize);
			vPeople.push_back(std::make_pair(strName,this_person));

			ui.tabInfo->insertRow(ui.tabInfo->rowCount());

			ui.tabInfo->setItem(ui.tabInfo->rowCount() - 1,
				0,
				new QTableWidgetItem(strName));
			ui.tabInfo->setItem(ui.tabInfo->rowCount() - 1,
				1,
				new QTableWidgetItem(u8"男"));
		}
		if (videoCap.isOpened())
			theTimer.start(1);
		else
		{
			currImage = srcImage.clone();
			updateImage();
		}
	}
}

void mainwindow::positionChanged(int position)
{
	videoCap.set(CV_CAP_PROP_POS_FRAMES, position);
}

void mainwindow::paintEvent(QPaintEvent *e)
{
	//显示方法一
	//QPainter painter(this);
	//QImage image1 = QImage((uchar*)(currImage.data), currImage.cols, currImage.rows, QImage::Format_RGB888);
	//painter.drawImage(QPoint(20, 20), image1);
	//显示方法二
	if (currImage.data)
	{
		const QImage image2 = QImage(static_cast<uchar*>(currImage.data),
			currImage.cols, currImage.rows, QImage::Format_RGB888);

		ui.ImageLabel->setPixmap(QPixmap::fromImage(image2));
		ui.ImageLabel->resize(image2.size());
		ui.ImageLabel->show();
	}
}

void mainwindow::updateImage()
{
	if (videoCap.isOpened())videoCap >> currImage;
	MRESULT res = MOK;
	if (currImage.data)
	{
		float x_ratio = static_cast<float>(currImage.cols) / imageSize.width;
		float y_ratio = static_cast<float>(currImage.rows) / imageSize.height;

		float ratio = std::max(x_ratio, y_ratio);
		cv::resize(currImage, currImage,
			cv::Size(currImage.cols / ratio - int(currImage.cols / ratio) % 2, currImage.rows / ratio));
		cv::cvtColor(currImage, currImage, cv::COLOR_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR

		ColorSpaceConversion(currImage.cols, currImage.rows,
			ASVL_PAF_RGB24_B8G8R8, currImage.data, offscreen);

		//第一张人脸
		//ASF_MultiFaceInfo detectedFaces1 = { nullptr };
		ASF_SingleFaceInfo SingleDetectedFaces = { 0 };
		//ASF_FaceFeature feature1 = { 0 };

		res = ASFDetectFacesEx(handle, &offscreen, &detectedFaces);
		if (res != MOK && detectedFaces.faceNum > 0)
		{
			//printf("ASFDetectFaces 1 fail: %d\n", res);
		}
		else
		{
			for (int i = 0; i != detectedFaces.faceNum; ++i)
			{
				const MRECT facerect = detectedFaces.faceRect[i];
				cv::rectangle(currImage,
					cv::Point(facerect.left, facerect.top),
					cv::Point(facerect.right, facerect.bottom),
					cv::Scalar(255, 0, 0));


				ASF_FaceFeature currFeature;
				ASF_SingleFaceInfo SingleDetectedFace = { facerect,detectedFaces.faceOrient[i] };
				ASFFaceFeatureExtractEx(handle, &offscreen, &SingleDetectedFace, &currFeature);

				// 单人脸特征比对
				MFloat confidenceLevel = 0, maxConfidenceLevel = 0;
				QString strName = "unKnown";
				for (auto &person : vPeople)
				{
					res = ASFFaceFeatureCompare(handle, &currFeature, &person.second.feature,
						&confidenceLevel);
					if (confidenceLevel > maxConfidenceLevel&&confidenceLevel > 0.8)
					{
						maxConfidenceLevel = confidenceLevel;
						strName = person.first;
					}
					//maxConfidenceLevel = std::max()
					/*if (res != MOK)
						printf("ASFFaceFeatureCompare fail: %d\n", res);
					else
						printf("ASFFaceFeatureCompare sucess: %lf\n", confidenceLevel);*/
				}
				//cv::Mat img = currImage.clone();
				QImage image = QImage(static_cast<uchar*>(currImage.data),
					currImage.cols, currImage.rows, currImage.step,
					QImage::Format_RGB888);
				QPainter p;
				p.begin(&image);
				p.setPen(QPen(Qt::red));
				p.setFont(QFont("Times", 12, QFont::Bold));
				p.drawText(QPoint(facerect.left, facerect.top - 10), strName);
				p.end();
				//currImage = cv::Mat(image.height(), image.width(), CV_8UC3, image.bits()).clone();
				/*cv::putText(currImage, strName, cv::Point(facerect.left, facerect.top - 10),
					CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);*/
			}
			// 单人脸特征提取
			/*res = ASFFaceFeatureExtractEx(handle, &offscreen, &SingleDetectedFaces, &feature1);
			if (res != MOK)
			{
				QMessageBox::information(this,
					tr(u8"错误"),
					tr(u8"ASFFaceFeatureExtractEx 1 fail: %1").arg(res));
				return;
			}
			else*/
			{
				//拷贝feature，否则第二次进行特征提取，会覆盖第一次特征提取的数据，导致比对的结果为1
				/*copyfeature1.featureSize = feature1.featureSize;
				copyfeature1.feature = (MByte *)malloc(feature1.featureSize);
				memset(copyfeature1.feature, 0, feature1.featureSize);
				memcpy(copyfeature1.feature, feature1.feature, feature1.featureSize);*/
			}
		}


		//uint8_t* c_out = reinterpret_cast<uint8_t*>(PyArray_DATA(np_ret));
		//currImage = cv::Mat(dims[0], dims[1], CV_8UC3, reinterpret_cast<void*>(c_out)).clone();
		this->update(); //发送刷新消息
	}
}

void mainwindow::updateDurationInfo()
{
	QString tStr;

	if (fileName.isEmpty())
	{
		tStr = QDateTime::currentDateTime().toString("hh:mm:ss") + " / --:--";
	}
	else
	{
		const int currentInfo = videoCap.get(CV_CAP_PROP_POS_MSEC) / 1000;

		ui.slrContent->setValue(static_cast<int>(videoCap.get(CV_CAP_PROP_POS_FRAMES)));

		const QTime currentTime((currentInfo / 3600) % 60,
			(currentInfo / 60) % 60,
			(currentInfo % 60),
			(currentInfo * 1000) % 1000);
		const QTime totalTime((cDuration / 3600) % 60,
			(cDuration / 60) % 60,
			(cDuration % 60),
			(cDuration * 1000) % 1000);
		QString format;

		if (cDuration > 3600)
			format = "hh:mm:ss";
		else format = "mm:ss";

		tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
	}

	ui.labContentDuration->setText(tStr);
}
