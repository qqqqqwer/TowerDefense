#pragma once
#define BOARD_WIDTH 25 //How mane squares are in one horizontal line
#define BOARD_HEIGHT 15 //Squares in vertical column
#define SPRITE_DIMENSION 48 //Square's dimension
#define PLAYFIELD_WIDTH 1200 //Playable field's width in pixels
#define PLAYFIELD_HEIGHT 720 //Playable field's height in pixels
#define WAVE_TIME 10 //Seconds between waves 
#define STARTING_WAVE_SIZE 5 //Enemies in 
#define FRAMERATE 1000 / 60 //Frame rate
#define PAUSE_MENU_WIDTH 700 //
#define PAUSE_MENU_HEIGHT 400 // 
#define RANGE_CONVERSION 10 //
#define STARTING_MONEY 1000

namespace constants {

	enum class Purpose
	{
		Ambient,
		Tower,
		BuildingPlace,
		Path,
		End,
		Start
	};

	enum class GameState {

		InGame,
		Menu
	};
}
