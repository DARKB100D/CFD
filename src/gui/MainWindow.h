#pragma once

#include <QMainWindow>
#include "../app/Visualizator.h"

// Forward Qt class declarations
class Ui_MainWindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	// Constructor/Destructor
	MainWindow();
	MainWindow(QString projectPath);
	~MainWindow() = default;

public slots:
	// file menu
	void createProject();
	void openProject();
	void saveProject();
	void loadModel();
	void loadMesh();
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

private:
	Ui_MainWindow * ui;
	Visualizator * visualizator;
	void connectObjects();
};