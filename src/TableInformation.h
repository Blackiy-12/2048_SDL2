#pragma once

#include "vec2.h"

#include <vector>

struct CellInfo
{
	vec2<float> TablePosition;

	int PowerOfTwo;
};

struct TableInformation
{
	std::vector<CellInfo> Cells;

	void addCell(CellInfo NewCell) { this->Cells.push_back(NewCell); }
};
