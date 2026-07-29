#ifndef CAMERA_H
#define CAMERA_H

class camera {
private:
    /*
        x , y là tọa độ trên trái của phần hiển thị 
        scale 
    */

    float x = 0.0f;
    float y = 0.0f;
    float scale = 1.0f;

public :
    camera() = default;
    float getX() const;
    float getY() const;
    float getScale() const;
    void  setPosition(float nx, float ny);
    void  setScale(float s);

    // Tăng scale thêm 0.05 
    void zoomIn();
    // Giảm scale đi 0.05
    void zoomOut();

    // Hàm focus một địa chỉ gì nào đó 
    // drawX, drawY là địa chỉ cần focus , thông qua 2 biến screen để cho focus vào giữa màn hình 
    void focus(float drawX, float drawY, float screenW, float screenH);

};

#endif // !CAMERA_H
