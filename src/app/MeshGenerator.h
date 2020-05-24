#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <math.h>
#include <gmsh.h>
#include <QString.h>

//namespace MeshGenerator {
//	enum Algorithm
//	{
//		MeshAdapt = 1,
//		Automatic = 2,
//		Delaunay = 5,
//		FrontalDelaunay = 6,
//		BAMG = 7,
//		FrontalDelaunayForQuads = 8,
//		PackingOfParallelograms = 9
//	};
//
//	enum Algorithm3D {
//		Delaunay = 1,
//		Frontal = 4,
//		MMG3D = 7,
//		RTree = 9,
//		HXT = 10
//	};
//
//	enum RecombinationAlgorithm {
//		Simple = 0,
//		Blossom = 1,
//		SimpleFullQuad = 2,
//		BlossomFullQuad = 3
//	};

	class MeshGenerator {

	public:
		MeshGenerator();
		~MeshGenerator();
		void generateMesh(QString in, QString out);
	};
//}
