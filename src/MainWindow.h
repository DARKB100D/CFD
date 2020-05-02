#ifndef MainWindow_H
#define MainWindow_H

#include <vtkSmartPointer.h>
#include <vtkActor.h>

#include <QMainWindow>

// Forward Qt class declarations
class Ui_MainWindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	// Constructor/Destructor
	MainWindow();
	~MainWindow() = default;

public slots:
	void slotExit();
	void openFile();
	void resetView();
	void savePNG();
	void about();

public:
	void connectObjects();

private:
	// Designer form
	Ui_MainWindow* ui;
	vtkSmartPointer<vtkRenderer> renderer;
};

#endif