#include "Converter.h"

void Converter::geometryFile_ToVtkPolyData(QString inputFileName, vtkPolyData * data)
{
	QFile modelfile(inputFileName);
	if (!modelfile.exists()) return;
	
	QFileInfo fileinfo(inputFileName); // Определяем путь к файлу
	QString suffix = fileinfo.suffix(); // возвращаем расширение файла, которое состоит из всех символов в файле после последнего символа точки (но не включая её)

	if (suffix == "stl") {
		vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
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
	else if (suffix == "vtp") {
		vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
		reader->SetFileName(inputFileName.toLocal8Bit());
		reader->Update();

		data->DeepCopy(reader->GetOutput());
	}

	//if fileType == '':
	//raise RuntimeError('The file does not have an extension')
	//	if fileType == 'stl' :
	//		reader = vtk.vtkSTLReader()
	//		reader.MergingOn()
	//		elif fileType == 'vtk' :
	//		reader = vtk.vtkPolyDataReader()
	//		elif fileType == 'tec' :
	//		reader = vtk.vtkTecplotReader()
	//		elif fileType == 'vtp' :
	//		reader = vtk.vtkXMLPolyDataReader()
	//		elif fileType == 'vtu' :
	//		reader = vtk.vtkXMLUnstructuredGridReader()
	//	else:
	//raise RuntimeError('Unknown file type %s' % fileType)
}

void Converter::vtkPolyData_ToVTKFile(QString path, vtkPolyData * data)
{
	vtkSmartPointer<vtkXMLPolyDataWriter> polyDataWriter = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	polyDataWriter->SetFileName(path.toLocal8Bit());
	polyDataWriter->SetInputData(data);
	polyDataWriter->Write();
}
