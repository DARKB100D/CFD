#pragma once

#include "QString.h"
#include "QFile.h"
#include "DefaultSolver.h"
#include "SolverConfig.h"

class Project
{
	private:
		QString name;
		QString path;
		SolverConfig config;
		DefaultSolver solver;

	public:
		QFile model;
		QFile mesh;
		QFile result;

		int GetState();
		void SetName();
		QString GetName();
		void SetPath();
		QString GetPath();

		void SetSolver();
		void SetConfig();

		Project(QString & _name);
		Project(QString & _name, QString & _path);
		~Project();
};

