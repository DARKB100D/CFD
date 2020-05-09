#pragma once

#include <QString>

__interface IVisualize
{
	public:
		void loadModel(QString inputFilename);
		void loadMesh(QString inputFilename);
		void loadResult(QString inputFilename);
		void setShowModel(bool _show);
		void setShowMesh(bool _show);
		void setShowResult(bool _show);
		void normalizeSize();
		void saveScreenshot(QString selectedFilename);
};

