#pragma once

#include "SolverResult.h"
#include <QString.h>

__interface ISolve
{
	public:
		void solve(QString inputPath, QString outputUPath, QString outputPPath);
		
};

