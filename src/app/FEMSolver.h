#pragma once
#include "ISolve.h"
#include "SolverConfig.h"
#include <engine.h>

class FEMSolver : public ISolve
{
private: SolverConfig* config;
	public:
		void solve(QString inputPath, QString outputUPath, QString outputPPath);
		FEMSolver(SolverConfig* _config);
};