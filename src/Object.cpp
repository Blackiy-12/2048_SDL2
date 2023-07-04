#include "Object.h"

#include "Game.h"

Object::Object()
{
	Game::getGame()->addUpadteObject(this);
}

Object::~Object()
{
	Game::getGame()->deleteUpdateObject(this);
}
