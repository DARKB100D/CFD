#pragma once

#include <QMainWindow>
#include "../app/Visualizer.h"
#include "../app/Project.h"
#include "../app/MeshGenerator.h"
#include <qstring.h>

// Forward Qt class declarations
class Ui_MainWindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	// Constructor/Destructor
	MainWindow();
	MainWindow(QString projectPath);
	~MainWindow();

public slots:
	// file menu
	void createProject();
	void openProject();
	void saveProject();
	void addModel();
	void addMesh();
	void appExit();

	// edit menu
	void normalizeSize();

	// view menu
	void viewModel();
	void viewMesh();
	void viewResult();

	// tools menu
	void saveAsPNG();
	void saveAsDataTable();

	// help menu
	void about();

	// mesh menu
	void meshGenerate();

	// settings actions
	void settingsGeneral();
	void settingsMesh();
	void settingsSolver();

private:
	Ui_MainWindow * ui;
	Visualizer * visualizer;
	Project * project;
	ISolve * solver;
	MeshGenerator * meshGen;
	void connectObjects();
	void updateTitle();
};