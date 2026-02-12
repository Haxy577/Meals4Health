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
#define MAX_RECIPES 50
#define MAX_INGREDIENTS 50
#define MAX_FOOD_ITEMS 20
#define MAX_INSTRUCTIONS 15



/*************************************************************************
*                          Typedef Declarations                          *
*************************************************************************/

typedef char string5[6];
typedef char string10[11];
typedef char string15[16];
typedef char string20[21];
typedef char string70[71];



/*************************************************************************
*                         Structure Declarations                         *
*************************************************************************/

struct ingredients
{
    string20 item;
    float quantity;
    string15 unit;
    int calories;
};

struct recipe
{
    string20 name;
    string10 classification;
    struct ingredients foodItems[MAX_FOOD_ITEMS];
    string70 instructions[MAX_INSTRUCTIONS];
    int servings;
    int totalCalories;
};


struct user
{
    string20 username,
             password;
    bool authorized;
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
void displayOption(string10 options, int index, int selected);