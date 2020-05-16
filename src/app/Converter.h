#pragma once

#include "SolverResult.h"
#include <qstring.h>
#include <qfileinfo.h>

#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include "vtkOFFReader.h"
#include <vtkPolyDataReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkXMLPolyDataWriter.h>

#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkUnstructuredGridWriter.h>
#include <vtkXMLUnstructuredGridWriter.h>

#include <vtkTecplotReader.h>


class Converter
{

public:
	void vtkPolyData_ToTable(SolverResult * result);
	static void geometryFile_ToVtkPolyData(QString inputFileName, vtkPolyData * data);
	static void vtkPolyData_ToVtkFile(QString path, vtkPolyData * data);
	static void vtkPolyData_ToVtkXMLFile(QString path, vtkPolyData * data);
	static void meshFile_ToVtkUnstructuredGrid(QString inputFileName, vtkUnstructuredGrid * data);
	static void vtkUnstructuredGrid_ToVTKFile(QString path, vtkUnstructuredGrid * data);
	static void vtkUnstructuredGrid_ToVTKXMLFile(QString path, vtkUnstructuredGrid * data);
};

