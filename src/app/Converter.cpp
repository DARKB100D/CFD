#include "Converter.h"

void Converter::geometryFile_ToVtkPolyData(QString inputFileName, vtkPolyData * data)
{
	QFile modelfile(inputFileName);
	if (!modelfile.exists()) return;
	
	QFileInfo fileinfo(inputFileName); 
	QString suffix = fileinfo.suffix(); // Returns the suffix (extension) of the file. The suffix consists of all characters in the file after(but not including) the last '.'.

	if (suffix == "stl") {
		vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
		reader->MergingOn(); // from example
		reader->SetFileName(inputFileName.toLocal8Bit());
		reader->Update();
		
		data->DeepCopy(reader->GetOutput());
	}
	else if (suffix == "off") {
		vtkSmartPointer<vtkOFFReader> reader = vtkSmartPointer<vtkOFFReader>::New();
		reader->SetFileName(inputFileName.toLocal8Bit());
		reader->Update();
		
		data->DeepCopy(reader->GetOutput());
	}
	else if (suffix == "vtk") {
		vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
		reader->SetFileName(inputFileName.toLocal8Bit());
		reader->Update();

		data->DeepCopy(reader->GetOutput());
	}
	//else if (suffix == "tec") {
	//	vtkSmartPointer<vtkTecplotReader> reader = vtkSmartPointer<vtkTecplotReader>::New();
	//	reader->SetFileName(inputFileName.toLocal8Bit());
	//	reader->Update();

	//	data->DeepCopy(reader->GetOutput()); // vtkMultiBlockDataSet
	//}
	else if (suffix == "vtp") {
		vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
		reader->SetFileName(inputFileName.toLocal8Bit());
		reader->Update();

		data->DeepCopy(reader->GetOutput());
	}
	//else if (suffix == "vtu") {
	//	vtkSmartPointer<vtkXMLUnstructuredGridReader> reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
	//	reader->SetFileName(inputFileName.toLocal8Bit());
	//	reader->Update();

	//	data->DeepCopy(reader->GetOutput()); // vtkUnstructuredGrid
	//}
}

void Converter::vtkPolyData_ToVTKFile(QString path, vtkPolyData * data)
{
	vtkSmartPointer<vtkXMLPolyDataWriter> polyDataWriter = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	polyDataWriter->SetFileName(path.toLocal8Bit());
	polyDataWriter->SetInputData(data);
	polyDataWriter->Write();
}
