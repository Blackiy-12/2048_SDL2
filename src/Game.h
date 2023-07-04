#pragma once

#include <vector>
#include <memory>

#include "Table.h"
#include "Render.h"

class Object;

class Game
{
public:
    Game(Game& other) = delete;

    void operator=(const Game&) = delete;

    static Game* getGame();

    void addUpadteObject(Object* NewObject);

    void deleteUpdateObject(Object* Object);

    void play();

private:
    std::vector<Object*> UpdatableObjects;

    std::unique_ptr<Table> TablePtr;

    std::unique_ptr<Render> RenderPtr;

    static Game* Pointer;

    bool Runnig = true;

private:
    Game() { this->init(); }

    void init();

    void updateObjects();

    void renderAnimation();
};

