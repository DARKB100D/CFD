#include "Visualizer.h"

#include "ui_MainWindow.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkPolyData.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkDataSetMapper.h>
#include <vtkExtractEdges.h>

#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkHedgeHog.h>
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>
#include <vtkSphereSource.h>

#include <QFileInfo>

Visualizer::Visualizer(Ui_MainWindow * ui)
{
	// VTK Renderer
	renderer = vtkSmartPointer<vtkRenderer>::New();

	// Setup the background gradient
	renderer->GradientBackgroundOn();
	renderer->SetBackground(1, 1, 1);
	renderer->SetBackground2(0.42578125, 0.59765625, 0.9453125);

	// VTK/Qt wedded
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	ui->qvtkWidget->setRenderWindow(renderWindow);
	ui->qvtkWidget->renderWindow()->AddRenderer(renderer);
}

Visualizer::~Visualizer()
{
}


void Visualizer::loadModel(vtkPolyData * data)
{
	if (!data->GetNumberOfPoints()) return;

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(data);

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	this->renderer->RemoveAllViewProps();
	this->renderer->AddActor(actor);
	this->normalizeSize();
}

void Visualizer::loadMesh(vtkUnstructuredGrid * data)
{
	if (!data->GetNumberOfPoints()) return;

	vtkSmartPointer<vtkExtractEdges> extractEdges = vtkSmartPointer<vtkExtractEdges>::New();
	extractEdges->SetInputData(data);
	extractEdges->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(extractEdges->GetOutputPort());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	this->renderer->RemoveAllViewProps();
	this->renderer->AddActor(actor);
	this->normalizeSize();
}

void Visualizer::loadResultU(vtkUnstructuredGrid * data)
{
	if (!data->GetNumberOfPoints()) return;

	data->GetPointData()->SetActiveScalars("u"); // for color (important)
	//data->GetPointData()->SetActiveVectors("u"); // no effect


	vtkSmartPointer<vtkLookupTable> colormap = vtkSmartPointer<vtkLookupTable>::New();
	colormap->SetHueRange(0.667, 0.0);
	colormap->SetNumberOfColors(1024);
	colormap->SetVectorModeToMagnitude();
	colormap->SetRange(data->GetScalarRange());
	colormap->Build();


	//// Hedge Hog 
	//vtkSmartPointer<vtkHedgeHog> hhog = vtkSmartPointer<vtkHedgeHog>::New();
	//hhog->SetInputData(data);
	//hhog->SetScaleFactor(0.01);

	//vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	//mapper->SetInputConnection(hhog->GetOutputPort());
	//mapper->SetLookupTable(colormap);
	//mapper->ScalarVisibilityOn();
	//mapper->SetScalarRange(data->GetScalarRange());
	//mapper->Update();


	// Arrows
	vtkSmartPointer<vtkArrowSource> arrow = vtkSmartPointer<vtkArrowSource>::New();
	arrow->SetTipResolution(6);
	arrow->SetTipRadius(0.1);
	arrow->SetTipLength(0.35);
	arrow->SetShaftResolution(6);
	arrow->SetShaftRadius(0.03);
	arrow->Update();

	vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();
	glyph->SetInputData(data);
	glyph->SetSourceData(arrow->GetOutput());
	glyph->OrientOn(); // Tell the glyph to orient all source objects
	glyph->SetVectorModeToUseVector(); // Tell the glyph to orient by vector
	glyph->SetScaleModeToScaleByVector(); // Tell the glyph to scale by vector. Can alternatively call ScalingOff() to make all lines the same length
	glyph->SetColorModeToColorByVector(); // And also to colour by vector
	glyph->SetScaleModeToDataScalingOff(); // Disable scaling (important)
	glyph->Update(); // Make sure all those orders took effect

	// map to graphics library
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(glyph->GetOutputPort());
	mapper->SetScalarRange(data->GetScalarRange());
	mapper->SetLookupTable(colormap);
	mapper->Update();


	//// Spheres
	//vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
	//sphere->SetRadius(0.4);
	//sphere->Update();

	//vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();
	//glyph->SetInputData(data);
	//glyph->SetSourceConnection(sphere->GetOutputPort());
	//glyph->ScalingOff();
	//glyph->Update();

	//vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	//mapper->SetInputConnection(glyph->GetOutputPort());
	//mapper->SetScalarRange(data->GetScalarRange());
	//mapper->SetLookupTable(colormap);
	//mapper->Update();
	

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	this->renderer->RemoveAllViewProps();
	this->renderer->AddActor(actor);
	this->normalizeSize();
}

void Visualizer::loadResultP(vtkUnstructuredGrid * data)
{
	if (!data->GetNumberOfPoints()) return;

	vtkSmartPointer<vtkLookupTable> colormap = vtkSmartPointer<vtkLookupTable>::New();
	colormap->SetHueRange(0.667, 0.0);
	colormap->SetNumberOfColors(1024);
	colormap->SetVectorModeToMagnitude();
	colormap->SetRange(data->GetScalarRange());
	colormap->Build();



	//// Wireframe
	//vtkSmartPointer<vtkExtractEdges> extractEdges = vtkSmartPointer<vtkExtractEdges>::New();
	//extractEdges->SetInputData(data);
	//extractEdges->Update();

	//vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	//mapper->SetInputConnection(extractEdges->GetOutputPort());
	//mapper->SetLookupTable(colormap);
	//mapper->ScalarVisibilityOn();
	//mapper->SetScalarRange(data->GetScalarRange());
	//mapper->Update();


	//// Surface
	//vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	//mapper->SetInputData(data);
	//mapper->SetLookupTable(colormap);
	//mapper->ScalarVisibilityOn();
	//mapper->SetScalarRange(data->GetScalarRange());
	//mapper->Update();
	

	// Spheres
	vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
	sphere->SetRadius(0.4);
	sphere->Update();

	vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();
	glyph->SetInputData(data);
	glyph->SetSourceConnection(sphere->GetOutputPort());
	glyph->ScalingOff();
	glyph->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(glyph->GetOutputPort());
	mapper->SetScalarRange(data->GetScalarRange());
	mapper->SetLookupTable(colormap);
	mapper->Update();
	

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	this->renderer->RemoveAllViewProps();
	this->renderer->AddActor(actor);
	this->normalizeSize();
}

void Visualizer::normalizeSize() {
	this->renderer->ResetCamera();
	this->renderer->GetRenderWindow()->Render();
}

void Visualizer::saveScreenshot(QString selectedFilename) {
	vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
	windowToImageFilter->SetInput(this->renderer->GetRenderWindow());
	windowToImageFilter->SetScale(2); // image quality
	windowToImageFilter->SetInputBufferTypeToRGBA(); //also record the alpha (transparency) channel
	windowToImageFilter->ReadFrontBufferOff(); // read from the back buffer
	windowToImageFilter->Update();

	vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
	writer->SetFileName(selectedFilename.toUtf8());
	writer->SetInputConnection(windowToImageFilter->GetOutputPort());
	writer->Write();

	this->renderer->GetRenderWindow()->Render(); // normalize
}