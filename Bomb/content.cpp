#include "content.hpp"
#include <iostream>

using namespace std;

///BITMAPS===================
ALLEGRO_BITMAP* main_bg;
ALLEGRO_BITMAP* main_title;
ALLEGRO_BITMAP* main_balloon;
ALLEGRO_BITMAP* main_airship1;
ALLEGRO_BITMAP* main_airship2;

ALLEGRO_BITMAP* UI_bar;
ALLEGRO_BITMAP* game_tile[4];

ALLEGRO_BITMAP* player_static;

ALLEGRO_BITMAP* game_enemy_up;
ALLEGRO_BITMAP* game_enemy_down;
ALLEGRO_BITMAP* game_enemy_left;
ALLEGRO_BITMAP* game_enemy_right;


ALLEGRO_BITMAP* game_brick_explosion;
/*ALLEGRO_BITMAP* game_portal;*/
ALLEGRO_BITMAP* game_player_up;
ALLEGRO_BITMAP* game_player_down;
ALLEGRO_BITMAP* game_player_left;
ALLEGRO_BITMAP* game_player_right;
ALLEGRO_BITMAP* game_bomb; // already loaded in default

ALLEGRO_BITMAP* victory_yellow;
ALLEGRO_BITMAP* victory_green;
ALLEGRO_BITMAP* victory_blue;
ALLEGRO_BITMAP* victory_orange;
ALLEGRO_BITMAP* victory_floor;
ALLEGRO_BITMAP* victory_bomberman;

ALLEGRO_BITMAP* gameover_bg;
ALLEGRO_BITMAP* gameover_animation;
ALLEGRO_BITMAP* gameover_title;
///==========================

///Fonts====================
ALLEGRO_FONT* font_debug;
ALLEGRO_FONT* font_bomberman;
ALLEGRO_FONT* font_menu;
///==========================

///Sounds======================
ALLEGRO_SAMPLE* BGM_mainmenu;
ALLEGRO_SAMPLE_ID BGM_mainmenu_id;
ALLEGRO_SAMPLE* SFX_menusound1;
ALLEGRO_SAMPLE* SFX_menusound2;

ALLEGRO_SAMPLE* BGM_gamescreen;
ALLEGRO_SAMPLE_ID BGM_gamescreen_id;
ALLEGRO_SAMPLE* SFX_put_bomb;
ALLEGRO_SAMPLE* SFX_explosion;
ALLEGRO_SAMPLE* SFX_pick_upgrade;

ALLEGRO_SAMPLE* BGM_victory;
ALLEGRO_SAMPLE_ID BGM_victory_id;

ALLEGRO_SAMPLE* BGM_gameover;
ALLEGRO_SAMPLE_ID BGM_gameover_id;
///==========================


//=================================
//DEFAULT
//=================================
void LoadDefaultContent()
{
	// BITMAPS
	game_bomb = al_load_bitmap("Sprites/GAMESCREEN/bomb.png");

	// Fonts
	font_debug = al_load_ttf_font("Fonts/debug.ttf", 10, ALLEGRO_TTF_MONOCHROME);
	font_bomberman = al_load_ttf_font("Fonts/bomberman.ttf", 45, ALLEGRO_TTF_MONOCHROME);
	font_menu = al_load_ttf_font("Fonts/menu.ttf", 30, ALLEGRO_TTF_MONOCHROME);


	// Sounds
	SFX_menusound1 = al_load_sample("Sounds/SFX/menusound1.wav");
	SFX_menusound2 = al_load_sample("Sounds/SFX/menusound2.wav");
}

void UnloadDefaultContent()
{
	// BITMAPS
	al_destroy_bitmap(game_bomb);

	// Fonts
	al_destroy_font(font_debug);
	al_destroy_font(font_bomberman);
	al_destroy_font(font_menu);

	// Sounds
	al_destroy_sample(SFX_menusound1);
	al_destroy_sample(SFX_menusound2);
}

//=================================
//MAINMENU
//=================================
void LoadMainmenuContent()
{
	//BITMAPS
	main_bg = al_load_bitmap("Sprites/MAINMENU/bg.png");
	main_title = al_load_bitmap("Sprites/MAINMENU/title.png");
	main_balloon = al_load_bitmap("Sprites/MAINMENU/balloon.png");
	main_airship1 = al_load_bitmap("Sprites/MAINMENU/airship1.png");
	main_airship2 = al_load_bitmap("Sprites/MAINMENU/airship2.png");

	//SOUNDS
	BGM_mainmenu = al_load_sample("Sounds/BGM/mainmenu.ogg");

	cout << "main menu content loaded" << endl;
}

void UnloadMainmenuContent()
{
	//BITMAPS
	al_destroy_bitmap(main_bg);
	al_destroy_bitmap(main_title);
	al_destroy_bitmap(main_balloon);
	al_destroy_bitmap(main_airship1);
	al_destroy_bitmap(main_airship2);

	// Sounds
	al_destroy_sample(BGM_mainmenu);
	cout << "main menu content destroyed" << endl;
}


//=================================
//GAMESCREEN
//=================================
void LoadGameSceneContent()
{
	//BITMAPS
	/// UI bar
	UI_bar = al_load_bitmap("Sprites/GAMESCREEN/UI_bar.png");
	/// Tilemaps
	game_tile[0] = al_load_bitmap("Sprites/GAMESCREEN/tiles/grass.png");
	game_tile[1] = al_load_bitmap("Sprites/GAMESCREEN/tiles/brick.png");
	game_tile[2] = al_load_bitmap("Sprites/GAMESCREEN/tiles/block.png");
	game_tile[3] = game_tile[0];

    player_static = al_load_bitmap("Sprites/GAMESCREEN/player_static.png");

	/// Enemy
	game_enemy_up = al_load_bitmap("Sprites/GAMESCREEN/enemy_up.png");
	game_enemy_down = al_load_bitmap("Sprites/GAMESCREEN/enemy_down.png");
	game_enemy_left = al_load_bitmap("Sprites/GAMESCREEN/enemy_left.png");
	game_enemy_right = al_load_bitmap("Sprites/GAMESCREEN/enemy_right.png");


	game_brick_explosion = al_load_bitmap("Sprites/GAMESCREEN/tiles/brick explosion.png");
	/*game_portal = al_load_bitmap("Sprites/GAMESCREEN/portal.png");*/
	game_player_up = al_load_bitmap("Sprites/GAMESCREEN/player up.png");
	game_player_down = al_load_bitmap("Sprites/GAMESCREEN/player down.png");
	game_player_left = al_load_bitmap("Sprites/GAMESCREEN/player left.png");
	game_player_right = al_load_bitmap("Sprites/GAMESCREEN/player right.png");

	//Sounds
	BGM_gamescreen = al_load_sample("Sounds/BGM/gamescreen.ogg");
	SFX_put_bomb = al_load_sample("Sounds/SFX/put bomb.wav");
	SFX_explosion = al_load_sample("Sounds/SFX/explosion.wav");
}

void UnloadGameSceneContent()
{
	// BITMAPS
	/// UI bar
	al_destroy_bitmap(UI_bar);
	/// Tilemaps
	al_destroy_bitmap(game_tile[0]);
	al_destroy_bitmap(game_tile[1]);
	al_destroy_bitmap(game_tile[2]);

	///Enemy
	al_destroy_bitmap(game_enemy_up);
	al_destroy_bitmap(game_enemy_down);
	al_destroy_bitmap(game_enemy_left);
	al_destroy_bitmap(game_enemy_right);

	al_destroy_bitmap(game_brick_explosion);
	/*al_destroy_bitmap(game_portal);

	al_destroy_bitmap(game_barra_superior);*/
	al_destroy_bitmap(player_static);

	al_destroy_bitmap(game_player_up);
	al_destroy_bitmap(game_player_down);
	al_destroy_bitmap(game_player_left);
	al_destroy_bitmap(game_player_right);

	//Sounds
	al_destroy_sample(BGM_gamescreen);
	al_destroy_sample(SFX_put_bomb);
	al_destroy_sample(SFX_explosion);

}


//=================================
//GAMEOVER
//=================================
void LoadGameoverContent()
{
	//BITMAPS
	gameover_bg = al_load_bitmap("Sprites/GAMEOVER/bg.png");
	gameover_title = al_load_bitmap("Sprites/GAMEOVER/title.png");
	gameover_animation = al_load_bitmap("Sprites/GAMEOVER/animation.png");

	//Sounds
	BGM_gameover = al_load_sample("Sounds/BGM/gameover.ogg");
}

void UnloadGameoverContent()
{
	//BITMAPS
	al_destroy_bitmap(gameover_bg);
	al_destroy_bitmap(gameover_animation);
	al_destroy_bitmap(gameover_title);

	//Sounds
	al_destroy_sample(BGM_gameover);
}

//=================================
//VICTORY
//=================================
void LoadVictoryContent()
{
	//BITMAPS
	victory_yellow = al_load_bitmap("Sprites/VICTORY/yellow.png");
	victory_green = al_load_bitmap("Sprites/VICTORY/green.png");
	victory_blue = al_load_bitmap("Sprites/VICTORY/blue.png");
	victory_orange = al_load_bitmap("Sprites/VICTORY/orange.png");
	victory_floor = al_load_bitmap("Sprites/VICTORY/floor.png");
	victory_bomberman = al_load_bitmap("Sprites/VICTORY/bomberman.png");

	//Sounds
	BGM_victory = al_load_sample("Sounds/BGM/victory.ogg");
}

void UnloadVictoryContent()
{
	//BITMAPS
	al_destroy_bitmap(victory_yellow);
	al_destroy_bitmap(victory_green);
	al_destroy_bitmap(victory_blue);
	al_destroy_bitmap(victory_orange);
	al_destroy_bitmap(victory_floor);
	al_destroy_bitmap(victory_bomberman);

	//Sounds
	al_destroy_sample(BGM_victory);
}


