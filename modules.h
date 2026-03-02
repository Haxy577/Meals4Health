#include "prototypes.h"


/******************************************************************************

******************************************************************************/


/******************************************************************************
*                                                                             *
*                             Display Functions                               *
*                                                                             *
******************************************************************************/

/******************************************************************************
    This function checks whether the integer is within the given range
    Preconditions:
        1. The parameters are integers.
    
    @param input the value to be evaluated.
	@param min the minimum value the input can be.
	@param max the maximum value the input can be.
    @param return outputs TRUE if its within range, FALSE otherwise.
******************************************************************************/
bool
isInRange(int input,
          int min,
          int max)
{
    bool result;

    if (input >= min && input <= max)
        result = TRUE;
    else
        result = FALSE;

    return result;
}

/******************************************************************************
	This function changes the text color in the command prompt.
	Preconditions:
        1. The parameters are non-negative integers.
        2. Parameters red, green, and blue are a number from 0 to 255.

	@param modifier tracks the modifier. 1 for bold color, 2 for a dim color.
	@param red tracks the intensity of the color red.
	@param green tracks the intensity of the color green.
	@param blue tracks the intensity of the color blue.
******************************************************************************/
void
paintText(int modifier,
	        int red,
	        int green,
	        int blue)
{
	//validate if the rgb values are within 0 to 255
	if (isInRange(modifier, 0, 2) &&
        isInRange(red, 0, 255) &&
		isInRange(green, 0, 255) &&
		isInRange(blue, 0, 255))
			printf("\33[%d;38;2;%d;%d;%dm", modifier, red, green, blue);
}



/******************************************************************************
    This function changes the background color of a line in the screen.
    Preconditions:
        1. The parameters are non-negative integers.
        2. Parameters red, green, and blue are a number from 0 to 255.

    @param nRed tracks the intensity of the color red.
	@param nGreen tracks the intensity of the color green.
	@param nBlue tracks the intensity of the color blue.
******************************************************************************/
void
paintLine(int red,
          int green,
          int blue)
{
    if (isInRange(red, 0, 255) &&
		isInRange(green, 0, 255) &&
		isInRange(blue, 0, 255))
    {
        //Set the color
        printf("\33[48;2;%d;%d;%dm", red, green, blue);

        //Clear the line to fill it with color
        printf("\33[2K");

        //Set the cursor at the start of the line
        printf("\33[H");
    }
}



/******************************************************************************
    This function moves the cursor down by MAX_SCREEN_HEIGHT + 5 which serves
        as a buffer between screens.
******************************************************************************/
void
nextScreen()
{
    int i;
    const int BUFFER = 5;
    char temp[MAX_SCREEN_HEIGHT + BUFFER + 1];

    printf("\33[%dE\33[%dC", MAX_SCREEN_HEIGHT, MAX_SCREEN_LENGTH); //move the cursor to the last row and column in the screen
    
    //create the space for the next screen
    for (i = 0; i < MAX_SCREEN_HEIGHT + BUFFER; i++)
        temp[i] = '\n';
    temp[i] = '\0';

    printf("%s", temp);

    printf("\33[%dF", MAX_SCREEN_HEIGHT); //move the cursor to the top of the next screen
}



/******************************************************************************
    This function moves the text cursor to a specific position on the console
        screen.
    Preconditions:
        1. x and y are positive integers.

    @param x the position in the x axis starting from the top left.
    @param y the position in the y axis starting from the top left.
******************************************************************************/
void
goToXY(int x,
       int y)
{
    if (x >= 0 && y >= 0)
        printf("\33[%d;%dH", x, y);
}



/*
    This function displays the option text with text modifications if the cursor/pointer is on
        that option, else it just displays the bare text.
    Preconditions:
        1. index and selected are non negative integers.
    
    @param options a 2D char array containing the strings for the options.
    @param index refers to the string to be displayed.
    @param selected refers to what index the cursor is currently at.
*/
void
displayOption(string20 options,
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



/******************************************************************************
    This function displays the header ASCII art of the program.
******************************************************************************/
void
displayHeader()
{
    //changeColor(1, 46, 111, 64);
    //changeBackground(255,255,255);
    //printf("\33[48;2;255;255;255m\33[2K\33[H");
    printf("  __   ____   ___  _  _  __  _  _  ____     __  ____     __   _  _  ____    ____  ____  ___  __  ____  ____  ____ \n");
    printf(" / _\\ (  _ \\ / __)/ )( \\(  )/ )( \\(  __)   /  \\(  __)   /  \\ / )( \\(  _ \\  (  _ \\(  __)/ __)(  )(  _ \\(  __)/ ___)\n");
    printf("/    \\ )   /( (__ ) __ ( )( \\ \\/ / ) _)   (  O )) _)   (  O )) \\/ ( )   /   )   / ) _)( (__  )(  ) __/ ) _) \\___ \\\n");
    printf("\\_/\\_/(__\\_) \\___)\\_)(_/(__) \\__/ (____)   \\__/(__)     \\__/ \\____/(__\\_)  (__\\_)(____)\\___)(__)(__)  (____)(____/\n");
    //printf("\33[0m\33[2J\33[H");
}


/******************************************************************************
    This function prints a divider on the screen. The character is based on
    the passed character.
    Preconditions:
        1. ch is a character that exist in the normal ASCII table.

    @param ch the character to be continuously printed to form a line.
******************************************************************************/
void
printLine(char ch)
{
    int i;
    char line[MAX_SCREEN_LENGTH + 1];

    for (i = 0; i < MAX_SCREEN_LENGTH; i++)
        line[i] = ch;
    line[i] = '\0';
    printf("%s\n", line);
}


/******************************************************************************
    This function prints the ANSI escape code for moving the cursor to the
    next line.
    Preconditions:
        1. x is a positive integer.

    @param x where to place the cursor on the screen.
******************************************************************************/
void
nextLine(int x)
{
    printf("\33[1E\33[%dG", x);
}