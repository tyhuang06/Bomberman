#include "Tilemap.hpp"
#include <iostream>

using namespace std;

Tilemap::Tilemap() {
}

Tilemap::~Tilemap() {
}

void Tilemap::init() {
	map_txt = fopen("Txt_files/map.txt", "r");
	if (!map_txt) {
		cout << "map.txt failed loading" << endl;
	}

	if (map_txt) {
		for (int i = 0; i < TILES_H; i++) {
			for (int j = 0; j < TILES_W; j++) {
				fscanf(map_txt, "%d", &map[i][j]);
				bomb_map[i][j] = 0;
			}
		}
	}
}

void Tilemap::draw() {
	for (int i = 0; i < TILES_H; i++) {
		for (int j = 0;j < TILES_W; j++) {
			al_draw_bitmap(game_tile[map[i][j]], MAP_X0 + j * TILESIZE, MAP_Y0 + i * TILESIZE, 0);
		}
	}
}

int Tilemap::GetTileID(int i, int j) {
	return map[i][j];
}

int Tilemap::GetEnemyPos(int i, int j) {
	return enemy_map[i][j];
}

void Tilemap::SetEnemyPos(int i, int j, bool value) {
	enemy_map[i][j] = value;
}
int Tilemap::GetBombPos(int i, int j){
    return bomb_map[i][j];
}

void Tilemap::SetBombPos(int i, int j, bool value){
    bomb_map[i][j] = value;
}

// should also handle player postion / bomb position in the future
bool Tilemap::IsPathBlocked(int i, int j) {
	return (GetTileID(i, j) != GRASS || GetEnemyPos(i, j) == 1 || GetBombPos(i, j) == 1);
}
