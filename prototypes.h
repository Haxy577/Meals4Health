/*************************************************************************
*                        Header File Declarations                        *
*************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <windows.h>



/*************************************************************************
*                         Constants Declarations                         *
*************************************************************************/

#define MAX_SCREEN_LENGTH 209
#define MAX_SCREEN_HEIGHT 54
#define MAX_RECIPE_INGREDIENTS 20
#define MAX_RECIPES 50
#define MAX_INGREDIENTS 50
#define MAX_FOOD_ITEMS 20
#define MAX_INSTRUCTIONS 15



/*************************************************************************
*                          Typedef Declarations                          *
*************************************************************************/

typedef char string15[16];
typedef char string20[21];
typedef char string70[71];



/*************************************************************************
*                        Enumeration Declarations                        *
*************************************************************************/

typedef enum
{
    VIEWER,
    TESTER,
    ADMIN
} userClass;


typedef enum
{
    STARTER,
    MAIN,
    DESSERT
} recipeClass;


typedef enum
{
    INCREASING,
    DECREASING
} sortType;


typedef enum
{
    FOREGROUND,
    BACKGROUND
} paintType;


typedef enum
{
    BOLD,
    ITALIC,
    UNDERLINE,
    STRIKETHROUGH
} styleType;


typedef enum
{
    BACKSPACE = 8,
    ENTER = 13,
    ESCAPE = 27,
    UP_ARROW = 72,
    LEFT_ARROW = 75,
    RIGHT_ARROW = 77,
    DOWN_ARROW = 80
} specialChar;



/*************************************************************************
*                         Structure Declarations                         *
*************************************************************************/

typedef struct
{
    string20    item;
    float       quantity;
    string15    unit;
} ingredientType;


typedef ingredientType ingredientList[MAX_RECIPE_INGREDIENTS];


typedef struct
{
    string20            name;
    recipeClass         class;
    ingredientList      ingredients;
    string70            instructions[MAX_INSTRUCTIONS];
    int                 nIngredients;
    int                 nInstructions;
    int                 servings;
    float               totalCalories;
} recipeType;


typedef struct
{
    ingredientType      ingredient;
    float               calorie;
} calorieType;


typedef recipeType recipeList[MAX_RECIPES];
typedef calorieType calorieList[MAX_INGREDIENTS];



typedef struct
{
    string20    username;
    string20    password;
    userClass   type;
} userType;



/*************************************************************************
*                                                                        *
*                          Function Prototypes                           *
*                                                                        *
*************************************************************************/


/*************************************************************************
*                            Cursor Functions                            *
*************************************************************************/

void goToXY(int x, int y);
void moveCursor(int x, int y);
void cursorVisibility(bool state);


/*************************************************************************
*                            Style Functions                             *
*************************************************************************/

void paintText(paintType type, int red, int green, int blue);
void resetText();
void paintLine(int red, int green, int blue);
void paintScreen(int red, int green, int blue);
void styleText(styleType type, bool state);


/*************************************************************************
*                            Helper Functions                            *
*************************************************************************/

bool isInRange(int value, int min, int max);
char * getInput(char str[], int size);


/*************************************************************************
*                           Display Functions                            *
*************************************************************************/

void nextScreen();
void displayOption(string20 options, int index, int selected);
void displayHeader();
void printLine(char ch);


/*************************************************************************
*                           Testing Functions                            *
*************************************************************************/

void testAllFunctions();
void displayTestResult(int testNum, string70 description, string70 input, string70 expected, string70 actual, bool result);
void testIsInRange();