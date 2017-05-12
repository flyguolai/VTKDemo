#pragma once
#include <QtWidgets/QMainWindow>
#include <QObject>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include "vtkResliceImageViewer.h"
#include "vtkResliceCursorLineRepresentation.h"
#include "vtkResliceCursorThickLineRepresentation.h"
#include "vtkResliceCursorWidget.h"
#include "vtkResliceCursorActor.h"
#include "vtkResliceCursorPolyDataAlgorithm.h"
#include "vtkResliceCursor.h"
#include "vtkDICOMImageReader.h"
#include "vtkCellPicker.h"
#include "vtkProperty.h"
#include "vtkPlane.h"
#include "vtkImageData.h"
#include "vtkCommand.h"
#include "vtkPlaneSource.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "vtkInteractorStyleImage.h"
#include "vtkImageSlabReslice.h"
#include "vtkBoundedPlanePointPlacer.h"
#include "vtkDistanceWidget.h"
#include "vtkDistanceRepresentation.h"
#include "vtkHandleRepresentation.h"
#include "vtkResliceImageViewerMeasurements.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkPointHandleRepresentation3D.h"
#include "vtkPointHandleRepresentation2D.h"
#include "vtkImagePlaneWidget.h"
#include "vtkImageCast.h"  
#include "vtkPiecewiseFunction.h"  
#include "vtkVolumeProperty.h"
#include "vtkColorTransferFunction.h"  
#include "vtkVolumeRayCastCompositeFunction.h"  
#include "vtkVolumeRayCastMapper.h"  
#include "vtkInteractorStyleSwitch.h"
#include "vtkCamera.h"
#include "vtkPolyDataNormals.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkOutlineFilter.h"
#include "vtkInteractorStyleTrackball.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkImageActor.h"
#include "vtkImageFlip.h"
#include "vtkMarchingCubes.h"

#include "QVTKWidget.h"

class Graphics:public QObject
{
	Q_OBJECT
public:
	void RenderThreeView(QVTKWidget *, QVTKWidget *, QVTKWidget *, QVTKWidget *);
	void RenderMarchingCube(QVTKWidget *);
	void RenderRayCasting(QVTKWidget *);


	void SetWindowLevelThreeView(int, int, int);

	//这里其实应该设置三个graphic，然后继承于一个有基础方法的graphic然后再继续写下去，变量会好很多，但是。。。我偷懒了

	//三视图属性
	vtkSmartPointer<vtkInteractorStyleImage> visimage[3];
	vtkSmartPointer<vtkRenderWindowInteractor> iteractor[3];
	vtkSmartPointer<vtkImagePlaneWidget> planeWidget[3];
	vtkSmartPointer<vtkRenderer> ren[3];
	vtkSmartPointer<vtkRenderWindow> renWin[3];
	vtkSmartPointer<vtkImageViewer2> imgViewer[3];

	//面绘制属性
	vtkSmartPointer<vtkMarchingCubes> skinExtractor;
	vtkSmartPointer<vtkRenderWindow> vtkMarchingCubeWindow;

	//体绘制属性
	vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction;
	vtkSmartPointer<vtkPiecewiseFunction> gradientTransferFunction;
	vtkSmartPointer<vtkVolumeProperty> volumeProperty;
	
	Graphics();
	~Graphics();
private:
};

