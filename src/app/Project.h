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
		vtkSmartPointer<vtkUnstructuredGrid> result_u;
		vtkSmartPointer<vtkUnstructuredGrid> result_p;

		void LoadModel(QString path);
		void LoadMesh(QString path);
		void LoadResultU(QString path);
		void LoadResultP(QString path);

		void SetName(QString _name);
		QString GetName();

		void SetPath(QString _path);
		QString GetPath();
		QString GetPathModel();
		QString GetPathMesh();
		QString GetPathResultU();
		QString GetPathResultP();
		QString GetPathConfig();

		bool Save();

		ProjectConfig proConfig;
		MeshConfig meshConfig;
		SolverConfig solverConfig;
};

