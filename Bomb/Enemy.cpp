#include "Enemy.hpp"

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

void Enemy::init(int i, int j) {
	anim[UP].Initialize(game_enemy_up, 4, 0.1, true);
	anim[DOWN].Initialize(game_enemy_down, 4, 0.1, true);
	anim[LEFT].Initialize(game_enemy_left, 4, 0.1, true);
	anim[RIGHT].Initialize(game_enemy_right, 4, 0.1, true);

	box[UP].Initialize(-16, -22, 32, 32);
	box[DOWN].Initialize(-16, -22, 32, 32);
	box[LEFT].Initialize(-16, -20, 34, 25);
	box[RIGHT].Initialize(-18, -20, 34, 25);

	// track tile count
	pos_i = i;
	pos_j = j;

	// real position
	x = MAP_X0 + j * TILESIZE + TILESIZE / 2;
	y = MAP_Y0 + i * TILESIZE + TILESIZE / 2;

	speed = ENEMY_SPEED;
	dir = rand() % 4;
	active = true;
	state = STATE_CHOOSING;
}

void Enemy::update(Tilemap &map, std::list<Explosion> explosion_list) {
	anim[dir].Update();
	Move(map);
	box[dir].UpdatePosition(x, y);

	// explosion
	std::list<Explosion>::iterator ex_it;
	for (ex_it = explosion_list.begin(); ex_it != explosion_list.end(); ex_it++) {
		if ((box[dir].CheckCollision((*ex_it).GetBoxY()) || box[dir].CheckCollision((*ex_it).GetBoxX()))) {
			active = false;
		}
	}
}

void Enemy::draw() {
	anim[dir].Draw(x, y - 15, 0.8, 0.8, 0.0, al_map_rgb(255, 255, 255));

	// Debug mode
	if (debug_mode) {
		al_draw_filled_circle(x, y, 3, al_map_rgb(0, 255, 0));
		al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), x + 10, y + 10, ALLEGRO_ALIGN_RIGHT, "State %d", state);
		al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), x + 10, y + 20, ALLEGRO_ALIGN_RIGHT, "Paths %d", paths_available);
	}
}

void Enemy::WalkCurrentDir() {
	if (dir == UP)
		y -= speed;
	else if (dir == DOWN)
		y += speed;
	else if (dir == LEFT)
		x -= speed;
	else if (dir == RIGHT)
		x += speed;
}

bool Enemy::OnTileCenter() {
	return ((x - MAP_X0) % (TILESIZE) == TILESIZE / 2 && (y - MAP_Y0) % (TILESIZE) == TILESIZE / 2);
}

void Enemy::CountPaths(Tilemap &map) {
	// reset
	paths_available = 0;
	for (int i = 0; i < 4; i++) {
		available_dir[i] = 0;
	}

	// check paths
	if (!map.IsPathBlocked(pos_i - 1, pos_j)) {
		paths_available++;
		available_dir[UP] = true;
	}
	if (!map.IsPathBlocked(pos_i + 1, pos_j)) {
		paths_available++;
		available_dir[DOWN] = true;
	}
	if (!map.IsPathBlocked(pos_i, pos_j - 1)) {
		paths_available++;
		available_dir[LEFT] = true;
	}
	if (!map.IsPathBlocked(pos_i, pos_j + 1)) {
		paths_available++;
		available_dir[RIGHT] = true;
	}
}

void Enemy::Move(Tilemap &map) {
	// update enemy map
	map.SetEnemyPos(pos_i, pos_j, false);
	pos_i = (y - MAP_Y0) / TILESIZE;
	pos_j = (x - MAP_X0) / TILESIZE;
	map.SetEnemyPos(pos_i, pos_j, true);

	// count # of available paths
	CountPaths(map);

	// walking
	if (state == STATE_WALKING) {
		WalkCurrentDir();

		if (OnTileCenter()) {
			// if path is blocked or reach crossroad
			if ((dir == UP && map.IsPathBlocked(pos_i - 1, pos_j))
				|| (dir == DOWN && map.IsPathBlocked(pos_i + 1, pos_j))
				|| (dir == LEFT && map.IsPathBlocked(pos_i, pos_j - 1))
				|| (dir == RIGHT && map.IsPathBlocked(pos_i, pos_j + 1))
				|| (paths_available > 2 && rand() % 100 <= 30)) {
				state = STATE_CHOOSING;
			}
		}
	}
	// choosing new path
	else {
		// all paths are blocked, can't move
		if (paths_available == 0) {
		}
		// only one path available
		else if (paths_available == 1) {
			for (int i = 0; i < 4; i++) {
				if (available_dir[i] == true) {
					dir = i;
					break;
				}
			}

			state = STATE_WALKING;
		}
		// two paths or above available
		else {
			// choose random direction instead of original path
			for (int i = rand() % 4; ; i = rand() % 4) {
				if (available_dir[i] == true && i != opposite_direction(dir)) {
					dir = i;
					break;
				}
			}

			state = STATE_WALKING;
		}
	}
}

bool Enemy::CollisionWith(Tilemap & map, int i, int j) {
	if (map.GetTileID(i, j) != GRASS)
	{
		return box[dir].CollisionWithTiles((j)*TILESIZE + MAP_X0, (i)*TILESIZE + MAP_Y0, TILESIZE, TILESIZE);
	}

	return false;
}


