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
	Last Modified: February 12, 2026
	Version: 1.1
	Acknowledgements:	
						https://github.com/Haxy577/Meals4Health.git -> repository of the project
                        https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 -> ANSI escape codes
	Compiled with: gcc -Wall -Wextra -pedantic -Werror -std=c99 -g main.c -o out
*/


#include "modules.h"


int
main()
{
    clearScreen();
    displayHeader();
    int i;

    for (i = 0; i < MAX_SCREEN_CHAR; i++)
        printf("=");
    printf("\n");
    for (i = 1; i <= 20; i++)
    {
        printf("ingredient %d\n", i);
    }
    
    return 0;
}