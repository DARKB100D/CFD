#pragma once
#include "IVisualize.h"
#include <vtkSmartPointer.h>
#include <vtkActor.h>

class Ui_MainWindow;

class Visualizator : public IVisualize
{
public:
	Visualizator(Ui_MainWindow * ui);
	~Visualizator();

	void visualizeModel(std::string inputFilename);

	void visualizeMesh();

	void visualizeResult();

	void normalizeSize();

	void saveScreenshot(std::string selectedFilename);

private:
	vtkSmartPointer<vtkRenderer> renderer;

};

