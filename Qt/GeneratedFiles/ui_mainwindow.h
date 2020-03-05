/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actChooseVideo;
    QAction *actExit;
    QAction *actOpenCam;
    QAction *actChooseImg;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTableWidget *tabInfo;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QPushButton *btnStart;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *ImageLabel;
    QSpacerItem *verticalSpacer;
    QSplitter *splitter;
    QSlider *slrContent;
    QLabel *labContentDuration;
    QHBoxLayout *horizontalLayout;
    QLineEdit *editName;
    QPushButton *btnInput;
    QMenuBar *menuBar;
    QMenu *File;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 295);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actChooseVideo = new QAction(MainWindow);
        actChooseVideo->setObjectName(QStringLiteral("actChooseVideo"));
        actExit = new QAction(MainWindow);
        actExit->setObjectName(QStringLiteral("actExit"));
        actOpenCam = new QAction(MainWindow);
        actOpenCam->setObjectName(QStringLiteral("actOpenCam"));
        actChooseImg = new QAction(MainWindow);
        actChooseImg->setObjectName(QStringLiteral("actChooseImg"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        tabInfo = new QTableWidget(centralWidget);
        if (tabInfo->columnCount() < 2)
            tabInfo->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        tabInfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        tabInfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tabInfo->setObjectName(QStringLiteral("tabInfo"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabInfo->sizePolicy().hasHeightForWidth());
        tabInfo->setSizePolicy(sizePolicy1);
        tabInfo->setSortingEnabled(true);

        verticalLayout->addWidget(tabInfo);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_2->addWidget(pushButton, 1, 1, 1, 1);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 0, 1, 1, 1);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 1, 0, 1, 1);

        btnStart = new QPushButton(centralWidget);
        btnStart->setObjectName(QStringLiteral("btnStart"));
        btnStart->setAutoDefault(false);
        btnStart->setFlat(false);

        gridLayout_2->addWidget(btnStart, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        ImageLabel = new QLabel(centralWidget);
        ImageLabel->setObjectName(QStringLiteral("ImageLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ImageLabel->sizePolicy().hasHeightForWidth());
        ImageLabel->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(ImageLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        slrContent = new QSlider(splitter);
        slrContent->setObjectName(QStringLiteral("slrContent"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(slrContent->sizePolicy().hasHeightForWidth());
        slrContent->setSizePolicy(sizePolicy3);
        slrContent->setOrientation(Qt::Horizontal);
        splitter->addWidget(slrContent);
        labContentDuration = new QLabel(splitter);
        labContentDuration->setObjectName(QStringLiteral("labContentDuration"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(labContentDuration->sizePolicy().hasHeightForWidth());
        labContentDuration->setSizePolicy(sizePolicy4);
        splitter->addWidget(labContentDuration);

        verticalLayout_2->addWidget(splitter);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        editName = new QLineEdit(centralWidget);
        editName->setObjectName(QStringLiteral("editName"));

        horizontalLayout->addWidget(editName);

        btnInput = new QPushButton(centralWidget);
        btnInput->setObjectName(QStringLiteral("btnInput"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(btnInput->sizePolicy().hasHeightForWidth());
        btnInput->setSizePolicy(sizePolicy5);
        btnInput->setAutoDefault(false);
        btnInput->setFlat(false);

        horizontalLayout->addWidget(btnInput);


        verticalLayout_3->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 23));
        File = new QMenu(menuBar);
        File->setObjectName(QStringLiteral("File"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(File->menuAction());
        File->addAction(actOpenCam);
        File->addAction(actChooseImg);
        File->addAction(actChooseVideo);
        File->addSeparator();
        File->addAction(actExit);

        retranslateUi(MainWindow);

        btnStart->setDefault(false);
        btnInput->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actChooseVideo->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\247\206\351\242\221(&C)", nullptr));
        actExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272(&E)", nullptr));
        actOpenCam->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264(&O)", nullptr));
        actChooseImg->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207(&P)", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tabInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\345\220\215\345\255\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tabInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\345\271\264\351\276\204", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        btnStart->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        ImageLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        labContentDuration->setText(QApplication::translate("MainWindow", "--:--/--:--", nullptr));
        btnInput->setText(QApplication::translate("MainWindow", "\345\275\225\345\205\245", nullptr));
        File->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
