#include "Render.h"

#include <string>

#include <iostream>
#include <SDL_ttf.h>

struct RGB
{
	uint8_t r, g, b;
};

const RGB CellColors[] =
{
	{238, 228, 218},
	{218, 224, 200},
	{242, 177, 121},
	{245, 149, 99},
	{246, 124, 96},
	{237, 207, 115},
	{237, 204, 98},
	{237, 200, 80},
	{237, 197, 63},
	{237, 194, 45}
};

Render::Render()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();

	const std::string Title = "2048";

	this->Window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);

	this->Renderer = SDL_CreateRenderer(this->Window, -1, SDL_RENDERER_ACCELERATED);

	this->Font = TTF_OpenFont("Font.ttf", 100);
}

Render::~Render()
{
	SDL_DestroyRenderer(this->Renderer);

	SDL_DestroyWindow(this->Window);

	TTF_CloseFont(this->Font);

	TTF_Quit();

	SDL_Quit();
}

void Render::render(TableInformation TableInfo)
{
	SDL_SetRenderDrawColor(this->Renderer, 0xff, 0xff, 0xff, 0xff);

	SDL_RenderClear(this->Renderer);

	this->drawTableWithCells(TableInfo);

	SDL_RenderPresent(this->Renderer);
}

void Render::drawTableWithCells(TableInformation TableInfo)
{
	vec2<int> WindowSize;

	SDL_GetWindowSizeInPixels(this->Window, &WindowSize.x, &WindowSize.y);

	SDL_Rect Table = { WindowSize.x * 0.05f, WindowSize.y * 0.15f, WindowSize.x - WindowSize.x * 0.1f, WindowSize.y - WindowSize.y * 0.2f };

	SDL_SetRenderDrawColor(this->Renderer, 0x80, 0x80, 0x80, 0xff);

	SDL_RenderFillRect(this->Renderer, &Table);

	SDL_SetRenderDrawColor(this->Renderer, 0xff, 0x00, 0x00, 0xff);

	SDL_Rect CellBackGround;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			CellBackGround = { int(Table.x + 0.04f * (x + 1) * Table.w + 0.2f * x * Table.w), int(Table.y + 0.04f * (y + 1) * Table.h + 0.2f * y * Table.h), int(Table.w * 0.2f), int(Table.h * 0.2f) };

			SDL_RenderFillRect(this->Renderer, &CellBackGround);
		}
	}

	SDL_Color  Black = { 0x0, 0x0, 0x0 };

	for (auto CellInfo : TableInfo.Cells)
	{
		std::string PowerOfTwo = std::to_string(int(std::pow(2, CellInfo.PowerOfTwo)));
		SDL_Surface* Surface = TTF_RenderUTF8_Blended(Font, PowerOfTwo.c_str(), Black);
		SDL_Texture* RenderText = SDL_CreateTextureFromSurface(this->Renderer, Surface);

		SDL_Rect Cell = { int(Table.x + 0.04f * (CellInfo.TablePosition.x + 1) * Table.w + 0.2f * CellInfo.TablePosition.x * Table.w), int(Table.y + 0.04f * (CellInfo.TablePosition.y + 1) * Table.h + 0.2f * CellInfo.TablePosition.y * Table.h), int(Table.w * 0.2f), int(Table.h * 0.2f) };
	
		int Color = CellInfo.PowerOfTwo - 1;

		SDL_SetRenderDrawColor(this->Renderer, CellColors[Color].r, CellColors[Color].g, CellColors[Color].b, 0xff);

		SDL_RenderFillRect(this->Renderer, &Cell);

		SDL_Rect TextPosition = {int(Cell.x + Cell.w * (0.4f - (0.1f * (PowerOfTwo.size() - 1)))), int(Cell.y + Cell.h * 0.2f), int(Cell.w * (0.2f + (0.1f * (PowerOfTwo.size() - 1)))), int(Cell.h * 0.6f) };

		SDL_RenderCopy(this->Renderer, RenderText, NULL, &TextPosition);

		SDL_FreeSurface(Surface);
		SDL_DestroyTexture(RenderText);
	}
}
