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
	Last Modified: March 30, 2026
	Version: 1.8
	Acknowledgements:	
		https://github.com/Haxy577/Meals4Health.git -> repository of the project.
        https://docs.google.com/spreadsheets/d/1q2fRXYvtUqxOdZb7gpCDgJ19lflnFXEQodQZB7JNsZs/edit?usp=sharing -> google sheets containing the test script.
        https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 -> ANSI escape codes.
	Compiled with: gcc -Wall -Wextra -pedantic -Werror -std=c99 -g main.c -o out
*/

#include "modules.h"
#include "testCases.h"
#include "options.h"

int
main()
{
    enum mainOptions
    {
        UPDATE_RECIPE_BOX,
        ACCESS_RECIPE_BOX,
        TEST_FUNCTIONS,
        EXIT,
        NUM_OPTIONS
    };

    bool exit = false;
    optionType options;
    string70 screenPath = "";

    srand(time(NULL));

    strcpy(options.prompt, "Choose an option:");
    strcpy(options.options[0], "Update Recipe Box");
    strcpy(options.options[1], "Access Recipe Box");
    strcpy(options.options[2], "Test All Functions");
    strcpy(options.options[3], "Exit");
    options.nOptions = NUM_OPTIONS;

    do
    {
        printLine('-', MAX_SCREEN_LENGTH);
        printf("\n\n");

        displayScreenPath(ACCESS, screenPath, "MAIN");

        switch (displayOptions(options) - 1)
        {
            case UPDATE_RECIPE_BOX:
                if (accountLogin(screenPath))
                    updateMenu(screenPath);
                break;
            
            case ACCESS_RECIPE_BOX:
                accessMenu(screenPath);
                break;

            case TEST_FUNCTIONS:
                printLine('-', MAX_SCREEN_LENGTH);
                printf("\n\n");
                testAllFunctions();
                break;

            case EXIT:
                exit = true;
                printf("Terminating program. Thanks for using it!");
                break;
            
            default:
                printf("Invalid Input!");
                break;
        }

        displayScreenPath(QUIT, screenPath, "MAIN");
    } while (exit == false);

    return 0;
}



/******************************************************************************
    This function displays all of the options associated with the update
        box menu.
    Preconditions:
        1. The string screenPath is initialized.

    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
updateMenu(string70 screenPath)
{
    enum updateOptions
    {
        ADD_CALORIE_INFO,
        VIEW_CALORIE_CHART,
        SAVE_CALORIE_INFO,
        LOAD_CALORIE_INFO,
        ADD_RECIPE,
        MODIFY_RECIPE,
        DELETE_RECIPE,
        LIST_RECIPES,
        SCAN_RECIPES,
        SEARCH_TITLE,
        EXPORT_RECIPES,
        IMPORT_RECIPES,
        RETURN_TO_MENU,
        NUM_OPTIONS
    };

    bool exit = false;
    optionType options;
    recipeList recipes;
    calorieList calories;

    initializeRecipeList(&recipes);
    initializeCalories(&calories);

    //initialize all options
    strcpy(options.options[0], "Add Food-Calorie Info");
    strcpy(options.options[1], "View Food-Calorie Chart");
    strcpy(options.options[2], "Save Food-Calorie Info");
    strcpy(options.options[3], "Load Food-Calorie Info");
    strcpy(options.options[4], "Add Recipe");
    strcpy(options.options[5], "Modify Recipe");
    strcpy(options.options[6], "Delete Recipe");
    strcpy(options.options[7], "List Recipe");
    strcpy(options.options[8], "Scan Recipe");
    strcpy(options.options[9], "Search Recipe By Title");
    strcpy(options.options[10], "Export Recipes");
    strcpy(options.options[11], "Import Recipes");
    strcpy(options.options[12], "Return To Menu");
    options.nOptions = NUM_OPTIONS;

    do
    {
        printLine('-', MAX_SCREEN_LENGTH);
        printf("\n\n");

        displayScreenPath(ACCESS, screenPath, "UPDATE RECIPE BOX");

        switch (displayOptions(options) - 1)
        {
            case ADD_CALORIE_INFO:
                addCalorieInfo(&calories, screenPath);
                updateCalories(&recipes, calories);
                break;
                
            case VIEW_CALORIE_CHART:
                viewCalorieChart(calories, screenPath);
                break;
                
            case SAVE_CALORIE_INFO:
                exportCalorieInfo(calories, screenPath);
                break;

            case LOAD_CALORIE_INFO:
                importCalorieInfo(&calories, screenPath);
                updateCalories(&recipes, calories);
                break;

            case ADD_RECIPE:
                addRecipe(&recipes, screenPath);
                updateCalories(&recipes, calories);
                break;

            case MODIFY_RECIPE:
                modifyRecipe(&recipes, screenPath);
                updateCalories(&recipes, calories);
                break;

            case DELETE_RECIPE:
                deleteRecipe(&recipes, screenPath);
                break;

            case LIST_RECIPES:
                listRecipeTitle(&recipes, screenPath);
                break;

            case SCAN_RECIPES:
                sortRecipeList(INCREASING, &recipes);
                scanRecipe(recipes, screenPath);
                break;

            case SEARCH_TITLE:
                searchByTitle(&recipes, screenPath);
                break;

            case EXPORT_RECIPES:
                exportRecipes(recipes, screenPath);
                break;

            case IMPORT_RECIPES:
                importRecipes(&recipes, screenPath);
                updateCalories(&recipes, calories);
                break;

            case RETURN_TO_MENU:
                exit = true;

                //clear the lists
                initializeRecipeList(&recipes);
                initializeCalories(&calories);
                break;
            
            default:
                printf("Invalid Input!");
                break;
        }

        displayScreenPath(QUIT, screenPath, "UPDATE RECIPE BOX");
    } while (exit == false);
}



/******************************************************************************
    This function displays all of the options associated with the access
        box menu.
    Preconditions:
        1. The string screenPath is initialized.

    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
accessMenu(string70 screenPath)
{
    enum accessOptions
    {
        IMPORT_RECIPES,
        IMPORT_CALORIE_INFO,
        LIST_RECIPE_TITLES,
        SCAN_RECIPES,
        SEARCH_TITLE,
        SHOPPING_LIST,
        SCAN_INGREDIENT,
        RECOMMENDED_MENU,
        RETURN_TO_MENU,
        NUM_OPTIONS
    };

    bool exit = false;
    optionType options;
    recipeList recipes;
    calorieList calories;

    initializeRecipeList(&recipes);
    initializeCalories(&calories);


    //initialize all options
    strcpy(options.options[0], "Import Recipes");
    strcpy(options.options[1], "Import Food-Calorie Info");
    strcpy(options.options[2], "List Recipe Titles");
    strcpy(options.options[3], "Scan Recipes");
    strcpy(options.options[4], "Search Recipe By Title");
    strcpy(options.options[5], "Generate Shopping List");
    strcpy(options.options[6], "Scan Recipe By Ingredient");
    strcpy(options.options[7], "Recommended Menu");
    strcpy(options.options[8], "Return to Menu");
    options.nOptions = NUM_OPTIONS;

    do
    {
        printLine('-', MAX_SCREEN_LENGTH);
        printf("\n\n");

        displayScreenPath(ACCESS, screenPath, "UPDATE RECIPE BOX");

        switch (displayOptions(options) - 1)
        {
            case IMPORT_RECIPES:
                importRecipes(&recipes, screenPath);
                updateCalories(&recipes, calories);
                break;

            case IMPORT_CALORIE_INFO:
                importCalorieInfo(&calories, screenPath);
                updateCalories(&recipes, calories);
                break;

            case LIST_RECIPE_TITLES:
                displayRecipeList(&recipes);
                break;

            case SCAN_RECIPES:
                sortRecipeList(INCREASING, &recipes);
                scanRecipe(recipes, screenPath);
                break;

            case SEARCH_TITLE:
                searchByTitle(&recipes, screenPath);
                break;
                
            case SHOPPING_LIST:
                genShoppingList(recipes, screenPath);
                break;

            case SCAN_INGREDIENT:
                scanByIngredient(recipes, screenPath);
                break;
                
            case RECOMMENDED_MENU:
                recommendedMenu(recipes, screenPath);
                break;

            case RETURN_TO_MENU:
                exit = true;

                //clear the lists
                initializeRecipeList(&recipes);
                initializeCalories(&calories);
                break;
            
            default:
                printf("Invalid Input!");
                break;
        }

        displayScreenPath(QUIT, screenPath, "UPDATE RECIPE BOX");
    } while (exit == false);
}