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
	int index;
		
	index = ui->Algorithm->findData(meshConfig->Algorithm);
	if (index != -1) ui->Algorithm->setCurrentIndex(index);

	index = ui->Algorithm3D->findData(meshConfig->Algorithm3D);
	if (index != -1) ui->Algorithm3D->setCurrentIndex(index);

	index = ui->RecombinationAlgorithm->findData(meshConfig->RecombinationAlgorithm);
	if (index != -1) ui->RecombinationAlgorithm->setCurrentIndex(index);
	
	ui->RecombineAll->setChecked(meshConfig->RecombineAll);
	
	index = ui->SubdivisionAlgorithm->findData(meshConfig->SubdivisionAlgorithm);
	if (index != -1) ui->SubdivisionAlgorithm->setCurrentIndex(index);
	
	ui->Smooth->setValue(meshConfig->Smoothing);
	
	ui->CharacteristicLengthFactor->setValue(meshConfig->CharacteristicLengthFactor);
	
	ui->CharacteristicLengthMin->setValue(meshConfig->CharacteristicLengthMin);
	
	ui->CharacteristicLengthMax->setValue(meshConfig->CharacteristicLengthMax);
}

void SettingsWindow::writeConfigs()
{
	meshConfig->Algorithm = ui->Algorithm->currentData().toInt();
	
	meshConfig->Algorithm3D = ui->Algorithm3D->currentData().toInt();

	meshConfig->RecombinationAlgorithm = ui->RecombinationAlgorithm->currentData().toInt();

	meshConfig->RecombineAll = ui->RecombineAll->isChecked();

	meshConfig->SubdivisionAlgorithm = ui->SubdivisionAlgorithm->currentData().toInt();

	meshConfig->Smoothing = ui->Smooth->value();

	meshConfig->CharacteristicLengthFactor = ui->CharacteristicLengthFactor->value();

	meshConfig->CharacteristicLengthMin = ui->CharacteristicLengthMin->value();

	meshConfig->CharacteristicLengthMax = ui->CharacteristicLengthMax->value();

}
