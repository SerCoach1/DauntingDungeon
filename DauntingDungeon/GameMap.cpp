#include "GameMap.h"
#include "TextureManager.h"
#include <fstream>
#include <iostream>
#include "Square.h"
#include "ColliderType.h"
#include "Engine.h"

GameMap::GameMap() :
	tileset(TextureManager::GetTexture("DauntingDungeon/Assets/map/dungeon.png"))
{
	dest.w = tileSize;
	dest.h = tileSize;

	mapHeight = 0;
	mapWidth = 0;

	/*height and width of rendered tile*/
	dest.x = dest.y = 0;
}

void GameMap::LoadMap(GameManager &gameManager)
{
	std::ifstream mapFile("DauntingDungeon/Assets/mapData/mapLayout.map");

	if (!mapFile) {
		std::cout << "Error loading in Map file!" << std::endl;
		return;
	}
	mapFile >> mapWidth;
	mapFile >> mapHeight;

	map = std::vector<std::vector<int>>(mapHeight, std::vector<int>(mapWidth, 0));

	std::vector<Square*> initTer;

	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {

			char type = 0;
			mapFile >> type;
			map[y][x] = type - '0';
		}
	}

	int type = 0;
	for (int row = 0; row < mapHeight; ++row) {
		for (int col = 0; col < mapWidth; ++col) {
			type = map[row][col];

			dest.x = col * tileSize;
			dest.y = row * tileSize;

			if (type == 1 || type == 3 || type == 4 || type == 5 || type == 6 || type == 7 || type == 8) {
				initTer.emplace_back(new Square(Vector2( //initially save top left corner of block as pos
					(float)col*tileSize, (float)row * tileSize), tileSize, tileSize));
			}
		}
	}

	/*Algorithm to combine terrain blocks into bigger colliders to save computation*/
	for (size_t i = 0; i < initTer.size(); ++i) {
		for (auto j = initTer.begin() + i; j != initTer.end();) {
			if (initTer[i]->pos.y == (*j)->pos.y &&
				initTer[i]->pos.x + initTer[i]->halfWidth == (*j)->pos.x &&
				initTer[i]->halfHeight == tileSize &&
				(*j)->halfHeight == tileSize && (*j)->halfWidth == tileSize) {
				initTer[i]->halfWidth += (*j)->halfWidth;
				delete (*j);
				j = initTer.erase(j);
			}
			else if (initTer[i]->pos.x == (*j)->pos.x &&
				initTer[i]->pos.y + initTer[i]->GetHalfHeight() == (*j)->pos.y &&
				initTer[i]->halfWidth == tileSize &&
				(*j)->halfWidth == tileSize && (*j)->halfHeight == tileSize) {
				initTer[i]->halfHeight += (*j)->halfHeight;
				delete (*j);
				j = initTer.erase(j);
			}
			else {
				++j;
			}
		}
	}

	//move pointers to primary vector and save actual center (x,y) pos and half width/height
	for (auto& o : initTer) {
		o->halfHeight /= 2;
		o->halfWidth /= 2;
		o->pos.x = o->pos.x + o->GetHalfWidth();
		o->pos.y = o->pos.y + o->GetHalfHeight();

		gameManager.AddTerrain(o);
	}

	/*std::cout << "numterrain: " << gameManager.terrain.size() << std::endl;
	for (auto a : gameManager.terrain) {
		std::shared_ptr<Square>s = std::dynamic_pointer_cast<Square>(a);
		std::cout << s->pos << " halfHeight= " << s->GetHalfHeight() << " halfWidth= " << s->GetHalfWidth() << std::endl;
	}*/
}

void GameMap::DrawMap()
{
	int type = 0;
	srand(420);
	SDL_Rect t;
	for (int row = 0; row < mapHeight; ++row) {
		for (int col = 0; col < mapWidth; ++col) {
			type = map[row][col];

			dest.x = (col * tileSize) - Engine::camera.x;
			dest.y = (row * tileSize) - Engine::camera.y;
			int r = rand() % 3 +1;
			switch (type) {
			case 0:
				TextureManager::Draw(tileset, tiles.ground, dest, 0, SDL_FLIP_NONE);
				break;
			case 1:
				TextureManager::Draw(tileset, tiles.upper_wall, dest, 0, SDL_FLIP_NONE);
				break;
			case 2:
				switch (r) {
				case 1: t = tiles.ground1;
					break;
				case 2: t = tiles.ground2;
					break;
				case 3: t = tiles.ground3;
					break;
				}
				TextureManager::Draw(tileset, t, dest, 0, SDL_FLIP_NONE);
				break;
			case 3:
				TextureManager::Draw(tileset, tiles.lava_fountain, dest, 0, SDL_FLIP_NONE);
				break;
			case 4:
				TextureManager::Draw(tileset, tiles.water_fountain, dest, 0, SDL_FLIP_NONE);
				break;
			case 5:
				TextureManager::Draw(tileset, tiles.flag_wall, dest, 0, SDL_FLIP_NONE);
				break;
			case 6:
				TextureManager::Draw(tileset, tiles.flag_wall_blue, dest, 0, SDL_FLIP_NONE);
				break;
			case 7:
				TextureManager::Draw(tileset, tiles.flag_wall_yellow, dest, 0, SDL_FLIP_NONE);
				break;
			case 8:
				TextureManager::Draw(tileset, tiles.wall_acid, dest, 0, SDL_FLIP_NONE);
				break;
			default:
				break;
			}
		}
	}
}