#include "VtkDemo.h"

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtWidgets/QGridLayout>

VtkDemo::VtkDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	RegisteComponent(this);

	Init();

	connectRegiste();
}

void VtkDemo::Init(){
	graphics = new Graphics();
	graphics->RenderThreeView(this->ui.qvtkWidget1, this->ui.qvtkWidget2, this->ui.qvtkWidget3, this->ui.qvtkWidget4);
	//graphics->RenderMarchingCube(this->ui.qvtkWidget1);
	//graphics->RenderRayCasting(this->ui.qvtkWidget1);
}

void VtkDemo::RegisteComponent(QMainWindow *VtkDemoClass){
	this->ui.actionOpen->setIcon(QIcon(":/VtkDemo/ImgSrc/openFile.png"));

	actionThreeView = new QAction(VtkDemoClass);
	actionThreeView->setObjectName(QStringLiteral("actionThreeView"));
	actionThreeView->setIcon(QIcon(":/VtkDemo/ImgSrc/ThreeView.png"));
	actionMarchingCube = new QAction(VtkDemoClass);
	actionMarchingCube->setObjectName(QStringLiteral("actionMarchingCube"));
	actionMarchingCube->setIcon(QIcon(":/VtkDemo/ImgSrc/marchingCube.png"));
	actionRayCasting = new QAction(VtkDemoClass);
	actionRayCasting->setObjectName(QStringLiteral("actionRayCasting"));
	actionRayCasting->setIcon(QIcon(":/VtkDemo/ImgSrc/RayCasting.png"));
	actionDeleteView = new QAction(VtkDemoClass);
	actionDeleteView->setObjectName(QStringLiteral("actionDeleteView"));
	actionDeleteView->setIcon(QIcon(":/VtkDemo/ImgSrc/RayCasting.png"));

	this->ui.mainToolBar->addAction(this->ui.actionOpen);
	this->ui.mainToolBar->addAction(actionThreeView);
	this->ui.mainToolBar->addAction(actionMarchingCube);
	this->ui.mainToolBar->addAction(actionRayCasting);
	this->ui.mainToolBar->addAction(actionDeleteView);

	
}

void VtkDemo::SetThreeViewMode(){
	this->DeleteAllView();

	QVTKWidget *qvtkWidget1;
	QVTKWidget *qvtkWidget2;
	QVTKWidget *qvtkWidget3;
	QVTKWidget *qvtkWidget4;

	qvtkWidget1 = new QVTKWidget(this->ui.gridLayoutWidget);
	qvtkWidget1->setObjectName(QStringLiteral("qvtkWidget1"));

	this->ui.gridLayout->addWidget(qvtkWidget1, 0, 0, 1, 1);

	qvtkWidget2 = new QVTKWidget(this->ui.gridLayoutWidget);
	qvtkWidget2->setObjectName(QStringLiteral("qvtkWidget2"));

	this->ui.gridLayout->addWidget(qvtkWidget2, 0, 1, 1, 1);

	qvtkWidget3 = new QVTKWidget(this->ui.gridLayoutWidget);
	qvtkWidget3->setObjectName(QStringLiteral("qvtkWidget3"));

	this->ui.gridLayout->addWidget(qvtkWidget3, 1, 0, 1, 1);

	qvtkWidget4 = new QVTKWidget(this->ui.gridLayoutWidget);
	qvtkWidget4->setObjectName(QStringLiteral("qvtkWidget4"));

	this->ui.gridLayout->addWidget(qvtkWidget4, 1, 1, 1, 1);

	graphics->RenderThreeView(qvtkWidget1, qvtkWidget2, qvtkWidget3, qvtkWidget4);
}

void VtkDemo::SetMarchingCubeMode(){

	this->DeleteAllView();
	QVTKWidget *qvtkWidget1;

	qvtkWidget1 = new QVTKWidget(this->ui.gridLayoutWidget);
	qvtkWidget1->setObjectName(QStringLiteral("qvtkWidget1"));

	this->ui.gridLayout->addWidget(qvtkWidget1, 0, 0, 1, 1);

	graphics->RenderMarchingCube(qvtkWidget1);
}

void VtkDemo::SetRayCastingMode(){
	this->DeleteAllView();

	QVTKWidget *qvtkWidget1;

	qvtkWidget1 = new QVTKWidget(this->ui.gridLayoutWidget);
	qvtkWidget1->setObjectName(QStringLiteral("qvtkWidget1"));

	this->ui.gridLayout->addWidget(qvtkWidget1, 0, 0, 1, 1);	

	graphics->RenderRayCasting(qvtkWidget1);

}

void VtkDemo::DeleteAllView(){
	/*
	int num = ui.gridLayout->count();
	if (!num){
		return;
	}
	QLayoutItem *p[100];
	for (int i = 0; i <= num; i++){
		p[i] = ui.gridLayout->itemAt(i);
		ui.gridLayout->removeItem(p[i]);
		delete p[i];
	}*/
	
	QLayoutItem *child;
	while (ui.gridLayout->count() != 0)
	{
		int num = ui.gridLayout->count();
		child = ui.gridLayout->takeAt(0);
		delete child->widget();
		delete child;
	}
	/*
	delete this->ui.qvtkWidget1;
	delete this->ui.qvtkWidget2;
	delete this->ui.qvtkWidget3;
	delete this->ui.qvtkWidget4;
	*/
}

void VtkDemo::open()
{
	QString path = QFileDialog::getExistingDirectory(this);
	if (!path.isEmpty()){
		this->DicomPath = path;
	}
	else
	{
		QMessageBox::warning(this, tr("Path") , tr("You did not select any file."));
	}
}

void VtkDemo::connectRegiste(){
	connect(this->ui.actionOpen, &QAction::triggered, this, &VtkDemo::open);
	connect(actionThreeView, &QAction::triggered, this, &VtkDemo::SetThreeViewMode);
	connect(actionMarchingCube, &QAction::triggered, this, &VtkDemo::SetMarchingCubeMode);
	connect(actionRayCasting, &QAction::triggered, this, &VtkDemo::SetRayCastingMode);
	connect(actionDeleteView, &QAction::triggered, this, &VtkDemo::DeleteAllView);
}

