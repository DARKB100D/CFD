#pragma once

#include "ISolve.h"
#include "SolverConfig.h"

class FEMSolver : public ISolve
{
private:
	SolverConfig * cfg;

public:
	FEMSolver(SolverConfig * cfg);
	void solve(QString in, QString out1, QString out2);
};