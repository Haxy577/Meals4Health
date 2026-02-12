#include "prototypes.h"



/*************************************************************************
*                           Display Functions                            *
*************************************************************************/
//This functions clears the console screen
void
clearScreen()
{
    system("cls"); //or printf("\33[0m\33[2J\33[H")
}



/*
    This function moves the text cursor to a specific position on the console screen.
    Preconditions:
        1. x and y are positive integers.

    @param x the position in the x axis
    @param y the position in the y axis
*/
void
goToXY(int x,
       int y)
{
    COORD coord;
    if (x >= 0 && y >= 0)
    {
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
}



/*
	This function changes the text color in the command prompt
	Preconditions: the parameters are non-negative integers and nRed, nGreen, and nBlue are
					a number from 0 to 255.

	@param modifier tracks the modifier. 1 for bold color, 2 for a dim color
	@param nRed tracks the intensity of the color red
	@param nGreen tracks the intensity of the color green
	@param nBlue tracks the intensity of the color blue
*/
void
paintText(int modifier,
	        int red,
	        int green,
	        int blue)
{
	//validate if the rgb values are within 0 to 255
	if (red > -1 && red < 256 &&
		green > -1 && green < 256 &&
		blue > -1 && blue < 256)
			printf("\x1b[%d;38;2;%d;%d;%dm", modifier, red, green, blue);
}



/*
    This function changes the background color of a line in the screen

    @param nRed tracks the intensity of the color red
	@param nGreen tracks the intensity of the color green
	@param nBlue tracks the intensity of the color blue
*/
void
paintLine(int red,
          int green,
          int blue)
{
	printf("\33[48;2;%d;%d;%dm\33[2K\33[H\n\33[0m", red, green, blue);
}



/*
    This function displays the option text with text modifications if the cursor/pointer is on
        that option, else it just displays the bare text.
    Preconditions:
        1. index and selected are non negative integers
    
    @param options a 2D char array containing the strings for the options
    @param index refers to the string to be displayed
    @param selected refers to what index the cursor is currently at
*/
void
displayOption(string10 options,
              int index,
              int selected)
{
    if (index == selected)
    {
        printf("> \33[4m");
        //changeColor(1, 46, 111, 64);
    }
    printf("%s", options);
    printf("\33[0m");
}



/*
    This function displays the header design of the program
*/
void
displayHeader()
{
    clearScreen();
    //changeColor(1, 46, 111, 64);
    //changeBackground(255,255,255);
    //printf("\33[48;2;255;255;255m\33[2K\33[H");
    printf("  __   ____   ___  _  _  __  _  _  ____     __  ____     __   _  _  ____    ____  ____  ___  __  ____  ____  ____ \n");
    printf(" / _\\ (  _ \\ / __)/ )( \\(  )/ )( \\(  __)   /  \\(  __)   /  \\ / )( \\(  _ \\  (  _ \\(  __)/ __)(  )(  _ \\(  __)/ ___)\n");
    printf("/    \\ )   /( (__ ) __ ( )( \\ \\/ / ) _)   (  O )) _)   (  O )) \\/ ( )   /   )   / ) _)( (__  )(  ) __/ ) _) \\___ \\\n");
    printf("\\_/\\_/(__\\_) \\___)\\_)(_/(__) \\__/ (____)   \\__/(__)     \\__/ \\____/(__\\_)  (__\\_)(____)\\___)(__)(__)  (____)(____/\n");
    //printf("\33[0m\33[2J\33[H");
}