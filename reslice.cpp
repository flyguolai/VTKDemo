#include "vtkDICOMImageReader.h"
#include "vtkOutlineFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImagePlaneWidget.h"
#include "vtkCellPicker.h"
#include "vtkProperty.h"
#include "vtkImageMapToColors.h"
#include "vtkImageActor.h"
#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkJPEGReader.h"
#include "vtkImageData.h"
#include "vtkResliceCursorWidget.h"
#include "vtkResliceCursorLineRepresentation.h"
#include "vtkResliceCursorThickLineRepresentation.h"
#include "vtkResliceCursorActor.h"
#include "vtkPlaneSource.h"
#include "vtkResliceCursorPolyDataAlgorithm.h"
#include "vtkImageReslice.h"

/*
class vtkWidgetWindowLevelCallback : public vtkCommand
{
public:
	static vtkWidgetWindowLevelCallback *New()
	{
		return new vtkWidgetWindowLevelCallback;
	}

	void Execute(vtkObject *caller, unsigned long vtkNotUsed(event),
		void *callData)
	{
		vtkImagePlaneWidget* self =
			reinterpret_cast< vtkImagePlaneWidget* >(caller);
		if (!self) return;

		double* wl = static_cast<double*>(callData);

		if (self == this->WidgetX)
		{
			this->WidgetY->SetWindowLevel(wl[0], wl[1]);
			this->WidgetZ->SetWindowLevel(wl[0], wl[1]);
		}
		else if (self == this->WidgetY)
		{
			this->WidgetX->SetWindowLevel(wl[0], wl[1]);
			this->WidgetZ->SetWindowLevel(wl[0], wl[1]);
		}
		else if (self == this->WidgetZ)
		{
			this->WidgetX->SetWindowLevel(wl[0], wl[1]);
			this->WidgetY->SetWindowLevel(wl[0], wl[1]);
		}
	}

	vtkWidgetWindowLevelCallback() :WidgetX(0), WidgetY(0), WidgetZ(0) {}

	vtkImagePlaneWidget* WidgetX;
	vtkImagePlaneWidget* WidgetY;
	vtkImagePlaneWidget* WidgetZ;
};

*/
class vtkResliceCursorCallback : public vtkCommand
{
public:
	static vtkResliceCursorCallback *New()
	{
		return new vtkResliceCursorCallback;
	}

	void Execute(vtkObject *caller, unsigned long ev,
		void *callData)
	{

		if (ev == vtkResliceCursorWidget::WindowLevelEvent ||
			ev == vtkCommand::WindowLevelEvent ||
			ev == vtkResliceCursorWidget::ResliceThicknessChangedEvent)
		{
			// Render everything
			for (int i = 0; i < 3; i++)
			{
				this->RCW[i]->Render();
			}
			this->IPW[0]->GetInteractor()->GetRenderWindow()->Render();
			return;
		}

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

	vtkResliceCursorCallback() {}
	vtkImagePlaneWidget* IPW[3];
	vtkResliceCursorWidget *RCW[3];
};


int main()
{

	vtkSmartPointer< vtkDICOMImageReader > reader =
		vtkSmartPointer< vtkDICOMImageReader >::New();
	reader->SetDataByteOrderToLittleEndian();
	reader->SetDirectoryName("E:\\vtkproject\\digest_article");
	reader->Update();
	int imageDims[3];
	reader->GetOutput()->GetDimensions(imageDims);

	vtkOutlineFilter *DicomOutline = vtkOutlineFilter::New();
	DicomOutline->SetInputConnection(reader->GetOutputPort());

	vtkPolyDataMapper *DicomMapper = vtkPolyDataMapper::New();
	DicomMapper->SetInputConnection(DicomOutline->GetOutputPort());

	vtkActor *DicomActor = vtkActor::New();
	DicomActor->SetMapper(DicomMapper);

	vtkSmartPointer<vtkRenderer> ren[4];
	for (int i = 0; i < 4; i++){
		ren[i] = vtkSmartPointer<vtkRenderer>::New();
	}
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();

	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren[1]);
	renWin->AddRenderer(ren[2]);
	renWin->AddRenderer(ren[3]);
	renWin->AddRenderer(ren[0]);
	iren->SetRenderWindow(renWin);
	//        ren->AddActor( DicomActor );

	vtkCellPicker * picker = vtkCellPicker::New();
	picker->SetTolerance(0.005);

	vtkSmartPointer<vtkImagePlaneWidget> planeWidget[4];

	for (int i = 0; i < 3; i++)
	{
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
		//riw[i]->GetRenderer()->SetBackground(color);

		//planeWidget[i]->SetTexturePlaneProperty(ipwProp);
		planeWidget[i]->TextureInterpolateOff();
		planeWidget[i]->SetResliceInterpolateToLinear();
		planeWidget[i]->SetInputConnection(reader->GetOutputPort());
		planeWidget[i]->SetPlaneOrientation(i);
		planeWidget[i]->SetSliceIndex(imageDims[i] / 2);
		planeWidget[i]->DisplayTextOn();
		planeWidget[i]->SetDefaultRenderer(ren[i]);
		planeWidget[i]->SetWindowLevel(1358, -27);
		planeWidget[i]->On();
		planeWidget[i]->InteractionOn();

		
	}

	vtkSmartPointer<vtkResliceCursorCallback> cbk =
		vtkSmartPointer<vtkResliceCursorCallback>::New();

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
		//resliceCursorRep[i]->GetResliceCursorActor()->
		//	GetCursorAlgorithm()->SetResliceCursor(resliceCursor);
		//resliceCursorRep[i]->GetResliceCursorActor()->
		//	GetCursorAlgorithm()->SetReslicePlaneNormal(i);

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
		/*
		resliceCursorWidget[i]->AddObserver(
			vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk);
		resliceCursorWidget[i]->AddObserver(
			vtkResliceCursorWidget::WindowLevelEvent, cbk);
		resliceCursorWidget[i]->AddObserver(
			vtkResliceCursorWidget::ResliceThicknessChangedEvent, cbk);
		resliceCursorWidget[i]->AddObserver(
			vtkResliceCursorWidget::ResetCursorEvent, cbk);
		resliceCursorWidget[i]->AddObserver(
			vtkCommand::WindowLevelEvent, cbk);
			*/
		// Make them all share the same color map.
		resliceCursorRep[i]->SetLookupTable(resliceCursorRep[0]->GetLookupTable());
		planeWidget[i]->GetColorMap()->SetLookupTable(resliceCursorRep[0]->GetLookupTable());
		//planeWidget[i]->GetColorMap()->SetInput(riw[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->GetColorMap()->GetInput());
		planeWidget[i]->SetColorMap(resliceCursorRep[i]->GetColorMap());

	}

	/*
	vtkImageMapToColors *colorMap1 = vtkImageMapToColors::New();
	colorMap1->PassAlphaToOutputOff(); //use in RGBA
	colorMap1->SetActiveComponent(0);
	colorMap1->SetOutputFormatToLuminance();
	colorMap1->SetInputData((vtkDataSet*)planeWidget[0]->GetResliceOutput());
	colorMap1->SetLookupTable((vtkScalarsToColors *)planeWidget[0]->GetLookupTable());
	vtkImageActor * imageActor1 = vtkImageActor::New();
	imageActor1->PickableOff();
	
	vtkSmartPointer<vtkImageActor> imageActor1 = vtkSmartPointer<vtkImageActor>::New();
	imageActor1->SetInputData(planeWidget[0]->GetResliceOutput());

	vtkImageMapToColors *colorMap2 = vtkImageMapToColors::New();
	colorMap2->PassAlphaToOutputOff();
	colorMap2->SetActiveComponent(0); // for muti-component
	colorMap2->SetOutputFormatToLuminance();
	colorMap2->SetInputData((vtkDataSet*)planeWidget[1]->GetResliceOutput());
	colorMap2->SetLookupTable((vtkScalarsToColors *)planeWidget[1]->GetLookupTable());
	vtkImageActor * imageActor2 = vtkImageActor::New();
	imageActor2->PickableOff();
	imageActor2->SetInputData(colorMap2->GetOutput());

	vtkImageMapToColors *colorMap3 = vtkImageMapToColors::New();
	colorMap3->PassAlphaToOutputOff();
	colorMap3->SetActiveComponent(0);
	colorMap3->SetOutputFormatToLuminance();
	colorMap3->SetInputData((vtkDataSet*)planeWidget[2]->GetResliceOutput());
	colorMap3->SetLookupTable((vtkScalarsToColors *)planeWidget[2]->GetLookupTable());
	//colorMap3->SetLookupTable(planeWidgetX->GetLookupTable());
	vtkImageActor *imageActor3 = vtkImageActor::New();
	imageActor3->PickableOff();
	imageActor3->SetInputData(colorMap3->GetOutput());
	*/
	//ren->AddActor(DicomActor); //outline
	//ren1->AddActor(imageActor1);
	//ren2->AddActor(imageActor2);
	//ren3->AddActor(imageActor3);
	

	// OK
	ren[0]->SetBackground(0.3, 0.3, 0.6);
	ren[1]->SetBackground(0.0, 0.0, 0.0);
	ren[2]->SetBackground(0.3, 0.3, 0.6);
	ren[3]->SetBackground(0.3, 0.3, 0.6);
	renWin->SetSize(600, 400);
	ren[0]->SetViewport(0, 0.5, 0.5, 1);
	ren[1]->SetViewport(0.5, 0.5, 1, 1);
	ren[2]->SetViewport(0, 0, 0.5, 0.5);
	ren[3]->SetViewport(0.5, 0, 1, 0.5);



	iren->Initialize();
	iren->Start();
	renWin->Render();

	return 0;
}