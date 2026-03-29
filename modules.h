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

    @param state decides the visibility of the cursor. true for visible,
        false for invisible.
******************************************************************************/
void
cursorVisibility(bool state)
{
    if (state == true)
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
    This function adds or removes a specific style to the text. The following
        styles are: bold, italic, underline, and strikethrough.

    @param type decides what style to add / remove.
    @param state decides whether to add or remove the style. if true then add,
        otherwise remove.
******************************************************************************/
void
styleText(styleType type,
          bool state)
{
    switch(type)
    {
        case BOLD:
            if (state == true)
                printf("\33[1m");
            else
                printf("\33[22m");
            break;
        case ITALIC:
            if (state == true)
                printf("\33[3m");
            else
                printf("\33[23m");
            break;
        case UNDERLINE:
            if (state == true)
                printf("\33[4m");
            else
                printf("\33[24m");
            break;
        case STRIKETHROUGH:
            if (state == true)
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
    @return outputs true if its within range, false otherwise.
******************************************************************************/
bool
isInRange(long long value,
          int min,
          int max)
{
    bool result;

    if (value >= min && value <= max)
        result = true;
    else
        result = false;

    return result;
}



/******************************************************************************
    This function checks whether the integer is within the given range
    
    @param value the value to be evaluated.
	@param min the minimum value the input can be.
	@param max the maximum value the input can be.
    @return outputs true if its within range, false otherwise.
******************************************************************************/
bool
floatInRange(double value,
             float min,
             float max)
{
    bool result;

    if (value >= min && value <= max)
        result = true;
    else
        result = false;

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

        cursorVisibility(true);

        input = getch(); //get the key press

        cursorVisibility(false);

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
                default:
                    moveCursor(i * -1, 0); //move the cursor to the start of the string
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
            for (j = len; j >= i; j--) //shift everything to the right of the cursor
                str[j + 1] = str[j];

            moveCursor(i * -1, 0); //move the cursor to the start of the string
            str[i] = input;
            i++;
        }

        else if (type == INTEGER && isInRange(input, '0', '9') && len < size)
        {
            for (j = len; j >= i; j--) //shift everything to the right of the cursor
                str[j + 1] = str[j];

            moveCursor(i * -1, 0); //move the cursor to the start of the string
            str[i] = input;
            i++;
        }

        else if (type == FRACTION && (isInRange(input, '0', '9') || input == '.') && len < size)
        {
            for (j = len; j >= i; j--) //shift everything to the right of the cursor
                str[j + 1] = str[j];

            moveCursor(i * -1, 0); //move the cursor to the start of the string
            str[i] = input;
            i++;
        }

        else if (type == CHARACTER && isInRange(input, ' ', '~') && len < size)
        {
            for (j = len; j >= i; j--) //shift everything to the right of the cursor
                str[j + 1] = str[j];

            moveCursor(i * -1, 0); //move the cursor to the start of the string
            str[i] = input;
            i++;
        }

        else
            moveCursor(i * -1, 0); //move the cursor to the start of the string

        len = strlen(str);

    } while (input != ENTER);

    cursorVisibility(true);
    
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
    This function converts a integer into a string.
    Preconditions:
        1. The parameter num does not exceed the integer limits.
        2. The string is initialized.

    @param num is the integer to be converted.
    @param str where the converted string is to be stored.
    @return a copy of the final string.
******************************************************************************/
char *
intToString(int num,
            char str[])
{
    int i = 0;
    bool isNegative = false;

    if (num == 0)
    {
        str[i++] = '0';
    }

    if (num < 0)
    {
        isNegative = true;
    }
    

    while (abs(num) > 0)
    {
        str[i] = '0' + abs(num) % 10; //extract the last digit
        i++;
        num /= 10; //remove the last digit
    }

    if (isNegative)
    {
        str[i++] = '-'; //append a sign if negative
    }

    str[i] = '\0'; //end with a null byte

    reverseString(str); //reverse the string

    return str;
}



/******************************************************************************
	This function will check whether the passed fileName is valid specifically
		in a windows environment.
	Preconditions:
		1. The file name does not contain any reserved names in windows.

	@param fileName the string to be checked.
	@param fileExt the desired extention of the file including the dot '.'.
	@return true if the file name is valid, false otherwise.
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
	{
        isValid = false;
        paintText(FOREGROUND, 255, 0, 0);
        printf("Error: Must have at least one character aside from the extention.\n");
        resetText();
    }
	else if (absStrCmp(fileName + nameLen - extLen, fileExt) == 0) //check if it has the right file extention.
		isValid = true;
    else
    {
        isValid = false;
        paintText(FOREGROUND, 255, 0, 0);
        printf("Error: Must have a valid extention -> \"%s\".\n", fileExt);
        resetText();
    }

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
			isValid = false;
            paintText(FOREGROUND, 255, 0, 0);
            printf("Error: Input contain(s) disallowed character(s).\n");
            resetText();
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
    This function will convert a array of strings into a single string.
    Preconditions:
        1. The contents of the array are strings.
        2. The array is initialized.
        3. nElem and maxLen are positive integers.

    @param maxLen is the maximum amount of characters each string can hold.
    @param nElem is the number of elements in the array.
    @param arr is the array to be converted.
    @param str where the final string is stored.
    @return a copy of the final string.
******************************************************************************/
char *
arrayToString(int maxLen,
              int nElem,
              char arr[nElem][maxLen],
              char str[nElem * maxLen])
{
    int i;

    for (i = 0; i < nElem; i++)
    {
        if (i > 0)
            strcat(str, ",");

        if (i == 0)
            strcpy(str, arr[i]);
        else
            strcat(str, arr[i]);
    }

    return str;
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
            case CLASS:
                break;
        }
        
        //swap if necessary
        if (i != swap)
        {
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[swap]);
            strcpy(arr[swap], temp);
        }
    }
}



/******************************************************************************
    This function reverses a string.
    Preconditions:
        1. The string is initialized.

    @param str is the string to be reversed.
    @return a copy of the reversed string.
******************************************************************************/
char *
reverseString(char str[])
{
    int start = 0;
    int end = strlen(str) - 1;
    char temp;

    for (start = 0; start < end; start++, end--)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
    }

    return str;
}



/******************************************************************************
    This function searches an array of strings and returns the index of
        the string that is equivalent to the passed key string.
    Preconditions:
        1. The strings are initialized.
        2. The nElem and maxLen parameters are non-negative integers.

    @param nElem is the amount of elements in the array.
    @param maxLen is the maximum length of the strings including the
        null byte.
    @param arr is the array of strings to be searched.
    @param key is the string to be searched for in the array.
    @return is the index of where the key string was found. Returns -1 if
        the key string does not exists.
******************************************************************************/
int
stringSearch(int nElem,
             int maxLen,
             char arr[nElem][maxLen],
             char key[maxLen])
{
    int i;
    int index = -1;

    for (i = 0; i < nElem && index == -1; i++)
        if (strcmp(arr[i], key) == 0)
            index = i;

    return index;
}



/******************************************************************************
    This function searches an array of recipeType structures and returns
        the index of the first recipe name that is equivalent to the
        passed key.
    Preconditions:
        1. The strings and array are initialized.

    @param recipes is the array of recipeType structures to be searched.
    @param key is the string to be searched for in the array.
    @return is the index of where the key string was first found. Returns -1
        if the key string does not exists.
******************************************************************************/
int
recipeNameSearch(recipeList recipes,
                 string20 key)
{
    int i;
    string20 arr[recipes.nRecipes];

    //transfer the recipe names into a array of strings
    for (i = 0; i < recipes.nRecipes; i++)
        strcpy(arr[i], recipes.recipeList[i].name);

    return stringSearch(recipes.nRecipes, 21, arr, key);
}



/******************************************************************************
    This function searches an array of ingredientType structures and returns
        the index of the first ingredient name that is equivalent to the
        passed key.
    Preconditions:
        1. The strings and array are initialized.
        2. The parameter nElem is a non-negative integer.

    @param nElem is the amount of elements in the array.
    @param list is the array of ingredientType structures to be searched.
    @param key is the string to be searched for in the array.
    @return is the index of where the key string was first found. Returns -1
        if the key string does not exists.
******************************************************************************/
int
ingredientNameSearch(int nElem,
                     ingredientType list[nElem],
                     string20 key)
{
    int i;
    string20 arr[nElem];

    //transfer the ingredient names into a array of strings
    for (i = 0; i < nElem; i++)
        strcpy(arr[i], list[i].item);

    return stringSearch(nElem, 21, arr, key);
}



/******************************************************************************
    This function initializes the structure of recipeType.

    @param recipe is the structure to be initialized.
******************************************************************************/
void
initializeRecipe(recipeType *recipe)
{
    int i;
    ingredientType ingredient;

    //initialize ingredients
    strcpy(ingredient.item, "");
    ingredient.quantity = 0;
    strcpy(ingredient.unit, "");
    ingredient.calorie = 0;

    //initialize classification
    strcpy(recipe->name, "");
    recipe->class = NONE;
    
    for (i = 0; i < MAX_RECIPE_INGREDIENTS; i++)
        recipe->ingredients[i] = ingredient;

    for (i = 0; i < MAX_INSTRUCTIONS; i++)
        strcpy(recipe->instructions[i], "");

    recipe->nIngredients = 0;
    recipe->nInstructions = 0;
    recipe->servings = 0;
    recipe->totalCalories = 0;
}



/******************************************************************************
    This function initializes all of the data in the recipeList structure.

    @param recipes is the address of the recipeList structure.
******************************************************************************/
void
initializeRecipeList(recipeList *recipes)
{
    int i;
    recipes->nRecipes = 0;

    for (i = 0; i < MAX_RECIPES; i++)
        initializeRecipe(&recipes->recipeList[i]);
}



/******************************************************************************
    This function initializes all of the data in the calorieList structure.

    @param calories is the address of the calorieList structure.
******************************************************************************/
void
initializeCalories(calorieList *calories)
{
    int i;
    ingredientType ingredient;
    calories->nElem = 0;

    strcpy(ingredient.item, "");
    ingredient.quantity = 0;
    strcpy(ingredient.unit, "");
    ingredient.calorie = 0;

    for (i = 0; i < MAX_INGREDIENTS; i++)
            calories->calorieList[i] = ingredient;
}



/******************************************************************************
    This function sorts an array of recipeType structures according to the
        passed type of sorting. These are: INCREASING which sorts from
        smallest to biggest, DECREASING which sorts from biggest to smallest,
        and CLASS which sorts according to the classification (STARTER ->
        MAIN -> DESSERT).
    Preconditions:
        1. The strings and array are initialized.

    @param type decides what type of sort is to be done: INCREASING,
        DECREASING, or CLASS.
    @param list is the array to be sorted.
******************************************************************************/
void
sortRecipeList(sortType type,
               recipeList *list)
{
    int i, j;
    int swap;
    recipeType temp;

    for (i = 0; i < list->nRecipes - 1;i++)
    {
        swap = i; //assume the first element is the largest/smallest
        
        switch (type)
        {
            case INCREASING:
                for (j = i + 1; j < list->nRecipes; j++)
                    if (strcmp(list->recipeList[swap].name, list->recipeList[j].name) > 0)
                        swap = j;
                break;
            case DECREASING:
                for (j = i + 1; j < list->nRecipes; j++)
                    if (strcmp(list->recipeList[swap].name, list->recipeList[j].name) < 0)
                        swap = j;
                break;
            case CLASS:
                for (j = i + 1; j < list->nRecipes; j++)
                    if (list->recipeList[swap].class > list->recipeList[j].class)
                        swap = j;
                break;
        }
        
        //swap if necessary
        if (i != swap)
        {
            temp = list->recipeList[i];
            list->recipeList[i] = list->recipeList[swap];
            list->recipeList[swap] = temp;
        }
    }
}



/******************************************************************************
    This function appends a ingredientType structure to a existing array.
    Preconditions:
        1. The strings and array are initialized.
        2. The parameter nElem is a non-negative integer.

    @param type corresponds to the type of the struct: RECIPES for recipeType,
        CALORIES for calorieList.
    @param nElem is the amount of elements in the array.
    @param list is the array where the new ingredient would be appended.
******************************************************************************/
void
addIngredient(listType type,
              int *nElem,
              ingredientType list[*nElem])
{
    bool success = true;
    ingredientType temp;
    int index = *nElem;

    //initialize
    strcpy(temp.item, "");
    temp.quantity = 0.0;
    strcpy(temp.unit, "");
    temp.calorie = 0.0;

    //item
    do
    {
        if (type == RECIPES)
            printf("Enter ingredient #%d name: ", *nElem + 1);
        else
            printf("Enter ingredient name: ");

        getInput(CHARACTER, temp.item, 20);
        printf("\n");

        if (ingredientNameSearch(*nElem, list, temp.item) == -1) //check if its unique
        {
            success = true;
            strcpy(list[index].item, temp.item); //store
            (*nElem)++; //update the count
        }
        else
        {
            paintText(FOREGROUND, 255, 0, 0);
            printf("Error: %s already exists!\n", temp.item);
            resetText();
        }
    } while (success == false);

    success = false;

    //quantity
    do
    {
        printf("Enter quantity: ");
        scanf("%f", &temp.quantity);

        if (floatInRange(temp.quantity, 0, FLT_MAX))
        {
            success = true;
            list[index].quantity = temp.quantity;
        }
        else
            displayError("Not within the range: [0.0, FLT_MAX].");
    } while (success == false);

    success = false;

    //unit
    do
    {
        printf("Enter unit: ");
        getInput(CHARACTER, temp.unit, 20);
        printf("\n");

        if (strlen(temp.unit) > 0)
        {
            success = true;
            strcpy(list[index].unit, temp.unit);
        }
        else
            displayError("Must have at least 1 character!");
    } while (success == false);

    success = false;

    if (type == CALORIES)
    {
        //calories
        do
        {
            printf("Enter calories: ");
            scanf("%f", &temp.calorie);
            if (floatInRange(temp.calorie, 0.0, FLT_MAX))
            {
                success = true;
                list[index].calorie = temp.calorie;
            }
            else
                displayError("Not within the range: [0.0, FLT_MAX].");
        } while (success == false);
    }
}



/******************************************************************************
    This function removes an ingredient and shifts every element to the
        right side of the removed index to the left by 1.
    Preconditions:
        1. The strings and array are initialized.

    @param recipe contains the array of ingredients.
******************************************************************************/
void
removeIngredient(recipeType *recipe)
{
    int i;
    int index;
    optionType option;

    if (recipe->nIngredients > 1)
    {
        //initialize the options
        strcpy(option.prompt, "Choose the number of the ingredient to be deleted:");
        option.nOptions = recipe->nIngredients;

        //display ingredients
        for(i = 0; i < recipe->nIngredients; i++)
            strcpy(option.options[i], recipe->ingredients[i].item);

        index = displayOptions(option) - 1; //get the index to be deleted

        recipe->nIngredients--; //update the ingredient count

        //shift elements
        for (i = index; i < recipe->nIngredients; i++)
            recipe->ingredients[i] = recipe->ingredients[i + 1];
    }
    else
        displayError("Recipe must have at least 1 ingredient!");
}



/******************************************************************************
    This function appends a string to a existing array.
    Preconditions:
        1. The strings and array are initialized.

    @param recipe is the structure where the array of strings exists.
******************************************************************************/
void
addInstruction(recipeType *recipe)
{
    bool isValid = false;
    string70 temp = "";

    if (recipe->nInstructions < MAX_INSTRUCTIONS - 1)
    {
        do
        {
            printf("Enter instruction #%d: ", recipe->nInstructions + 1);
            getInput(CHARACTER, temp, 70);
            printf("\n");

            if (strlen(temp) > 0)
            {
                isValid = true;
                strcpy(recipe->instructions[recipe->nInstructions++], temp); //store
            }
            else
                displayError("Must have at least 1 character!");
        } while (isValid == false);
    }
    else
        displayError("Max instructions reached!");
}



/******************************************************************************
    This function removes an instruction and shifts every element to the
        right side of the removed index to the left by 1.
    Preconditions:
        1. The strings and array are initialized.

    @param recipe contains the array of instructions.
******************************************************************************/
void
removeInstructions(recipeType *recipe)
{
    int i;
    int index;
    optionType option;

    if (recipe->nInstructions > 1)
    {
        //initialize the options
        strcpy(option.prompt, "Choose the number of the instruction to be deleted:");
        option.nOptions = recipe->nInstructions;

        //display instructions
        for(i = 0; i < recipe->nInstructions; i++)
            strcpy(option.options[i], recipe->instructions[i]);

        index = displayOptions(option) - 1; //get the index to be deleted

        recipe->nInstructions--; //update the instruction count

        //shift elements
        for (i = index; i < recipe->nInstructions; i++)
            strcpy(recipe->instructions[i], recipe->instructions[i + 1]);
    }
    else
        displayError("Recipe must have at least 1 instruction!");
}



/******************************************************************************
    This function removes a structure of recipeType and shifts every element
        to the right side of the removed index to the left by 1.
    Preconditions:
        1. The array of structures are initialized.

    @param recipe contains the array of recipeType structures.
******************************************************************************/
void
removeRecipe(recipeList *recipes)
{
    int i;
    int index;
    string20 name = "";

    if (recipes->nRecipes > 0)
    {
        displayRecipeList(recipes);

        printf("\nEnter the recipe title to be deleted: ");
        getInput(CHARACTER, name, 20);
        printf("\n");

        index = recipeNameSearch(*recipes, name); //get the index to be deleted

        if (index >= 0)
        {
            recipes->nRecipes--; //update the ingredient count

            //shift elements
            for (i = index; i < recipes->nRecipes; i++)
                recipes->recipeList[i] = recipes->recipeList[i + 1];
        }
        else
            displayError("Recipe title does not exists!");
    }
    else
        displayError("Must have at least 1 recipe!");
}



/******************************************************************************
    This function extracts a string from a file until it hits a new line
        character.
    Preconditions:
        1. This function is called after the desired file was opened.
        2. The parameter maxLen is a positive integer.

    @param fp is the file pointer.
    @param maxChar is the maximum characters the character array can store not
        including the null byte.
    @param arr is the array where the extracted string is to be stored.
    @return a copy of the extracted string.
******************************************************************************/
char *
getFileStr(FILE *fp,
          int maxChar,
          char arr[maxChar + 1])
{
    int i = 0;
    char ch;

    while ((ch = fgetc(fp)) != EOF && ch != '\n' && i <= maxChar)
        arr[i++] = ch;

    arr[i] = '\0';

    return arr;
}



/******************************************************************************
    This function writes all the information stored in the array of structures
        in a desired file.
    Preconditions:
        1. The parameter fileName and arr are initialized.
        2. The fileName is valid.

    @param fileName is the name of the file where the data would be
        written on.
    @param arr is the array that contains the information to be written.
******************************************************************************/
void
saveCalorieInfo(string20 fileName,
                calorieList arr)
{
    FILE *fp;
    int i;

    if ((fp = fopen(fileName, "w")) != NULL)
    {
        for (i = 0; i < arr.nElem; i++)
        {
            fprintf(fp, "%s\n%.2f %s %.2f\n\n", arr.calorieList[i].item,
                                                arr.calorieList[i].quantity,
                                                arr.calorieList[i].unit,
                                                arr.calorieList[i].calorie);
        }

        paintText(FOREGROUND, 0, 255, 0);
        printf("\"Saving Calorie Info to \"%s\" Complete!\n", fileName);
        resetText();

        fclose(fp);
    }
    else
        displayError("File does not exists!");
}



/******************************************************************************
    This function scans the given file and stores all of its contents into
        the passed array of structures.
    Preconditions:
        1. The parameter fileName and arr are initialized.
        2. The fileName is valid and exists.

    @param fileName is the name of the file where the data to be stored exists.
    @param arr is the array where the contents are to be stored.
******************************************************************************/
void
loadCalorieInfo(string20 fileName,
                calorieList *arr)
{
    FILE *fp;
    int i, j;
    bool dupe = false;
    optionType option;

    enum options
    {
        OVERWRITE = 1,
        KEEP
    };

    strcpy(option.options[0], "Overwrite the previous entry.");
    strcpy(option.options[1], "Keep the original entry.");
    option.nOptions = 2;

    if (arr->nElem < MAX_INGREDIENTS && (fp = fopen(fileName, "rt")) != NULL)
    {
        i = arr->nElem;

        while (i < MAX_INGREDIENTS && strlen(getFileStr(fp, 20, arr->calorieList[i].item)) > 0)
        {
            dupe = false;

            //store the data
            fscanf(fp, "%f %15s %f\n\n", &arr->calorieList[i].quantity,
                                         arr->calorieList[i].unit,
                                         &arr->calorieList[i].calorie);

            //search for duplicates
            if (i != 0) //if nothing is stored, dont search
                for (j = 0; j < i && dupe == false; j++)
                    if (strcmp(arr->calorieList[i].item, arr->calorieList[j].item) == 0)
                    {
                        dupe = true;
                        strcpy(option.prompt, arr->calorieList[i].item);
                        strcat(option.prompt, " already exists!");
                        displayError("Duplicate entry!");

                        if (displayOptions(option) == OVERWRITE)
                            arr->calorieList[j] = arr->calorieList[i];
                    }
            if (dupe == false)
                i++;
        }
        
        arr->nElem = i; //update the count

        paintText(FOREGROUND, 0, 255, 0);
        printf("\nLoading \"%s\" Complete!\n", fileName);
        resetText();

        fclose(fp);
    }
    else
        displayError("Calorie list is full / file does not exist!");
}



/******************************************************************************
    This function writes all the information stored in the array of structures
        in a desired file.
    Preconditions:
        1. The parameter fileName and arr are initialized.
        2. The fileName is valid.

    @param fileName is the name of the file where the data would be
        written on.
    @param arr is the array that contains the information to be written.
******************************************************************************/
void
saveRecipes(string20 fileName,
            recipeList list)
{
    FILE *fp;
    int i, j;

    if ((fp = fopen(fileName, "w")) != NULL)
    {
        for (i = 0; i < list.nRecipes; i++)
        {
            fprintf(fp, "%s\n", list.recipeList[i].name);
            fprintf(fp, "%d ", list.recipeList[i].servings);

            switch(list.recipeList[i].class)
            {
                case NONE:
                    fprintf(fp, "none\n");
                    break;

                case STARTER:
                    fprintf(fp, "starter\n");
                    break;

                case MAIN:
                    fprintf(fp, "main\n");
                    break;

                case DESSERT:
                    fprintf(fp, "dessert\n");
                    break;
            }

            fprintf(fp, "Ingredients %d\n", list.recipeList[i].nIngredients);
            
            for (j = 0; j < list.recipeList[i].nIngredients; j++)
            {
                fprintf(fp, "%.2f %s %s\n", list.recipeList[i].ingredients[j].quantity,
                                            list.recipeList[i].ingredients[j].unit,
                                            list.recipeList[i].ingredients[j].item);
            }

            fprintf(fp, "Steps %d\n", list.recipeList[i].nInstructions);
            
            for (j = 0; j < list.recipeList[i].nInstructions; j++)
                fprintf(fp, "%s\n", list.recipeList[i].instructions[j]);

            fprintf(fp, "\n");
        }

        paintText(FOREGROUND, 0, 255, 0);
        printf("\"Saving Recipe List to \"%s\" Complete!\n", fileName);
        resetText();

        fclose(fp);
    }
    else
        displayError("File does not exists!");
}



/******************************************************************************
    This function scans the given file and stores all of its contents into
        the passed array of structures.
    Preconditions:
        1. The parameter fileName and arr are initialized.
        2. The fileName is valid and exists.

    @param fileName is the name of the file where the data to be stored exists.
    @param arr is the array where the contents are to be stored.
******************************************************************************/
void
loadRecipes(string20 fileName,
            recipeList *list)
{
    FILE *fp;
    int i, j;
    char class[10];
    bool dupe = false;
    optionType option;

    enum options
    {
        OVERWRITE = 1,
        KEEP
    };

    strcpy(option.options[0], "Overwrite the previous entry.");
    strcpy(option.options[1], "Keep the original entry.");
    option.nOptions = 2;

    if (list->nRecipes < MAX_RECIPES && (fp = fopen(fileName, "rt")) != NULL)
    {
        i = list->nRecipes; //start at the last element

        while (i < MAX_RECIPES && strlen(getFileStr(fp, 20, list->recipeList[i].name)) > 0)
        {
            dupe = false;

            //store the data
            fscanf(fp, "%d %9s\n", &list->recipeList[i].servings, class);

            if (absStrCmp(class, "starter") == 0)
                list->recipeList[i].class = STARTER;
            else if (absStrCmp(class, "main") == 0)
                list->recipeList[i].class = MAIN;
            else if (absStrCmp(class, "dessert") == 0)
                list->recipeList[i].class = DESSERT;

            fscanf(fp, "Ingredients %d\n", &list->recipeList[i].nIngredients);

            for (j = 0; j < list->recipeList[i].nIngredients; j++)
            {
                fscanf(fp, "%f %15s %20s\n", &list->recipeList[i].ingredients[j].quantity,
                                             list->recipeList[i].ingredients[j].unit,
                                             list->recipeList[i].ingredients[j].item);
            }

            fscanf(fp, "Steps %d\n", &list->recipeList[i].nInstructions);
            
            for (j = 0; j < list->recipeList[i].nInstructions; j++)
                fscanf(fp, "%s\n", list->recipeList[i].instructions[j]);

            //search for duplicates
            if (i != 0) //if nothing is stored, dont search
                for (j = 0; j < i && dupe == false; j++)
                    if (strcmp(list->recipeList[i].name, list->recipeList[j].name) == 0)
                    {
                        dupe = true;
                        strcpy(option.prompt, list->recipeList[j].name);
                        strcat(option.prompt, " already exists!");
                        displayError("Duplicate entry!");

                        if (displayOptions(option) == OVERWRITE)
                            list->recipeList[j] = list->recipeList[i];
                    }
            if (dupe == false)
                i++;
        }
        
        list->nRecipes = i; //update the count

        paintText(FOREGROUND, 0, 255, 0);
        printf("\nLoading \"%s\" Complete!\n", fileName);
        resetText();

        fclose(fp);
    }
    else
        displayError("Recipe list is full / file does not exist!");
}



/******************************************************************************
    This function updates each recipe ingredient calorie count and its total
        calories if that ingredient exists in the calorieList structure.
    Preconditions:
        1. The structures are initialized.

    @param recipes is the structure to be updated.
    @param calories is the source of the data.
******************************************************************************/
void
updateCalories(recipeList *recipes,
               calorieList calories)
{
    int i, j;
    int index = -1;
    double calPerUnit = 0.0;
    double total = 0;

    for (i = 0; i < recipes->nRecipes; i++)
    {
        total = 0.0;
        for (j = 0; j < recipes->recipeList[i].nIngredients; j++)
        {
            if ((index = ingredientNameSearch(calories.nElem, calories.calorieList, recipes->recipeList[i].ingredients[j].item)) != -1)
            {
                if (calories.calorieList[index].quantity > 0)
                {
                    calPerUnit = calories.calorieList[index].calorie / calories.calorieList[index].quantity;
                    recipes->recipeList[i].ingredients[j].calorie = (float) calPerUnit * recipes->recipeList[i].ingredients[j].quantity;
                }
            }

            total += recipes->recipeList[i].ingredients[j].calorie;
        }
        recipes->recipeList[i].totalCalories = (float) total;
    }
}



/******************************************************************************
    This function would return a random recipe that has the exact same
        classification with the passed class parameter and does not exceed the
        maxCal value.
    Preconditions:
        1. The structures are initialized.
        2. The parameter maxCal is initialized.

    @param class is the classification of the recipe.
    @param recipes contains all existing recipes.
    @param maxCal is the maximum calories a recipe can be.
    @return is the random recipe that was chosen and met all requirements.
******************************************************************************/
recipeType
randRecipe(recipeClass class,
           recipeList recipes,
           double *maxCal)
{
    recipeList validRecipes;
    recipeType selected;
    int i;
    double calPerServing;

    initializeRecipeList(&validRecipes);
    initializeRecipe(&selected);

    for (i = 0; i < recipes.nRecipes; i++)
    {
        if (recipes.recipeList[i].servings > 0)
            calPerServing = recipes.recipeList[i].totalCalories / recipes.recipeList[i].servings;
        else
            calPerServing = 0.0;

        if (recipes.recipeList[i].class == class && calPerServing <= *maxCal)
            validRecipes.recipeList[validRecipes.nRecipes++] = recipes.recipeList[i];
    }

    if (validRecipes.nRecipes > 0)
    {
        selected = validRecipes.recipeList[rand() % validRecipes.nRecipes];
        if (selected.servings > 0)
            *maxCal -= selected.totalCalories / selected.servings;
    }

    return selected;
}



/******************************************************************************
*                                                                             *
*                             Display Functions                               *
*                                                                             *
******************************************************************************/


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



/******************************************************************************
    This function displays the prompt and all the available options. This
        function would also get the use's input depending on what option
        they chose.
    Preconditions:
        1. The strings are initialized.
        2. The parameter nOptions is a positive integer.
        3. The strings in the array options must have a string length of under
            70 total characters not including the null byte.
        4. The parameter nOptions should not exceed the maximum amount of
            elements stored in the options array.

    @param prompt is a string containing the prompt to be displayed.
    @param options is a array of strings containing the available options.
    @param nOptions is the number of options to be displayed.
******************************************************************************/
int
displayOptions(optionType option)
{
    int i;
    string20 input = "";
    string20 max = "";
    string70 errorMsg;
    bool success = false;

    //print the option prompt
    printf("\n%s\n", option.prompt);

    for (i = 0; i < option.nOptions; i++)
        printf("%d. %s\n", i + 1, option.options[i]);

    printf("\n");

    //get the input
    do
    {
        printf("Input: ");
        getInput(INTEGER, input, 20);
        printf("\n");

        if (isInRange(stringToInt(input), 1, option.nOptions))
            success = true;
        else
        {
            strcpy(errorMsg, "Input is not within the range [1,");
            strcat(errorMsg, intToString(option.nOptions, max));
            strcat(errorMsg, "].");
            displayError(errorMsg);
        }
    } while (success == false);
    
    return stringToInt(input);
}



/******************************************************************************
    This function displays a string indicating where the user is currently in.
    Preconditions:
        1. The strings are initialized.

    @param action decides whether to append or remove a path. ACCESS for
        append, QUIT for remove.
    @param screenPath is a string that contains the screen path to
        be displayed.
    @param screenName is the string containing the screen name to be
        appended or deleted.
******************************************************************************/
void
displayScreenPath(pathType action,
                  char screenPath[],
                  char screenName[])
{
    int delete = 0;

    if (action == ACCESS)
    {
        if ((int) strlen(screenPath) > 0)
            strcat(screenPath, " -> "); //append a divider

        strcat(screenPath, screenName);
        printf("%s", screenPath);
    }
    else if (action == QUIT)
    {
        delete = strlen(screenPath) - strlen(screenName) - strlen(" -> ");

        if (delete < 0)
            delete = 0;

        screenPath[delete] = '\0';
    }
}



/******************************************************************************
    This function displays an error message.
    Preconditions:
        1. The string are initialized.

    @param errorMsg is ths string to be displayed.
******************************************************************************/
void
displayError(char errorMsg[])
{
    paintText(FOREGROUND, 255, 0, 0); //change the color to red
    printf("Error: %s\n", errorMsg);
    resetText();
}



/******************************************************************************
    This function displays all of the information stored in the recipeType
        structure.
    Preconditions:
        1. The structure is initialized.

    @param recipe is the recipeType structure to be displayed.
******************************************************************************/
void
displayRecipe(recipeType recipe)
{
    int i;

    printf("%-20s     ", recipe.name);
    printf("%d", recipe.servings);
    moveCursorX(35);
    printf("%.2f\n", recipe.totalCalories);

    switch(recipe.class)
        {
            case NONE:
                printf("None\n");
                break;
            case STARTER:
                printf("Starter\n");
                break;
            case MAIN:
                printf("Main\n");
                break;
            case DESSERT:
                printf("Dessert\n");
                break;
        }

    printf("\nIngredients:\n");

    for (i = 0; i < recipe.nIngredients; i++)
    {
        printf("%.2f", recipe.ingredients[i].quantity);
        moveCursorX(15);
        printf("%-15s  ", recipe.ingredients[i].unit);
        printf("%-20s   ", recipe.ingredients[i].item);
        printf("%.2f\n", recipe.ingredients[i].calorie);
    }

    printf("Procedure:\n");

    for (i = 0; i < recipe.nInstructions; i++)
        printf("%d. %-70s\n", i + 1, recipe.instructions[i]);
}



/******************************************************************************
    This function displays all of the recipe names stored in the struct.
    Preconditions:
        1. The structure is initialized.

    @param recipe is the recipeType structure that contains the names
        to be displayed.
******************************************************************************/
void
displayRecipeList(recipeList *recipes)
{
    int i;

    sortRecipeList(INCREASING, recipes);

    printf("Recipe Titles:\n");

    for (i = 0; i < recipes->nRecipes; i++)
        printf("%s\n", recipes->recipeList[i].name);
}



#endif