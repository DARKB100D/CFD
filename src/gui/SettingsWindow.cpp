#include "SettingsWindow.h"

// This is included here because it is forward declared in
// SettingsWindow.h
#include "ui_SettingsWindow.h"

#include "MeshAlgorithmModel.h"
#include "MeshAlgorithm3DModel.h"
#include "MeshRecombinationAlgorithm.h"
#include "MeshSubdivisionAlgorithm.h"

SettingsWindow::SettingsWindow(int CurrentIndex, ProjectConfig * proConfig, MeshConfig * meshConfig, SolverConfig * solverConfig) {
	this->proConfig = proConfig;
	this->meshConfig = meshConfig;
	this->solverConfig = solverConfig;

	// Load UI
	this->ui = new Ui_SettingsWindow;
	this->ui->setupUi(this);
	this->ui->Algorithm->setModel(new MeshAlgorithmModel(this));
	this->ui->Algorithm3D->setModel(new MeshAlgorithm3DModel(this));
	this->ui->RecombinationAlgorithm->setModel(new MeshRecombinationAlgorithm(this));
	this->ui->SubdivisionAlgorithm->setModel(new MeshSubdivisionAlgorithm(this));

	// set default params to form
	loadConfigs();

	// connect signals and slots
	connectObjects();

	// set current tab
	this->ui->tabWidget->setCurrentIndex(CurrentIndex);
}

SettingsWindow::~SettingsWindow()
{
	delete ui;
}

void SettingsWindow::btnOk_Click()
{
	writeConfigs();
	SettingsWindow::close();
}

void SettingsWindow::btnCancel_Click()
{
	SettingsWindow::close();
}

void SettingsWindow::connectObjects()
{
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(btnOk_Click()));
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(btnCancel_Click()));
}

void SettingsWindow::loadConfigs()
{

}

void SettingsWindow::writeConfigs()
{

}
