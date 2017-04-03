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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
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
    QWidget *MarchingCubeSetPropsTabBox;
    QWidget *RayCastingSetPropsTab;
    QGroupBox *VtkPropsBox;
    QTabWidget *tabWidget;
    QWidget *VtkPrpsTab;
    QMenuBar *menuBar;
    QMenu *menuFiles;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VtkDemoClass)
    {
        if (VtkDemoClass->objectName().isEmpty())
            VtkDemoClass->setObjectName(QStringLiteral("VtkDemoClass"));
        VtkDemoClass->resize(900, 600);
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
        tabWidget->addTab(VtkPrpsTab, QString());
        VtkDemoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VtkDemoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 900, 23));
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
