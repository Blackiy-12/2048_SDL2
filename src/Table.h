#pragma once

#include "TableInformation.h"
#include "Cell.h"
#include "vec2.h"
#include <vector>
#include <memory>

enum class SlideDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Table
{
public:

	Table();

	~Table() {}

	void slideCells(SlideDirection Direction);

	bool isAllCellNotFree();

	void update();

	TableInformation getTableInformation();

	bool isAllCellsInPosition();

	void uniteCells();

	void deleteCells();

private:

	std::vector<std::shared_ptr<Cell>> Cells;

	bool Changes;

private:

	void createNewCell();

	std::vector<std::vector<std::shared_ptr<Cell>>> getVerticalLines();

	std::vector<std::vector<std::shared_ptr<Cell>>> getHorizontalLines();

	void slideUp();

	void slideDown();
	
	void slideLeft();

	void slideRight();

	std::vector<vec2<int>> getFreeCells();

	void increseCellsPower();

	int getTableScore();
};

