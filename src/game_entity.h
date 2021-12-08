#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

class UiPageViewQt;

class GameEntityI
{
public:
    virtual ~GameEntityI() {};
    virtual void addToPage(UiPageViewQt* page) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
};

#endif // GAME_ENTITY_H
