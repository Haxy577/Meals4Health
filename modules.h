#include "prototypes.h"


/******************************************************************************

******************************************************************************/


/******************************************************************************
*                                                                             *
*                             Cursor Functions                                *
*                                                                             *
******************************************************************************/


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



/******************************************************************************
    This function prints the ANSI escape code for moving the cursor by x amount
        to the left or right and by y amount to to the up or down. A negative
        integer would correspond to left or down and a positive integer would
        correspond to right or up.

    @param x the amount of displacement of the cursor in the y-axis.
    @param y the amount of displacement of the cursor in the y-axis.
******************************************************************************/
void
moveCursor(int x,
           int y)
{
    if (x > 0)
        printf("\33[%dC", x); //right
    else if (x < 0)
        printf("\33[%dD", x * -1); //left
    
    if (y > 0)
        printf("\33[%dA", y); //up
    else if (y < 0)
        printf("\33[%dB", y * -1); //down
}



/******************************************************************************
    This function sets the cursor visible or invisible.

    @param state decides the visibility of the cursor. TRUE for visible,
        FALSE for invisible.
******************************************************************************/
void
cursorVisibility(bool state)
{
    if (state == TRUE)
        printf("\33[?25h"); //visible
    else
        printf("\33[?25l"); //invisible
}



/******************************************************************************
*                                                                             *
*                             Style Functions                                 *
*                                                                             *
******************************************************************************/


/******************************************************************************
	This function changes the text color in the command prompt.
	Preconditions:
        1. The parameters are non-negative integers.
        2. Parameters red, green, and blue are a number from 0 to 255.

	@param type defines what color to change. 0 for the foreground, 1 for the
        background.
	@param red tracks the intensity of the color red.
	@param green tracks the intensity of the color green.
	@param blue tracks the intensity of the color blue.
******************************************************************************/
void
paintText(paintType type,
	        int red,
	        int green,
	        int blue)
{
	//validate if the rgb values are within 0 to 255
	if (isInRange(red, 0, 255) &&
		isInRange(green, 0, 255) &&
		isInRange(blue, 0, 255))
    {
        if (type == FOREGROUND)
            printf("\33[38;2;%d;%d;%dm", red, green, blue);
        else if (type == BACKGROUND)
            printf("\33[48;2;%d;%d;%dm", red, green, blue);
    }
}



/******************************************************************************
	This function removes all styles and colors.
******************************************************************************/
void
resetText()
{
	printf("\33[0m");
}



/******************************************************************************
    This function changes the background color of a line in the screen.
    Preconditions:
        1. The parameters are non-negative integers.
        2. Parameters red, green, and blue are a number from 0 to 255.

    @param red tracks the intensity of the color red.
	@param green tracks the intensity of the color green.
	@param blue tracks the intensity of the color blue.
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
        printf("\33[1G");

        //Reset all styles
        printf("\33[0m");
    }
}



/******************************************************************************
    This function changes the background color of the whole screen starting
        from where the cursor is.
    Preconditions:
        1. The parameters are non-negative integers.
        2. Parameters red, green, and blue are a number from 0 to 255.

    @param nRed tracks the intensity of the color red.
	@param nGreen tracks the intensity of the color green.
	@param nBlue tracks the intensity of the color blue.
******************************************************************************/
void
paintScreen(int red,
            int green,
            int blue)
{
    if (isInRange(red, 0, 255) &&
		isInRange(green, 0, 255) &&
		isInRange(blue, 0, 255))
    {
        //Set the color
        printf("\33[48;2;%d;%d;%dm", red, green, blue);

        //Clear the screen starting from the cursor
        printf("\33[0J");

        //Set the cursor at the start of the line and the top of the new screen
        printf("\33[1G\33[%dF", MAX_SCREEN_HEIGHT);

        //Reset all styles
        printf("\33[0m");
    }
}



/******************************************************************************
    This function adds or removes a specific style to the text. The following
        styles are: bold, italic, underline, and strikethrough.

    @param type decides what style to add / remove.
    @param state decides whether to add or remove the style. if TRUE then add,
        otherwise remove.
******************************************************************************/
void
styleText(styleType type,
          bool state)
{
    switch(type)
    {
        case BOLD:
            if (state == TRUE)
                printf("\33[1m");
            else
                printf("\33[22m");
            break;
        case ITALIC:
            if (state == TRUE)
                printf("\33[3m");
            else
                printf("\33[23m");
            break;
        case UNDERLINE:
            if (state == TRUE)
                printf("\33[4m");
            else
                printf("\33[24m");
            break;
        case STRIKETHROUGH:
            if (state == TRUE)
                printf("\33[9m");
            else
                printf("\33[29m");
            break;
    }
}



/******************************************************************************
*                                                                             *
*                             Helper Functions                                *
*                                                                             *
******************************************************************************/


/******************************************************************************
    This function checks whether the integer is within the given range
    Preconditions:
        1. The parameters are integers.
    
    @param value the value to be evaluated.
	@param min the minimum value the input can be.
	@param max the maximum value the input can be.
    @return outputs TRUE if its within range, FALSE otherwise.
******************************************************************************/
bool
isInRange(int value,
          int min,
          int max)
{
    bool result;

    if (value >= min && value <= max)
        result = TRUE;
    else
        result = FALSE;

    return result;
}



/******************************************************************************
    This function lets a user edit the string passed through the parameter.

    @param str an array to store the input of the user.
    @param size the maximum amount of characters str can take. This does not
        include the null byte.
    @return a copy of the final edited string.
******************************************************************************/
char *
getInput(char str[], int size)
{
    int len = strlen(str);
    char input;
    int i = len;
    int j;

    str[size + 1] = '\0'; //to prevent any crashes

    do
    {
        printf("%s", str);
        moveCursor(len * -1, 0); //move the cursor at the start of the string
        moveCursor(i, 0); //move the cursor at the value of i

        cursorVisibility(TRUE);

        input = getch(); //get the key press

        cursorVisibility(FALSE);

        if (input == 0) //if the input is the left or right arrows
        {
            switch (getch()) //get the input again
            {
                case RIGHT_ARROW:
                    moveCursor(i * -1, 0); //move the cursor to the start of the string
                    if (i < len)
                        i++;
                    break;
                case LEFT_ARROW:
                    moveCursor(i * -1, 0); //move the cursor to the start of the string
                    if (i > 0)
                        i--;
                    break;
            }
        }       
        else if (input == BACKSPACE && i > 0)
        {
            for (j = i - 1; j < len; j++) //shift everything to the left
                str[j] = str[j + 1];

            moveCursor(i * -1, 0); //move the cursor to the start of the string
            moveCursor(len - 1, 0); //move the cursor to the last character of the string
            printf(" "); //remove the character by printing a space
            moveCursor(len * -1, 0); //move the cursor to the start of the string
            i--;
        }
        else if (input >= ' ' && input <= '~' && len < size)
        {
            for (j = len + 1; j >= i; j--) //shift everything to the right of the cursor
                str[j + 1] = str[j];

            moveCursor(i * -1, 0); //move the cursor to the start of the string
            str[i] = input;
            i++;
        }
        else if (input == ENTER)
            str[len + 1] = '\0'; //end the string with a null byte
        else
            moveCursor(i * -1, 0); //move the cursor to the start of the string

        len = strlen(str);

    } while (input != ENTER);
    
    return str;
}



/******************************************************************************
*                                                                             *
*                             Display Functions                               *
*                                                                             *
******************************************************************************/


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
*                                                                             *
*                             Testing Functions                               *
*                                                                             *
******************************************************************************/


/******************************************************************************
    This function calls all the test functions.
******************************************************************************/
void
testAllFunctions()
{
    testIsInRange();
}



/******************************************************************************
    This function displays the details of the test case and its result.

    @param testNum the test case number.
    @param description the description of the test case.
    @param input what was inputted in the function parameters.
    @param expected the expected output of the function.
    @param actual the actual output of the function.
    @param result whether the expected matches the actual. Prints "PASS" if
        it matches, "FAIL" if it does not.
******************************************************************************/
void
displayTestResult(int testNum,
              string70 description,
              string70 input,
              string70 expected,
              string70 actual,
              bool result)
{
    styleText(BOLD, TRUE);
    printf("Test case #%d\n", testNum);
    styleText(BOLD, FALSE);
    printf("Description: %s\n", description);
    printf("Input: %s\n", input);
    printf("Expected: %s\n", expected);
    printf("Actual: %s\n", actual);
    printf("Result: ");
    if (result == TRUE)
    {
        paintText(FOREGROUND, 0 ,255, 0);
        printf("PASS\n\n");
    }
    else
    {
        paintText(FOREGROUND, 255, 0, 0);
        printf("FAIL\n\n");
    }
    resetText();
}



/******************************************************************************
    This function tests whether the function "isInRange" works as expected.
    Test Cases:
        1. The value is within the given range.
        2. The value is outside the given range.
        3. The value, min, and max are equal.
******************************************************************************/
void
testIsInRange()
{
    int testNum = 0;
    string70 expected;
    string70 actual;

    styleText(BOLD, TRUE);
    printf("Testing \"isInRange\" function\n\n");
    styleText(BOLD, FALSE);

    //Test case 1
    testNum++;

    strcpy(expected, "TRUE");

    if (isInRange(2, 1, 3))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(testNum,
                      "The value is outside the given range",
                      "Value: 1 ; Min: 2 ; Max: 3",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
    
    //Test case 2
    testNum++;

    strcpy(expected, "TRUE");

    if (isInRange(2, 1, 3))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(testNum,
                      "The value is within range",
                      "Value: 2 ; Min: 1 ; Max: 3",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);

    //Test case 3
    testNum++;

    strcpy(expected, "TRUE");

    if (isInRange(2, 1, 3))
        strcpy(actual, "TRUE");
    else
        strcpy(actual, "FALSE");

    displayTestResult(testNum,
                      "The value, min, and max are equal",
                      "Value: 1 ; Min: 1 ; Max: 1",
                      expected,
                      actual,
                      strcmp(expected, actual) == 0);
}