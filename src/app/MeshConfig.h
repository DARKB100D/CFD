#pragma once

#include <QDataStream.h>
#include <QSettings.h>

struct MeshConfig
{
	int Algorithm = 2;
	int Algorithm3D = 1;
	int RecombinationAlgorithm = 1;
	bool RecombineAll = false;
	int SubdivisionAlgorithm = 0;
	int Smoothing = 1;
	double CharacteristicLengthFactor = 1;
	double CharacteristicLengthMin = 0;
	double CharacteristicLengthMax = 1e+22;
};

Q_DECLARE_METATYPE(MeshConfig);