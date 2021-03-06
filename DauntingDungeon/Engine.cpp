#include "Engine.h"
#include "GameObject.h"
#include "GameMap.h"
#include <memory>
#include <string>
#include "SDL2/SDL_mixer.h"
#include <stdio.h>
SDL_Renderer* Engine::renderer = nullptr;
SDL_Rect Engine::camera = { 0,0, 960, 640 };

Engine::Engine() : window(nullptr, SDL_DestroyWindow) {
	//don't need to initialise unique_ptr because it's null by default
}

void Engine::Initialise(std::string title, int x, int y, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		isRunning = false;

		std::cout << "Error Initialising Game!" << std::endl;
		return;
	}
	else { std::cout << "Game Initialised Successfully!" << std::endl; }

	if (TTF_Init() == -1) { printf("Unable to initialise TTF! SDL_ttf Error: %s\n", TTF_GetError()); }
	else { printf("TTF_Initialised!\n"); }

	window.reset(SDL_CreateWindow(title.c_str(), x, y, width, height, (fullscreen | SDL_WINDOW_RESIZABLE)));
	if (window) { std::cout << "Window Created Successfully!" << std::endl; }

	renderer = SDL_CreateRenderer(window.get(), -1, 0);
	if (renderer) { std::cout << "Renderer Created Successfully!" << std::endl; }

	//initialise SDL_mixer
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0) {
		printf("SDL_mixer could not be initialised! Error: %s\n", Mix_GetError());
	}
	else {
		printf("SDL_mixer initialised!\n");
	}

	SDL_RenderSetLogicalSize(renderer, 960, 640);

	isRunning = true;
	audioManager = new AudioManager();
	gameManager = std::make_unique<GameManager>(audioManager);
	gameManager->Initialise();
	inputManager = std::make_unique<InputManager>();
	ui = std::make_unique<UIManager>();

	

	audioManager->PlayMusic();
}

void Engine::Update(std::string fps, Uint32 dt)
{
	inputManager->HandleInput(isRunning, *gameManager, *audioManager);
	gameManager->Update(dt);

	camera.x = gameManager->GetPlayer().position.x - 440;
	camera.y = gameManager->GetPlayer().position.y - 320;

	ui->UpdateFPS("FPS: "+fps);
	ui->UpdateScore("SCORE: " + std::to_string(gameManager->GetScore()));
}

void Engine::Render()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 25, 0, 25, 255);

	gameManager->Draw();
	ui->DrawUI(gameManager->GetLives(), gameManager->GetPaused(), gameManager->GetDied());
	SDL_RenderPresent(renderer);
}

bool Engine::Running()
{
	return isRunning;
}

void Engine::ExitGame()
{
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Exited" << std::endl;
}


