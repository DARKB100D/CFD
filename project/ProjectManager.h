#pragma once

#include "Project.h"
#include "QString.h"

class ProjectManager
{
	public:
		Project CreateProject();
		Project OpenProject(QString & path);
		Project SaveProject(QString & path);

};

