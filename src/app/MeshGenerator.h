#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <math.h>
#include <gmsh.h>
#include <QString.h>

class MeshGenerator
{
	public:
		MeshGenerator();
		~MeshGenerator();
		void generateMesh(QString in, QString out);
};

