#pragma once

class IExport
{
	public:
		virtual ~IExport() {};
		virtual void Export() = 0;
};