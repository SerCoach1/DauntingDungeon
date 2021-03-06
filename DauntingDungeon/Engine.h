#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include "TextureManager.h"
#include "InputManager.h"
#include <memory>
#include "UIManager.h"
#include "GameManager.h"
#include "AudioManager.h"

class Engine {
public:
	Engine();

	void Initialise(std::string title, int x, int y, int width, int height, bool fullscreen);
	void Render();
	bool Running();
	void ExitGame();
	void Update(std::string fps, Uint32 dt);
	static SDL_Renderer* renderer;
	static SDL_Rect camera;

private:
	
	bool isRunning;
	std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window; // need to pass in a custom deleter because need to call SDL_DestroyWindow
	std::unique_ptr<InputManager> inputManager;
	std::unique_ptr<UIManager> ui;
	std::unique_ptr<GameManager> gameManager;
	AudioManager* audioManager;
};