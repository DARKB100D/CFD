#include "Visualizer.h"

#include "ui_MainWindow.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>

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
	ui->qvtkWidget->SetRenderWindow(renderWindow);
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
}

Visualizer::~Visualizer()
{
}


void Visualizer::loadModel(QString inputFilename) {
	vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName(inputFilename.toLocal8Bit());
	reader->Update();

	// Visualize
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	this->renderer->RemoveAllViewProps();
	this->renderer->AddActor(actor);
	this->normalizeSize();
}

void Visualizer::loadMesh(QString inputFilename) {

}

void Visualizer::loadResult(QString inputFilename) {

}

void Visualizer::setShowModel(bool _show)
{
	showModel = _show;
	this->update();
}

void Visualizer::setShowMesh(bool _show)
{
	showMesh = _show;
	this->update();
}

void Visualizer::setShowResult(bool _show)
{
	showResult = _show;
	this->update();
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
	writer->SetFileName(selectedFilename.toLocal8Bit());
	writer->SetInputConnection(windowToImageFilter->GetOutputPort());
	writer->Write();

	this->renderer->GetRenderWindow()->Render(); // normalize
}

void Visualizer::update()
{
	if (showModel) {}
	if (showMesh) {}
	if (showResult) {}
}