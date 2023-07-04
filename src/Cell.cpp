#include "Cell.h"

void Cell::update()
{
	vec2<float> FTablePosition(this->TablePosition.x, this->TablePosition.y);

	if (this->LocalePosition != FTablePosition)
	{
		if (this->LocalePosition.x != FTablePosition.x)
		{
			float DifX = this->LocalePosition.x - FTablePosition.x;

			if (abs(DifX) < 0.1f)
				this->LocalePosition.x = FTablePosition.x;
			else if (DifX > 0.0f)
				this->LocalePosition.x -= this->Acceleration.x;
			else
				this->LocalePosition.x += this->Acceleration.x;
		}

		if (this->LocalePosition.y != FTablePosition.y)
		{
			float DifY = this->LocalePosition.y - FTablePosition.y;

			if (abs(DifY) < 0.1f)
				this->LocalePosition.y = FTablePosition.y;
			else if (DifY > 0.0f)
				this->LocalePosition.y -= this->Acceleration.y;
			else
				this->LocalePosition.y += this->Acceleration.y;
		}
	}
}

void Cell::setNewTablePosition(vec2<int> NewPosition)
{
	this->TablePosition = NewPosition;

	this->Acceleration.x = abs(float(NewPosition.x) - LocalePosition.x) / 30.0f;
	this->Acceleration.y = abs(float(NewPosition.y) - LocalePosition.y) / 30.0f;
}

CellInfo Cell::getCellInfo()
{
	return CellInfo{ this->LocalePosition, this->PowerOfTwo };
}

bool Cell::isCellInPosition()
{
	if (float(this->TablePosition.x) == this->LocalePosition.x && float(this->TablePosition.y) == this->LocalePosition.y)
		return true;

	return false;
}

void Cell::deleteNextRound()
{
	this->WillDelete = true;
}
