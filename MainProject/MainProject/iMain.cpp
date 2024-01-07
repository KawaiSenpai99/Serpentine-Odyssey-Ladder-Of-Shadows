#include "iGraphics.h"
#include "menu.h"
#define ScreenWidth 1200
#define ScreenHeight 600
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void iDraw()
{
	iClear();
	if (menuPage)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\Menu.png"));
	}

	else if (menuPage != true && startPage == true)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\LadderRoom.png"));
	}
	
	else if (menuPage != true && scorePage == true)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\NeutralRoom.png"));
	}

	else if (menuPage != true && controlPage == true)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\SnakeRoom.png"));
	}

	else if (menuPage != true && aboutPage == true)
	{
		iShowImage(0, 0, ScreenWidth, ScreenHeight, iLoadImage("image\\TreasureRoom.png"));
	}

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
		if (menuPage == true && (mx >= 465 && mx <= 735) && (my >= 336 && my <= 414))
		{
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
		if (menuPage != true)
		{
			menuPageHandler();
		}
		else if (menuPage == true)
		{
			exit (0);
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
				
	}
	if (key == GLUT_KEY_LEFT)
	{
		
	}
	
	if (key == GLUT_KEY_HOME)
	{
		
	}
	
}


int main()
{
	///srand((unsigned)time(NULL));
	iInitialize(ScreenWidth, ScreenHeight, "Project Title");
	///updated see the documentations
	iStart();
	return 0;
}