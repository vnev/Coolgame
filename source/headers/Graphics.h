#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();
	SDL_Surface* LoadImage(const std::string &filePath);
	void DrawSurface(SDL_Texture* renderer, SDL_Rect* sourceRect, SDL_Rect* destRect);
	void Render();
	void Clear();
	SDL_Renderer* GetRenderer() const;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif
