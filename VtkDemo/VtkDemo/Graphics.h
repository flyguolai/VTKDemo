#pragma once
#include <QtWidgets/QMainWindow>
#include <QObject>

#include "QVTKWidget.h"

class Graphics:public QObject
{
	Q_OBJECT
public:
	void RenderThreeView(QVTKWidget *, QVTKWidget *, QVTKWidget *, QVTKWidget *);
	void RenderMarchingCube(QVTKWidget *);
	void RenderRayCasting(QVTKWidget *);
	Graphics();
	~Graphics();
private:
};

