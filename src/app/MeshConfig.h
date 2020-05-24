#pragma once

struct MeshConfig
{
	int Algorithm;
	int Algorithm3D;
	int RecombinationAlgorithm;
	bool RecombineAll;
	int SubdivisionAlgorithm;
	int Smoothing;
	double CharacteristicLengthFactor;
	double CharacteristicLengthMin;
	double CharacteristicLengthMax;
};