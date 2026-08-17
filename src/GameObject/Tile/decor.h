#ifndef DECOR_H
#define DECOR_H

#include <string>
#include "tile.h"
#include "../../engine/Animation.h"

/*
	O trang tri - khong co va cham.
*/
class decor : public tile {
private:
	Animation anim;
	std::string animKey = "-";      // "-" nghia la khong co animation

	// Moi sprite trong thu muc Animation deu co dung 2 khung
	static constexpr int   ANIM_FRAMES = 2;
	static constexpr float ANIM_TIME = 0.3f;

public:
	using tile::tile; // ke thua 3 constructor cua tile (decor tinh)

	// Constructor cho decor co animation
	decor(int m, int n, std::string t, int srcX, int srcY, std::string key);

	const std::string& getAnimKey() const { return animKey; }
	Animation& getAnim() { return anim; }
	bool hasAnim() const { return animKey != "-" && !animKey.empty(); }

	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
};

#endif // !DECOR_H
