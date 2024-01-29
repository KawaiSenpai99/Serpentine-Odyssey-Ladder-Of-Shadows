#ifndef DICEBOARD_H_INCLUDED
#define DICEBOARD_H_INCLUDED
//#include <ctime>
#include "menu.h"
//--------------Variables-----------------

int boardMoveCounter = 1;
int animeIndex = 0;
int roomAnimeIndex = 0;
int boardy = 0;
int animeBoardX = 0;
int animeBoardY = 0;
int diceIndex;
int diceRoll;
int totalRoll = 0;
int roomIndex = 0;
bool rollDice = true;

int snakeX = 800;
int snakeY = 100;
int snakeVenomX;
int snakeVenomY;
int snakeLife = 3;
bool snakeAlive = true;
bool venomThrow = true;
bool charInit = true;

bool check = true;


//---------------FUNCTIONS-------------------

void ran()
{
	//time_t now = time(0);
	int gen = rand() % 100;
	diceIndex = (/*now * */ gen) % 6;
	diceRoll = diceIndex + 1;
	totalRoll += diceRoll;
}

void diceBoardMenuInitialize()
{
	boardMoveCounter = 1;
	animeIndex = 0;
	boardy = 0;
	animeBoardX = 0;
	animeBoardY = 0;
	totalRoll = 0;
}

void boardAnimeMove(){

	for (int i = 0; i < diceRoll; i++)
	{
		if (totalRoll>=20)
		{
			totalRoll -= diceRoll;
			diceRoll = 0;
		}
		else if ((animeBoardX >= 832 && boardMoveCounter == 1) || (animeBoardX <= 0 && boardMoveCounter == (-1)))
		{
			animeBoardY += 208;
			boardMoveCounter *= (-1);


		}
		else
		{
			animeBoardX += boardMoveCounter * 208;
		}


	}
}

void boardAnimeChange(){
	animeIndex++;
	if (animeIndex >= 4)
	{
		animeIndex = 0;
	}
}

void roomAnimeChange(){
	roomAnimeIndex++;
	if (roomAnimeIndex >= 4)
	{
		roomAnimeIndex = 0;
	}
}

void snakeVenomInitialize()
{
	snakeVenomX = snakeX;
	snakeVenomY = snakeY +(285/2);
}



void room(){
	if (totalRoll % 4 == 0)
		roomIndex = 1;
	else if (totalRoll % 4 == 1)
		roomIndex = 2;
	else if (totalRoll % 4 == 2)
		roomIndex = 3;
	else if (totalRoll % 4 == 3)
		roomIndex = 0;
}

#endif // !DICEBOARD_H_INCLUDED
