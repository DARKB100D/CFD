#include "FEMSolver.h"


#define BUFSIZE 1000



void FEMSolver::solve(QString inputPath, QString outputUPath, QString outputPPath)
{/*
	Engine *matlab = engOpen(NULL);
	QString myString = "Svistok(" + 
		QString::number(config->Viscosity) +
		", "+ inputPath + 
		", " + outputUPath + 
		", " + outputPPath + 
		config->R_X+
		config->R_Y+
		config->R_Z+");";

	if (matlab == NULL) {
		printf("Can't start MATLAB engine!!!\n");
		exit(-1);
	}
	{

		char buffer[BUFSIZE + 1];
		buffer[BUFSIZE] = '\0';
		engOutputBuffer(matlab, buffer, BUFSIZE);
		engEvalString(matlab, "clc;clear;");

		engEvalString(matlab, "cd \'C:\\Program Files (x86)\\Getfem-5.2-Matlab2016'");
		engEvalString(matlab, myString.toUtf8());
		printf("%s\n", buffer);


	}
	system("pause");
	engClose(matlab);*/
};

FEMSolver::FEMSolver(SolverConfig* _config)
{
	this->config = _config;
}
