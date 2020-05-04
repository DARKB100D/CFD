#include "Visualizator.h"

#include "ui_MainWindow.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>

Visualizator::Visualizator(Ui_MainWindow * ui)
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

Visualizator::~Visualizator()
{
}


void Visualizator::visualizeModel(std::string inputFilename) {
	vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName(inputFilename.c_str());
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

void Visualizator::visualizeMesh() {

}

void Visualizator::visualizeResult() {

}

void Visualizator::normalizeSize() {
	this->renderer->ResetCamera();
	this->renderer->GetRenderWindow()->Render();
}

void Visualizator::saveScreenshot(std::string selectedFilename) {
	vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
	windowToImageFilter->SetInput(this->renderer->GetRenderWindow());
	windowToImageFilter->SetScale(2); // image quality
	windowToImageFilter->SetInputBufferTypeToRGBA(); //also record the alpha (transparency) channel
	windowToImageFilter->ReadFrontBufferOff(); // read from the back buffer
	windowToImageFilter->Update();

	vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
	writer->SetFileName(selectedFilename.c_str());
	writer->SetInputConnection(windowToImageFilter->GetOutputPort());
	writer->Write();

	this->renderer->GetRenderWindow()->Render(); // normalize
}