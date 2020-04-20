#include "MainWindow.h"

// This is included here because it is forward declared in
// MainWindow.h
#include "ui_MainWindow.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>

#include <vtkPolyData.h>
#include <vtkSTLReader.h>

#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>

#include <vtkCylinderSource.h>

#include <QFileDialog>

// Constructor
MainWindow::MainWindow()
{
  this->ui = new Ui_MainWindow;
  this->ui->setupUi(this);
  
  connectObjects();

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;

  this->ui->qvtkWidget->SetRenderWindow(renderWindow);

  // Sphere
  //vtkNew<vtkSphereSource> sphereSource;
  //sphereSource->Update();
  vtkSmartPointer<vtkCylinderSource> sphereSource = vtkSmartPointer<vtkCylinderSource>::New();
  sphereSource->SetResolution(210);

  vtkNew<vtkPolyDataMapper> sphereMapper;
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkNew<vtkActor> sphereActor;
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());

  // VTK Renderer
  //vtkNew<vtkRenderer> renderer;
  renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(sphereActor);
  renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
  // Setup the background gradient
  renderer->GradientBackgroundOn();
  renderer->SetBackground(1, 1, 1);
  renderer->SetBackground2(0.42578125, 0.59765625, 0.9453125);

  
  // VTK/Qt wedded

  this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
  this->ui->qvtkWidget->GetRenderWindow()->SetWindowName(
      "MainWindow");

  // Set up action signals and slots
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
}

void MainWindow::slotExit()
{
  qApp->exit();
}

void MainWindow::connectObjects() {
	connect(ui->btnOpenFile, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(ui->btnReset, SIGNAL(clicked()), this, SLOT(resetView()));
	connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(savePNG()));
}

void MainWindow::openFile() {
	// open a file dialog
	auto selected_file = QFileDialog::getOpenFileName(this, tr("Open a file"), QApplication::applicationDirPath());

	if (selected_file.isNull()) return;
	
	vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
	std::string inputFilename = selected_file.toLocal8Bit();
	reader->SetFileName(inputFilename.c_str());
	reader->Update();

	// Visualize
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	this->renderer->RemoveAllViewProps();
	this->renderer->AddActor(actor);
	this->resetView();
}

void MainWindow::resetView() {
	//vtkNew<vtkNamedColors> colors;
	//this->sphereActor->GetProperty()->SetColor(colors->GetColor4d("Green").GetData());
	this->renderer->ResetCamera();
	this->renderer->GetRenderWindow()->Render();

}

void MainWindow::savePNG() {
	auto selected_file = QFileDialog::getSaveFileName(this, tr("Save screenshot"), QApplication::applicationDirPath(), "*.png");

	// Screenshot  
	vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
		vtkSmartPointer<vtkWindowToImageFilter>::New();
	windowToImageFilter->SetInput(this->renderer->GetRenderWindow());
	windowToImageFilter->SetScale(2); // image quality
	windowToImageFilter->SetInputBufferTypeToRGBA(); //also record the alpha (transparency) channel
	windowToImageFilter->ReadFrontBufferOff(); // read from the back buffer
	windowToImageFilter->Update();

	vtkSmartPointer<vtkPNGWriter> writer =
		vtkSmartPointer<vtkPNGWriter>::New();
	std::cout << selected_file.toStdString() << std::endl;
	writer->SetFileName(selected_file.toStdString().c_str());
	writer->SetInputConnection(windowToImageFilter->GetOutputPort());
	writer->Write();

	this->renderer->GetRenderWindow()->Render();
}