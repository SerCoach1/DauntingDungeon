#pragma once
#include "SDL.h"
#include <vector>
#include "Square.h"
#include "Circle.h"
#include <memory>
#include "GameObject.h"
#include "Vector2.h"

class CollisionManager {
	friend class PhysicsManager;
	friend class GameMap; //refactor to not need this
protected:
	struct collision {
		GameObject* obj1;
		GameObject* obj2;
		Vector2 normal;
		float penetration;
	};

	std::vector<collision*> collisions;
	std::vector<std::shared_ptr<Collidable>> terrain;
	std::vector<GameObject*> allObjects;

	static float CalculateImpulse(const GameObject * a, const GameObject * b, Vector2&normal);
public:
	void HandleCollisionResolution();
	void AddCollision(collision*);

	bool AABB(const Square *a, const Square *b, Vector2 &normal, float &penDist);
	bool SphereCollision(const Circle *a, const Circle *b, Vector2 &normal, float &penDist);
	bool CircleSquareCollision(const Square * square,
		const Circle * circle, Vector2 &normal, float &penDist);
	void ObjectTerrainCollision(std::vector<GameObject*> &allObjects);
	void CollisionDetection(std::vector<GameObject*> &allObjects);
	void ObjectCollision(std::vector<GameObject*> &allObjects);

	CollisionManager() {}
	void Draw();

	void AddTerrainCollider(std::shared_ptr<Collidable> col);
private:
	
	
};