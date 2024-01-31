#include "iGraphics.h"
#include "menu.h"
#include "diceboard.h"
#include "bitmap_loader.h"
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
bool hit = true;
bool fireAnime = false;

//------------------------------HIGH SCORE------------------------------

int point = 0;
char sc[1000];

void sortScore();
void readScore();
int len = 0;
char str1[100];
bool newScore = true;

struct Hscore{
	char name[20];
	int score=0;
}highScore[5];

void readScore()
{
	FILE *fp;
	fp = fopen("Score.txt", "r");
	char showName[5][30], showScore[5][5];
	for (int i = 0; i < 5; i++){
		fscanf(fp, "%s %d\n", highScore[i].name, &highScore[i].score);
	}
	for (int i = 0; i < 5; i++){
		sprintf(showName[i], "%s", highScore[i].name);
		sprintf(showScore[i], "%d", highScore[i].score);
		iSetColor(255, 0, 0);
		iText(400, 430 - 85 * i, showName[i], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(500, 430 - 85 * i, showScore[i], GLUT_BITMAP_TIMES_ROMAN_24);
	}
	fclose(fp);
}

void sortScore()
{
	FILE *fp;
	fp = fopen("Score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s %d\n", highScore[i].name, &highScore[i].score);
	}
	fclose(fp);
	int temp;
	char n[30];
	if (newScore)
	{
		for (int i = 0; i < 5; i++)
		{
			if (highScore[i].score < point)
			{
				highScore[4].score = point;
				strcpy(highScore[4].name, str1);
				for (int j = 0; j < 5; j++)
				{
					for (int k = 5; k>j; k--)
					{
						if (highScore[k].score > highScore[k - 1].score)
						{
							temp = highScore[k - 1].score;
							highScore[k - 1].score = highScore[k].score;
							highScore[k].score = temp;

							strcpy(n, highScore[k - 1].name);
							strcpy(highScore[k - 1].name, highScore[k].name);
							strcpy(highScore[k].name,n);
						}
					}
				}

				FILE* fp = fopen("Score.txt", "w");
				for (int i = 0; i < 5; i++)
				{
					fprintf(fp, "%s %d\n", highScore[i].name, highScore[i].score);
				}
				fclose(fp);

				newScore = false;
				break;
			}
		}
	}
}

void showChar(){

	iSetColor(255, 0, 0);
	iText(400, 200, "Enter Your Name : ", GLUT_BITMAP_TIMES_ROMAN_24);
	iRectangle(495, 150, 160, 30);
	iText(500, 160, str1, GLUT_BITMAP_TIMES_ROMAN_24);

}

void takeChar(unsigned key){

	if (key == '\r')
	{
		menuPageHandler();
		sortScore();
	}
	else if (key == '\b')
	{
		if (len <= 0)
			len = 0;
		else
			len--;
		str1[len] ='\0';
	}
	else
	{
		str1[len] = key;
		len++;

		if (len > 15)
			len = 15;
		str1[len] = '\0';
	}

}

//-------------------SHOWING SCORE------------------------------

void showScore(){

	if (roomPage == true || diceBoardMenu == true){

		iSetColor(255, 0, 0);
		iText(1060, 470, "Score", GLUT_BITMAP_TIMES_ROMAN_24);

		sprintf(sc, "%d", point);
		iText(1060, 450, sc, GLUT_BITMAP_TIMES_ROMAN_24);

	}

}


//-------------------------FOR EVERY START GAME-----------------------------------

void startgame()
{
	boardMoveCounter = 1;
	animeIndex = 0;
	roomAnimeIndex = 0;
	boardy = 0;
	animeBoardX = 0;
	animeBoardY = 0;
	totalRoll = 0;
	roomIndex = 0;
	rollDice = true;
	snakeX = 800;
	snakeY = 100;
	snakeLife = 3;
	snakeAlive = true;
	venomThrow = true;
	charInit = true;
	check = true;
	multiple = false;
	pause = false;


	diceBoardHandler();
	startPageHandler();


	playerLife = 5;
	heart = 3;
	crouchTimer = 0;
	stand = true;
	crouch = false;
	hit = true;
	fireAnime = false;
	point = 0;
	len = 0;
	newScore = true;
	chest = true;


}


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
//--------------------------LifeRelated---------------------------
void lifeBarShow()
{
	if (roomPage && pause==false)
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
	if (hit == false && crouch == false && pause == false)
	{
		bulletPlayerIndex++;
		if (bulletPlayerIndex == 3)
		{
			bulletPlayerIndex = 0;
			fireAnime = false;
			stand = true;
			
		}
	}
	

}
//-------------------------Losing to Snake---------------------------
void ladderDown()
{
	
	if (animeBoardY != 0)
	{
		boardMoveCounter *= (-1);
		boardy += 208;
	}
		
	if (totalRoll == 7)
		totalRoll = 2;
	else if (totalRoll == 11)
		totalRoll = 8;
	else if (totalRoll == 15)
		totalRoll = 14;
	else if (totalRoll == 19)
		totalRoll = 10;
}
//-----------------------------Winning In Life-----------------------
void ladderUp()
{
	diceRoll = false;
	if (animeBoardY >= 0)
	{
		boardMoveCounter *= (-1);
		boardy -= 208;
	}
	if (totalRoll == 2)
		totalRoll = 7;
	else if (totalRoll == 6)
		totalRoll = 13;
	else if (totalRoll == 10)
		totalRoll = 19 ;
	else if (totalRoll == 14)
		totalRoll = 15;
}


void iDraw()
{
	//printf("%d", totalRoll);
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

		readScore();


	}

	else if (menuPage != true && controlPage == true)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\MenuControls.png"));
	}

	else if (menuPage != true && aboutPage == true)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\MenuAbout.png"));
	}

	else if (gameOverPage)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\GameOver.png"));
		showChar();
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

		iShowImage(1060, 280, 128, 128, iLoadImage("image\\Pause Button.png"));

	}

	//----------------------------ROOMPAGE--------------------------------------------

	if (roomPage){

		room();
		
		int room[4] = { iLoadImage("image\\SnakeRoom-min.png"),
			iLoadImage("image\\NeutralRoom-min.png"),
			iLoadImage("image\\TreasureRoom-min.png"),
			iLoadImage("image\\LadderRoom-min.png") };
			
		int player1[4] = { iLoadImage("image\\player00.png"),
			iLoadImage("image\\player01.png"),
			iLoadImage("image\\player02.png"),
			iLoadImage("image\\player03.png") };

		iShowImage(0, 0, ScreenWidth, ScreenHeight, room[roomIndex]);
		if (stand==true)
		{
			iShowImage(playerX, playerY, 208, 208, player1[roomAnimeIndex]);
			if (charInit)
			{
				charInitialize();
				charInit = false;
			}
		}

		if (hit == false)
		{
			iShowImage(bulletX, bulletY, 16, 16, iLoadImage("image\\pro0.png"));
		}

		if (fireAnime == true && crouch == false)
		{
			int bulletPlayer[3] = { iLoadImage("image\\player09.png"),
				iLoadImage("image\\player10.png"),
				iLoadImage("image\\player11.png") };
			iShowImage(playerX, playerY, 208, 208, bulletPlayer[bulletPlayerIndex]);
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
		
		if (roomIndex == 2 && chest == true)
		{
			iShowImage(600, 100, 208 / 2, 208 / 2, iLoadImage("image\\Chest.png"));
		}

		if (crouch)
		{

			actionCrouch();
			crouchTimer++;
			if (crouchTimer >= 10)
			{
				crouchTimer = 0;
				crouch = false;
				stand = true;
			}

		}
		lifeBarShow();
		iShowImage(550, 500, 100, 100, iLoadImage("image\\Pause Button.png"));

	}
	if (roomPauseMenu==true || boardPauseMenu==true)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\PauseMenu.png"));
	}
	lifeHeartShow();
	showScore();

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
			startgame();
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
		
		else if (diceBoardMenu == true && (mx >= 1060 && mx <= 1060+128) && (my >= 280 && my <= 280+128))
		{
			boardPauseHandler();
		}
		
		else if (roomPage == true && (mx >= 550 && mx <= 650) && (my >= 500 && my <= 600))
		{
			roomPauseHandler();
		}
		
		else if (boardPauseMenu == true && (mx >= 300 && mx <= 870) && (my >= 330 && my <= 495))
		{
			diceBoardHandler();
		}
		else if (boardPauseMenu == true && (mx >= 300 && mx <= 870) && (my >= 115 && my <= 275))
		{
			menuPageHandler();
		}
		
		else if (roomPauseMenu == true && (mx >= 300 && mx <= 870) && (my >= 330 && my <= 495))
		{
			roomPageHandler();
		}
		else if (roomPauseMenu == true && (mx >= 300 && mx <= 870) && (my >= 115 && my <= 275))
		{
			menuPageHandler();
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

	if (gameOverPage)
	{
		takeChar(key);
	}

	if (key == '\b')
	{
		if (menuPage != true && (diceBoardMenu == true || scorePage==true || aboutPage==true || controlPage==true))
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
		if (diceBoardMenu==true && rollDice==true && totalRoll!=19)
		{
			ran();
			
			check = true;
			boardAnimeMove();
			if (!multiple)
				point += diceRoll;
			if (animeBoardY > 208){
				boardy -= 208;
				animeBoardY = 208;
			}
			rollDice = false;
			if (multiple ){
				rollDice = true;
				multiple = false;
			}
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
			chest = true;
			
		}


	}

	if (key == 'm')
	{
		if (sound == true)
		{
			sound = false;
			PlaySound(0, 0, 0);
		}
		else
		{
			sound = true;
			PlaySound("music\\Kindled_Cosy_Combat.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}

	if (key == ' ')
	{
		if (roomPage==true && stand==true && hit==true && roomIndex==0 && snakeAlive==true)
		{
			hit = false;
			fireAnime = true;
			stand = false;
			crouch = false;
		}
	}

	if (key == 'l')
	{
		if (roomIndex == 3 && totalRoll<16 && playerX >= 600 && pause==false)
		{
			check = true;
			diceBoardHandler();
			charInit = true;
			ladderUp();

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
			if (roomIndex == 0)
			{
				if (playerX + 208 < snakeX)
					playerX += 20;
			}
			else if (roomIndex == 2 && chest == true)
			{
				playerX += 20;
				if (playerX + 180 >= 600){
					if (heart < 3)
						heart++;
					else{
						point+=2;
					}
					chest = false;
				}
			}
			else
			{
				if (playerX + 208 < ScreenWidth)
					playerX += 20;
			}
			
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
			bulletPlayerIndex = 0;
		}
	}
	
}

void snakeVenomBulletChange()
{
	if (roomPage==true && roomIndex==0 && snakeAlive==true)
	{
		snakeVenomX -= 20;
		if (stand == true && snakeVenomX <= playerX + 150 && snakeVenomX >= playerX)
		{
			snakeVenomInitialize();
			playerLife--;
			if (playerLife == 0)
			{
				point -= 2;
				snakeAlive = true;
				check = true;
				diceBoardHandler();
				venomThrow = true;
				charInit = true;
				playerLife = 5;
				heart--;
				if (heart == 0)
					gameOverPageHandler();
				ladderDown();
			}
		}
		else if (snakeVenomX <= 0)
		{
			snakeVenomX = snakeX;
		}
	}
	if (roomPage == true && hit == false )
	{
		bulletX += 20;
		if (bulletX >= snakeX)
		{
			bulletInitialize();
			
			hit = true;
			snakeLife--;
			if (snakeLife == 0 && totalRoll!=19)
			{
				snakeAlive = false;
				check = false;
				point += 10;
			}
			else if (snakeLife == 0 && totalRoll == 19)
			{
				point += 10;
				gameOverPageHandler();
			}
		}
	}
	
}


int main()
{
	bulletInitialize();
	snakeVenomInitialize();
	iSetTimer(100, boardAnimeChange);
	iSetTimer(150, roomAnimeChange);
	iSetTimer(50, snakeVenomBulletChange);
	iSetTimer(100, charFire);
	if (sound)
		PlaySound("music\\Kindled_Cosy_Combat.wav", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(ScreenWidth, ScreenHeight, "Serpentine Odyssey : Ladder of Shadows");
	///updated see the documentations
	iStart();
	return 0;
}