#pragma once
#include "SDL2/SDL_image.h"
#include <memory>

class TextureManager {
public:
	static SDL_Texture* GetTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, const SDL_Rect &dest, float rotation, SDL_RendererFlip flip);
};