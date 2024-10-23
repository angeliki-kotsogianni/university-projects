#include "gamestate.h"
#include "level.h"
#include "player.h"
#include <thread>
#include <chrono>
#include "util.h"
using namespace std::chrono_literals;

GameState::GameState()
{
}

GameState::~GameState()
{
	if (m_current_level)
		delete m_current_level;
}

GameState* GameState::getInstance()
{
	if (!m_unique_instance)
	{
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

void GameState::loadNextLevel()
{
	phasenum += 1;
	m_phase = m_phases[phasenum];
	m_coinstocollect += m_current_level->m_coinstocoll;
	m_collected_coins += m_current_level->m_collcoins;
	if (phasenum != 8) {
		m_levelname = m_phase;

		delete m_current_level;

		
		m_current_level = new Level(m_levelname);
		m_current_level->init();
	}
	else {
		totalcoins = std::to_string(m_collected_coins) + "/" + std::to_string(m_coinstocollect);
		draw();
	}
	
}

bool GameState::init()
{
	graphics::playMusic(getFullAssetPath("spacemusic.mp3"), 1.0f, true, 0);
	m_current_level = new Level(m_levelname);
	m_current_level->init();

	m_player = new Player("Player");
	m_player->init();

	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");

	return true;
}


void GameState::draw()
{
	if (m_phase == m_phases[0]) {
		graphics::Brush textBrush;
		graphics::Brush textBrush1;
		float p = 0.3 + fabs(cos(graphics::getGlobalTime() / 500));
		graphics::setFont(m_asset_path + "slkscr.ttf");
		SETCOLOR(textBrush.fill_color, p, p, p);
		SETCOLOR(textBrush.outline_color, 0, 0, 0);
		SETCOLOR(textBrush1.fill_color, 1, 1, 1);
		SETCOLOR(textBrush1.outline_color, 0, 0, 0);
		textBrush.fill_opacity = 1.0f;
		textBrush.outline_opacity = 1.0f;
		textBrush1.fill_opacity = 1.0f;
		textBrush1.outline_opacity = 1.0f;
		m_menu_brush.outline_opacity = 0.0f;
		m_menu_brush.texture = getFullAssetPath("space.png");
		graphics::drawRect(m_canvas_width * 0.5f, m_canvas_height * 0.5f, m_canvas_width, m_canvas_height, m_menu_brush);
		graphics::drawText(getCanvasWidth() * 0.5f - 2.5f, getCanvasHeight() * 0.5f + 1.5f, 0.4f, "Press SPACE to start the game", textBrush);
		graphics::drawText(getCanvasWidth() * 0.5f - 1.9f, getCanvasHeight() * 0.5f - 0.5f, 0.7f, "SpaceRunner", textBrush1);
		graphics::drawText(getCanvasWidth() * 0.5f - 5.0f, getCanvasHeight() * 0.5f + 3.0f, 0.5f, "H-HELP", textBrush1);
	}
	else if (m_phase == m_phases[1]) {
		graphics::Brush textBrush1;
		graphics::setFont(m_asset_path + "slkscr.ttf");
		SETCOLOR(textBrush1.outline_color, 0, 0, 0);
		textBrush1.fill_opacity = 1.0f;
		textBrush1.outline_opacity = 1.0f;
		m_menu_brush.outline_opacity = 0.0f;
		m_menu_brush.texture = getFullAssetPath("nameinput.png");
		graphics::drawRect(m_canvas_width * 0.5f, m_canvas_height * 0.5f, m_canvas_width, m_canvas_height, m_menu_brush);
		graphics::drawText(getCanvasWidth() * 0.5f - 2.2f, getCanvasHeight() * 0.5f + 1.5f, 0.4f, "Press ENTER to continue", textBrush1);
		graphics::drawText(getCanvasWidth() * 0.5f - 2.5f, getCanvasHeight() * 0.5f - 0.5f, 0.7f, "Enter your name:", textBrush1);
		graphics::drawText(getCanvasWidth() * 0.5f - 2.0f, getCanvasHeight() * 0.5f + 0.5f, 0.5f, m_name, textBrush1);
	}
	else if (m_phase == m_phases[2]) {
		m_menu_brush.texture = getFullAssetPath("help.png");
		graphics::drawRect(m_canvas_width * 0.5f, m_canvas_height * 0.5f, m_canvas_width, m_canvas_height, m_menu_brush);
	}
	else if (m_phase == m_phases[8]) {
		graphics::Brush textBrush;
		graphics::setFont(m_asset_path + "slkscr.ttf");
		SETCOLOR(textBrush.outline_color, 0, 0, 0);
		textBrush.fill_opacity = 1.0f;
		textBrush.outline_opacity = 1.0f;
		std::string finishtext;
		if (m_collected_coins <= m_coinstocollect * 1 / 3) {
			m_menu_brush.texture = getFullAssetPath("worstfinish.png");
			finishtext = "Very few coins. You fell into a black hole...";
		}
		else if (m_collected_coins <= m_coinstocollect * 2 / 3) {
			m_menu_brush.texture = getFullAssetPath("mediumfinish.png");
			finishtext = "Not enough coins. You returned back to earth";
		}
		else {
			m_menu_brush.texture = getFullAssetPath("bestfinish.png");
			finishtext = "Well done! You made it to the other dimension";
		}
		float p = 0.3 + fabs(cos(graphics::getGlobalTime() / 500));
		SETCOLOR(textBrush.fill_color, p, p, p);
		SETCOLOR(m_menu_brush.fill_color, p, p, p);
		graphics::drawRect(m_canvas_width * 0.5f, m_canvas_height * 0.5f, m_canvas_width, m_canvas_height, m_menu_brush);
		graphics::drawText(getCanvasWidth() * 0.5f - 0.5f, getCanvasHeight() * 0.5f + 2.0f, 0.7f, totalcoins, textBrush);
		graphics::drawText(getCanvasWidth() * 0.5f - 4.7f, getCanvasHeight() * 0.5f - 1.5f, 0.5f, finishtext, textBrush);
	}
	else {
		if (!m_current_level)
			return;
		m_current_level->draw();
	}

}

void GameState::update(float dt)
{

	if (m_phase == m_phases[0]) {
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			m_phase = m_phases[1];
			phasenum = 1;
		}
		if (graphics::getKeyState(graphics::SCANCODE_H)) {
			m_phase = m_phases[2];
			phasenum = 2;
		}
	}
	else if (m_phase == m_phases[1]) {
		static bool prevKeyState[256] = { false };

		for (int i = 4; i <= 29; ++i) {
			bool currKeyState = graphics::getKeyState(static_cast<graphics::scancode_t>(i));

			if (currKeyState && !prevKeyState[i]) {
				if (m_name.size() < 15) {
					m_name += static_cast<char>('A' + (i - 4));
				}
			}

			prevKeyState[i] = currKeyState;
		}

		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) { 
			m_name = m_name ;
		}

		bool backspaceKeyState = graphics::getKeyState(graphics::SCANCODE_BACKSPACE);
		if (backspaceKeyState && !prevKeyState[graphics::SCANCODE_BACKSPACE]) {
			if (!m_name.empty()) {
				m_name.pop_back();
			}
		}
		prevKeyState[graphics::SCANCODE_BACKSPACE] = backspaceKeyState;

		if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
			graphics::stopMusic();
			m_phase = m_phases[3];
			phasenum = 3;
			graphics::playMusic(getFullAssetPath("levelsmusic.mp3"), 1.0f, true, 0);
		}
	}
	else if (m_phase == m_phases[2]) {
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			m_phase = m_phases[1];
			phasenum = 1;
		}
	}
	else if (m_phase != m_phases[0] && m_phase != m_phases[1] && m_phase != m_phases[2] && m_phase != m_phases[8]) {
		// Skip an update if a long delay is detected 
		// to avoid messing up the collision simulation
		if (dt > 500) // ms
			return;
					// Avoid too quick updates
		float sleep_time = std::max(17.0f - dt, 0.0f);
		if (sleep_time > 0.0f)
		{
			std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
		}
		if (!m_current_level)
			return;
		m_global_offset_x += 0.1f * dt / 1000.0f;
		m_current_level->update(dt);
		m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
		
	}
}

std::string GameState::getFullAssetPath(const std::string & asset)
{
	return m_asset_path + asset;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

GameState* GameState::m_unique_instance = nullptr;