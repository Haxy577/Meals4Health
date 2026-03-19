#ifndef MODULES_H
#define MODULES_H
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

    @param x the amount of displacement of the cursor in the x-axis.
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
    This function prints the ANSI escape code for moving the cursor by the
        desired x position in the console.

    @param x the position of the cursor in the console starting at 1.
******************************************************************************/
void
moveCursorX(int x)
{
    if (x > 0)
        printf("\33[%dG", x);
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
isInRange(long long value,
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
    This function checks whether the integer is within the given range
    
    @param value the value to be evaluated.
	@param min the minimum value the input can be.
	@param max the maximum value the input can be.
    @return outputs TRUE if its within range, FALSE otherwise.
******************************************************************************/
bool
floatInRange(double value,
             float min,
             float max)
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
    Preconditions:
        1. The string is initialized with a null byte.
        2. The parameter size is a positive integer.
        3. There is sufficient space in the console where the function is
            called. Wherein the text field should only be on one row in
            the console and the text should not wrap to another line when it
            reached the end of the console screen.

    @param type decides what to store. INTEGER for int data only, FRACTION for
        float data, and CHARACTER for char data.
    @param str an array to store the input of the user.
    @param size the maximum amount of characters str can take. This does not
        include the null byte.
    @return a copy of the final edited string.
******************************************************************************/
char *
getInput(dataType type,
         char str[],
         int size)
{
    int len = strlen(str);
    int input;
    int i = len; //the current position of the cursor
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

        if (input == 0 || input == 224) //if the input is the left or right arrows
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

        else if ((type == INTEGER || type == FRACTION) && input == '-' && i == 0) //if the user wants the number to be negative
        {
            for (j = len + 1; j >= i; j--) //shift everything to the right of the cursor
                str[j + 1] = str[j];

            moveCursor(i * -1, 0); //move the cursor to the start of the string
            str[i] = input;
            i++;
        }

        else if (type == INTEGER && isInRange(input, '0', '9') && len < size)
        {
            for (j = len + 1; j >= i; j--) //shift everything to the right of the cursor
                str[j + 1] = str[j];

            moveCursor(i * -1, 0); //move the cursor to the start of the string
            str[i] = input;
            i++;
        }

        else if (type == FRACTION && (isInRange(input, '0', '9') || input == '.') && len < size)
        {
            for (j = len + 1; j >= i; j--) //shift everything to the right of the cursor
                str[j + 1] = str[j];

            moveCursor(i * -1, 0); //move the cursor to the start of the string
            str[i] = input;
            i++;
        }

        else if (type == CHARACTER && isInRange(input, ' ', '~') && len < size)
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
    This functions takes a string and converts it into its corresponding
        integer representation.
    Preconditions:
        1. The string only contains characters from 0 - 9, a dash '-' or
			a dot '.'.
        2. There must be only one instance of the dash '-' character in the
            string.
        3. The dash '-' character must only exist in the first element
            of the string.
        4. The string must be initialized.

    @param str is the array to be converted to an integer.
    @return the converted integer.
******************************************************************************/
int
stringToInt(char str[])
{
    int i;
    int result = 0;
    int size = strlen(str);
	int sign = 1;

    if (str[0] == '-')
	{
		sign = -1;
		i = 1; //skip the negative sign
	}
    else
        i = 0;

    while (i < size && isInRange(result * 10, 0, INT_MAX))
    {
        result *= 10; //make space for the new number
        result += str[i] - '0'; //add the number
        i++;
	}

    return result * sign;
}



/******************************************************************************
    This functions takes a string and converts it into its corresponding
        integer representation.
    Preconditions:
        1. The string only contains characters from 0 - 9, a dash '-' or
			a dot '.'.
        2. There must be only one instance of the dash '-' character in the
            string.
        3. The dash '-' character must only exist in the first element
            of the string.
        4. The string must be initialized.

    @param str is the array to be converted to an integer.
    @return the converted integer.
******************************************************************************/
float
stringToFloat(char str[])
{
    int i, j;
    double whole = 0.0; //use double for precision
    double fraction = 0.0;
    int size = strlen(str);
    int sign = 1;

    if (str[0] == '-')
    {
        sign = -1;
        i = 1; //skip the negative sign
    }
    else
        i = 0;

	//convert the whole part of the number
    while (i < size && floatInRange(whole * 10.0, 0, FLT_MAX) && str[i] != '.')
    {
        
        whole *= 10.0;
        whole += (double) str[i] - '0';
        i++;
    }

    j = i + 1;

    if (j < size)
    {
        while (j < size && str[j] != '.')
            j++; //set j to the end of the float number

	    //convert the fractional part of the number
        while (--j > i && floatInRange((whole + fraction) / 10.0, 0, FLT_MAX))
        {
            fraction += (double) str[j] - '0';
            fraction /= 10;
        }
    }

    return (float) (whole + fraction) * sign; //typecast to float
}



/******************************************************************************
	This function will check whether the passed fileName is valid specifically
		in a windows environment.
	Preconditions:
		1. The file name does not contain any reserved names in windows.

	@param fileName the string to be checked.
	@param fileExt the desired extention of the file including the dot '.'.
	@return TRUE if the file name is valid, FALSE otherwise.
******************************************************************************/
bool
isFileNameValid(char fileName[],
				char fileExt[])
{
	int i;
	bool isValid;
	int nameLen = strlen(fileName);
	int extLen = strlen(fileExt);

	if (nameLen <= extLen) //check if the file name contains something aside from the extention.
		isValid = FALSE;
	else if (absStrCmp(fileName + nameLen - extLen, fileExt) == 0) //check if it has the right file extention.
		isValid = TRUE;

	for (i = 0; i < nameLen; i++) //check for disallowed characters
	{
		if (fileName[i] == '<' ||
			fileName[i] == '>' ||
			fileName[i] == ';' ||
			fileName[i] == '"' ||
			fileName[i] == '/' ||
			fileName[i] == '\\' ||
			fileName[i] == '|' ||
			fileName[i] == '?' ||
			fileName[i] == '*')
		{
			isValid = FALSE;
		}	
	}

	return isValid;
}



/******************************************************************************
	This function will convert a string depending on the type of modification
		the user desires. The following are the string modifications
		available:
		1. UPPER_CASE - transforms all lower case letters into upper case.
		2. LOWER_CASE - transforms all upper case letters into lower case.

	@param str is the string to be modified.
	@param type defines the type of modification to be done to the string.
	@return is a copy of the final edited string.
******************************************************************************/
char *
convertString(char str[],
			 convertStr type)
{
	int i;
	int len = strlen(str);

	for (i = 0; i < len; i++)
		switch (type)
		{
			case UPPER_CASE: //change all lower case letters to upper case
				if (isInRange((int) str[i], (int) 'a', (int) 'z'))
					str[i] -= 'a' - 'A';
				break;
			case LOWER_CASE: //change all upper case letters into upper case
				if (isInRange((int) str[i], (int) 'A', (int) 'Z'))
					str[i] += 'a' - 'A';
				break;
		}

	return str; //return a copy of the string
}



/******************************************************************************
    This function will compare would convert all lower case letters to
		upper case letters then compare these two strings together.
        The passed strings would not be modified.

	@param str1 the first string to be compared to str2.
	@param str2 the second string to be compared to str1.
	@return the result of strcmp of str1 and str 2.
******************************************************************************/
int
absStrCmp(char str1[],
		  char str2[])
{
	const int len1 = strlen(str1);
	const int len2 = strlen(str2);
	char temp1[len1];
	char temp2[len2];

	strcpy(temp1, str1);
	strcpy(temp2, str2);
	convertString(temp1, UPPER_CASE);
	convertString(temp2, UPPER_CASE);
	
	return strcmp(temp1, temp2);
}



/******************************************************************************
    This function sorts a given 1D array containing strings.
    Preconditions:
        1. The contents of the array are strings.
        2. The array is initialized.
        3. nElem is a positive integer.

    @param type decides the order of the sorted array. INCREASING for smallest
        to largest, DECREASING for largest to smallest.
    @param nElem is the number of elements in the array.
    @param maxLen is the maximum amount of characters each string can hold.
    @param arr is the array to be sorted.
******************************************************************************/
void
sortStrArray(sortType type,
             int nElem,
             int maxLen,
             char arr[nElem][maxLen])
{
    int i, j;
    int swap;
    char temp[maxLen + 1];

    for (i = 0; i < nElem - 1;i++)
    {
        swap = i; //assume the first element is the largest/smallest
        
        switch (type)
        {
            case INCREASING:
                for (j = i + 1; j < nElem; j++)
                    if (strcmp(arr[swap], arr[j]) > 0)
                        swap = j;
                break;
            case DECREASING:
                for (j = i + 1; j < nElem; j++)
                    if (strcmp(arr[swap], arr[j]) < 0)
                        swap = j;
                break;
        }
        
        //swap if necessary
        if (i != swap)
        {
            strcpy(temp, arr[j]);
            strcpy(arr[j], arr[swap]);
            strcpy(arr[swap], temp);
        }
    }
}




void
displayAllOptions(options option[MAX_ROW_OPTIONS],
                  int lastRow)
{
    int i;
    
    for (i = 0; i <= lastRow; i++)
    {
        if (i > 0)
        {
            moveCursorX(1);
            moveCursor(0, (option[i].x - option[i - 1].x) * -1);
        }

        displayOptions(option[i]);
    }
}


/******************************************************************************
    This function displays the available options in a row.
    Preconditions:
        1. The structure is initialized.

    @param option is the structure containing the options to be displayed.
******************************************************************************/
void
displayOptions(options option)
{
    int i;
    
    for (i = 0; i < option.nOptions; i++)
    {
        if (i == 0)
            printf(" ");
        else
            printf(" | "); //display the divider between options

        if (option.hover - 1 == i && option.selected - 1 == i)
        {
            styleText(BOLD, TRUE);
            styleText(UNDERLINE, TRUE);
            printf("%s", option.names[i]);
            styleText(UNDERLINE, FALSE);
            styleText(BOLD, FALSE);
        }
        else if (option.hover - 1 == i)
        {
            styleText(UNDERLINE, TRUE);
            printf("%s", option.names[i]);
            styleText(UNDERLINE, FALSE);
        }
        else if (option.selected - 1 == i)
        {
            styleText(BOLD, TRUE);
            printf("%s", option.names[i]);
            styleText(BOLD, FALSE);
        }
        else 
            printf("%s", option.names[i]);
    }
}



/******************************************************************************
    This function lets the user navigate through the different options using
        the arrow keys.
******************************************************************************/
void
userNavigation(userNav *pos,
               options menu[MAX_ROW_OPTIONS])
{
    int input;
    bool end = FALSE;

    cursorVisibility(FALSE);
    printf("\33[1G");
    displayAllOptions(menu, pos->rowMax);

    do
    {
        input = getch(); //get the key press

        if (input == 0 || input == 224) //if the input are the arrow keys
        {
            switch (getch()) //get the input again
            {
                case UP_ARROW:
                    if (pos->row > 0)
                    {
                        //remove the hover & underline
                        menu[pos->row].hover = 0;

                        //move the cursor to the start of the previous set of options
                        moveCursorX(1);

                        //display the original options to remove the underline
                        displayOptions(menu[pos->row]);

                        //move the cursor at the desired y location
                        moveCursor(0, menu[pos->row].x - menu[pos->row - 1].x - 1);
                        moveCursor(0, 1);

                        //update the positions
                        pos->col = 0;
                        pos->row--;

                        //put the hover at the starting option of the next set of options
                        menu[pos->row].hover = 1;
                    }
                    break;
                case DOWN_ARROW:
                    if (pos->row < pos->rowMax)
                    {
                        //remove the hover & underline
                        menu[pos->row].hover = 0;

                        //move the cursor to the next set of options
                        moveCursorX(1);

                        //display the original options to remove the underline
                        displayOptions(menu[pos->row]);

                        //move the cursor at the start of the next line
                        moveCursor(0, (menu[pos->row + 1].x - menu[pos->row].x) * -1);
                        moveCursorX(1);

                        //update the positions
                        pos->col = 0;
                        pos->row++;

                        //put the hover at the starting option of the next set of options
                        menu[pos->row].hover = 1;
                    }
                    break;
                case RIGHT_ARROW:
                    //update the position. Wrap to the start if it goes beyond the max options
                    pos->col = (pos->col + 1) % menu[pos->row].nOptions;

                    //update the hover position
                    menu[pos->row].hover = pos->col + 1;
                    break;
                case LEFT_ARROW:
                    //update the position
                    if (pos->col == 0) //wrap to the last option if needed
                        pos->col = menu[pos->row].nOptions - 1;
                    else
                        pos->col--;

                    //update the hover position
                    menu[pos->row].hover = pos->col + 1;
                    break;
            }

            moveCursorX(1);
            displayOptions(menu[pos->row]);
        }
        else if (input == ENTER)
            if (pos->col + 1 != menu[pos->row].selected) //if the option has not been selected previously
            {
                //set selected to the chosen option
                menu[pos->row].selected = pos->col + 1;

                //initialize the next set of options depending on the option selected
                initializeOptions(pos, menu);

                //remove the hover & underline
                menu[pos->row].hover = 0;

                //update the positions
                pos->row++;
                pos->col = 0;

                //terminate the loop
                end = TRUE;
            }
    } while (!end);
}



void
initializeOptions(userNav *pos,
                  options rowOptions[MAX_ROW_OPTIONS])
{
    if (rowOptions[0].selected == UPDATE_RECIPE_BOX)
    {
        //printf("ADD CALORIE INFO | VIEW CALORIE CHART | SAVE CALORIES | LOAD CALORIES | ADD RECIPE | MODIFY RECIPE | DELETE RECIPE | LIST RECIPES | SCAN RECIPES | SEARCH RECIPE | EXPORT RECIPES | IMPORT RECIPES");
        pos->rowMax = 1;
        strcpy(rowOptions[1].names[0], "ADD CALORIE INFO");
        strcpy(rowOptions[1].names[1], "VIEW CALORIE CHART");
        strcpy(rowOptions[1].names[2], "SAVE CALORIES");
        strcpy(rowOptions[1].names[3], "LOAD CALORIES");
        strcpy(rowOptions[1].names[4], "ADD RECIPE");
        strcpy(rowOptions[1].names[5], "MODIFY RECIPE");
        strcpy(rowOptions[1].names[6], "DELETE RECIPE");
        strcpy(rowOptions[1].names[7], "LIST RECIPES");
        strcpy(rowOptions[1].names[8], "SCAN RECIPES");
        strcpy(rowOptions[1].names[9], "SEARCH RECIPE");
        strcpy(rowOptions[1].names[10], "EXPORT RECIPES");
        strcpy(rowOptions[1].names[11], "IMPORT RECIPES");
        rowOptions[1].nOptions = 12;
        rowOptions[1].hover = 1;
        rowOptions[1].selected = 0;
        rowOptions[1].x = 2;
    }

    else if (rowOptions[0].selected == ACCESS_RECIPE_BOX)
    {

    }

    else if (rowOptions[0].selected == ACCOUNT)
    {
        printf("yayyy");
    }
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



/******************************************************************************
    This function displays the header ASCII art of the program.
******************************************************************************/
void
displayHeader()
{
    paintText(BACKGROUND, 255, 255, 255); //change the background to white
    paintText(FOREGROUND, 0, 255, 0); //change the text color to green
    styleText(BOLD, TRUE);
    printf("  __   ____   ___  _  _  __  _  _  ____     __  ____     __   _  _  ____    ____  ____  ___  __  ____  ____  ____ \n");
    printf(" / _\\ (  _ \\ / __)/ )( \\(  )/ )( \\(  __)   /  \\(  __)   /  \\ / )( \\(  _ \\  (  _ \\(  __)/ __)(  )(  _ \\(  __)/ ___)\n");
    printf("/    \\ )   /( (__ ) __ ( )( \\ \\/ / ) _)   (  O )) _)   (  O )) \\/ ( )   /   )   / ) _)( (__  )(  ) __/ ) _) \\___ \\\n");
    printf("\\_/\\_/(__\\_) \\___)\\_)(_/(__) \\__/ (____)   \\__/(__)     \\__/ \\____/(__\\_)  (__\\_)(____)\\___)(__)(__)  (____)(____/\n");
    resetText();
}


/******************************************************************************
    This function prints a divider on the screen. The character is based on
    the passed character and the length of the line is determined by the
    passed integer.
    Preconditions:
        1. ch is a character that exist in the normal ASCII table.
        2. len is a positive integer.

    @param ch the character to be continuously printed to form a line.
    @param len the length of the line to be printed.
******************************************************************************/
void
printLine(char ch,
          int len)
{
    int i;
    char line[len + 1];

    for (i = 0; i < len; i++)
        line[i] = ch;
    line[i] = '\0';
    printf("%s\n", line);
}


#endif