#pragma once

#include "QString.h"
#include "QFile.h"
#include "QFileDialog"
#include "qdir.h"
#include "qsettings.h"
#include "DefaultSolver.h"
#include "SolverConfig.h"

class Project
{
	private:
		QString * name;
		QString * path;
		SolverConfig * config;
		void LoadConfig();

	public:
		Project();
		Project(QString _path);
		~Project();

		QString model;
		QString mesh;
		QString result;

		void SetName(QString * _name);
		const QString * GetName();

		void SetPath(QString _path);
		const QString * GetPath();

		void SetConfig(QSettings * _cfg);
		bool Save();

};

