#include "MainWindow.h"

// This is included here because it is forward declared in
// MainWindow.h
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMessagebox>

#include "SettingsWindow.h"

MainWindow::MainWindow()
{
	// Load UI
	this->ui = new Ui_MainWindow;
	this->ui->setupUi(this);

	// Set the parameters of the stretching areas
	this->ui->splitter->setStretchFactor(0, 0);
	this->ui->splitter->setStretchFactor(1, 1);

	// Initialize VTK widget
	this->visualizer = new Visualizer(ui);

	// Set up action signals and slots
	connectObjects();

	this->project = new Project();

	// Set window title
	this->updateTitle();

	// create mesh generator
	this->meshGen = new MeshGenerator(&this->project->meshConfig);
}

MainWindow::MainWindow(QString _path) //: MainWindow()
{
	// Load UI
	this->ui = new Ui_MainWindow;
	this->ui->setupUi(this);

	// Set the parameters of the stretching areas
	this->ui->splitter->setStretchFactor(0, 0);
	this->ui->splitter->setStretchFactor(1, 1);

	// Initialize VTK widget
	this->visualizer = new Visualizer(ui);

	// Set up action signals and slots
	connectObjects(); 
	
	// Open project
	this->project = new Project(_path);

	// Visualize project data
	this->visualizer->loadModel(this->project->model);
	this->visualizer->loadMesh(this->project->mesh);
	this->visualizer->loadResult(this->project->result);

	// Set window title
	this->updateTitle();

	// create mesh generator
	this->meshGen = new MeshGenerator(&this->project->meshConfig);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete visualizer;
	delete project;
	delete solver;
	delete meshGen;
}

void MainWindow::connectObjects() {
	connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(createProject()));
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openProject()));
	connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveProject()));
	
	connect(ui->actionAddModel, SIGNAL(triggered()), this, SLOT(addModel()));
	connect(ui->actionAddMesh, SIGNAL(triggered()), this, SLOT(addMesh()));

	connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(appExit()));
	
	connect(ui->actionReset, SIGNAL(triggered()), this, SLOT(normalizeSize()));

	connect(ui->actionViewModel, SIGNAL(triggered()), this, SLOT(viewModel()));
	connect(ui->actionViewMesh, SIGNAL(triggered()), this, SLOT(viewMesh()));
	connect(ui->actionViewResult, SIGNAL(triggered()), this, SLOT(viewResult()));
		
	connect(ui->actionSaveAsImage, SIGNAL(triggered()), this, SLOT(saveAsPNG()));
	connect(ui->actionSaveAsTable, SIGNAL(triggered()), this, SLOT(saveAsDataTable()));

	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui->actionMeshGenerate, SIGNAL(triggered()), this, SLOT(meshGenerate()));

	connect(ui->actionGeneralSettings, SIGNAL(triggered()), this, SLOT(settingsGeneral()));
	connect(ui->actionMeshSettings, SIGNAL(triggered()), this, SLOT(settingsMesh()));
	connect(ui->actionSolverSettings, SIGNAL(triggered()), this, SLOT(settingsSolver()));
}

void MainWindow::updateTitle()
{
	this->setWindowTitle(tr("Вычислительная гемодинамика") + " - " + this->project->GetName() + " " + this->project->GetPath());
}

void MainWindow::createProject()
{
	MainWindow * window = new MainWindow();
	window->show();
}

void MainWindow::openProject()
{
	QString selected_path = QFileDialog::getExistingDirectory(this, tr("Укажите место расположения проекта"), QApplication::applicationDirPath(), QFileDialog::ShowDirsOnly);
	
	if (selected_path.isNull()) return;

	MainWindow * window = new MainWindow(selected_path);

	window->show();

}

void MainWindow::saveProject()
{
	while (!this->project->Save())
	{
		QString selected_path = QFileDialog::getExistingDirectory(this, tr("Укажите место расположения проекта"), QApplication::applicationDirPath(), QFileDialog::ShowDirsOnly);
		if (selected_path.isNull()) return;
		this->project->SetPath(selected_path);
	}

	// Set window title
	this->updateTitle();
}

void MainWindow::addModel() {
	QString selected_file = QFileDialog::getOpenFileName(this, tr("Выберите файл модели"), QApplication::applicationDirPath());

	if (selected_file.isNull()) return;

	Converter::geometryFile_ToVtkPolyData(selected_file, project->model);

	visualizer->loadModel(project->model);
}

void MainWindow::addMesh()
{
	QString selected_file = QFileDialog::getOpenFileName(this, tr("Выберите файл расчетной сетки"), QApplication::applicationDirPath());

	if (selected_file.isNull()) return;

	Converter::meshFile_ToVtkUnstructuredGrid(selected_file, project->mesh);

	visualizer->loadMesh(project->mesh);
}

void MainWindow::appExit()
{
	qApp->quit();
}

void MainWindow::normalizeSize() {
	this->visualizer->normalizeSize();
}

void MainWindow::viewModel()
{
	this->visualizer->setShowModel(this->ui->actionViewModel->isChecked());
}

void MainWindow::viewMesh()
{
	this->visualizer->setShowMesh(this->ui->actionViewMesh->isChecked());
}

void MainWindow::viewResult()
{
	this->visualizer->setShowResult(this->ui->actionViewResult->isChecked());
}

void MainWindow::saveAsPNG() {
	QString selected_file = QFileDialog::getSaveFileName(this, tr("Сохранить картинку"), QApplication::applicationDirPath(), "*.png");

	if (selected_file.isNull()) return;

	this->visualizer->saveScreenshot(selected_file);
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

void MainWindow::meshGenerate()
{
	// сохраним во временное хранилище модель проекта
	QString tempPathModel = QDir::tempPath() + "/model.ply";
	Converter::vtkPolyData_ToPLYFile(tempPathModel, project->model);

	// сгенерируем сетку
	QString tempPathMesh = QDir::tempPath() + "/mesh.vtk";
	meshGen->generateMesh(tempPathModel, tempPathMesh);
	
	// загрузим в проект полученный файл сетки
	project->LoadMesh(tempPathMesh);
	visualizer->loadMesh(project->mesh);
	
	// удалим временные файлы
	QFile::remove(tempPathMesh);
	QFile::remove(tempPathModel);
}

void MainWindow::settingsGeneral()
{
	SettingsWindow * window = new SettingsWindow(0, &this->project->proConfig, &this->project->meshConfig, &this->project->solverConfig);
	window->show();
}

void MainWindow::settingsMesh()
{
	SettingsWindow * window = new SettingsWindow(1, &this->project->proConfig, &this->project->meshConfig, &this->project->solverConfig);
	window->show();
}

void MainWindow::settingsSolver()
{
	SettingsWindow * window = new SettingsWindow(2, &this->project->proConfig, &this->project->meshConfig, &this->project->solverConfig);
	window->show();
}
