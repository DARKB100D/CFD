#pragma once

#include "QString.h"
#include "QFile.h"
#include "QFileDialog"
#include "qdir.h"
#include "qsettings.h"
#include "ISolve.h"
#include "ProjectConfig.h"
#include "MeshConfig.h"
#include "SolverConfig.h"
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include "Converter.h"


class Project
{
	private:
		QString name;
		QString path;
		void LoadConfig();

	public:
		Project();
		Project(QString _path);
		~Project();

		vtkSmartPointer<vtkPolyData> model;
		vtkSmartPointer<vtkUnstructuredGrid> mesh;
		vtkSmartPointer<vtkPolyData> result;

		void LoadModel(QString path);
		void LoadMesh(QString path);
		void LoadResult(QString path);
				
		void SetName(QString _name);
		QString GetName();

		void SetPath(QString _path);
		QString GetPath();
		QString GetPathModel();
		QString GetPathMesh();
		QString GetPathResult();
		QString GetPathConfig();

		bool Save();

		ProjectConfig proConfig;
		MeshConfig meshConfig;
		SolverConfig solverConfig;
};

