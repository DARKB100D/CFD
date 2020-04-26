#pragma once
class IVisualize
{
	public:
		virtual ~IVisualize() {};
		virtual void visualizeModel() = 0;
		virtual void visualizeMesh() = 0;
		virtual void visualizeResult() = 0;
};

