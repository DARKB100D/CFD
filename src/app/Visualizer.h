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
	void loadModel(QString inputFilename);
	void loadMesh(QString inputFilename);
	void loadResult(QString inputFilename);
	void setShowModel(bool _show);
	void setShowMesh(bool _show);
	void setShowResult(bool _show);
	void normalizeSize();
	void saveScreenshot(QString selectedFilename);

private:
	vtkSmartPointer<vtkRenderer> renderer;
	bool showModel;
	bool showMesh;
	bool showResult;
	void update();
};