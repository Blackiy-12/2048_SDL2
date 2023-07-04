#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "TableInformation.h"

class Render
{
public:
	Render();

	~Render();

	void render(TableInformation TableInfo);

private:
	SDL_Window* Window;

	SDL_Renderer* Renderer;

	TTF_Font* Font;

private:

	void drawTableWithCells(TableInformation TableInfo);
};

