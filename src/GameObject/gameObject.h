#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL3/SDL.h"
#include "SDL3_image/SDl_image.h"

class gameObject
{
private:
    double x, y;
    double width, height;
    SDL_FRect rect;
    SDL_Texture* tex;
public:
    // Constructor
    gameObject(double x, double y, double width, double height);
    gameObject();
    // 
    double getWidth() const;
    double getHeight() const;
    double getX() const;
    double getY() const;
    SDL_FRect* getRect();
    SDL_Texture* getTexture() const;

    //
    void setX(double newX);
    void setY(double newY);
    void setPosition(double newX, double newY);
    void setWidth(double newWidth);
    void setHeight(double newHeight);
    void setSize(double newWidth, double newHeight);
    void setTexture(SDL_Texture* tex);
    //
    void udpRect();
    virtual void update(float deltaTime);
    virtual void render(SDL_Renderer *renderer);
};

#endif