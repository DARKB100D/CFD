#pragma once

#include "ISolve.h"

class SPHSolver : public ISolve
{
	public:
		SolverResult solve();
};