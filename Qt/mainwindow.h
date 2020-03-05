#pragma once

#include <QtWidgets/QMainWindow>
#include <QPaintEvent>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QTime>

#include "../common/include/inc/free/arcsoft_face_sdk.h"
#include "../common/include/inc/amcomdef.h"
#include "../common/include/inc/asvloffscreen.h"
#include "../common/include/inc/merror.h"
#include "opencv2/opencv.hpp"

#include "ui_mainwindow.h"
//using namespace cv;

//从开发者中心获取APPID/SDKKEY
#define APPID (MPChar)("FnrFdkLR6XpeWw8s6dePvKpuMrFxwoRdQPHAoiwcuRo4")
#define SDKKEY (MPChar)("FYStvUonWC5ga1cxHttgQoN2dadNX28F3rYt25oGQCWz")

#define NSCALE 16 
#define FACENUM	5

#define VIDEO_FRAME_DEFAULT_WIDTH 640
#define VIDEO_FRAME_DEFAULT_HEIGHT 480

#define SafeFree(p) { if ((p)) free(p); (p) = NULL; }
#define SafeArrayDelete(p) { if ((p)) delete [] (p); (p) = NULL; } 
#define SafeDelete(p) { if ((p)) delete (p); (p) = NULL; } 

class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent = 0);
	~mainwindow();
public slots:
	void updateImage();
	void updateDurationInfo();
	void openFile();
	void openCam();
	void openImg();
	void onInput();
	void positionChanged(int position);
private:
	/////////////OpenCV////////////////
	cv::VideoCapture videoCap{};
	cv::Mat currImage, srcImage;
	cv::Size imageSize{ 640, 480 };
	int cDuration = 0;
	/////////////QT///////////////////
	Ui::MainWindow ui{};
	QString fileName{};
	QTimer theTimer{};
	QVector<std::string> vClasses{};
	/////////////ArcFace/////////////
	MHandle handle = nullptr;
	ASVLOFFSCREEN offscreen = { 0 };
	typedef struct
	{
		int age, gender;
		ASF_FaceFeature feature;
	}person_info;
	typedef std::pair<QString, person_info> nameinfoPack;
	QVector<nameinfoPack> vPeople;
	ASF_MultiFaceInfo detectedFaces = { nullptr };
protected:
	void paintEvent(QPaintEvent *e) override;
};