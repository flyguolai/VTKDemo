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
	this->SetThreeViewMode();
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

	actionSliderMove = new QAction(VtkDemoClass);

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

	this->GetThreeViewProps();
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
	QLayoutItem *child;
	while (ui.gridLayout->count() != 0)
	{
		int num = ui.gridLayout->count();
		child = ui.gridLayout->takeAt(0);
		delete child->widget();
		delete child;
	}
}

void VtkDemo::GetThreeViewProps(){
	char* str[3];
	
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget->resize(ui.tabWidget->width(), ui.tabWidget->height());
	QTableWidgetItem *item00 = new QTableWidgetItem("ren1");
	item00->setBackgroundColor(QColor(200, 200, 200));

	ui.tableWidget->setRowHeight(0, 20);
	ui.tableWidget->setColumnCount(2);
	ui.tableWidget->setRowCount(3);
	ui.tableWidget->setItem(0, 0, new QTableWidgetItem("ren1WindowValue"));
	//itoa(graphics->GetWindowLevelThreeView(0)[0], str[0],10);
	ui.tableWidget->setItem(0, 1, new QTableWidgetItem("3"));

	QTableWidgetItem *columnHeaderItem0 = ui.tableWidget->horizontalHeaderItem(0);
	if (columnHeaderItem0){
		columnHeaderItem0->setText(QString("Props"));
	}

	QTableWidgetItem *columnHeaderItem1 = ui.tableWidget->horizontalHeaderItem(1);
	if (columnHeaderItem1){
		columnHeaderItem1->setText(QString("value"));
	}
	

	ui.tableWidget->setColumnWidth(0, ui.tableWidget->width() / 3);
	ui.tableWidget->setColumnWidth(1, ui.tableWidget->width() * 2 / 3);
	ui.tableWidget->verticalHeader()->setVisible(false);
};

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

void VtkDemo::SetWindowLevel1(){
	QSlider *slider;
	slider = ui.horizontalSlider_1;
	double wl = slider->value();
	graphics->imgViewer[0]->SetColorLevel(wl);
	graphics->renWin[0]->Render();
	ui.spinBox_1->setValue(wl);
};

void VtkDemo::SetWindowLevel2(){
	QSlider *slider;
	slider = ui.horizontalSlider_2;
	double wl = slider->value();
	graphics->imgViewer[1]->SetColorLevel(wl);
	graphics->renWin[1]->Render();
	ui.spinBox_2->setValue(wl);
};

void VtkDemo::SetWindowLevel3(){
	QSlider *slider;
	slider = ui.horizontalSlider_3;
	double wl = slider->value();
	graphics->imgViewer[2]->SetColorLevel(wl);
	graphics->renWin[2]->Render();
	ui.spinBox_3->setValue(wl);
};

void VtkDemo::SetWindow1(){
	QSlider *slider;
	slider = ui.horizontalSlider_4;
	double wl = slider->value();
	graphics->imgViewer[0]->SetColorWindow(wl);
	graphics->renWin[0]->Render();
	ui.spinBox_4->setValue(wl);
};

void VtkDemo::SetWindow2(){
	QSlider *slider;
	slider = ui.horizontalSlider_5;
	double wl = slider->value();
	graphics->imgViewer[1]->SetColorWindow(wl);
	graphics->renWin[1]->Render();
	ui.spinBox_5->setValue(wl);
};


void VtkDemo::SetWindow3(){
	QSlider *slider;
	slider = ui.horizontalSlider_6;
	double wl = slider->value();
	graphics->imgViewer[2]->SetColorWindow(wl);
	graphics->renWin[2]->Render();
	ui.spinBox_6->setValue(wl);
};




void VtkDemo::connectRegiste(){
	connect(this->ui.actionOpen, &QAction::triggered, this, &VtkDemo::open);
	connect(actionThreeView, &QAction::triggered, this, &VtkDemo::SetThreeViewMode);
	connect(actionMarchingCube, &QAction::triggered, this, &VtkDemo::SetMarchingCubeMode);
	connect(actionRayCasting, &QAction::triggered, this, &VtkDemo::SetRayCastingMode);
	connect(actionDeleteView, &QAction::triggered, this, &VtkDemo::DeleteAllView);

	connect(ui.horizontalSlider_1, &QSlider::valueChanged, this, &VtkDemo::SetWindowLevel1);
	connect(ui.horizontalSlider_2, &QSlider::valueChanged, this, &VtkDemo::SetWindowLevel2);
	connect(ui.horizontalSlider_3, &QSlider::valueChanged, this, &VtkDemo::SetWindowLevel3);

	connect(ui.horizontalSlider_4, &QSlider::valueChanged, this, &VtkDemo::SetWindow1);
	connect(ui.horizontalSlider_5, &QSlider::valueChanged, this, &VtkDemo::SetWindow2);
	connect(ui.horizontalSlider_6, &QSlider::valueChanged, this, &VtkDemo::SetWindow3);

}

