#pragma once

#include "vec2.h"
#include "Object.h"
#include "TableInformation.h"

class Cell : public Object
{
public:
	Cell(vec2<int> TablePosition, int PowerOfTwo = 1) : TablePosition(TablePosition), LocalePosition(TablePosition.x, TablePosition.y), PowerOfTwo(PowerOfTwo),
		WillDelete(false), IncreasedPower(PowerOfTwo) {}

	~Cell() {}

	void update() override;

	vec2<int> getTablePosition() { return this->TablePosition; }

	int getPowerOfTwo() { return this->IncreasedPower; }

	void setNewTablePosition(vec2<int> NewPosition);

	CellInfo getCellInfo();

	void increasePowerOfTwo() { this->IncreasedPower++; }

	bool isCellInPosition();

	void deleteNextRound();

	void setNewPower() { this->PowerOfTwo = this->IncreasedPower; }

	bool isNeedToDelete() { return this->WillDelete; }

private:
	int PowerOfTwo;

	int IncreasedPower;

	vec2<int> TablePosition;

	vec2<float> LocalePosition;

	vec2<float> Acceleration = {0.0f, 0.0f};

	bool WillDelete;
};

