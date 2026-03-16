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
	Last Modified: March 14, 2026
	Version: 1.8
	Acknowledgements:	
		https://github.com/Haxy577/Meals4Health.git -> repository of the project.
        https://docs.google.com/spreadsheets/d/1q2fRXYvtUqxOdZb7gpCDgJ19lflnFXEQodQZB7JNsZs/edit?usp=sharing -> google sheets containing the test script.
        https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 -> ANSI escape codes.
        https://patorjk.com/software/taag/ -> provided the ascii art for the header.
	Compiled with: gcc -Wall -Wextra -pedantic -Werror -std=c99 -g main.c -o out
*/


#include "modules.h"
#include "testCases.h"

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
    testAllFunctions();

    return 0;
}