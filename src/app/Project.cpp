#include "Project.h"

Project::Project()
{
	this->name = QObject::tr("Новый");
	this->path = "";
	this->model = vtkSmartPointer<vtkPolyData>::New();
	this->mesh = vtkSmartPointer<vtkUnstructuredGrid>::New();
	this->result_u = vtkSmartPointer<vtkUnstructuredGrid>::New();
	this->result_p = vtkSmartPointer<vtkUnstructuredGrid>::New();
}

Project::Project(QString _path)
{
	this->path = _path;
	this->LoadConfig();
}

Project::~Project()
{

}

bool Project::Save()
{
	if (this->path.isEmpty()) return false;

	// create folder if not exist
	QDir dir(path);
	if (!dir.exists()) dir.mkpath(".");

	// write vtkPolyData files
	Converter::vtkPolyData_ToPLYFile(GetPathModel(), model);
	Converter::vtkUnstructuredGrid_ToVTKFile(GetPathMesh(), mesh);
	
	// write project config file
	qRegisterMetaTypeStreamOperators<ProjectConfig>("ProjectConfig");
	qRegisterMetaTypeStreamOperators<MeshConfig>("MeshConfig");
	qRegisterMetaTypeStreamOperators<SolverConfig>("SolverConfig");
	QSettings s(GetPathConfig(), QSettings::IniFormat);
	s.setValue("project", QVariant::fromValue(meshConfig));
	s.setValue("mesh", QVariant::fromValue(meshConfig));
	s.setValue("solver", QVariant::fromValue(meshConfig));

	return true;
}

void Project::LoadConfig()
{
	// load data
	LoadModel(GetPathModel());
	LoadMesh(GetPathMesh());
	LoadResultU(GetPathResultU());
	LoadResultP(GetPathResultP());

	// load configuration
	qRegisterMetaTypeStreamOperators<ProjectConfig>("ProjectConfig");
	qRegisterMetaTypeStreamOperators<MeshConfig>("MeshConfig");
	qRegisterMetaTypeStreamOperators<SolverConfig>("SolverConfig");
	QSettings s(GetPathConfig(), QSettings::IniFormat);
	QVariant QVariantProject = s.value("project");
	this->proConfig = QVariantProject.value<ProjectConfig>();
	QVariant QVariantMesh = s.value("mesh");
	this->meshConfig = QVariantMesh.value<MeshConfig>();
	QVariant QVariantSolver = s.value("solver");
	this->solverConfig = QVariantSolver.value<SolverConfig>();
}


void Project::LoadModel(QString path)
{
	this->model = vtkSmartPointer<vtkPolyData>::New();
	Converter::geometryFile_ToVtkPolyData(path, model);
}

void Project::LoadMesh(QString path)
{
	this->mesh = vtkSmartPointer<vtkUnstructuredGrid>::New();
	Converter::meshFile_ToVtkUnstructuredGrid(path, mesh);
}

void Project::LoadResultU(QString path)
{
	this->result_u = vtkSmartPointer<vtkUnstructuredGrid>::New();
	Converter::meshFile_ToVtkUnstructuredGrid(path, result_u);
}

void Project::LoadResultP(QString path)
{
	this->result_p = vtkSmartPointer<vtkUnstructuredGrid>::New();
	Converter::meshFile_ToVtkUnstructuredGrid(path, result_p);
}

void Project::SetName(QString _name)
{
	this->name = _name;
}

QString Project::GetName()
{
	return this->name;
}

void Project::SetPath(QString _path)
{
	this->path = _path;
}

QString Project::GetPath()
{
	return this->path;
}

QString Project::GetPathModel()
{
	return this->path + QString("/model.ply");
}

QString Project::GetPathMesh()
{
	return this->path + QString("/mesh.vtk");
}

QString Project::GetPathResultU()
{
	return this->path + QString("/result_u.vtk");
}

QString Project::GetPathResultP()
{
	return this->path + QString("/result_p.vtk");
}

QString Project::GetPathConfig()
{
	return this->path + QString("/config.ini");
}



QDataStream& operator<<(QDataStream& out, const ProjectConfig & v) {
	return out;
}

QDataStream& operator>>(QDataStream& in, ProjectConfig & v) {
	return in;
}

QDataStream& operator<<(QDataStream& out, const MeshConfig & v) {
	out << v.Algorithm << v.Algorithm3D << v.RecombinationAlgorithm << v.RecombineAll << v.SubdivisionAlgorithm << v.Smoothing << v.CharacteristicLengthFactor << v.CharacteristicLengthMin << v.CharacteristicLengthMax;
	return out;
}

QDataStream& operator>>(QDataStream& in, MeshConfig & v) {
	in >> v.Algorithm;
	in >> v.Algorithm3D;
	in >> v.RecombinationAlgorithm;
	in >> v.RecombineAll;
	in >> v.SubdivisionAlgorithm;
	in >> v.Smoothing;
	in >> v.CharacteristicLengthFactor;
	in >> v.CharacteristicLengthMin;
	in >> v.CharacteristicLengthMax;
	return in;
}

QDataStream& operator<<(QDataStream& out, const SolverConfig & v) {
	return out;
}

QDataStream& operator>>(QDataStream& in, SolverConfig & v) {
	return in;
}