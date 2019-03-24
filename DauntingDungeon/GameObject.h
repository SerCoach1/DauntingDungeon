#pragma once
#include "SDL.h"
#include <memory>
#include <string>
#include "PhysicsObject.h"
#include "Collidable.h"

/*Handles Object's texture (setup and Rendering), its position and a reference to collider*/

class GameObject : public PhysicsObject{
	friend class PhysicsManager;
	friend class GameManager;
public:
	GameObject(const std::string textureName, Vector2 pos);
	//~GameObject();
	void MovePosAndCol(Vector2 posChange);
	void UpdateTexPos();
	void Render();

	Collidable* GetCollider() { return collider; }

	void AddCollider(std::unique_ptr<Collidable> col);

protected:
	Collidable* collider;

	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> objTexture;
	SDL_Rect srcRect, destRect; /*Position of the texture*/
};