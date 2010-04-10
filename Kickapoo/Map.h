#pragma once
#include "Common.h"

static const int BLOCK_SIZE = 25;

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
		return y * width + x;
	}

	void loadContent(vector<Player>& playerList, vector<Tower>& towerList);

public:
	string map;
	vector<float> blockRandom;

	int width;
	int height;
	Texture* wall;
	Texture* tower;
};