/**************************************************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. I have
constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons, nor did I employ the use of AI in any part of the deliverable.
Richmond Jase Von M. Salvador, DLSU ID# 12506338
**************************************************************************************************************************************/

/*  Description: A repository for cooking recipes wherein the user can add new recipes, view existing recipes,
                    generate a shopping list, and to recommend menu.
	Programmed by: Richmond Jase Von M. Salvador  S15A
	Last Modified: March 6, 2026
	Version: 1.6
	Acknowledgements:	
		https://github.com/Haxy577/Meals4Health.git -> repository of the project.
        https://docs.google.com/spreadsheets/d/1q2fRXYvtUqxOdZb7gpCDgJ19lflnFXEQodQZB7JNsZs/edit?usp=sharing -> google sheets containing the test script.
        https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 -> ANSI escape codes.
        https://patorjk.com/software/taag/ -> provided the ascii art for the header.
	Compiled with: gcc -Wall -Wextra -pedantic -Werror -std=c99 -g main.c -o out
*/


#include "modules.h"

void getFullscreenDimensions() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        printf("Your current width is: %d chars\n", width);
        printf("Your current height is: %d chars\n", height);
    }
}


int
main()
{
    string20 str = "TEST";
    printf("Input: ");
    getInput(str, 20);
    printf("\nActual: %s", str);

    return 0;



//   printLine('-');
//   printf("Name\n");
//   printf("class\n");
//   printf("servings\n");
//   printf("total calories\n");
//   printf("\nIngredients:\n");
//   for (i = 1; i <= 20; i++)
//       printf("ingredients\n");
//   printf("\nIngredients:\n");
//   for (i = 1; i <= 15; i++)
//       printf("instructions\n");
//   printf("\33[s\33[6;0H");
//   printf("tes\33[u");
//   
//   return 0;
}