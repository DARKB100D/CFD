#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <gmsh.h>
#include <QString.h>
#include "MeshConfig.h"

class MeshGenerator {

public:
	MeshGenerator(MeshConfig * config);
	~MeshGenerator();
	void generateMesh(QString in, QString out);

private:
	MeshConfig * config;

};
