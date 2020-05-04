#include "MainWindow.h"

// This is included here because it is forward declared in
// MainWindow.h
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMessagebox>

MainWindow::MainWindow()
{
	// Load UI
	this->ui = new Ui_MainWindow;
	this->ui->setupUi(this);

	// Initialize VTK widget
	this->visualizator = new Visualizator(ui);

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
	auto selected_file = QFileDialog::getOpenFileName(this, tr("Выберите файл модели"), QApplication::applicationDirPath());

	if (selected_file.isNull()) return;

	std::string inputFilename = selected_file.toLocal8Bit();

	visualizator->visualizeModel(inputFilename);
}

void MainWindow::loadMesh()
{

}

void MainWindow::appExit()
{
	qApp->quit();
}

void MainWindow::normalizeSize() {
	this->visualizator->normalizeSize();
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

	this->visualizator->saveScreenshot(selected_file.toStdString());
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