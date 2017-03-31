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



Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

void Graphics::RenderThreeView(QVTKWidget *widget1, QVTKWidget *widget2, QVTKWidget *widget3, QVTKWidget *widget4){
	
	vtkSmartPointer< vtkDICOMImageReader > reader = vtkSmartPointer< vtkDICOMImageReader >::New();
	reader->SetDirectoryName("D:\\vtkproject\\digest_article");
	reader->Update();


	int imageDims[3];
	reader->GetOutput()->GetDimensions(imageDims);
	vtkSmartPointer<vtkResliceImageViewer> riw[3];

	vtkSmartPointer<vtkRenderWindowInteractor> iteractorImage = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	vtkSmartPointer<vtkInteractorStyleImage> visimage = vtkSmartPointer<vtkInteractorStyleImage>::New();

	iteractorImage->SetInteractorStyle(visimage);

	for (int i = 0; i < 3; i++)
	{
		riw[i] = vtkSmartPointer< vtkResliceImageViewer >::New();
		//riw[i]->SetupInteractor(iteractorImage);
	}
	//widget1->SetRenderWindow(riw[0]->GetRenderWindow());

	widget1->GetRenderWindow()->AddRenderer(riw[0]->GetRenderer());
	widget2->GetRenderWindow()->AddRenderer(riw[1]->GetRenderer());
	widget3->GetRenderWindow()->AddRenderer(riw[2]->GetRenderer());

	for (int i = 0; i < 3; i++)
	{
		// make them all share the same reslice cursor object.
		riw[i]->SetInputData(reader->GetOutput());
		riw[i]->SetSliceOrientation(i);
		riw[i]->SetResliceMode(0);
		//riw[i]->SetResliceModeToAxisAligned();
		riw[i]->Render();
	}

	

	vtkSmartPointer<vtkCellPicker> picker =
		vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);

	vtkSmartPointer<vtkProperty> ipwProp =
		vtkSmartPointer<vtkProperty>::New();

	vtkSmartPointer< vtkRenderer > ren =
		vtkSmartPointer< vtkRenderer >::New();

	widget4->GetRenderWindow()->AddRenderer(ren);
	vtkRenderWindowInteractor *iren = widget4->GetInteractor();

	vtkSmartPointer <vtkImagePlaneWidget> planeWidget[3];

	//vtkSmartPointer <vtkImageMapToWindowLevelColors> windowLevel[3];

	//vtkSmartPointer <vtkImageActor> imageActor[3];

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

		color[0] /= 4.0;
		color[1] /= 4.0;
		color[2] /= 4.0;
		riw[i]->GetRenderer()->SetBackground(color);


		planeWidget[i]->SetTexturePlaneProperty(ipwProp);
		planeWidget[i]->TextureInterpolateOff();
		planeWidget[i]->SetResliceInterpolateToLinear();
		planeWidget[i]->SetInputConnection(reader->GetOutputPort());
		planeWidget[i]->SetPlaneOrientation(i);
		planeWidget[i]->SetSliceIndex(imageDims[i] / 2);
		planeWidget[i]->DisplayTextOn();
		//planeWidget[i]->SetDefaultRenderer(ren);
		planeWidget[i]->SetWindowLevel(1358, -27);
		//planeWidget[i]->SetColorMap(windowLevel[i]) ;
		planeWidget[i]->On();
		planeWidget[i]->InteractionOn();

	}

}

void Graphics::RenderMarchingCube(QVTKWidget *widget){
	vtkSmartPointer<vtkRenderer> aRenderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	//renWin->AddRenderer(aRenderer);
	widget->GetRenderWindow()->AddRenderer(aRenderer);
	//vtkSmartPointer<vtkInteractorStyleTrackball> TrackBall = vtkSmartPointer<vtkInteractorStyleTrackball>::New();

	vtkSmartPointer<vtkInteractorStyleSwitch> InteractorSwitch = vtkSmartPointer<vtkInteractorStyleSwitch>::New();

	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	iren->SetInteractorStyle(InteractorSwitch);
	//iren->SetRenderWindow(renWin);

	vtkSmartPointer<vtkDICOMImageReader> v16 = vtkSmartPointer<vtkDICOMImageReader>::New();
	v16->SetDataByteOrderToLittleEndian();
	v16->SetDirectoryName("D:\\vtkproject\\digest_article");// ÎÄ¼þÄ¿Â¼path  
	v16->SetDataSpacing(3.2, 3.2, 1.5);

	vtkSmartPointer<vtkContourFilter> skinExtractor = vtkSmartPointer<vtkContourFilter>::New();
	skinExtractor->SetInputConnection(v16->GetOutputPort());
	skinExtractor->SetValue(0, 500);

	vtkSmartPointer<vtkPolyDataNormals> skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();
	skinNormals->SetInputConnection(skinExtractor->GetOutputPort());
	skinNormals->SetFeatureAngle(60.0);

	vtkSmartPointer<vtkPolyDataMapper> skinMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	skinMapper->SetInputConnection(skinNormals->GetOutputPort());
	skinMapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> skin = vtkSmartPointer<vtkActor>::New();
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
	aRenderer->AddActor(outline);
	aRenderer->AddActor(skin);
	aRenderer->SetActiveCamera(aCamera);
	aRenderer->ResetCamera();
	aCamera->Dolly(1.5);

	//  
	aRenderer->SetBackground(1, 1, 1);// can change  
	//renWin->SetSize(640, 480);

	//  
	aRenderer->ResetCameraClippingRange();
}



/*
//----------------------------------------------------------------------------
class vtkResliceCursorCallback3 : public vtkCommand
{
public:
	static vtkResliceCursorCallback3 *New()
	{
		return new vtkResliceCursorCallback3;
	}


	void Execute(vtkObject *caller, unsigned long,
		void *callData) VTK_OVERRIDE
	{

		vtkImagePlaneWidget* ipw =
		dynamic_cast< vtkImagePlaneWidget* >(caller);

		if (ipw)
		{
			double* wl = static_cast<double*>(callData);

			if (ipw == this->IPW[0])
			{
				this->IPW[1]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[2]->SetWindowLevel(wl[0], wl[1], 1);
			}
			else if (ipw == this->IPW[1])
			{
				this->IPW[0]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[2]->SetWindowLevel(wl[0], wl[1], 1);
			}
			else if (ipw == this->IPW[2])
			{
				this->IPW[0]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[1]->SetWindowLevel(wl[0], wl[1], 1);
			}
		}

		vtkResliceCursorWidget *rcw = dynamic_cast<
			vtkResliceCursorWidget * >(caller);
		if (rcw)
		{
			vtkResliceCursorLineRepresentation *rep = dynamic_cast<
				vtkResliceCursorLineRepresentation * >(rcw->GetRepresentation());
			// Although the return value is not used, we keep the get calls
			// in case they had side-effects
			rep->GetResliceCursorActor()->GetCursorAlgorithm()->GetResliceCursor();
			for (int i = 0; i < 3; i++)
			{
				vtkPlaneSource *ps = static_cast< vtkPlaneSource * >(
					this->IPW[i]->GetPolyDataAlgorithm());
				ps->SetOrigin(this->RCW[i]->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetOrigin());
				ps->SetPoint1(this->RCW[i]->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetPoint1());
				ps->SetPoint2(this->RCW[i]->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetPoint2());

				// If the reslice plane has modified, update it on the 3D widget
				this->IPW[i]->UpdatePlacement();
			}
		}

		// Render everything
		for (int i = 0; i < 3; i++)
		{
			this->RCW[i]->Render();
		}
		this->IPW[0]->GetInteractor()->GetRenderWindow()->Render();
	}

	vtkResliceCursorCallback3() {}
	vtkImagePlaneWidget* IPW[3];
	vtkResliceCursorWidget *RCW[3];
};


//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	//char* fname = vtkTestUtilities::ExpandDataFileName(argc, argv, "Data/headsq/quarter");

	vtkSmartPointer<vtkDICOMImageReader> reader =
		vtkSmartPointer<vtkDICOMImageReader>::New();
	reader->SetDirectoryName("D:\\vtkproject\\digest_article");
	reader->Update();

	vtkSmartPointer<vtkOutlineFilter> outline =
		vtkSmartPointer<vtkOutlineFilter>::New();
	outline->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	outlineMapper->SetInputConnection(outline->GetOutputPort());

	vtkSmartPointer<vtkActor> outlineActor =
		vtkSmartPointer<vtkActor>::New();
	outlineActor->SetMapper(outlineMapper);

	vtkSmartPointer<vtkRenderer> ren[4];

	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->SetMultiSamples(0);

	for (int i = 0; i < 4; i++)
	{
		ren[i] = vtkSmartPointer<vtkRenderer>::New();
		renWin->AddRenderer(ren[i]);
	}

	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	vtkSmartPointer<vtkCellPicker> picker =
		vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);

	vtkSmartPointer<vtkProperty> ipwProp =
		vtkSmartPointer<vtkProperty>::New();


	//assign default props to the ipw's texture plane actor
	vtkSmartPointer<vtkImagePlaneWidget> planeWidget[3];
	int imageDims[3];
	reader->GetOutput()->GetDimensions(imageDims);

	for (int i = 0; i < 3; i++)
	{
		planeWidget[i] = vtkSmartPointer<vtkImagePlaneWidget>::New();
		planeWidget[i]->SetInteractor(iren);
		planeWidget[i]->SetPicker(picker);
		planeWidget[i]->RestrictPlaneToVolumeOn();
		double color[3] = { 0, 0, 0 };
		color[i] = 1;
		planeWidget[i]->GetPlaneProperty()->SetColor(color);
		planeWidget[i]->SetTexturePlaneProperty(ipwProp);
		planeWidget[i]->TextureInterpolateOff();
		planeWidget[i]->SetResliceInterpolateToLinear();
		planeWidget[i]->SetInputConnection(reader->GetOutputPort());
		planeWidget[i]->SetPlaneOrientation(i);
		planeWidget[i]->SetSliceIndex(imageDims[i] / 2);
		planeWidget[i]->DisplayTextOn();
		planeWidget[i]->SetDefaultRenderer(ren[3]);
		planeWidget[i]->SetWindowLevel(1358, -27);
		planeWidget[i]->On();
		planeWidget[i]->InteractionOn();
	}

	planeWidget[1]->SetLookupTable(planeWidget[0]->GetLookupTable());
	planeWidget[2]->SetLookupTable(planeWidget[0]->GetLookupTable());


	vtkSmartPointer<vtkResliceCursorCallback3> cbk =
		vtkSmartPointer<vtkResliceCursorCallback3>::New();

	// Create the reslice cursor, widget and rep

	vtkSmartPointer< vtkResliceCursor > resliceCursor =
		vtkSmartPointer< vtkResliceCursor >::New();
	resliceCursor->SetCenter(reader->GetOutput()->GetCenter());
	resliceCursor->SetThickMode(1);
	//resliceCursor->SetThickness(10, 10, 10);
	resliceCursor->SetImage(reader->GetOutput());

	vtkSmartPointer< vtkResliceCursorWidget > resliceCursorWidget[3];
	vtkSmartPointer< vtkResliceCursorThickLineRepresentation > resliceCursorRep[3];


	double viewUp[3][3] = { { 0, 0, -1 }, { 0, 0, 1 }, { 0, 1, 0 } };

	for (int i = 0; i < 3; i++)
	{
		resliceCursorWidget[i] = vtkSmartPointer< vtkResliceCursorWidget >::New();
		resliceCursorWidget[i]->SetInteractor(iren);

		resliceCursorRep[i] =
			vtkSmartPointer< vtkResliceCursorThickLineRepresentation >::New();
		resliceCursorWidget[i]->SetRepresentation(resliceCursorRep[i]);
		resliceCursorRep[i]->GetResliceCursorActor()->
			GetCursorAlgorithm()->SetResliceCursor(resliceCursor);
		resliceCursorRep[i]->GetResliceCursorActor()->
			GetCursorAlgorithm()->SetReslicePlaneNormal(i);

		const double minVal = reader->GetOutput()->GetScalarRange()[0];
		if (vtkImageReslice *reslice =
			vtkImageReslice::SafeDownCast(resliceCursorRep[i]->GetReslice()))
		{
			reslice->SetBackgroundColor(minVal, minVal, minVal, minVal);
		}

		resliceCursorWidget[i]->SetDefaultRenderer(ren[i]);
		resliceCursorWidget[i]->SetEnabled(1);

		ren[i]->GetActiveCamera()->SetFocalPoint(0, 0, 0);
		double camPos[3] = { 0, 0, 0 };
		camPos[i] = 1;
		ren[i]->GetActiveCamera()->SetPosition(camPos);

		ren[i]->GetActiveCamera()->ParallelProjectionOn();
		ren[i]->GetActiveCamera()->SetViewUp(viewUp[i]);
		ren[i]->ResetCamera();
		ren[i]->ResetCameraClippingRange();

		// Tie the Image plane widget and the reslice cursor widget together
		cbk->IPW[i] = planeWidget[i];
		cbk->RCW[i] = resliceCursorWidget[i];
		resliceCursorWidget[i]->AddObserver(vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk);

		// Initialize the window level to a sensible value
		double range[2];
		reader->GetOutput()->GetScalarRange(range);
		resliceCursorRep[i]->SetWindowLevel(range[1] - range[0], (range[0] + range[1]) / 2.0);
		planeWidget[i]->SetWindowLevel(range[1] - range[0], (range[0] + range[1]) / 2.0);

		// Make them all share the same color map.
		resliceCursorRep[i]->SetLookupTable(resliceCursorRep[0]->GetLookupTable());
		//planeWidget[i]->GetColorMap()->SetLookupTable(resliceCursorRep[0]->GetLookupTable());
	}


	// Add the actors
	//
	ren[0]->SetBackground(0.3, 0.1, 0.1);
	ren[1]->SetBackground(0.1, 0.3, 0.1);
	ren[2]->SetBackground(0.1, 0.1, 0.3);
	ren[3]->AddActor(outlineActor);
	ren[3]->SetBackground(0.1, 0.1, 0.1);
	renWin->SetSize(600, 600);
	//renWin->SetFullScreen(1);

	ren[0]->SetViewport(0, 0, 0.5, 0.5);
	ren[1]->SetViewport(0.5, 0, 1, 0.5);
	ren[2]->SetViewport(0, 0.5, 0.5, 1);
	ren[3]->SetViewport(0.5, 0.5, 1, 1);

	// Set the actors' postions
	//
	renWin->Render();

	ren[3]->GetActiveCamera()->Elevation(110);
	ren[3]->GetActiveCamera()->SetViewUp(0, 0, -1);
	ren[3]->GetActiveCamera()->Azimuth(45);
	ren[3]->GetActiveCamera()->Dolly(1.15);
	ren[3]->ResetCameraClippingRange();

	vtkSmartPointer< vtkInteractorStyleTrackballCamera > style =
		vtkSmartPointer< vtkInteractorStyleTrackballCamera >::New();
	iren->SetInteractorStyle(style);

	iren->Initialize();

	//int retVal = vtkRegressionTestImage(renWin);

	iren->Start();


	return 0;
	}*/