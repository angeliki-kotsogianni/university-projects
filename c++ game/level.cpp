#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "util.h"
#include <iostream>
#include <fstream>


void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	std::string& name = m_block_names[i];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	m_block_brush.texture = m_state->getFullAssetPath(name);

	graphics::drawRect(x, y, 2.5f * m_block_size, 2.5f * m_block_size, m_block_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);
}

void Level::drawWinningFlag()
{
	m_flag_brush.outline_opacity = 0.0f;
	m_flag_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_flag_brush.outline_color, 0.0f, 1.0f, 1.0f);
	SETCOLOR(m_flag_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_flag_brush_debug.outline_color, 0.2f, 1.0f, 1.0f);

	m_flag_brush.texture = m_state->getFullAssetPath("flag.png");


	m_flag.m_pos_x = m_blocks_enemy[m_blocks_enemy.size() - 1].m_pos_x + 6.0f;

	float x = m_flag.m_pos_x + m_state->m_global_offset_x;
	float y = m_flag.m_pos_y + m_state->m_global_offset_y;

	graphics::drawRect(x, y, m_flag.m_width, m_flag.m_height, m_flag_brush);

	if (m_state->m_debugging)
		graphics::drawRect(m_flag.m_pos_x, m_flag.m_pos_y, m_flag.m_width, m_flag.m_height, m_flag_brush_debug);
}

void Level::drawBackground(int i)
{
	Box& box = m_backgrounds[i];
	std::string& name = m_background_name[i];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	m_brush_background.texture = m_state->getFullAssetPath(name);

	graphics::drawRect(x, y, 1.8f * m_background_size, 1.8f * m_background_size, m_brush_background);

}

void Level::drawBlock1(int i)
{
	Box& box = m_blocks_enemy[i];
	std::string& name = m_block_enemy_names[i];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	m_block_brush.texture = m_state->getFullAssetPath(name);

	graphics::drawRect(x, y, 1.8f * m_block_size, 1.8f * m_block_size, m_block_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);

}

void Level::drawExplosions(float x, float y, int i){ //afto den leiturgei...
	Box& box = m_explosions[i];
	std::string& name = m_explosion_names[i];

	m_explosion_brush.texture = m_state->getFullAssetPath(name);

	graphics::drawRect(x, y, 5.0f, 5.0f, m_explosion_brush);
}

void Level::drawCoins(int i)
{
	Box& box = m_coins[i];
	std::string& name = m_coins_names[i];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	m_coin_brush.texture = m_state->getFullAssetPath(name);

	graphics::drawRect(x, y, m_coin_size, m_coin_size, m_coin_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_coin_size, m_coin_size, m_coin_brush_debug);

}

void Level::checkCollisions()
{

	float offset = 0.0f;
	if (offset = m_state->getPlayer()->intersect(m_flag)) {
		m_state->loadNextLevel();
		return;
	}

	for (auto& block : m_blocks_enemy)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block))
		{
			m_state->getPlayer()->m_pos_y += offset;

			// add sound event
			if (m_state->getPlayer()->m_vy >= 0.0f) {

				for (auto& explosion : m_explosions) {
					explosion.setActive(true);
					explosion.m_pos_x = m_state->getPlayer()->m_vx;
					explosion.m_pos_y = m_state->getPlayer()->m_vy;
					draw();
				}
				
				graphics::playSound(m_state->getFullAssetPath("Metal2.wav"), 1.0f);
				Level::reset();
				return;



			}


			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}
	}


	for (auto& block : m_blocks_enemy)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(block))
		{
			m_state->getPlayer()->m_pos_x += offset;

			if (m_state->getPlayer()->m_vx <= 0.0f) {
				for (auto& explosion : m_explosions) {
					explosion.setActive(true);
					explosion.m_pos_x = m_state->getPlayer()->m_vx;
					explosion.m_pos_y = m_state->getPlayer()->m_vy;
					draw();
				}
				
				graphics::playSound(m_state->getFullAssetPath("Metal2.wav"), 1.0f);
				Level::reset();
				return;

			}


			m_state->getPlayer()->m_vx = 0.0f;

			break;
		}

	}

	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(block))
		{
			m_state->getPlayer()->m_pos_x += offset;


			m_state->getPlayer()->m_vx = 0.0f;

			break;
		}

	}

	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block))
		{
			m_state->getPlayer()->m_pos_y += offset;


			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}
	}

	for (auto& coin : m_coins)
	{
		if (coin.isActive1() && m_state->getPlayer()->intersect(coin))
		{
			// Player collided with a coin
			coin.setActive(false); // Mark the coin as collected
			// Add logic for collecting the coin, like increasing the player's score
			// You can also play a sound effect here
			m_collcoins += 1;
			graphics::playSound(m_state->getFullAssetPath("collect.wav"), 1.0f);
		}
	}





}

void Level::reset()
{

	attempt++;
	m_collcoins = 0;
	for (auto& explosion : m_explosions) {
		explosion.setActive(false);
	}
	m_state->getPlayer()->m_pos_x = 5.0f;
	m_state->getPlayer()->m_pos_y = 5.0f;
	m_state->getPlayer()->m_vx = 0.0f;
	m_state->getPlayer()->m_vy = 0.0f;
	m_state->getPlayer()->m_rotation = 0.0f;
	for (size_t i = 0; i < m_blocks.size(); ++i) {
		m_blocks[i].m_pos_x = m_initialBlockPositions[i].m_pos_x;
		m_blocks[i].m_pos_y = m_initialBlockPositions[i].m_pos_y;
	}

	for (size_t i = 0; i < m_coins.size(); ++i) {
		m_coins[i].m_pos_x = m_initialCoinsPosition[i].m_pos_x;
		m_coins[i].m_pos_y = m_initialCoinsPosition[i].m_pos_y;
		m_coins[i].setActive(true);
	}

	for (size_t i = 0; i < m_blocks_enemy.size(); ++i) {
		m_blocks_enemy[i].m_pos_x = m_initialBlockPositions1[i].m_pos_x;
		m_blocks_enemy[i].m_pos_y = m_initialBlockPositions1[i].m_pos_y;
	}

	for (size_t i = 0; i < m_backgrounds.size(); ++i) {
		m_backgrounds[i].m_pos_x = m_initialBackgroundPosition[i].m_pos_x;
		m_backgrounds[i].m_pos_y = m_initialBackgroundPosition[i].m_pos_y;
	}

	m_flag.m_pos_x = m_initial_flag.m_pos_x;
	m_flag.m_pos_y = m_initial_flag.m_pos_y;

	draw();

}

void Level::update(float dt)
{

	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

	for (auto& backgr : m_backgrounds) {
		backgr.m_pos_x -= m_background_speed * dt / 50.0f;
	}

	for (auto& block : m_blocks) {
		block.m_pos_x -= m_background_speed * dt / 50.0f;
	}

	for (auto& block : m_blocks_enemy) {
		block.m_pos_x -= m_background_speed * dt / 50.0f;
	}

	for (auto& block : m_coins) {
		block.m_pos_x -= m_background_speed * dt / 50.0f;
	}

	m_flag.m_pos_x -= m_background_speed * dt / 50.0f;

	checkCollisions();

	GameObject::update(dt);
}


void Level::draw()
{
	graphics::setFont("assets//slkscr.ttf");
	SETCOLOR(textBrush.fill_color, 1, 1, 1);
	SETCOLOR(textBrush.outline_color, 0, 0, 0);
	std::string attemptStr = std::to_string(attempt);
	graphics::drawText(1.0f, 1.0f, 0.4f, "Attempt: " + attemptStr, textBrush);
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();
	float offset_x = m_state->m_global_offset_x / 2.0 + w / 2.0f;
	float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

	for (int i = 0; i < m_backgrounds.size(); i++)
	{
		drawBackground(i);
	}
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();



	drawWinningFlag();



	for (int i = 0; i < m_blocks_enemy.size(); i++)
	{
		drawBlock1(i);
	}
	for (int i = 0; i < m_blocks.size(); i++)
	{
		drawBlock(i);
	}


	for (int i = 0; i < m_coins.size(); i++)
	{
		if (m_coins[i].isActive1())
		{
			drawCoins(i);
		}
	}

	for (int i = 0; i < m_explosions.size(); i++)
	{
		if (m_explosions[i].isActive1())
		{
			drawExplosions(m_state->getPlayer()->m_pos_x, m_state->getPlayer()->m_pos_y, i);
			m_explosions[i].setActive(false);
		}
	}

}

void Level::init()
{
	// Stage 1
	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();


	// initialize some collidable blocks here.
	// normally, you should build a Block class 
	// and automate the process more.
	m_obst = std::stoi(m_arr[1]);
	for (int i = -5; i < 10 + (m_obst - 1) * 8 + 10; i++) {
		m_blocks.push_back(Box(i, 6, 1, 1));
		m_block_names.push_back("block1.png");
	}


	float x = m_state->getCanvasWidth();
	float y = m_state->getCanvasHeight();

	int i = 0;
	while (i < (10 + (m_obst - 1) * 8 + 12)) {
		m_backgrounds.push_back(Box(i, 4, x, y));
		i += 9;
		m_background_name.push_back(m_arr[0]);
	}

	i = 10;
	y = 3.7f;
	while (i < 10 + (m_obst-1) * 8 + 1) {
		m_blocks_enemy.push_back(Box(i, 4.7, 0.5, 0.5));
		m_coins.push_back(Box(i + 3, y, 0.05, 0.05));
		i += 8;
	}


	std::string name;
	std::string img;
	bool fl = false;
	int imgn = 1;
	for (int i = 1; i <= m_obst; i++) {
		if (fl == false) {
			img = "image";
			fl = true;
		}
		else {
			img = "imagee";
			fl = false;
		}
		name = img + std::to_string(imgn) + ".png";
		m_block_enemy_names.push_back(name);
		imgn += 1;
		if (imgn == 4)
			imgn = 1;
		m_coins_names.push_back("coin.png");
	}

	for (int i = 0; i < 6; i++) {
		m_explosions.push_back(Box(0.0f, 0.0f, 5.0, 5.0));
		m_explosions[i].setActive(false);
	}

	m_initialBlockPositions1 = m_blocks_enemy;

	m_initialBackgroundPosition = m_backgrounds;
	m_initialCoinsPosition = m_coins;






	m_initialBlockPositions = m_blocks;


	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush.outline_color, 0.0f, 1.0f, 1.0f);
	SETCOLOR(m_block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.2f, 1.0f, 1.0f);

	m_coin_brush.outline_opacity = 0.0f;
	m_coin_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_coin_brush.outline_color, 0.0f, 1.0f, 1.0f);
	SETCOLOR(m_coin_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_coin_brush_debug.outline_color, 0.2f, 1.0f, 1.0f);
}

Level::Level(std::string& name)
	: GameObject(name)
{
	std::ifstream file(m_state->getFullAssetPath(name));

	if (!file.is_open()) {
		std::cerr << "Failed to open the file." << name << std::endl;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) continue;

		line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

		size_t pos = line.find('=');

		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1);

		value.erase(0, value.find_first_not_of(" \t\r\n"));
		value.erase(value.find_last_not_of(" \t\r\n") + 1);


		if (key == "background")
			m_arr[0] = value;
		else if (key == "obstacles")
			m_arr[1] = value;
		else if (key == "speed")
			m_arr[2] = value;
	}

	file.close();


	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath(m_arr[0]);
	m_explosion_brush.outline_opacity = 0.0f;

	m_speed = std::stof(m_arr[2]);
	m_background_speed = m_speed;
	m_background_position_x = 0.0f;
	m_coinstocoll += std::stoi(m_arr[1]);


}

Level::~Level()
{
	for (auto p_go : m_static_objects)
		delete p_go;
	for (auto p_go : m_dynamic_objects)
		delete p_go;
}