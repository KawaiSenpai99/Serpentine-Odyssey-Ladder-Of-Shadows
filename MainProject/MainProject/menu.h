#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#define ScreenWidth 1200
#define ScreenHeight 600
#include "diceboard.h"

//-------------------------------Menu Buttons Booleans -------------------------------------------


bool menuPage = true;
bool startPage = false;
bool scorePage = false;
bool controlPage = false;
bool aboutPage = false;
bool diceBoardMenu = false;
bool roomPage = false;
bool gameOverPage = false;

//--------------------------------Menu button handler  -------------------------------------------

void menuPageHandler()
{
	menuPage = true;
	startPage = false;
	scorePage = false;
	controlPage = false;
	aboutPage = false;
	diceBoardMenu = false;
	roomPage = false;
	gameOverPage = false;
}

void diceBoardHandler()
{
	menuPage = false;
	startPage = false;
	scorePage = false;
	controlPage = false;
	aboutPage = false;
	diceBoardMenu = true;
	roomPage = false;
	snakeAlive = true;
	snakeLife = 3;
	gameOverPage = false;
}

void startPageHandler()
{
	menuPage = false;
	startPage = true;
	scorePage = false;
	controlPage = false;
	aboutPage = false;
	diceBoardMenu = false;
	roomPage == false;
	gameOverPage = false;
}

void scorePageHandler()
{
	menuPage = false;
	startPage = false;
	scorePage = true;
	controlPage = false;
	aboutPage = false;
	diceBoardMenu = false;
	roomPage = false;
	gameOverPage = false;
}

void controlPageHandler()
{
	menuPage = false;
	startPage = false;
	scorePage = false;
	controlPage = true;
	aboutPage = false;
	diceBoardMenu = false;
	roomPage = false;
	gameOverPage = false;
}

void aboutPageHandler()
{
	menuPage = false;
	startPage = false;
	scorePage = false;
	controlPage = false;
	aboutPage = true;
	diceBoardMenu = false;
	roomPage = false;
	gameOverPage = false;
}
void roomPageHandler()
{
	menuPage = false;
	startPage = false;
	scorePage = false;
	controlPage = false;
	aboutPage = false;
	diceBoardMenu = false;
	roomPage = true;
	gameOverPage = false;
}

void gameOverPageHandler()
{
	menuPage = false;
	startPage = false;
	scorePage = false;
	controlPage = false;
	aboutPage = false;
	diceBoardMenu = false;
	roomPage = false;
	gameOverPage = true;
}


#endif // !MENU_H_INCLUDED
