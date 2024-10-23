#pragma once

#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "player.h"

class Level : public GameObject
{
	graphics::Brush m_brush_background;

	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;

	// add some collidable blocks
	std::vector<Box> m_blocks;
	std::vector<Box> m_blocks_enemy;
	std::vector<std::string> m_block_enemy_names;
	std::vector<std::string> m_block_names;
	const float m_block_size = 1.0f;
	const float m_coin_size = 0.7f;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;
	graphics::Brush m_coin_brush;
	graphics::Brush m_coin_brush_debug;
	graphics::Brush textBrush;
	graphics::Brush m_flag_brush;
	graphics::Brush m_flag_brush_debug;
	graphics::Brush m_explosion_brush;
	const float m_background_size = 5.0f;
	int attempt = 0;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;
	std::vector<Box> m_initialBlockPositions;
	std::vector<Box> m_initialBlockPositions1;
	std::vector<Box> m_initialBackgroundPosition;
	std::vector<Box> m_initialCoinsPosition;
	std::vector<Box> m_backgrounds;
	std::vector<Box> m_coins;
	std::vector<Box> m_explosions;
	std::vector<std::string> m_explosion_names = { "explosion0.png", "explosion1.png", "explosion2.png", "explosion3.png", "explosion4.png", "explosion5.png" };
	std::vector<std::string> m_coins_names;
	std::vector<std::string> m_background_name;
	Box m_flag = Box(0, 5, 0.5, 2);
	Box m_initial_flag = Box(30, 5, 0.5, 2);
	std::string m_arr[3];
	int m_obst;
	float m_speed;
	int m_level = 1;

	// dedicated method to draw a block
	void drawBlock(int i);
	void drawBackground(int i);
	void drawWinningFlag();
	void drawCoins(int i);

	void drawBlock1(int i);
	void drawExplosions(float x, float y, int i);

	// detect collisions
	void checkCollisions();



private:	
	float m_background_position_x;
	float m_background_speed;
	float m_totalElapsedTime;  // Add this line to store the total elapsed time

public:
	int m_collcoins = 0;
	int m_coinstocoll = 0;


public:
	void update(float dt) override;
	void moveBackground(float dt);
	void draw() override;
	void init() override;
	void reset();
	Level(std::string& name);
	~Level() override;
};
