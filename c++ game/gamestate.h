#pragma once

#include <string>
#include <sgg/graphics.h>

class GameState
{

	graphics::Brush m_menu_brush;

private:
	static GameState* m_unique_instance;

	const std::string m_asset_path = "assets\\";

	const float m_canvas_width = 12.0f;
	const float m_canvas_height = 6.0f;
	class Level* m_current_level = 0;
	class Player* m_player = 0;
	int m_collected_coins = 0;
	int m_coinstocollect = 0;

	GameState();

public:
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;
	int phasenum = 0;
	bool m_debugging = false;
	std::string m_name = "";
	std::string totalcoins = "";

public:
	~GameState();
	static GameState* getInstance();
	
	std::string m_phases[9] = { "MENU" , "NAME", "HELP" , "level1.txt" , "level2.txt" , "level3.txt", "level4.txt", "level5.txt", "FINISH"};
	std::string m_phase = m_phases[0];
	
	std::string m_levelname = m_phases[3];

	void loadNextLevel();
	

	bool init();
	void draw();
	void update(float dt);

	std::string getFullAssetPath(const std::string& asset);
	std::string getAssetDir();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	class Player* getPlayer() { return m_player; }
};