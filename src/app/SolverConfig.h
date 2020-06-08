#pragma once

#include <QDataStream.h>
#include <QSettings.h>
#include <QString.h>

struct SolverConfig
{
	double Viscosity = 3.8;
	QString R_X = "0";
	QString R_Y = "x.^2+z.^2";
	QString R_Z = "0";
};

Q_DECLARE_METATYPE(SolverConfig);