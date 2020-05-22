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

	gmsh::option::setNumber("Mesh.Algorithm", 8);
	gmsh::option::setNumber("Mesh.CharacteristicLengthMin", 1);
	gmsh::option::setNumber("Mesh.CharacteristicLengthMax", 2);
	gmsh::option::setNumber("Mesh.Optimize", 1);
	gmsh::option::setNumber("Mesh.QualityType", 2);

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
