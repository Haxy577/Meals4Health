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

#define MAX_SCREEN_CHAR 209
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
*                         Structure Declarations                         *
*************************************************************************/

typedef enum
{
    VIEWER,
    ADMIN
} userType;


typedef enum
{
    STARTER,
    MAIN,
    DESSERT
} recipeClass;


//add documentation
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



struct user
{
    string20    username;
    string20    password;
    userType    type;
};



/*************************************************************************
*                                                                        *
*                          Function Prototypes                           *
*                                                                        *
*************************************************************************/


/*************************************************************************
*                           Display Functions                            *
*************************************************************************/

void clearScreen();
void goToXY(int x, int y);
void paintText(int modifier, int red, int green, int blue);
void paintLine(int red, int green, int blue);
void displayOption(string20 options, int index, int selected);