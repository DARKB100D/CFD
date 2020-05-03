#pragma once

#include <QMainWindow>

// Forward Qt class declarations
class Ui_StartupWindow;

class StartupWindow : public QMainWindow
{
public:
	StartupWindow();
	~StartupWindow() = default;

private:
	Q_OBJECT
	Ui_StartupWindow * ui;
	void connectObjects();
	void fillProjectHistory();
	void openProject();

public slots:
	void btnCreateProject_Click();
	void btnOpenProject_Click();
	void projectList_Click();
};

