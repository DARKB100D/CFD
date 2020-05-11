#pragma once

#include "SolverResult.h"
#include <vtkPolyData.h>
#include <qstring.h>
#include <qfileinfo.h>
#include <vtkSTLReader.h>
#include "vtkOFFReader.h"
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>

class Converter
{

public:
	void vtkPolyData_ToTable(SolverResult * result);
	static void geometryFile_ToVtkPolyData(QString inputFileName, vtkPolyData * data);
	static void vtkPolyData_ToVTKFile(QString path, vtkPolyData * data);

};

