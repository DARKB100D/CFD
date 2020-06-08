#pragma once

#include <QMainWindow>
#include "../app/Visualizer.h"
#include "../app/Project.h"
#include "../app/MeshGenerator.h"
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
	// file menu
	void createProject();
	void openProject();
	void saveProject();
	void addModel();
	void addMesh();
	void addResultU();
	void addResultP();
	void appExit();

	// view menu
	void normalizeSize();

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