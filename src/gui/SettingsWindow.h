#pragma once

#include <QMainWindow>
#include "../app/ProjectConfig.h"
#include "../app/MeshConfig.h"
#include "../app/SolverConfig.h"

// Forward Qt class declarations
class Ui_SettingsWindow;

class SettingsWindow : public QMainWindow
{
public:
	SettingsWindow(int CurrentIndex, ProjectConfig * proConfig, MeshConfig * meshConfig, SolverConfig * solverConfig);
	~SettingsWindow();

private:
	Q_OBJECT
	Ui_SettingsWindow * ui;
	void connectObjects();
	ProjectConfig * proConfig;
	MeshConfig * meshConfig;
	SolverConfig * solverConfig;
	void loadConfigs();
	void writeConfigs();

public slots:
	void btnCancel_Click();
	void btnOk_Click();

};

