#pragma once
#include "Common.h"

static const int BLOCK_SIZE = 20;

class Player;
class Tower;

class Map
{
public:
	Map();

	~Map();

	static Map* load(const std::string& name);

	void update();

	void draw();

	void fill();
	void fill_r(int x, int y, float dt);

	int index(int x, int y) const {
		if(y >= height || y < 0 || x >= width || x <= 0)
			return 0;
		return y * width + x;
	}

	bool blocked(int x, int y, bool withTower = true) const;

	bool collides(const D3DXVECTOR2& v) const;

	D3DXVECTOR2 slide(const D3DXVECTOR2& a, const D3DXVECTOR2& );

	void loadContent(vector<Player>& playerList, vector<Tower>& towerList);

public:
	string map;
	vector<Tower*> towerListMapped;
	vector<float> blockRandom;

	int width;
	int height;
	Texture* wall;
	Texture* tower;
	Texture* tower2;
	Texture* tower_death;
	Texture* playerTexture;
	Texture* playerSelected;
	Texture* player2Texture;
	Texture* player2Selected;
};