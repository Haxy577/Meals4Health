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
    userNav pos;
    options rowOptions[MAX_ROW_OPTIONS];

    pos.row = 0;
    pos.col = 0;
    pos.rowMax = 0;

    strcpy(rowOptions[0].names[0], "HOME");
    strcpy(rowOptions[0].names[1], "UPDATE");
    strcpy(rowOptions[0].names[2], "ACCESS");
    strcpy(rowOptions[0].names[3], "ACCOUNT");
    strcpy(rowOptions[0].names[4], "EXIT");
    rowOptions[0].nOptions = 5;
    rowOptions[0].hover = 1;
    rowOptions[0].selected = 0;
    rowOptions[0].x = 0;

    nextScreen();
    userNavigation(&pos, rowOptions);
    nextScreen();
    userNavigation(&pos, rowOptions);


    printf("\nselected: %d", rowOptions[0].selected);
    printf("\nselected: %d", rowOptions[1].selected);
    printf("\nx: %d", pos.col);

    //testAllFunctions();

    return 0;
}