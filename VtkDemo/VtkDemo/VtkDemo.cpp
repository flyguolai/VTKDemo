#include "VtkDemo.h"
#include "Graphics.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

VtkDemo::VtkDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connectRegiste();
	RegisteComponent(this);

	Init();
	
}

void VtkDemo::Init(){
	Graphics *graphics = new Graphics();
	graphics->RenderThreeView(this->ui.qvtkWidget1, this->ui.qvtkWidget2, this->ui.qvtkWidget3, this->ui.qvtkWidget4);
	//graphics->RenderMarchingCube(this->ui.qvtkWidget1);
}

void VtkDemo::RegisteComponent(QMainWindow *VtkDemoClass){

	QAction *actionThreeView;
	QAction *actionMarchingCube;
	QAction *actionRayCasting;

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

	this->ui.mainToolBar->addAction(this->ui.actionOpen);
	this->ui.mainToolBar->addAction(actionThreeView);
	this->ui.mainToolBar->addAction(actionMarchingCube);
	this->ui.mainToolBar->addAction(actionRayCasting);


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
	connect(this->ui.actionOpen, &QAction::triggered,this,&VtkDemo::open);
}

