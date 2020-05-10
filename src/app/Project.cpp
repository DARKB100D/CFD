#include "Project.h"

Project::Project()
{
	this->name = new QString("Новый");
	this->path = new QString("");
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

	// write msh, stl, res files
	QFile::copy(model, *path + QString("//model.stl"));
	QFile::copy(mesh, *path + QString("//mesh.off"));

	// write cfg file
	
	return true;
}

void Project::LoadConfig()
{
	// load model
	QString modelFilePath = path + QString("//model.stl");
	QFile * modelfile = new QFile(modelFilePath);
	if (modelfile->exists()) model = modelFilePath;

	// load mesh
	QString meshFilePath = path + QString("//mesh.off");
	QFile * meshfile = new QFile(meshFilePath);
	if (meshfile->exists()) mesh = meshFilePath;

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
