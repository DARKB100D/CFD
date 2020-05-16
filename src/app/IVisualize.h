#pragma once

#include <QString>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>

__interface IVisualize
{
	public:
		void loadModel(vtkPolyData * data);
		void loadMesh(vtkUnstructuredGrid * data);
		void loadResult(vtkPolyData * data);
		void setShowModel(bool _show);
		void setShowMesh(bool _show);
		void setShowResult(bool _show);
		void normalizeSize();
		void saveScreenshot(QString selectedFilename);
};

