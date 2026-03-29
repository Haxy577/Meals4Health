#ifndef PROTOTYPES_H
#define PROTOTYPES_H

/*************************************************************************
*                        Header File Declarations                        *
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <time.h>



/*************************************************************************
*                         Constants Declarations                         *
*************************************************************************/

#define FILE_TYPE ".txt"
#define MAX_SCREEN_LENGTH 150
#define MAX_RECIPE_INGREDIENTS 20
#define MAX_RECIPES 50
#define MAX_INGREDIENTS 50
#define MAX_FOOD_ITEMS 20
#define MAX_INSTRUCTIONS 15
#define MAX_OPTIONS 20
#define MAX_RECOMMENDATION 3



/*************************************************************************
*                          Typedef Declarations                          *
*************************************************************************/

typedef char string15[16];
typedef char string20[21];
typedef char string50[51];
typedef char string70[71];
typedef char string128[129];



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
    NONE,
    STARTER,
    MAIN,
    DESSERT
} recipeClass;


typedef enum
{
    INCREASING,
    DECREASING,
    CLASS
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


typedef enum
{
    INTEGER,
    FRACTION,
    CHARACTER
} dataType;


typedef enum
{
    UPPER_CASE,
    LOWER_CASE
} convertStr;


typedef enum
{
    ACCESS,
    QUIT
} pathType;


typedef enum
{
    RECIPES,
    CALORIES
} listType;



/*************************************************************************
*                         Structure Declarations                         *
*************************************************************************/


/**********************************************************
    Information for a single ingredient. This struct
        tracts the name, quantity, unit, and calories.
**********************************************************/
typedef struct
{
    string20    item;       //The name of the ingredient.
    float       quantity;   //The amount of the ingredient.
    string15    unit;       // The unit of measurement.
    float       calorie;    //Total calories of the ingredient.
} ingredientType;


/**********************************************************
    Information for a single recipe. This struct
        tracts the name, classification, ingredients,
        instructions, number of ingredients, number of
        instructions, serving size, and the total
        calories of the recipe.
**********************************************************/
typedef struct
{
    string20            name;                                   //The title or name of the recipe.
    recipeClass         class;                                  //The classification: STARTER, MAIN, or DESSERT.
    ingredientType      ingredients[MAX_RECIPE_INGREDIENTS];    //An array of ingredientType containing the recipe's ingredients.
    string70            instructions[MAX_INSTRUCTIONS];         //An array of strings containing the instructions.
    int                 nIngredients;                           //The total number of ingredients.
    int                 nInstructions;                          //The total number of instructions.
    int                 servings;                               //The serving size of the recipe.
    float               totalCalories;                          //The total amount of calories.
} recipeType;


/**********************************************************
    Information for list of recipes. This struct tracts
        an array of recipe structures, and the total
        number of recipes.
**********************************************************/
typedef struct
{
    recipeType  recipeList[MAX_RECIPES];    //An array of recipeType containing all of the recipes.
    int         nRecipes;                   //The total number of elements in the array.
} recipeList;


/**********************************************************
    Information for list of ingredients. This struct tracts
        an array of ingredient structures, and the total
        number of elements.
**********************************************************/
typedef struct 
{
    ingredientType  calorieList[MAX_INGREDIENTS];   //An array of ingredientType containing all of the ingredients.
    int             nElem;                          //The total number of elements in the array.
} calorieList;



/**********************************************************
    Information for a single user account. This struct
        tracts the user's username, password, and
        account type.
**********************************************************/
typedef struct
{
    string20    username;   //The user's username.
    string20    password;   //The user's password.
    userClass   type;       //The type of the account: VIEWER, TESTER, or ADMIN.
} userType;


/**********************************************************
    Information for a single option to be displayed. This
        struct tracts the option's prompt, the list of
        options, and the total number of options.
**********************************************************/
typedef struct
{
    string50    prompt;                 //The option's prompt.
    string50    options[MAX_OPTIONS];   //The list of options.
    int         nOptions;               //The total amount of options.
} optionType;


/**********************************************************
    Information for a single test case. This struct
        tracts the test case's number, test description,
        the test's input, the expected output, the actual
        output, and the result of the test.
**********************************************************/
typedef struct
{
    int         testNum;        //the test case number.
    string70    description;    //the description of the test case.
    string128   input;          //what was inputted in the function parameters.
    string70    expected;       //the expected output of the function.
    string70    actual;         //the actual output of the function.
    bool        result;         //whether the expected matches the actual. Prints "PASS" if it matches, "FAIL" otherwise.
} testType;



/*************************************************************************
*                                                                        *
*                          Function Prototypes                           *
*                                                                        *
*************************************************************************/


/*************************************************************************
*                           Cursor Functions                             *
*************************************************************************/

void goToXY(int x, int y);
void moveCursor(int x, int y);
void moveCursorX(int x);
void cursorVisibility(bool state);



/*************************************************************************
*                            Style Functions                             *
*************************************************************************/

void paintText(paintType type, int red, int green, int blue);
void resetText();
void styleText(styleType type, bool state);



/*************************************************************************
*                            Helper Functions                            *
*************************************************************************/

bool isInRange(long long value, int min, int max);
bool floatInRange(double value, float min, float max);
char * getInput(dataType type, char str[], int size);
int stringToInt(char str[]);
float stringToFloat(char str[]);
char * intToString(int num, char str[]);
bool isFileNameValid(char fileName[], char fileExt[]);
char * convertString(char str[], convertStr type);
int absStrCmp(char str1[], char str2[]);
char * arrayToString(int maxLen, int nElem, char arr[nElem][maxLen], char str[nElem * maxLen]);
void sortStrArray(sortType type, int nElem, int maxLen, char arr[nElem][maxLen]);
char * reverseString(char str[]);
int stringSearch(int nElem, int maxLen, char arr[nElem][maxLen], char key[maxLen]);
int recipeNameSearch(recipeList recipes, string20 key);
int ingredientNameSearch(int nElem, ingredientType list[nElem], string20 key);
void initializeRecipe(recipeType *recipe);
void initializeRecipeList(recipeList *recipes);
void initializeCalories(calorieList *calories);
void sortRecipeList(sortType type, recipeList *list);
void addIngredient(listType type, int *nElem, ingredientType list[*nElem]);
void removeIngredient(recipeType *recipe);
void addInstruction(recipeType *recipe);
void removeInstructions(recipeType *recipe);
void removeRecipe(recipeList *recipes);
char * getFileStr(FILE *fp, int maxChar, char arr[maxChar + 1]);
void saveCalorieInfo(string20 fileName, calorieList arr);
void loadCalorieInfo(string20 fileName, calorieList *arr);
void saveRecipes(string20 fileName, recipeList list);
void loadRecipes(string20 fileName, recipeList *list);
void updateCalories(recipeList *recipes, calorieList calories);
recipeType randRecipe(recipeClass class, recipeList recipes, double *maxCal);



/*************************************************************************
*                           Display Functions                            *
*************************************************************************/

void printLine(char ch, int len);
int displayOptions(optionType option);
void displayScreenPath(pathType action, char screenPath[], char screenName[]);
void displayError(char errorMsg[]);
void displayRecipe(recipeType recipe);
void displayRecipeList(recipeList *recipes);



/*************************************************************************
*                       Machine Project Functions                        *
*************************************************************************/

void updateMenu(string70 screenPath);
void accessMenu(string70 screenPath);
void addCalorieInfo(calorieList *calories, string70 screenPath);
void viewCalorieChart(calorieList list, string70 screenPath);
void importCalorieInfo(calorieList *calories, string70 screenPath);
void exportCalorieInfo(calorieList calories, string70 screenPath);
void importRecipes(recipeList *recipes, string70 screenPath);
void exportRecipes(recipeList recipes, string70 screenPath);
void listRecipeTitle(recipeList *recipes, string70 screenPath);
void addRecipe(recipeList *recipes, string70 screenPath);
void modifyRecipe(recipeList *recipes, string70 screenPath);
void deleteRecipe(recipeList *recipes, string70 screenPath);
void scanRecipe(recipeList recipes, string70 screenPath);
void searchByTitle(recipeList *recipes, string70 screenPath);
void genShoppingList(recipeList recipes, string70 screenPath);
void scanByIngredient(recipeList recipes, string70 screenPath);
bool accountLogin(string70 screenPath);
void recommendedMenu(recipeList recipes, string70 screenPath);



/*************************************************************************
*                           Testing Functions                            *
*************************************************************************/

void testAllFunctions();
void displayTestResult(testType test);
void testIsInRange();
void testFloatInRange();
void testStringToInt();
void testStringToFloat();
void testIsFileNameValid();
void testConvertString();
void testAbsStrCmp();
void testSortStrArray();
void testReverseString();
void testIntToString();
void testStringSearch();



#endif