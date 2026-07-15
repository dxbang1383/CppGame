#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL3/SDL.h>

class gameObject
{
private: 
    int x, y;
    int width, height;
    SDL_Rect rect;

public:
    // Constructor
    gameObject(int x, int y, int width, int height);

    // 
    int getWidth() const;
    int getHeight() const;
    int getX() const;
    int getY() const;
    //
    void setX(int newX);
    void setY(int newY);
    void setPosition(int newX, int newY);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setSize(int newWidth, int newHeight);
    //
    virtual void update(float deltaTime);
    virtual void render(SDL_Renderer *renderer);
};

#endif