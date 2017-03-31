#pragma once
#include <QtWidgets/QMainWindow>
#include <QObject>
#include "VtkDemo.h"
class Graphics:public QObject
{
	Q_OBJECT
public:
	void setUi(VtkDemo *);
	void RenderThreeView(QVTKWidget *, QVTKWidget *, QVTKWidget *, QVTKWidget *);
	void RenderMarchingCube(QVTKWidget *);
	void RenderRayCasting();
	void ClearAllGraphics();
	Graphics();
	~Graphics();
private:
	VtkDemo *uiView;
};

