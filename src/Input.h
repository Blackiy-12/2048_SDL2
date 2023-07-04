#pragma once

#include <SDL.h>
#include "Table.h"

enum class InputInteraction
{
	NONE,
	WINDOW_RESIZE,
	WINDOW_CLOSE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Input
{
public:
	static void getNewInput()
	{
		while (true)
		{
			SDL_Event Event;
			while (SDL_WaitEvent(&Event))
			{
				switch (Event.type)
				{
				case SDL_KEYDOWN:
					if (Event.key.keysym.scancode == SDL_SCANCODE_DOWN)
					{
						Input::NewInput = InputInteraction::DOWN;
						return;
					}
					else if (Event.key.keysym.scancode == SDL_SCANCODE_UP)
					{
						Input::NewInput = InputInteraction::UP;
						return;
					}
					else if (Event.key.keysym.scancode == SDL_SCANCODE_LEFT)
					{
						Input::NewInput = InputInteraction::LEFT;
						return;
					}
					else if (Event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
					{
						Input::NewInput = InputInteraction::RIGHT;
						return;
					}
					break;

				case SDL_QUIT:
					Input::NewInput = InputInteraction::WINDOW_CLOSE;
					return;
				default:
					break;
				}
			}
		}
	}

	static InputInteraction NewInput;
};

InputInteraction Input::NewInput = InputInteraction::NONE;