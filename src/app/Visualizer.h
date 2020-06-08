#pragma once
#include "IVisualize.h"
#include <vtkSmartPointer.h>
#include <vtkActor.h>

class Ui_MainWindow;

class Visualizer : public IVisualize
{
public:
	Visualizer(Ui_MainWindow * ui);
	~Visualizer();
	void loadModel(vtkPolyData * data);
	void loadMesh(vtkUnstructuredGrid * data);
	void loadResultU(vtkUnstructuredGrid * data);
	void loadResultP(vtkUnstructuredGrid * data);
	void normalizeSize();
	void saveScreenshot(QString selectedFilename);

private:
	vtkSmartPointer<vtkRenderer> renderer;
};