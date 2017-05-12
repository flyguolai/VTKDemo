/********************************************************************************
** Form generated from reading UI file 'VtkDemo.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VTKDEMO_H
#define UI_VTKDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_VtkDemoClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QVTKWidget *qvtkWidget3;
    QVTKWidget *qvtkWidget1;
    QVTKWidget *qvtkWidget2;
    QVTKWidget *qvtkWidget4;
    QGroupBox *VtkSetValueBox;
    QTabWidget *tabWidget_2;
    QWidget *ThreeViewPropSetTab;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinBox_1;
    QSlider *horizontalSlider_1;
    QLabel *ren1WinLevel;
    QLabel *ren2WinLevel;
    QLabel *ren3WinLevel;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinBox_2;
    QSlider *horizontalSlider_2;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *spinBox_3;
    QSlider *horizontalSlider_3;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QSpinBox *spinBox_4;
    QSlider *horizontalSlider_4;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *spinBox_5;
    QSlider *horizontalSlider_5;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_6;
    QSpinBox *spinBox_6;
    QSlider *horizontalSlider_6;
    QWidget *MarchingCubeSetPropsTabBox;
    QWidget *RayCastingSetPropsTab;
    QGroupBox *VtkPropsBox;
    QTabWidget *tabWidget;
    QWidget *VtkPrpsTab;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menuFiles;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VtkDemoClass)
    {
        if (VtkDemoClass->objectName().isEmpty())
            VtkDemoClass->setObjectName(QStringLiteral("VtkDemoClass"));
        VtkDemoClass->resize(899, 600);
        actionOpen = new QAction(VtkDemoClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralWidget = new QWidget(VtkDemoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 651, 531));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        qvtkWidget3 = new QVTKWidget(gridLayoutWidget);
        qvtkWidget3->setObjectName(QStringLiteral("qvtkWidget3"));

        gridLayout->addWidget(qvtkWidget3, 1, 0, 1, 1);

        qvtkWidget1 = new QVTKWidget(gridLayoutWidget);
        qvtkWidget1->setObjectName(QStringLiteral("qvtkWidget1"));

        gridLayout->addWidget(qvtkWidget1, 0, 0, 1, 1);

        qvtkWidget2 = new QVTKWidget(gridLayoutWidget);
        qvtkWidget2->setObjectName(QStringLiteral("qvtkWidget2"));

        gridLayout->addWidget(qvtkWidget2, 0, 1, 1, 1);

        qvtkWidget4 = new QVTKWidget(gridLayoutWidget);
        qvtkWidget4->setObjectName(QStringLiteral("qvtkWidget4"));

        gridLayout->addWidget(qvtkWidget4, 1, 1, 1, 1);

        VtkSetValueBox = new QGroupBox(centralWidget);
        VtkSetValueBox->setObjectName(QStringLiteral("VtkSetValueBox"));
        VtkSetValueBox->setGeometry(QRect(670, 230, 221, 311));
        tabWidget_2 = new QTabWidget(VtkSetValueBox);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(10, 20, 201, 281));
        ThreeViewPropSetTab = new QWidget();
        ThreeViewPropSetTab->setObjectName(QStringLiteral("ThreeViewPropSetTab"));
        horizontalLayoutWidget = new QWidget(ThreeViewPropSetTab);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 20, 191, 24));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        spinBox_1 = new QSpinBox(horizontalLayoutWidget);
        spinBox_1->setObjectName(QStringLiteral("spinBox_1"));
        spinBox_1->setMaximum(1000);

        horizontalLayout->addWidget(spinBox_1);

        horizontalSlider_1 = new QSlider(horizontalLayoutWidget);
        horizontalSlider_1->setObjectName(QStringLiteral("horizontalSlider_1"));
        horizontalSlider_1->setMaximum(1024);
        horizontalSlider_1->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider_1);

        ren1WinLevel = new QLabel(ThreeViewPropSetTab);
        ren1WinLevel->setObjectName(QStringLiteral("ren1WinLevel"));
        ren1WinLevel->setGeometry(QRect(0, 0, 81, 16));
        ren2WinLevel = new QLabel(ThreeViewPropSetTab);
        ren2WinLevel->setObjectName(QStringLiteral("ren2WinLevel"));
        ren2WinLevel->setGeometry(QRect(0, 80, 81, 16));
        ren3WinLevel = new QLabel(ThreeViewPropSetTab);
        ren3WinLevel->setObjectName(QStringLiteral("ren3WinLevel"));
        ren3WinLevel->setGeometry(QRect(0, 160, 81, 16));
        horizontalLayoutWidget_2 = new QWidget(ThreeViewPropSetTab);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 100, 191, 24));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        spinBox_2 = new QSpinBox(horizontalLayoutWidget_2);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMaximum(1000);

        horizontalLayout_2->addWidget(spinBox_2);

        horizontalSlider_2 = new QSlider(horizontalLayoutWidget_2);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setMaximum(1000);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_2);

        horizontalLayoutWidget_3 = new QWidget(ThreeViewPropSetTab);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 180, 191, 24));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        spinBox_3 = new QSpinBox(horizontalLayoutWidget_3);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMaximum(1000);

        horizontalLayout_3->addWidget(spinBox_3);

        horizontalSlider_3 = new QSlider(horizontalLayoutWidget_3);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setMaximum(1000);
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_3);

        horizontalLayoutWidget_4 = new QWidget(ThreeViewPropSetTab);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(0, 50, 191, 24));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        spinBox_4 = new QSpinBox(horizontalLayoutWidget_4);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setMaximum(1000);

        horizontalLayout_4->addWidget(spinBox_4);

        horizontalSlider_4 = new QSlider(horizontalLayoutWidget_4);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setMaximum(1000);
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSlider_4);

        horizontalLayoutWidget_5 = new QWidget(ThreeViewPropSetTab);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(0, 130, 191, 24));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        spinBox_5 = new QSpinBox(horizontalLayoutWidget_5);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setMaximum(1000);

        horizontalLayout_5->addWidget(spinBox_5);

        horizontalSlider_5 = new QSlider(horizontalLayoutWidget_5);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setMaximum(1000);
        horizontalSlider_5->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(horizontalSlider_5);

        horizontalLayoutWidget_6 = new QWidget(ThreeViewPropSetTab);
        horizontalLayoutWidget_6->setObjectName(QStringLiteral("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(0, 210, 191, 24));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        spinBox_6 = new QSpinBox(horizontalLayoutWidget_6);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setMaximum(1000);

        horizontalLayout_6->addWidget(spinBox_6);

        horizontalSlider_6 = new QSlider(horizontalLayoutWidget_6);
        horizontalSlider_6->setObjectName(QStringLiteral("horizontalSlider_6"));
        horizontalSlider_6->setMaximum(1000);
        horizontalSlider_6->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(horizontalSlider_6);

        tabWidget_2->addTab(ThreeViewPropSetTab, QString());
        MarchingCubeSetPropsTabBox = new QWidget();
        MarchingCubeSetPropsTabBox->setObjectName(QStringLiteral("MarchingCubeSetPropsTabBox"));
        tabWidget_2->addTab(MarchingCubeSetPropsTabBox, QString());
        RayCastingSetPropsTab = new QWidget();
        RayCastingSetPropsTab->setObjectName(QStringLiteral("RayCastingSetPropsTab"));
        tabWidget_2->addTab(RayCastingSetPropsTab, QString());
        VtkPropsBox = new QGroupBox(centralWidget);
        VtkPropsBox->setObjectName(QStringLiteral("VtkPropsBox"));
        VtkPropsBox->setGeometry(QRect(670, 10, 221, 221));
        tabWidget = new QTabWidget(VtkPropsBox);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 20, 201, 191));
        VtkPrpsTab = new QWidget();
        VtkPrpsTab->setObjectName(QStringLiteral("VtkPrpsTab"));
        tableWidget = new QTableWidget(VtkPrpsTab);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 191, 171));
        tabWidget->addTab(VtkPrpsTab, QString());
        VtkDemoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VtkDemoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 899, 23));
        menuFiles = new QMenu(menuBar);
        menuFiles->setObjectName(QStringLiteral("menuFiles"));
        VtkDemoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VtkDemoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        VtkDemoClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VtkDemoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VtkDemoClass->setStatusBar(statusBar);

        menuBar->addAction(menuFiles->menuAction());
        menuFiles->addAction(actionOpen);

        retranslateUi(VtkDemoClass);

        tabWidget_2->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(VtkDemoClass);
    } // setupUi

    void retranslateUi(QMainWindow *VtkDemoClass)
    {
        VtkDemoClass->setWindowTitle(QApplication::translate("VtkDemoClass", "VtkDemo", 0));
        actionOpen->setText(QApplication::translate("VtkDemoClass", "Open", 0));
        VtkSetValueBox->setTitle(QApplication::translate("VtkDemoClass", "\346\223\215\344\275\234\350\247\206\347\252\227", 0));
        ren1WinLevel->setText(QApplication::translate("VtkDemoClass", "\350\247\206\347\252\2271\347\252\227\345\256\275\344\270\216\347\252\227\344\275\215\357\274\232", 0));
        ren2WinLevel->setText(QApplication::translate("VtkDemoClass", "\350\247\206\347\252\2272\347\252\227\345\256\275\344\270\216\347\252\227\344\275\215\357\274\232", 0));
        ren3WinLevel->setText(QApplication::translate("VtkDemoClass", "\350\247\206\347\252\2273\347\252\227\345\256\275\344\270\216\347\252\227\344\275\215\357\274\232:", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(ThreeViewPropSetTab), QApplication::translate("VtkDemoClass", "\344\270\211\347\273\264\350\247\206\345\233\276", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(MarchingCubeSetPropsTabBox), QApplication::translate("VtkDemoClass", "\351\235\242\347\273\230\345\210\266", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(RayCastingSetPropsTab), QApplication::translate("VtkDemoClass", "\344\275\223\347\273\230\345\210\266", 0));
        VtkPropsBox->setTitle(QApplication::translate("VtkDemoClass", "\345\261\236\346\200\247\350\247\206\347\252\227", 0));
        tabWidget->setTabText(tabWidget->indexOf(VtkPrpsTab), QApplication::translate("VtkDemoClass", "\345\261\236\346\200\247\345\200\274", 0));
        menuFiles->setTitle(QApplication::translate("VtkDemoClass", "Files", 0));
    } // retranslateUi

};

namespace Ui {
    class VtkDemoClass: public Ui_VtkDemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTKDEMO_H
