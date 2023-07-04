#include "Table.h"

#include <random>

Table::Table()
{
	this->Cells = {};

	this->Changes = true;
}

void Table::createNewCell()
{
	auto FreeCells = this->getFreeCells();

	std::random_device rd;

	std::uniform_int_distribution<int> dist(0, FreeCells.size()-1);

	int NewPosition = dist(rd);

	this->Cells.push_back(std::make_shared<Cell>(FreeCells.at(NewPosition)));
}

void Table::deleteCells()
{
	for (int Index = 0; Index < this->Cells.size(); Index++)
	{
		auto CurentCell = this->Cells.begin() + Index;

		if (CurentCell->get()->isNeedToDelete() == true)
		{
			this->Cells.erase(CurentCell);
			Index--;
		}
	}
}

void Table::slideCells(SlideDirection Direction)
{
	switch (Direction)
	{
	case SlideDirection::UP:
		this->slideUp();
		break;
	case SlideDirection::DOWN:
		this->slideDown();
		break;
	case SlideDirection::LEFT:
		this->slideLeft();
		break;
	case SlideDirection::RIGHT:
		this->slideRight();
		break;
	}
}

bool Table::isAllCellNotFree()
{

	if (this->Cells.size() != 16)
		return false;

	for (auto CheckCell : this->Cells)
	{
		vec2<int> LeftPos = CheckCell->getTablePosition() + vec2<int>(1, 0);
		vec2<int> RightPos = CheckCell->getTablePosition() + vec2<int>(-1, 0);
		vec2<int> DownPos = CheckCell->getTablePosition() + vec2<int>(0, 1);
		vec2<int> UpPos = CheckCell->getTablePosition() + vec2<int>(0, -1);

		for (auto Cell : this->Cells)
		{
			if (Cell->getTablePosition() == LeftPos || Cell->getTablePosition() == RightPos || Cell->getTablePosition() == DownPos || Cell->getTablePosition() == UpPos)
			{
				if (CheckCell->getPowerOfTwo() == Cell->getPowerOfTwo())
					return false;
			}
		}
	}

	return true;
}

void Table::update()
{
	if (this->Changes == true)
	{
		if (this->Cells.size() != 16)
			this->createNewCell();

		this->deleteCells();

		this->increseCellsPower();

		this->Changes = false;
	}
}

TableInformation Table::getTableInformation()
{
	TableInformation Result;

	for (auto Cell : this->Cells)
	{
		Result.addCell(Cell->getCellInfo());
	}

	return Result;
}

bool Table::isAllCellsInPosition()
{
	for (auto Cell : this->Cells)
	{
		if (Cell->isCellInPosition() == false)
			return false;
	}

	return true;
}


std::vector<std::vector<std::shared_ptr<Cell>>> Table::getVerticalLines()
{
	std::vector<std::shared_ptr<Cell>> LeftCells, MiddleLeftCells, MiddleRightCells, RightCells;

	for (auto Cell : this->Cells)
	{
		switch (Cell->getTablePosition().x)
		{
		case 0:
			LeftCells.push_back(Cell);
			break;
		case 1:
			MiddleLeftCells.push_back(Cell);
			break;
		case 2:
			MiddleRightCells.push_back(Cell);
			break;
		case 3:
			RightCells.push_back(Cell);
			break;
		}
	}

	return std::vector<std::vector<std::shared_ptr<Cell>>>{LeftCells, MiddleLeftCells, MiddleRightCells, RightCells};
}

std::vector<std::vector<std::shared_ptr<Cell>>> Table::getHorizontalLines()
{
	std::vector<std::shared_ptr<Cell>> TopCells, MiddleTopCells, MiddleBottomCells, BottomCells;


	for (auto Cell : this->Cells)
	{
		switch (Cell->getTablePosition().y)
		{
		case 0:
			TopCells.push_back(Cell);
			break;
		case 1:
			MiddleTopCells.push_back(Cell);
			break;
		case 2:
			MiddleBottomCells.push_back(Cell);
			break;
		case 3:
			BottomCells.push_back(Cell);
			break;
		}
	}

	return std::vector<std::vector<std::shared_ptr<Cell>>>{TopCells, MiddleTopCells, MiddleBottomCells, BottomCells};
}


void Table::uniteCells()
{
	for (int Index = 0; Index < this->Cells.size(); Index++)
	{
		for (int Prev = Index - 1; Prev >= 0; Prev--)
		{
			if (this->Cells.at(Index)->getTablePosition() == this->Cells.at(Prev)->getTablePosition() && this->Cells.at(Index)->getPowerOfTwo() == this->Cells.at(Prev)->getPowerOfTwo())
			{
				auto NewCellPosition = this->Cells.at(Index)->getTablePosition();
				int NewPower = this->Cells.at(Index)->getPowerOfTwo();
				this->Cells.erase(this->Cells.begin() + Index);
				this->Cells.erase(this->Cells.begin() + Prev);
				this->Cells.push_back(std::make_shared<Cell>(NewCellPosition, NewPower));
				Index--;
				break;
			}
		}
	}
}

void Table::slideUp()
{
	auto Lines = this->getVerticalLines();

	auto sortFunc = [](std::shared_ptr<Cell> Left, std::shared_ptr<Cell> Right) -> bool
	{
		return Left->getTablePosition().y < Right->getTablePosition().y;
	};

	for (auto Vector : Lines)
	{
		std::sort(Vector.begin(), Vector.end(), sortFunc);

		for (int Index = 0; Index < Vector.size(); Index++)
		{
			auto Itr = Vector.begin() + Index;

			if (Itr == Vector.begin())
			{
				if (Itr->get()->getTablePosition().y == 0)
					continue;

				Itr->get()->setNewTablePosition(vec2<int>(Itr->get()->getTablePosition().x, 0));
				this->Changes = true;
				continue;
			}

			auto Prev = Itr - 1;

			if (Prev->get()->getPowerOfTwo() == Itr->get()->getPowerOfTwo())
			{
				Itr->get()->setNewTablePosition(Prev->get()->getTablePosition());
				Prev->get()->increasePowerOfTwo();
				Index--;
				Itr->get()->deleteNextRound();
				this->Changes = true;
				Vector.erase(Itr);
			}
			else
			{
				if (Prev->get()->getTablePosition().y == 2)
					continue;

				if ((Prev->get()->getTablePosition() + vec2<int>(0, 1))== Itr->get()->getTablePosition())
					continue;

				Itr->get()->setNewTablePosition((Prev->get()->getTablePosition() + vec2<int>(0, 1)));
				this->Changes = true;
			}
		}
	}
}

void Table::slideDown()
{
	auto Lines = this->getVerticalLines();

	auto sortFunc = [](std::shared_ptr<Cell> Left, std::shared_ptr<Cell> Right) -> bool
	{
		return Left->getTablePosition().y > Right->getTablePosition().y;
	};

	for (auto Vector : Lines)
	{
		std::sort(Vector.begin(), Vector.end(), sortFunc);

		for (int Index = 0; Index < Vector.size(); Index++)
		{
			auto Itr = Vector.begin() + Index;

			if (Itr == Vector.begin())
			{
				if (Itr->get()->getTablePosition().y == 3)
					continue;

				Itr->get()->setNewTablePosition(vec2<int>(Itr->get()->getTablePosition().x, 3));
				this->Changes = true;
				continue;
			}

			auto Prev = Itr - 1;

			if (Prev->get()->getPowerOfTwo() == Itr->get()->getPowerOfTwo())
			{
				Itr->get()->setNewTablePosition(Prev->get()->getTablePosition());
				Prev->get()->increasePowerOfTwo();
				Index--;
				Itr->get()->deleteNextRound();
				this->Changes = true;
				Vector.erase(Itr);
			}
			else
			{

				if ((Prev->get()->getTablePosition() + vec2<int>(0, -1)) == Itr->get()->getTablePosition())
					continue;

				Itr->get()->setNewTablePosition(Prev->get()->getTablePosition() + vec2<int>(0, -1));
				this->Changes = true;
			}
		}
	}
}

void Table::slideLeft()
{
	auto Lines = this->getHorizontalLines();

	auto sortFunc = [](std::shared_ptr<Cell> Left, std::shared_ptr<Cell> Right) -> bool
	{
		return Left->getTablePosition().x < Right->getTablePosition().x;
	};

	for (auto Vector : Lines)
	{
		std::sort(Vector.begin(), Vector.end(), sortFunc);

		for (int Index = 0; Index < Vector.size(); Index++)
		{
			auto Itr = Vector.begin() + Index;

			if (Itr == Vector.begin())
			{
				if (Itr->get()->getTablePosition().x == 0)
					continue;

				Itr->get()->setNewTablePosition(vec2<int>(0, Itr->get()->getTablePosition().y));
				this->Changes = true;
				continue;
			}

			auto Prev = Itr - 1;

			if (Prev->get()->getPowerOfTwo() == Itr->get()->getPowerOfTwo())
			{
				Itr->get()->setNewTablePosition(Prev->get()->getTablePosition());
				Prev->get()->increasePowerOfTwo();
				Itr->get()->deleteNextRound();
				Index--;
				this->Changes = true;
				Vector.erase(Itr);
			}
			else
			{
				if (Prev->get()->getTablePosition().x == 2)
					continue;

				if ((Prev->get()->getTablePosition() + vec2<int>(1, 0)) == Itr->get()->getTablePosition())
					continue;

				Itr->get()->setNewTablePosition((Prev->get()->getTablePosition() + vec2<int>(1, 0)));
				this->Changes = true;
			}
		}
	}
}

void Table::slideRight()
{
	auto Lines = this->getHorizontalLines();

	auto sortFunc = [](std::shared_ptr<Cell> Left, std::shared_ptr<Cell> Right) -> bool
	{
		return Left->getTablePosition().x > Right->getTablePosition().x;
	};

	for (auto Vector : Lines)
	{
		std::sort(Vector.begin(), Vector.end(), sortFunc);

		for (int Index = 0; Index < Vector.size(); Index++)
		{
			auto Itr = Vector.begin() + Index;

			if (Itr == Vector.begin())
			{
				if (Itr->get()->getTablePosition().x == 3)
					continue;

				Itr->get()->setNewTablePosition(vec2<int>(3, Itr->get()->getTablePosition().y));
				this->Changes = true;
				continue;
			}

			auto Prev = Itr - 1;

			if (Prev->get()->getPowerOfTwo() == Itr->get()->getPowerOfTwo())
			{
				Itr->get()->setNewTablePosition(Prev->get()->getTablePosition());
				Prev->get()->increasePowerOfTwo();
				Itr->get()->deleteNextRound();
				Index--;
				this->Changes = true;
				Vector.erase(Itr);
			}
			else
			{
				if (Prev->get()->getTablePosition().x == 1)
					continue;

				if ((Prev->get()->getTablePosition() + vec2<int>(-1, 0)) == Itr->get()->getTablePosition())
					continue;

				Itr->get()->setNewTablePosition((Prev->get()->getTablePosition() + vec2<int>(-1, 0)));
				this->Changes = true;
			}
		}
	}
}

std::vector<vec2<int>> Table::getFreeCells()
{
	std::vector<vec2<int>> PosiblePosition;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			PosiblePosition.push_back(vec2<int>(x, y));
		}
	}

	for (auto CellItr = this->Cells.begin(); CellItr != this->Cells.end(); CellItr++)
	{
		for (auto PosItr = PosiblePosition.begin(); PosItr != PosiblePosition.end(); PosItr++)
		{
			if (CellItr->get()->getTablePosition() == *PosItr)
			{
				PosiblePosition.erase(PosItr);
				break;
			}
		}
	}
	
	return PosiblePosition;
}

void Table::increseCellsPower()
{
	for (auto Cell : this->Cells)
	{
		Cell->setNewPower();
	}
}

int Table::getTableScore()
{
	int Result = 0;

	for (auto CurrrentCell : this->Cells)
	{
		Result += CurrrentCell->getPowerOfTwo();
	}

	return Result;
}
