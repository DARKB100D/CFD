#pragma once

#include <QMainWindow>
#include "../app/Visualizer.h"
#include "../app/Project.h"
#include "../app/MeshGenerator.h"
#include "../app/FEMSolver.h"
#include <QString.h>
#include <QListWidget.h>
#include <QIcon.h>

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
	void structList_AddItem(QString name, QString value, QIcon icon);
	void fillStructList();

public slots:
	// project menu
	void createProject();
	void openProject();
	void saveProject();

	// add menu
	void addModel();
	void addMesh();
	void addResultU();
	void addResultP();
	
	// export menu
	void saveAsPNG();
	void saveAsDataTable();

	void settingsGeneral();
	void appExit();
	
	// mesh menu
	void meshGenerate();
	void settingsMesh();

	// solver menu
	void solve();
	void settingsSolver();

	// view menu
	void normalizeSize();

	// help menu
	void about();

	// left panel
	void structList_Click(QListWidgetItem *item);

private:
	Ui_MainWindow * ui;
	Visualizer * visualizer;
	Project * project;
	ISolve * solver;
	MeshGenerator * meshGen;
	void connectObjects();
	void updateTitle();
};