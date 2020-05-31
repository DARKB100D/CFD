#pragma once

#include "ISolve.h"

class FEMSolver : public ISolve
{
	public:
		SolverResult solve();
		void loadConfig();
};