#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#define ScreenWidth 1200
#define ScreenHeight 600

//-------------------------------Menu Buttons Booleans -------------------------------------------

bool menuPage = true;
bool startPage = false;
bool scorePage = false;
bool controlPage = false;
bool aboutPage = false;

//--------------------------------Menu button handler  -------------------------------------------

void menuPageHandler()
{
	menuPage = true;
	startPage = false;
	scorePage = false;
	controlPage = false;
	aboutPage = false;
}

void startPageHandler()
{
	menuPage = false;
	startPage = true;
	scorePage = false;
	controlPage = false;
	aboutPage = false;
}

void scorePageHandler()
{
	menuPage = false;
	startPage = false;
	scorePage = true;
	controlPage = false;
	aboutPage = false;
}

void controlPageHandler()
{
	menuPage = false;
	startPage = false;
	scorePage = false;
	controlPage = true;
	aboutPage = false;
}

void aboutPageHandler()
{
	menuPage = false;
	startPage = false;
	scorePage = false;
	controlPage = false;
	aboutPage = true;
}


#endif // !MENU_H_INCLUDED
