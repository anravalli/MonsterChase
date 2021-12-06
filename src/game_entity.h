#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

class UiPageQt;

class GameEntityI
{
public:
    virtual ~GameEntityI() {};
    virtual void addToPage(UiPageQt* page) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
};

#endif // GAME_ENTITY_H
