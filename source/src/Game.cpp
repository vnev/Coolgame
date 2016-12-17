#include <SDL2/SDL.h>

#include "../headers/Game.h"
#include "../headers/Graphics.h"
#include "../headers/Input.h"

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = (5 * 1000) / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->GameLoop();
}

Game::~Game() {
}

void Game::GameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;

	this->_player = Player(graphics, 100, 100);
	this->_level = Level(graphics, "Map 1", Vector2(100, 100));

	int LAST_UPDATE_TIME = SDL_GetTicks();

	while (true) {
		input.BeginNewFrame();
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.KeyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.KeyUpEvent(event);
			}
			if (event.type == SDL_QUIT) {
				return;
			}
		}

		if (input.WasKeyPressed(SDL_SCANCODE_ESCAPE)) {
			return;
		}
		else if (input.IsKeyHeld(SDL_SCANCODE_LEFT)) {
			this->_player.MoveLeft();
		}
		else if (input.IsKeyHeld(SDL_SCANCODE_RIGHT)) {
			this->_player.MoveRight();
		}

		if (!input.IsKeyHeld(SDL_SCANCODE_LEFT) && !input.IsKeyHeld(SDL_SCANCODE_RIGHT)) {
			this->_player.StopMoving();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		this->Update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->Draw(graphics);
	}
}

void Game::Draw(Graphics &graphics) {
	graphics.Clear();
	this->_level.Draw(graphics);
	this->_player.Draw(graphics);
	graphics.Render();
}

void Game::Update(float elapsedTime) {
	this->_player.Update(elapsedTime);
	this->_level.Update(elapsedTime);
}
