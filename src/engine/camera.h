#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

class camera {
private:
    /*
        x , y là tọa độ trên trái của phần hiển thị 
        scale 
    */

    float x = 10.0f;
    float y = 10.0f;
    float scale = 1.0f;
    float velocityX = 0.0f;
    float velocityY = 0.0f;

public :
    
    camera() = default;

    // chỉnh các thông số của camera 
    float getX() const;
    float getY() const;
    float getScale() const;

    //chuyển x y sang giữa 2 chế độ 
    float xWorldToScreen(float xWorld) const;
    float yWorldToScreen(float yWorld) const;
    float xScreenToWorld(float xS) const;
    float yScreenToWorld(float yS) const;



    void setPosition(float nx, float ny);
    void setScale(float s);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void getInfo();

    // Tăng scale thêm 0.05 
    void zoomIn();
    // Giảm scale đi 0.05
    void zoomOut();

    // Hàm focus một địa chỉ gì nào đó 
    // drawX, drawY là địa chỉ cần focus , thông qua 2 biến screen để cho focus vào giữa màn hình 
    void focus(float drawX, float drawY, float screenW, float screenH);

};


#endif // !CAMERA_H
