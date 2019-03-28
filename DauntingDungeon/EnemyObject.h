#pragma once
#include "GameObject.h"

class EnemyObject : public GameObject {
public:
	EnemyObject(const std::string textureName, Vector2 pos);

	void UpdateObject() override;

private:
	int time;
	Vector2 direction;
};