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

	// Add items to left panel
	fillStructList();

	// Create project
	this->project = new Project();

	// Set window title
	this->updateTitle();

	// create mesh generator
	this->meshGen = new MeshGenerator(&this->project->meshConfig);

	// create FEM solver
	this->solver = new FEMSolver(&this->project->solverConfig);
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

	// Add items to left panel
	fillStructList();
	
	// Open project
	this->project = new Project(_path);

	// Visualize project data
	this->visualizer->loadModel(this->project->model);
	this->visualizer->loadMesh(this->project->mesh);
	this->visualizer->loadResultU(this->project->result_u);
	this->visualizer->loadResultP(this->project->result_p);

	// Set window title
	this->updateTitle();

	// create mesh generator
	this->meshGen = new MeshGenerator(&this->project->meshConfig);

	// create FEM solver
	this->solver = new FEMSolver(&this->project->solverConfig);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete visualizer;
	delete project;
	delete solver;
	delete meshGen;
}

void MainWindow::structList_AddItem(QString name, QString value, QIcon icon)
{
	QVariant fullData(value);

	QListWidgetItem * newItem = new QListWidgetItem;
	newItem->setData(Qt::UserRole, fullData);
	newItem->setText(name);
	newItem->setIcon(icon);
	ui->structListWidget->addItem(newItem);
}

void MainWindow::fillStructList()
{
	structList_AddItem("Модель", "model", QIcon(":/Application/model.png"));
	structList_AddItem("Сетка", "mesh", QIcon(":/Application/mesh.png"));
	structList_AddItem("Скорость", "velocity", QIcon(":/Application/velocity.png"));
	structList_AddItem("Давление", "pressure", QIcon(":/Application/pressure.png"));
}

void MainWindow::connectObjects() {
	connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(createProject()));
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openProject()));
	connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveProject()));
	
	connect(ui->actionAddModel, SIGNAL(triggered()), this, SLOT(addModel()));
	connect(ui->actionAddMesh, SIGNAL(triggered()), this, SLOT(addMesh()));
	connect(ui->actionAddResultU, SIGNAL(triggered()), this, SLOT(addResultU()));
	connect(ui->actionAddResultP, SIGNAL(triggered()), this, SLOT(addResultP()));

	connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(appExit()));
	
	connect(ui->actionReset, SIGNAL(triggered()), this, SLOT(normalizeSize()));
		
	connect(ui->actionSaveAsImage, SIGNAL(triggered()), this, SLOT(saveAsPNG()));
	connect(ui->actionSaveAsTable, SIGNAL(triggered()), this, SLOT(saveAsDataTable()));

	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));

	connect(ui->actionMeshGenerate, SIGNAL(triggered()), this, SLOT(meshGenerate()));
	connect(ui->actionSolve, SIGNAL(triggered()), this, SLOT(solve()));

	connect(ui->actionGeneralSettings, SIGNAL(triggered()), this, SLOT(settingsGeneral()));
	connect(ui->actionMeshSettings, SIGNAL(triggered()), this, SLOT(settingsMesh()));
	connect(ui->actionSolverSettings, SIGNAL(triggered()), this, SLOT(settingsSolver()));

	connect(ui->structListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(structList_Click(QListWidgetItem*)));
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

void MainWindow::addResultU() {
	QString selected_file = QFileDialog::getOpenFileName(this, tr("Выберите файл"), QApplication::applicationDirPath());

	if (selected_file.isNull()) return;

	Converter::meshFile_ToVtkUnstructuredGrid(selected_file, project->result_u);

	visualizer->loadResultU(project->result_u);
}

void MainWindow::addResultP() {
	QString selected_file = QFileDialog::getOpenFileName(this, tr("Выберите файл"), QApplication::applicationDirPath());

	if (selected_file.isNull()) return;

	Converter::meshFile_ToVtkUnstructuredGrid(selected_file, project->result_p);

	visualizer->loadResultP(project->result_p);
}

void MainWindow::appExit()
{
	qApp->quit();
}

void MainWindow::normalizeSize() {
	this->visualizer->normalizeSize();
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

void MainWindow::solve()
{
	// сохраним во временное хранилище модель проекта
	QString tempPathModel = QDir::tempPath() + "/model.ply";
	Converter::vtkPolyData_ToPLYFile(tempPathModel, project->model);

	// сгенерируем сетку (выгрузка сетки не удалась, поэтому будем генерировать заново)
	QString tempPathMesh = QDir::tempPath() + "/mesh.msh";
	meshGen->generateMesh(tempPathModel, tempPathMesh, 1);

	// запустим решатель
	QString tempPathResultU = QDir::tempPath() + "/result_u.vtk";
	QString tempPathResultP = QDir::tempPath() + "/result_p.vtk";
	solver->solve(tempPathMesh, tempPathResultU, tempPathResultP);

	// загрузим в проект полученный результат
	project->LoadResultU(tempPathResultU);
	visualizer->loadResultU(project->result_u);
	project->LoadResultP(tempPathResultP);
	visualizer->loadResultP(project->result_p);

	// удалим временные файлы
	//QFile::remove(tempPathModel);
	//QFile::remove(tempPathMesh);
	//QFile::remove(tempPathResultU);
	//QFile::remove(tempPathResultP);
}

void MainWindow::settingsSolver()
{
	SettingsWindow * window = new SettingsWindow(2, &this->project->proConfig, &this->project->meshConfig, &this->project->solverConfig);
	window->show();
}

void MainWindow::structList_Click(QListWidgetItem * item)
{
	QVariant data = item->data(Qt::UserRole);
	QString value = data.toString();

	if (value == "model") {
		visualizer->loadModel(project->model);
	}
	else if (value == "mesh") {
		visualizer->loadMesh(project->mesh);
	}
	else if (value == "velocity") {
		visualizer->loadResultU(project->result_u);
	}
	else if (value == "pressure") {
		visualizer->loadResultP(project->result_p);
	}
}
