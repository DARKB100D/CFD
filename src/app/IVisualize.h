#pragma once

#include <string>

__interface IVisualize
{
	public:
		void visualizeModel(std::string inputFilename);
		void visualizeMesh();
		void visualizeResult();
		void normalizeSize();
		void saveScreenshot(std::string selectedFilename);
};

