#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VtkDemo.h"
#include "Graphics.h"


class VtkDemo : public QMainWindow
{
    Q_OBJECT

public:
    VtkDemo(QWidget *parent = Q_NULLPTR);

	void Init();

	void RegisteComponent(QMainWindow *); // 注册控件，并显示
	
	void open();//打开的方法

	void connectRegiste();// QT 信号槽注册

	void SetThreeViewMode();

	void SetMarchingCubeMode();

	void SetRayCastingMode();

	void DeleteAllView();

private:
    Ui::VtkDemoClass ui;
	QString DicomPath;
	QAction *actionThreeView;
	QAction *actionMarchingCube;
	QAction *actionRayCasting;
	QAction *actionDeleteView;
	Graphics *graphics;
};
