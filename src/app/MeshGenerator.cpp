#include "MeshGenerator.h"

MeshGenerator::MeshGenerator()
{
	
}

MeshGenerator::~MeshGenerator()
{
	
}

void MeshGenerator::generateMesh(QString in, QString out)
{
	gmsh::initialize();

	gmsh::option::setNumber("General.Terminal", 1);

	gmsh::option::setNumber("Mesh.Algorithm", 1);
	gmsh::option::setNumber("Mesh.Algorithm3D", 1);
	gmsh::option::setNumber("Mesh.RecombinationAlgorithm", 1);
	gmsh::option::setNumber("Mesh.RecombineAll", 0);
	gmsh::option::setNumber("Mesh.SubdivisionAlgorithm", 0);
	gmsh::option::setNumber("Mesh.Smoothing", 10);
	gmsh::option::setNumber("Mesh.CharacteristicLengthFactor", 1);
	gmsh::option::setNumber("Mesh.CharacteristicLengthMin", 0);
	gmsh::option::setNumber("Mesh.CharacteristicLengthMax", 1e+22);

	gmsh::merge(in.toStdString());

	// Create a volume from all the surfaces
	std::vector<std::pair<int, int> > s;
	gmsh::model::getEntities(s, 2);
	std::vector<int> sl;
	for (std::size_t i = 0; i < s.size(); i++) sl.push_back(s[i].second);
	int l = gmsh::model::geo::addSurfaceLoop(sl);
	gmsh::model::geo::addVolume({ l });

	gmsh::model::geo::synchronize();

	gmsh::model::mesh::generate(3);

	gmsh::write(out.toStdString());

	gmsh::finalize();
}
