#pragma once

#include <QMainWindow>
#include <QListWidget.h>

// Forward Qt class declarations
class Ui_StartupWindow;

class StartupWindow : public QMainWindow
{
public:
	StartupWindow();
	~StartupWindow();

private:
	Q_OBJECT
	Ui_StartupWindow * ui;
	void connectObjects();
	void fillProjectHistory();

public slots:
	void btnCreateProject_Click();
	void btnOpenProject_Click();
	void projectList_Click(QListWidgetItem *item);
};

