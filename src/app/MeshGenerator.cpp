#include "MeshGenerator.h"

MeshGenerator::MeshGenerator(MeshConfig * config)
{
	this->config = config;
}

MeshGenerator::~MeshGenerator()
{
	
}

void MeshGenerator::generateMesh(QString in, QString out)
{
	gmsh::initialize();

	gmsh::option::setNumber("General.Terminal", 1);

	gmsh::option::setNumber("Mesh.Algorithm", config->Algorithm);
	gmsh::option::setNumber("Mesh.Algorithm3D", config->Algorithm3D);
	gmsh::option::setNumber("Mesh.RecombinationAlgorithm", config->RecombinationAlgorithm);
	gmsh::option::setNumber("Mesh.RecombineAll", config->RecombineAll);
	gmsh::option::setNumber("Mesh.SubdivisionAlgorithm", config->SubdivisionAlgorithm);
	gmsh::option::setNumber("Mesh.Smoothing", config->Smoothing);
	gmsh::option::setNumber("Mesh.CharacteristicLengthFactor", config->CharacteristicLengthFactor);
	gmsh::option::setNumber("Mesh.CharacteristicLengthMin", config->CharacteristicLengthMin);
	gmsh::option::setNumber("Mesh.CharacteristicLengthMax", config->CharacteristicLengthMax);

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
