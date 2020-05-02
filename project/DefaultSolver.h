#pragma once

#include "ISolve.h"

class DefaultSolver : public ISolve
{
	public:
		SolverResult solve();
};