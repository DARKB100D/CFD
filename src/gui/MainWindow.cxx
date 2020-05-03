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
#include <QMessagebox>

// Constructor
MainWindow::MainWindow()
{
	// Load UI
	this->ui = new Ui_MainWindow;
	this->ui->setupUi(this);

	// Initialize VTK widget
	initVTKWidget();

	// Set up action signals and slots
	connectObjects();
}

void MainWindow::connectObjects() {
	connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(createProject()));
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openProject()));
	connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveProject()));
	
	connect(ui->actionAddModel, SIGNAL(triggered()), this, SLOT(loadModel()));
	connect(ui->actionAddMesh, SIGNAL(triggered()), this, SLOT(loadMesh()));

	connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(appExit()));
	
	connect(ui->actionReset, SIGNAL(triggered()), this, SLOT(normalizeSize()));

	connect(ui->actionViewModel, SIGNAL(triggered()), this, SLOT(viewModel()));
	connect(ui->actionViewMesh, SIGNAL(triggered()), this, SLOT(viewMesh()));
	connect(ui->actionViewResult, SIGNAL(triggered()), this, SLOT(viewResult()));
		
	connect(ui->actionSaveAsImage, SIGNAL(triggered()), this, SLOT(saveAsPNG()));
	connect(ui->actionSaveAsTable, SIGNAL(triggered()), this, SLOT(saveAsDataTable()));

	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::initVTKWidget() {
	vtkNew<vtkNamedColors> colors;
	
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	this->ui->qvtkWidget->SetRenderWindow(renderWindow);

	// VTK Renderer
	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
	// Setup the background gradient
	renderer->GradientBackgroundOn();
	renderer->SetBackground(1, 1, 1);
	renderer->SetBackground2(0.42578125, 0.59765625, 0.9453125);

	// VTK/Qt wedded
	this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
	this->ui->qvtkWidget->GetRenderWindow()->SetWindowName("MainWindow");



	// Sphere (DEMO)
	//vtkSmartPointer<vtkCylinderSource> sphereSource = vtkSmartPointer<vtkCylinderSource>::New();
	//sphereSource->SetResolution(210);

	//vtkNew<vtkPolyDataMapper> sphereMapper;
	//sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
	//vtkNew<vtkActor> sphereActor;
	//sphereActor->SetMapper(sphereMapper);
	//sphereActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());

	//renderer->AddActor(sphereActor);
}

void MainWindow::createProject()
{
}

void MainWindow::openProject()
{
}

void MainWindow::saveProject()
{

}

void MainWindow::loadModel() {
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
	this->normalizeSize();
}

void MainWindow::loadMesh()
{
}

void MainWindow::appExit()
{
	qApp->quit();
}

void MainWindow::normalizeSize() {
	this->renderer->ResetCamera();
	this->renderer->GetRenderWindow()->Render();
}

void MainWindow::viewModel()
{
	if (ui->actionViewModel->isChecked()) {

	} else {

	}
}

void MainWindow::viewMesh()
{
}

void MainWindow::viewResult()
{
}

void MainWindow::saveAsPNG() {
	QString selected_file = QFileDialog::getSaveFileName(this, tr("Сохранить картинку"), QApplication::applicationDirPath(), "*.png");

	if (selected_file.isNull()) return;

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

void MainWindow::saveAsDataTable()
{
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("О программе"),
		tr("<h2>Вычислительная гемодинамика</h2>"
			"<p>Программный комплекс по расчету параметров течения крови в сосудах человека.<p>"
			"<p>Исходный код: https://github.com/DARKB100D/CFD<p>"));
}