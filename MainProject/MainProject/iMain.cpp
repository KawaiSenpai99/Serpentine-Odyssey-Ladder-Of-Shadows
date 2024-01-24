#include "iGraphics.h"
#include "menu.h"
#include "diceboard.h"
#define ScreenWidth 1200
#define ScreenHeight 600
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

int playerX = 208;
int playerY = 100;
int playerLife = 5;
int heart = 3;

int lifeBarX = 50;
int lifeBarY = 550;

int heartX = 1040;
int heartY = 530;


int bulletX;
int bulletY;
int bulletPlayerIndex = 0;


int crouchTimer = 0;
bool stand = true;
bool crouch = false;
bool fire = false;
bool hit = true;

void actionCrouch()
{
	iShowImage(playerX, playerY, 208, 208, iLoadImage("image\\player08.png"));
}

void charInitialize()
{
	playerX = 208;
	playerY = 100;
}

void bulletInitialize()
{
	bulletX = playerX + 208;
	bulletY = playerY + 208/2;
}

void lifeBarShow()
{
	if (roomPage)
	{
		int lifeBar[6] = { iLoadImage("image\\HP6.png"),
			iLoadImage("image\\HP5.png"),
			iLoadImage("image\\HP4.png"),
			iLoadImage("image\\HP3.png") ,
			iLoadImage("image\\HP2.png") ,
			iLoadImage("image\\HP1.png") };
		iShowImage(lifeBarX,lifeBarY , 208, 50, lifeBar[playerLife]);

	}
	
}

void lifeHeartShow()
{
	if (roomPage==true || diceBoardMenu==true)
	{
		int lifeBar[3] = { iLoadImage("image\\life2.png"),
			iLoadImage("image\\life1.png"),
			iLoadImage("image\\life0.png"),};
		iShowImage(heartX, heartY, 160, 50, lifeBar[heart-1]);

	}

}

void charFire()
{
	if (fire==true && crouch==false)
	{
		int bulletPlayer[3] = { iLoadImage("image\\player09.png"),
			iLoadImage("image\\player10.png"),
			iLoadImage("image\\player11.png") };
		iShowImage(playerX, playerY, 208, 208, bulletPlayer[bulletPlayerIndex]);
		bulletPlayerIndex++;
		if (bulletPlayerIndex == 3)
		{
			bulletPlayerIndex = 0;
		}
	}
	

}

void checkCollision()
{

}

void iDraw()
{
	iClear();
	//------------------------------Menupage-------------------------------
	if (menuPage)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\Menu.png"));
	}

	else if (menuPage != true && startPage == true)
	{
		diceBoardHandler();
	}
	
	else if (menuPage != true && scorePage == true)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\MenuHighScore.png"));
	}

	else if (menuPage != true && controlPage == true)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\MenuControls.png"));
	}

	else if (menuPage != true && aboutPage == true)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\MenuAbout.png"));
	}

	//----------------------------StartGame--------------------------------------------
	

	if (diceBoardMenu)
	{
		int dice[6] = { iLoadImage("image\\1.png"),
			iLoadImage("image\\2.png"),
			iLoadImage("image\\3.png"),
			iLoadImage("image\\4.png"),
			iLoadImage("image\\5.png"),
			iLoadImage("image\\6.png") };

		int player[4] = { iLoadImage("image\\idle0.png"),
			iLoadImage("image\\idle1.png"),
			iLoadImage("image\\idle2.png"),
			iLoadImage("image\\idle3.png") };

		int bg[1] = { iLoadImage("image\\Board.png") };

		iShowImage(0, boardy, 1200, 1040, bg[0]);
		iShowImage(1040, 0, 160, 160, dice[diceIndex]);
		iShowImage(animeBoardX, animeBoardY, 208, 208, player[animeIndex]);
		
	}

	//----------------------------ROOMPAGE--------------------------------------------

	if (roomPage){

		room();
		
		int room[4] = { iLoadImage("image\\SnakeRoom.png"),
			iLoadImage("image\\NeutralRoom.png"),
			iLoadImage("image\\TreasureRoom.png"),
			iLoadImage("image\\LadderRoom.png") };

		int player1[4] = { iLoadImage("image\\player00.png"),
			iLoadImage("image\\player01.png"),
			iLoadImage("image\\player02.png"),
			iLoadImage("image\\player03.png") };

		iShowImage(0, 0, ScreenWidth, ScreenHeight, room[roomIndex]);
		if (stand==true && fire == false)
		{
			iShowImage(playerX, playerY, 208, 208, player1[roomAnimeIndex]);
			if (charInit)
			{
				charInitialize();
				charInit = false;
			}
		}

		if (fire)
		{
			charFire();
			iShowImage(bulletX, bulletY, 16, 16, iLoadImage("image\\pro0.png"));
			//stand = true;
		}

		if (snakeAlive==true && roomIndex==0)
		{
			iShowImage(snakeX, snakeY, 256, 285, iLoadImage("image\\snake.png"));
			iShowImage(snakeVenomX, snakeVenomY, 30, 30, iLoadImage("image\\pro1.png"));
			if (venomThrow)
			{
				snakeVenomInitialize();
				venomThrow = false;
			}
		}
		

		if (crouch)
		{

			actionCrouch();
			crouchTimer++;
			if (crouchTimer >= 3)
			{
				crouchTimer = 0;
				crouch = false;
				stand = true;
			}

		}
		lifeBarShow();

	}
	lifeHeartShow();

}





/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
	
}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("x=%d y=%d", mx, my);
		if (menuPage == true && (mx >= 465 && mx <= 735) && (my >= 336 && my <= 414))
		{
			diceBoardMenuInitialize();
			startPageHandler();
		}

		else if (menuPage == true && (mx >= 465 && mx <= 735) && (my >= 234 && my <= 312))
		{
			scorePageHandler();
		}

		else if (menuPage == true && (mx >= 465 && mx <= 735) && (my >= 130 && my <= 208))
		{
			controlPageHandler();
		}

		else if (menuPage == true && (mx >= 465 && mx <= 735) && (my >= 25 && my <= 105))
		{
			aboutPageHandler();
		}

		
	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
	if (key == '\b')
	{
		if (menuPage != true && diceBoardMenu == true)
		{
			menuPageHandler();
		}
		else if (menuPage == true)
		{
			exit (0);
		}
	}

	if (key == 'd')
	{
		if (diceBoardMenu && rollDice)
		{
			ran();
			check = true;
			boardAnimeMove();
			if (animeBoardY > 208){
				boardy -= 208;
				animeBoardY = 208;
			}
			rollDice = false;
		}
		
	}

	if (key == '\r')
	{
		if (diceBoardMenu==true && totalRoll!=0 && check==true)
		{
			if (totalRoll < 20 )
			{
				check = false;
				roomPageHandler();
			}
		}
		else if (roomPage)
		{
			if (roomIndex == 0 && snakeAlive == false)
			{
				rollDice = true;
				diceBoardHandler();
				venomThrow = true;
				charInit = true;
				snakeAlive = true;
			}
			else if (roomIndex != 0)
			{
				rollDice = true;
				diceBoardHandler();
				venomThrow = true;
				charInit = true;
			}
			
		}


	}

	if (key == 'm')
	{
		if (roomPage)
		{
			snakeAlive = false;
		}
	}

	if (key == ' ')
	{
		if (roomPage==true && fire==false && stand==true && hit==true && roomIndex==0 && snakeAlive==true)
		{
			fire = true;
			hit = false;
		}
	}
	
	
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	
	if (key == GLUT_KEY_RIGHT)
	{
		if (roomPage)
		{
			if (playerX + 208 < snakeX)
				playerX += 20;
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (roomPage)
		{
			if (playerX>0)
				playerX -= 20;
		}
	}
	
	if (key == GLUT_KEY_DOWN)
	{
		if (roomPage==true && crouch == false)
		{
			crouch = true;
			stand = false;
		}
	}
	
}

void snakeVenomBulletChange()
{
	if (roomPage==true && roomIndex==0)
	{
		snakeVenomX -= 50;
		if (stand == true && snakeVenomX <= playerX + 150 && snakeVenomX >= playerX)
		{
			snakeVenomInitialize();
			playerLife--;
			if (playerLife == 0)
			{
				check = true;
				rollDice = true;
				diceBoardHandler();
				venomThrow = true;
				charInit = true;
				playerLife = 5;
				heart--;
				if (heart == 0)
					exit(0);
			}
		}
		else if (snakeVenomX <= 0)
		{
			snakeVenomX = snakeX;
		}
	}
	if (roomPage == true && fire == true )
	{
		bulletX += 50;
		if (bulletX >= snakeX)
		{
			bulletInitialize();
			fire = false;
			hit = true;
			snakeLife--;
			if (snakeLife == 0)
			{
				snakeAlive = false;
			}
		}
	}
	
}


int main()
{
	bulletInitialize();
	snakeVenomInitialize();
	iSetTimer(100, boardAnimeChange);
	iSetTimer(100, roomAnimeChange);
	iSetTimer(10, snakeVenomBulletChange);
	iSetTimer(10, charFire);
	iInitialize(ScreenWidth, ScreenHeight, "Serpentine Odyssey : Ladder of Shadows");
	///updated see the documentations
	iStart();
	return 0;
}