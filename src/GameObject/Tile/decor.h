#ifndef DECOR_H
#define DECOR_H

#include <string>
#include "tile.h"
#include "../../engine/Animation.h"

/*
	O trang tri - khong co va cham. Co hai dang:

	  TINH  : cat tu sprite sheet -> can texKey + srcX + srcY
	  DONG  : file sprite rieng -> chi can texKey (trung voi ten file trong Tiles/Animation)

	Phan biet bang so khung cua Animation:
	  frameCount == 1  ->  tinh   (Animation() mac dinh)
	  frameCount >  1  ->  dong

*/
class decor : public tile {
private:
	Animation anim;

	// Moi sprite trong thu muc Animation deu co dung 2 khung
	static constexpr int   ANIM_FRAMES = 2;
	static constexpr float ANIM_TIME = 0.3f;

public:
	// Decor TINH 
	decor(int col, int row, std::string texKey, int srcX, int srcY);

	// Decor DONG 
	decor(int col, int row, std::string animKey);

	bool hasAnim() const { return anim.getFrameCount() > 1; }
	Animation& getAnim() { return anim; }

	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
};

#endif // !DECOR_H
