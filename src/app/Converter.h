#pragma once

#include "SolverResult.h"
#include <qstring.h>
#include <qfileinfo.h>

#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkPLYReader.h>
#include "vtkOFFReader.h"
#include <vtkPolyDataReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPLYWriter.h>

#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkUnstructuredGridWriter.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkUnstructuredGridGeometryFilter.h>

#include <vtkTecplotReader.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <gmsh.h>

class Converter
{

public:
	static void geometryFile_ToVtkPolyData(QString inputFileName, vtkPolyData * data);
	static void vtkPolyData_ToVtkFile(QString path, vtkPolyData * data);
	static void vtkPolyData_ToVtkXMLFile(QString path, vtkPolyData * data);
	static void vtkPolyData_ToPLYFile(QString path, vtkPolyData * data);
	static void meshFile_ToVtkUnstructuredGrid(QString inputFileName, vtkUnstructuredGrid * data);
	static void vtkUnstructuredGrid_ToVTKFile(QString path, vtkUnstructuredGrid * data);
	static void vtkUnstructuredGrid_ToVTKXMLFile(QString path, vtkUnstructuredGrid * data);
	static void vtkUnstructuredGrid_ToMSHFile(QString path, vtkUnstructuredGrid * data);
	static void vtkUnstructuredGrid_ToPLYFile(QString path, vtkUnstructuredGrid * data);
	static void vtkUnstructuredGrid_ToVTKOldFile(QString path, vtkUnstructuredGrid * data);
};

