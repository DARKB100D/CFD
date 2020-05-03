#include "StartupWindow.h"

// This is included here because it is forward declared in
// StartupWindow.h
#include "ui_StartupWindow.h"

#include "..\gui\mainWindow.h"

StartupWindow::StartupWindow() {
	// Load UI
	this->ui = new Ui_StartupWindow;
	this->ui->setupUi(this);

	// connect signals and slots
	connectObjects();

	// fill last projects list
	fillProjectHistory();
}

void StartupWindow::btnCreateProject_Click()
{
	this->hide();
	MainWindow * window = new MainWindow();
	window->show();
}

void StartupWindow::btnOpenProject_Click()
{

}

void StartupWindow::projectList_Click()
{

}

void StartupWindow::connectObjects()
{
	connect(ui->btnCreateProject, SIGNAL(clicked()), this, SLOT(btnCreateProject_Click()));
	connect(ui->btnOpenProject, SIGNAL(clicked()), this, SLOT(btnOpenProject_Click()));
	connect(ui->ProjectsListWidget, SIGNAL(doubleclicked()), this, SLOT(ProjectList_Click()));
}

void StartupWindow::fillProjectHistory()
{
	QListWidgetItem * item = new QListWidgetItem("Test project (D:\\Hemodynamics\\CFD\\testproject)");
	ui->ProjectsListWidget->addItem(item);
}

void StartupWindow::openProject()
{
}

