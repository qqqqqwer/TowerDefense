#pragma once
#define BOARD_WIDTH 25
#define BOARD_HEIGHT 15
#define SPRITE_DIMENSION 48
#define PLAYFIELD_WIDTH 1200
#define PLAYFIELD_HEIGHT 720


enum class Purpose
{
	Ambient,
	Tower,
	BuildingPlace,
	Path,
	End,
	Start
};