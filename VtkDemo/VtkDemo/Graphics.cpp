#include "Graphics.h"

#include "vtkSmartPointer.h"

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
#include "vtkImplicitPlaneWidget.h"
#include "vtkStripper.h"
#include "vtkMarchingCubes.h"


Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

class vtkReslicePickerCallback : public vtkCommand{
public:
	static vtkReslicePickerCallback *New(){
		return new vtkReslicePickerCallback;
	}

	void Execute(vtkObject *caller, unsigned long e, void *callData){

	}
};

class vtkResliceCursorCallback : public vtkCommand
{
public:
	static vtkResliceCursorCallback *New()
	{
		return new vtkResliceCursorCallback;
	}

	void Execute(vtkObject *caller, unsigned long e/*ev*/,
		void *callData) VTK_OVERRIDE
	{
		vtkImagePlaneWidget* ipw =
		dynamic_cast< vtkImagePlaneWidget* >(caller);
		vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
		
		vtkInteractorStyleImage *irenstyle = dynamic_cast<vtkInteractorStyleImage*>(caller);
		if (e == vtkCommand::StartPickEvent){
			if (irenstyle == this->RWin[0]->GetInteractor()->GetInteractorStyle())
			{
				this->IPW[1]->SetPlaneOrientation(1);
				this->IPW[2]->SetPlaneOrientation(2);
				int x, y;
				RWin[0]->GetInteractor()->GetEventPosition(x, y);
				picker->Pick(x, y, 0, this->ren[0]);
				picker->GetPickPosition(pos);
				
				this->IPW[1]->SetSliceIndex((int)pos[0] / spacey);
				this->IPW[2]->SetSliceIndex(extent[5] - extent[0] - ((int)pos[1] / spacez));
			}

			if (irenstyle == this->RWin[1]->GetInteractor()->GetInteractorStyle())
			{
				this->IPW[0]->SetPlaneOrientation(0);
				this->IPW[2]->SetPlaneOrientation(2);
				int x, y;
				RWin[1]->GetInteractor()->GetEventPosition(x, y);
				picker->Pick(x, y, 0, this->ren[1]);
				picker->GetPickPosition(pos);
				this->IPW[0]->SetSliceIndex(-(int)pos[0] / spacex);
				this->IPW[2]->SetSliceIndex((int)pos[1] / spacez);
			}

			if (irenstyle == this->RWin[2]->GetInteractor()->GetInteractorStyle())
			{
				this->IPW[1]->SetPlaneOrientation(1);
				this->IPW[0]->SetPlaneOrientation(0);
				int x, y;
				RWin[2]->GetInteractor()->GetEventPosition(x, y);
				picker->Pick(x, y, 0, this->ren[2]);
				picker->GetPickPosition(pos);
				this->IPW[0]->SetSliceIndex((int)pos[0] / spacex);
				this->IPW[1]->SetSliceIndex(this->extent[3]-this->extent[2] - (int)pos[1] / spacey);
			}
			this->RWinPlane->Render();
		}

		if (e == vtkCommand::MouseWheelForwardEvent){
			if (irenstyle == this->RWin[0]->GetInteractor()->GetInteractorStyle())
			{
				int index[2];
				index[0] = this->IPW[1]->GetSliceIndex();
				index[1] = this->IPW[2]->GetSliceIndex();
				this->IPW[1]->SetPlaneOrientation(1);
				this->IPW[2]->SetPlaneOrientation(2);
				this->IPW[1]->SetSliceIndex(index[0]);
				this->IPW[2]->SetSliceIndex(index[1]);
				this->IPW[0]->SetSliceIndex(this->IPW[0]->GetSliceIndex() - 1);
			}

			if (irenstyle == this->RWin[1]->GetInteractor()->GetInteractorStyle())
			{
				int index[2];
				index[0] = this->IPW[0]->GetSliceIndex();
				index[1] = this->IPW[2]->GetSliceIndex();
				this->IPW[0]->SetPlaneOrientation(0);
				this->IPW[2]->SetPlaneOrientation(2);
				this->IPW[0]->SetSliceIndex(index[0]);
				this->IPW[2]->SetSliceIndex(index[1]);
				this->IPW[1]->SetSliceIndex(this->IPW[1]->GetSliceIndex() - 1);
			}

			if (irenstyle == this->RWin[2]->GetInteractor()->GetInteractorStyle())
			{
				int index[2];
				index[0] = this->IPW[1]->GetSliceIndex();
				index[1] = this->IPW[0]->GetSliceIndex();
				this->IPW[1]->SetPlaneOrientation(1);
				this->IPW[0]->SetPlaneOrientation(0);
				this->IPW[1]->SetSliceIndex(index[0]);
				this->IPW[0]->SetSliceIndex(index[1]);
				this->IPW[2]->SetSliceIndex(this->IPW[2]->GetSliceIndex() - 1);
			}
			this->RWinPlane->Render();
		}

		if (e == vtkCommand::MouseWheelBackwardEvent){
			if (irenstyle == this->RWin[0]->GetInteractor()->GetInteractorStyle())
			{
				int index[2];
				index[0] = this->IPW[1]->GetSliceIndex();
				index[1] = this->IPW[2]->GetSliceIndex();
				this->IPW[1]->SetPlaneOrientation(1);
				this->IPW[2]->SetPlaneOrientation(2);
				this->IPW[1]->SetSliceIndex(index[0]);
				this->IPW[2]->SetSliceIndex(index[1]);
				this->IPW[0]->SetSliceIndex(this->IPW[0]->GetSliceIndex() + 1);
			}

			if (irenstyle == this->RWin[1]->GetInteractor()->GetInteractorStyle())
			{
				int index[2];
				index[0] = this->IPW[0]->GetSliceIndex();
				index[1] = this->IPW[2]->GetSliceIndex();
				this->IPW[0]->SetPlaneOrientation(0);
				this->IPW[2]->SetPlaneOrientation(2);
				this->IPW[0]->SetSliceIndex(index[0]);
				this->IPW[2]->SetSliceIndex(index[1]);
				this->IPW[1]->SetSliceIndex(this->IPW[1]->GetSliceIndex() + 1);
			}

			if (irenstyle == this->RWin[2]->GetInteractor()->GetInteractorStyle())
			{
				int index[2];
				index[0] = this->IPW[1]->GetSliceIndex();
				index[1] = this->IPW[0]->GetSliceIndex();
				this->IPW[1]->SetPlaneOrientation(1);
				this->IPW[0]->SetPlaneOrientation(0);
				this->IPW[1]->SetSliceIndex(index[0]);
				this->IPW[0]->SetSliceIndex(index[1]);
				this->IPW[2]->SetSliceIndex(this->IPW[2]->GetSliceIndex() + 1);
			}
			this->RWinPlane->Render();
		}
		

		if (e == vtkCommand::StartInteractionEvent){
			if (ipw)
			{
				ipw->GetCurrentCursorPosition(pos);
				if (ipw == this->IPW[0])
				{
					this->IPW[1]->SetPlaneOrientation(1);
					this->IPW[2]->SetPlaneOrientation(2);
					this->IPW[1]->SetSliceIndex(pos[1]);
					this->IPW[2]->SetSliceIndex(pos[2]);
				}
				else if (ipw == this->IPW[1])
				{
					this->IPW[0]->SetPlaneOrientation(0);
					this->IPW[2]->SetPlaneOrientation(2);
					this->IPW[0]->SetSliceIndex(pos[0]);
					this->IPW[2]->SetSliceIndex(pos[2]);
				}
				else if (ipw == this->IPW[2])
				{
					this->IPW[1]->SetPlaneOrientation(1);
					this->IPW[0]->SetPlaneOrientation(0);
					this->IPW[1]->SetSliceIndex(pos[1]);
					this->IPW[0]->SetSliceIndex(pos[0]);
				}
			}
		}

		if (e = vtkCommand::EndInteractionEvent){

		}
		for (int i = 0; i < 3; i++){
			this->flip[i]->Update();
			this->RWin[i]->Render();
		}
	}

	vtkResliceCursorCallback() {}
	vtkSmartPointer<vtkImagePlaneWidget> IPW[3];
	vtkSmartPointer<vtkRenderWindow> RWin[3];
	vtkSmartPointer<vtkRenderer> ren[3];
	vtkSmartPointer<vtkImageFlip> flip[3];
	vtkSmartPointer<vtkImageViewer2> image[3];
	vtkSmartPointer<vtkRenderWindow> RWinPlane;
	vtkSmartPointer<vtkPoints> LineCenterPoint[3];
	vtkSmartPointer<vtkLine> line[3][2];
	int extent[6];
	double pos[3];
	double spacex, spacey, spacez;
};

void Graphics::RenderThreeView(QVTKWidget *widget1, QVTKWidget *widget2, QVTKWidget *widget3, QVTKWidget *widget4){

	vtkSmartPointer< vtkDICOMImageReader > reader = vtkSmartPointer< vtkDICOMImageReader >::New();
	reader->SetDirectoryName("D:\\vtkproject\\digest_article");
	reader->Update();

	int imageDims[3];
	reader->GetOutput()->GetDimensions(imageDims);

	double x, y, z;

	reader->GetDataSpacing(x, y, z);
	int extent[6];
	reader->GetDataExtent(extent);


	for (int i = 0; i < 3; i++){
		visimage[i] = vtkSmartPointer<vtkInteractorStyleImage>::New();
		iteractor[i] = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		iteractor[i]->SetInteractorStyle(visimage[i]);
	}



	for (int i = 0; i < 3; i++){
		ren[i] = vtkSmartPointer<vtkRenderer>::New();
	}

	vtkSmartPointer<vtkCellPicker> picker =
		vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);

	vtkSmartPointer<vtkProperty> ipwProp =
		vtkSmartPointer<vtkProperty>::New();

	vtkSmartPointer< vtkRenderer > ThreeViewRen =
		vtkSmartPointer< vtkRenderer >::New();

	widget4->GetRenderWindow()->AddRenderer(ThreeViewRen);

	//ren->GetActiveCamera()->SetFocalPoint(0,0,0);


	vtkRenderWindowInteractor *iren = widget4->GetInteractor();
	ThreeViewRen->ResetCamera();

	for (int i = 0; i < 3; i++)
	{
		//windowLevel[i] = vtkSmartPointer <vtkImageMapToWindowLevelColors>::New();
		planeWidget[i] = vtkSmartPointer<vtkImagePlaneWidget>::New();
		planeWidget[i]->SetInteractor(iren);
		planeWidget[i]->SetPicker(picker);
		planeWidget[i]->RestrictPlaneToVolumeOn();
		double color[3] = { 0, 0, 0 };
		color[i] = 1;
		planeWidget[i]->GetPlaneProperty()->SetColor(color);

		//planeWidget[i]->SetKeyPressActivationValue('x');
		planeWidget[i]->SetTexturePlaneProperty(ipwProp);
		planeWidget[i]->TextureInterpolateOff();
		planeWidget[i]->SetResliceInterpolateToLinear();
		planeWidget[i]->SetInputConnection(reader->GetOutputPort());
		planeWidget[i]->SetPlaneOrientation(i);
		planeWidget[i]->SetSliceIndex(imageDims[i] / 2);
		planeWidget[i]->DisplayTextOn();
		planeWidget[i]->SetDefaultRenderer(ThreeViewRen);
		planeWidget[i]->SetWindowLevel(1358, -27);
		planeWidget[i]->On();
		planeWidget[i]->InteractionOn();
	}

	planeWidget[1]->SetLookupTable(planeWidget[0]->GetLookupTable());
	planeWidget[2]->SetLookupTable(planeWidget[0]->GetLookupTable());

	ThreeViewRen->GetActiveCamera()->Elevation(110);
	ThreeViewRen->GetActiveCamera()->SetViewUp(0, 0, -1);
	ThreeViewRen->GetActiveCamera()->Azimuth(45);
	ThreeViewRen->GetActiveCamera()->Dolly(1.15);
	ThreeViewRen->ResetCameraClippingRange();

	vtkSmartPointer<vtkImageFlip> flip[3];

	vtkSmartPointer<vtkImagePlaneWidget> ipw[3];

	for (int i = 0; i < 3; i++){
		flip[i] = vtkSmartPointer<vtkImageFlip>::New();
		flip[i]->SetInputData(planeWidget[i]->GetResliceOutput());
		if (i != 1){
			flip[i]->SetFilteredAxes(1);
		}

		flip[i]->Update();

		imgViewer[i] = vtkSmartPointer<vtkImageViewer2>::New();
		imgViewer[i]->SetInputData(flip[i]->GetOutput());

		imgViewer[i]->UpdateDisplayExtent();
		imgViewer[i]->SetColorLevel(800);
		imgViewer[i]->SetColorWindow(1387);
		
		imgViewer[i]->SetRenderer(ren[i]);
	}
	imgViewer[1]->GetImageActor()->RotateZ(90);

	vtkSmartPointer<vtkPoints> LineCenterPoint[3];
	vtkSmartPointer<vtkLine> line[3][2];
	vtkSmartPointer<vtkPolyData> linesPolyData = vtkSmartPointer<vtkPolyData>::New();

	vtkSmartPointer<vtkResliceCursorCallback> cbk = vtkSmartPointer<vtkResliceCursorCallback>::New();

	for (int i = 0; i < 3; i++)
	{
		LineCenterPoint[i] = vtkSmartPointer<vtkPoints>::New();
		line[i][0] = vtkSmartPointer<vtkLine>::New();
		line[i][1] = vtkSmartPointer<vtkLine>::New();

		cbk->flip[i] = flip[i];
		cbk->IPW[i] = planeWidget[i];
		cbk->ren[i] = imgViewer[i]->GetRenderer();
		cbk->image[i] = imgViewer[i];
		
	}

	for (int i = 0; i < 6; i++)
	{
		cbk->extent[i] = extent[i];
	}

	

	cbk->spacex = x;
	cbk->spacey = y;
	cbk->spacez = z;
	

	cbk->RWin[0] = widget1->GetRenderWindow();
	cbk->RWin[1] = widget2->GetRenderWindow();
	cbk->RWin[2] = widget3->GetRenderWindow();
	cbk->RWinPlane = widget4->GetRenderWindow();

	//这里添加回调监听
	for (int i = 0; i < 3; i++){
		visimage[i]->AddObserver(vtkCommand::StartPickEvent, cbk);
		visimage[i]->AddObserver(vtkCommand::MouseWheelForwardEvent, cbk);
		visimage[i]->AddObserver(vtkCommand::MouseWheelBackwardEvent, cbk);
		//visimage[i]->AddObserver(vtkCommand::WindowLevelEvent, cbk);
		planeWidget[i]->AddObserver(vtkCommand::LeftButtonPressEvent, cbk);
		planeWidget[i]->AddObserver(vtkCommand::StartInteractionEvent, cbk);
		planeWidget[i]->AddObserver(vtkCommand::EndInteractionEvent, cbk);
	}

	//widget1->SetRenderWindow(imgViewer[0]->GetRenderWindow());
	
	widget1->GetRenderWindow()->AddRenderer(ren[0]);
	renWin[0] = widget1->GetRenderWindow();
	widget1->GetRenderWindow()->GetInteractor()->SetInteractorStyle(visimage[0]);
	widget1->GetInteractor()->SetPicker(picker);
	widget2->GetRenderWindow()->AddRenderer(ren[1]);
	renWin[1] = widget2->GetRenderWindow();
	widget2->GetRenderWindow()->GetInteractor()->SetInteractorStyle(visimage[1]);
	widget2->GetInteractor()->SetPicker(picker);
	widget3->GetRenderWindow()->AddRenderer(ren[2]);
	renWin[2] = widget3->GetRenderWindow();
	widget3->GetRenderWindow()->GetInteractor()->SetInteractorStyle(visimage[2]);
	widget3->GetInteractor()->SetPicker(picker);

	

	ren[0]->ResetCamera();
	ren[1]->ResetCamera();
	ren[2]->ResetCamera();

}

void Graphics::SetWindowLevelThreeView(int i,int window,int level){

	

}

void Graphics::RenderMarchingCube(QVTKWidget *widget){
	vtkSmartPointer<vtkRenderer> aRenderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkActor> skin = vtkSmartPointer<vtkActor>::New();
	aRenderer->AddActor(skin);
	//renWin->AddRenderer(aRenderer);
	
	//vtkSmartPointer<vtkInteractorStyleTrackball> TrackBall = vtkSmartPointer<vtkInteractorStyleTrackball>::New();

	vtkSmartPointer<vtkInteractorStyleSwitch> InteractorSwitch = vtkSmartPointer<vtkInteractorStyleSwitch>::New();

	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	iren->SetInteractorStyle(InteractorSwitch);
	//iren->SetRenderWindow(renWin);

	vtkSmartPointer<vtkDICOMImageReader> v16 = vtkSmartPointer<vtkDICOMImageReader>::New();
	v16->SetDataByteOrderToLittleEndian();
	v16->SetDirectoryName("D:\\vtkproject\\digest_article");// 文件目录path  
	//v16->SetDataSpacing(3.2, 3.2, 1.5);

	skinExtractor = vtkSmartPointer<vtkMarchingCubes>::New();
	skinExtractor->SetInputConnection(v16->GetOutputPort());
	skinExtractor->SetValue(0, 140  );
	skinExtractor->ComputeGradientsOn();
	skinExtractor->ComputeNormalsOn();
	skinExtractor->ComputeScalarsOn();
	
	/*
	vtkSmartPointer<vtkContourFilter> skinExtractor = vtkSmartPointer<vtkContourFilter>::New();
	skinExtractor->SetInputConnection(v16->GetOutputPort());
	skinExtractor->SetValue(0, 140);
	*/

	vtkSmartPointer<vtkStripper> stripper = vtkSmartPointer<vtkStripper>::New();
	stripper->SetInputConnection(skinExtractor->GetOutputPort());

	vtkSmartPointer<vtkPolyDataNormals> skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();
	skinNormals->SetInputConnection(stripper->GetOutputPort());
	skinNormals->SetFeatureAngle(60.0);

	vtkSmartPointer<vtkPolyDataMapper> skinMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	skinMapper->SetInputConnection(skinNormals->GetOutputPort());
	skinMapper->ScalarVisibilityOff();

	
	skin->SetMapper(skinMapper);

	//   
	
	vtkSmartPointer<vtkOutlineFilter> outlineData = vtkSmartPointer<vtkOutlineFilter>::New();
	outlineData->SetInputConnection(v16->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapOutline = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapOutline->SetInputConnection(outlineData->GetOutputPort());

	vtkSmartPointer<vtkActor> outline = vtkSmartPointer<vtkActor>::New();
	outline->SetMapper(mapOutline);
	outline->GetProperty()->SetColor(0, 0, 0);
	
	//  
	vtkSmartPointer<vtkCamera> aCamera = vtkSmartPointer<vtkCamera>::New();
	aCamera->SetViewUp(0, 0, -1);
	aCamera->SetPosition(0, 1, 0);
	aCamera->SetFocalPoint(0, 0, 0);
	aCamera->ComputeViewPlaneNormal();
	aCamera->Azimuth(30.0); //New  
	aCamera->Elevation(30.0);//New  

	//  
	//aRenderer->AddActor(outline);
	
	aRenderer->SetActiveCamera(aCamera);
	aRenderer->ResetCamera();
	//aCamera->Dolly(1.5);

	//  
	aRenderer->SetBackground(1, 1, 1);// can change  
	//renWin->SetSize(640, 480);

	//  
	//aRenderer->ResetCameraClippingRange();
	widget->GetRenderWindow()->AddRenderer(aRenderer);

	vtkMarchingCubeWindow = widget->GetRenderWindow();
}

class vtkRayCastingPlaneCallback : public vtkCommand
{
public:
	static vtkRayCastingPlaneCallback *New()
	{
		return new vtkRayCastingPlaneCallback;
	}

	void Execute(vtkObject *caller, unsigned long e, void *callData){
		vtkImplicitPlaneWidget *planeWidget =
			reinterpret_cast<vtkImplicitPlaneWidget*>(caller);
		planeWidget->GetPlane(this->Plane);
		this->Volume->VisibilityOn();
	}

	vtkRayCastingPlaneCallback() :Plane(0), Volume(0) {}
	vtkPlane *Plane;
	vtkVolume *Volume;
};

void Graphics::RenderRayCasting(QVTKWidget *widget){
	vtkSmartPointer<vtkDICOMImageReader>dicomImagereader = vtkSmartPointer<vtkDICOMImageReader>::New();
	dicomImagereader->SetDirectoryName("D:\\vtkproject\\digest_article");
	dicomImagereader->SetDataByteOrderToLittleEndian();
	dicomImagereader->Update();
	//dicomImagereader->SetDataByteOrderToLittleEndian();


	int extent[6];
	dicomImagereader->GetDataExtent(extent);

	double spacing[3];
	dicomImagereader->GetDataSpacing(spacing);

	int xx, yy, zz;
	xx = (int)((extent[1] + 1)*spacing[0]);
	yy = (int)((extent[3] + 1)*spacing[1]);
	zz = (int)((extent[5] + 1)*spacing[2]);

	vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();

	vtkSmartPointer<vtkImageCast>readerImageCast = vtkSmartPointer<vtkImageCast>::New();
	readerImageCast->SetInputConnection(dicomImagereader->GetOutputPort());
	readerImageCast->SetOutputScalarTypeToUnsignedShort();
	readerImageCast->Update();

	vtkSmartPointer<vtkPiecewiseFunction>opactiyTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
	opactiyTransferFunction->AddPoint(0, 0.00);
	opactiyTransferFunction->AddPoint(100, 0.00);
	opactiyTransferFunction->AddPoint(500, 0.15);
	opactiyTransferFunction->AddPoint(1000, 0.15);
	opactiyTransferFunction->AddPoint(1150, 0.85);

	colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
	colorTransferFunction->AddRGBPoint(0, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(500, 1.0, 0.5, 0.3);
	colorTransferFunction->AddRGBPoint(1000, 1.0, 0.5, 0.3);
	colorTransferFunction->AddRGBPoint(1150, 1.0, 1.0, 0.9);

	gradientTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
	gradientTransferFunction->AddPoint(0, 0.00);
	gradientTransferFunction->AddPoint(500, 0.15);
	gradientTransferFunction->AddPoint(1000, 0.15);
	gradientTransferFunction->AddPoint(1150, 0.85);

	volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetColor(colorTransferFunction);
	volumeProperty->SetScalarOpacity(opactiyTransferFunction);
	volumeProperty->SetGradientOpacity(gradientTransferFunction);
	volumeProperty->ShadeOn();//阴影  
	volumeProperty->SetInterpolationTypeToLinear();//直线与样条插值之间逐发函数  
	volumeProperty->SetAmbient(0.2);//环境光系数  
	volumeProperty->SetDiffuse(0.9);//漫反射  
	volumeProperty->SetSpecular(0.2);//高光系数  
	volumeProperty->SetSpecularPower(10);//高光强度  

	//vtkSmartPointer<vtkVolumeRayCastCompositeFunction>compositeRaycastFunction = vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();

	vtkSmartPointer<vtkGPUVolumeRayCastMapper>volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	//vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
	//volumeMapper->SetVolumeRayCastFunction(compositeRaycastFunction);//载入体绘制方法  
	volumeMapper->SetBlendModeToComposite();
	volumeMapper->SetSampleDistance(0.1);
	volumeMapper->SetInputConnection(readerImageCast->GetOutputPort());

	volumeMapper->AddClippingPlane(plane);
	/*fixedPointVolumeMapper=vtkFixedPointVolumeRayCastMapper::New();
	fixedPointVolumeMapper->SetInput(dicomImagereader->GetOutput());*/

	vtkSmartPointer<vtkVolume>volume = vtkSmartPointer<vtkVolume>::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);//设置体属性  

	vtkSmartPointer<vtkRenderer>ren1 = vtkSmartPointer<vtkRenderer>::New();
	ren1->AddVolume(volume);
	//ren1->GetActiveCamera()->SetPosition(0, 0, 1);

	vtkSmartPointer<vtkRayCastingPlaneCallback> CallBack = vtkSmartPointer<vtkRayCastingPlaneCallback>::New();
	CallBack->Plane = plane;
	CallBack->Volume = volume;

	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren = widget->GetInteractor();

	vtkSmartPointer<vtkImplicitPlaneWidget> planeWidget = vtkSmartPointer<vtkImplicitPlaneWidget>::New();
	planeWidget->SetInteractor(iren);
	planeWidget->SetPlaceFactor(1.25);
	planeWidget->GetPlaneProperty()->SetOpacity(0.1);
	planeWidget->GetOutlineProperty()->SetColor(0, 0, 1);
	planeWidget->SetOrigin(xx / 2, yy / 2, zz / 2);
	planeWidget->SetInputData((vtkDataSet *)dicomImagereader->GetOutput());
	planeWidget->PlaceWidget();
	planeWidget->AddObserver(vtkCommand::InteractionEvent, CallBack);
	//planeWidget->SetDefaultRenderer(ren1);
	//planeWidget->SetEnabled(1);

	widget->GetRenderWindow()->AddRenderer(ren1);

	iren->SetKeyCode('i');
	
}
