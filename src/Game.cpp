#include "Game.h"

#include "Object.h"
#include "Input.h"

Game* Game::Pointer = nullptr;

Game* Game::getGame()
{
    if ( Pointer == nullptr) { Pointer = new Game(); }

    return Pointer;
}

void Game::addUpadteObject(Object* NewObject)
{
    for (auto UpdatableObject : this->UpdatableObjects)
    {
        if (UpdatableObject == NewObject)
            return;
    }

    this->UpdatableObjects.push_back(NewObject);
}

void Game::deleteUpdateObject(Object* Object)
{
    for (auto Itr = this->UpdatableObjects.begin(); Itr != this->UpdatableObjects.end(); Itr++)
    {
        auto UpdatableObject = *Itr;

        if (UpdatableObject == Object)
        {
            this->UpdatableObjects.erase(Itr);
            return;
        }
    }
}

void Game::play()
{
    while (this->Runnig)
    {
        this->TablePtr->update();

        if (this->TablePtr->isAllCellNotFree())
            return;

        this->RenderPtr->render(this->TablePtr->getTableInformation());

        Input::getNewInput();

        switch (Input::NewInput)
        {
        case InputInteraction::WINDOW_CLOSE:
            return;

        case InputInteraction::WINDOW_RESIZE:
            continue;

        case InputInteraction::UP:
            this->TablePtr->slideCells(SlideDirection::UP);
            break;

        case InputInteraction::DOWN:
            this->TablePtr->slideCells(SlideDirection::DOWN);
            break;

        case InputInteraction::LEFT:
            this->TablePtr->slideCells(SlideDirection::LEFT);
            break;

        case InputInteraction::RIGHT:
            this->TablePtr->slideCells(SlideDirection::RIGHT);
            break;
;       }

        this->renderAnimation();
    }
}

void Game::init()
{
    this->TablePtr = std::make_unique<Table>();

    this->RenderPtr = std::make_unique<Render>();
}

void Game::updateObjects()
{
    for (auto UpdatableObject : this->UpdatableObjects)
    {
        UpdatableObject->update();
    }
}

void Game::renderAnimation()
{
    while (this->TablePtr->isAllCellsInPosition() == false)
    {
        this->updateObjects();

        this->RenderPtr->render(this->TablePtr->getTableInformation());
    }

}
