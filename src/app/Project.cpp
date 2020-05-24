#include "Project.h"

Project::Project()
{
	this->name = QObject::tr("Новый");
	this->path = "";
	this->model = vtkSmartPointer<vtkPolyData>::New();
	this->mesh = vtkSmartPointer<vtkUnstructuredGrid>::New();
	this->result = vtkSmartPointer<vtkPolyData>::New();
	this->proConfig = new ProjectConfig;
	this->meshConfig = new MeshConfig;
	this->solverConfig = new SolverConfig;
}

Project::Project(QString _path)
{
	this->path = _path;
	this->LoadConfig();
}

Project::~Project()
{
	delete proConfig;
	delete meshConfig;
	delete solverConfig;
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
	

	return true;
}

void Project::LoadConfig()
{
	// load model
	this->model = vtkSmartPointer<vtkPolyData>::New();
	Converter::geometryFile_ToVtkPolyData(GetPathModel(), model);
	
	// load mesh
	this->mesh = vtkSmartPointer<vtkUnstructuredGrid>::New();
	Converter::meshFile_ToVtkUnstructuredGrid(GetPathMesh(), mesh);

	// load result
	this->result = vtkSmartPointer<vtkPolyData>::New();

	// load configuration
	this->proConfig = new ProjectConfig;
	this->meshConfig = new MeshConfig;
	this->solverConfig = new SolverConfig;
	/*QSettings cfg = 
	this->name*/
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
