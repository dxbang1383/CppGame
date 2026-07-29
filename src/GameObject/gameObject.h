#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL3/SDL.h"
#include "SDL3_image/SDl_image.h"
#include "../engine/camera.h"

class gameObject
{
private:
    double x, y; // x, y là tọa độ trong world
    double width, height; // kích thước hcn gốc
    SDL_FRect rect; // tọa độ thực tế trong không gian thế giới , đồng bộ với x,y ,width, height qua updRect()
    SDL_Texture* tex; // con trỏ texture
    SDL_FRect renderRect; // tọa độ để vẽ vật thể lên màn hình 
public:
    // Constructor
    gameObject(double x, double y, double width, double height);
    gameObject();

    // getter
    
    // w của hcn thế giới
    double getWidth() const;
    // h của hcn thế giới 
    double getHeight() const;
    // x của hcn thế giới
    double getX() const;
    // y của hcn thế giới
    double getY() const;
    // Trả về con trỏ của hình chữ nhật tọa độ trong world 
    SDL_FRect* getRect();
    // Trả về con trỏ của texture (có const)
    SDL_Texture* getTexture() const;
    // Trả về con trỏ của hình chữ nhật render , đã được tính qua scale và căn chỉnh theo cam 
    SDL_FRect* getRenderRect();

    // setter

    // set x của hcn thế giới
    void setX(double newX);
    // set y của hcn thế giới
    void setY(double newY);
    // set tọa độ hcn thế giới
    void setPosition(double newX, double newY);
    // set rộng hcn thế giới
    void setWidth(double newWidth);
    // set cao hcn thế giới
    void setHeight(double newHeight);
    // set rộng & cao hcn thế giới
    void setSize(double newWidth, double newHeight);
    // set tex tài nguyên 
    void setTexture(SDL_Texture* tex);
    // set hcn vẽ lên màn hình ( hcn được tính qua camera )
    void setRenderRect(SDL_FRect* rec);

    // Đồng bộ x, y, width , height với rect;
    void udpRect();

    // Dựa trên vị trí của camera nhận vào để tính lại renderRect.
    void updRenderRect(const camera &cam);
    // Hàm này chỉ update vị trí của hình chữ nhật trong thế giới , không update renderRect
    virtual void update(float deltaTime);
    // vẽ với vị trí vẽ là renderRect
    virtual void render(SDL_Renderer *renderer);
};

#endif