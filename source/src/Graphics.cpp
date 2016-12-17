#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "../headers/Graphics.h"
#include "../headers/Global.h"

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Coolgame");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface* Graphics::LoadImage(const std::string &filePath) {
	if (this->_spriteSheets.count(filePath) == 0) {
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}

	return this->_spriteSheets[filePath];
}

void Graphics::DrawSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destRect) {
	SDL_RenderCopy(this->_renderer, texture, sourceRect, destRect);
}

void Graphics::Render() {
	SDL_RenderPresent(this->_renderer);
}

void Graphics::Clear() {
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::GetRenderer() const {
	return this->_renderer;
}

