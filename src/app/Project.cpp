#include "Project.h"

Project::Project()
{
	this->name = new QString("Новый");
	this->path = new QString("");
	this->model = vtkSmartPointer<vtkPolyData>::New();
	this->mesh = vtkSmartPointer<vtkUnstructuredGrid>::New();
	this->result = vtkSmartPointer<vtkPolyData>::New();
}

Project::Project(QString _path)
{
	this->path = new QString(_path);
	this->LoadConfig();
}

Project::~Project()
{
	delete path;
	delete name;
	delete config;

}

void Project::SetConfig(QSettings * _cfg)
{

}

bool Project::Save()
{
	if (this->path->isEmpty()) return false;

	// create folder if not exist
	QDir dir(*path);
	if (!dir.exists()) dir.mkpath(".");

	// write vtkPolyData files
	Converter::vtkPolyData_ToVtkXMLFile(*path + QString("//model.vtp"), model);
	Converter::vtkUnstructuredGrid_ToVTKXMLFile(*path + QString("//mesh.vtu"), mesh);

	
	// write project config file
	
	return true;
}

void Project::LoadConfig()
{
	// load model
	this->model = vtkSmartPointer<vtkPolyData>::New();
	Converter::geometryFile_ToVtkPolyData(path + QString("//model.vtp"), model);
	
	// load mesh
	this->mesh = vtkSmartPointer<vtkUnstructuredGrid>::New();
	Converter::meshFile_ToVtkUnstructuredGrid(path + QString("//mesh.vtu"), mesh);

	// load result
	this->result = vtkSmartPointer<vtkPolyData>::New();

	// load project configuration

	/*QSettings cfg = 
	this->name*/
}


void Project::SetName(QString * _name)
{
	this->name = _name;
}

const QString * Project::GetName()
{
	return this->name;
}

void Project::SetPath(QString _path)
{
	this->path = new QString(_path);
}

const QString * Project::GetPath()
{
	return this->path;
}
