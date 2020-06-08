#pragma once

#include <QString>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>

__interface IVisualize
{
	public:
		void loadModel(vtkPolyData * data);
		void loadMesh(vtkUnstructuredGrid * data);
		void loadResultU(vtkUnstructuredGrid * data);
		void loadResultP(vtkUnstructuredGrid * data);
		void normalizeSize();
		void saveScreenshot(QString selectedFilename);
};

