#ifndef OPTIONS_H
#define OPTIONS_H
#include "prototypes.h"





/******************************************************************************
*                                                                             *
*                          Food-Calorie Functions                             *
*                                                                             *
******************************************************************************/


/******************************************************************************
    This function appends a new entry in the array of ingredientType struct.
    Preconditions:
        1. The string screenPath is initialized.
        2. The calories struct is initialized.

    @param calories contains where the new information is to be stored.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
addCalorieInfo(calorieList *calories,
               string70 screenPath)
{
    ingredientType temp;

    //initialize
    strcpy(temp.item, "");
    temp.quantity = 0.0;
    strcpy(temp.unit, "");
    temp.calorie = 0.0;

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "ADD CALORIE INFO");
    printf("\n\n");

    if (calories->nElem < MAX_INGREDIENTS)
        addIngredient(CALORIES, &calories->nElem, calories->calorieList);
    else
        displayError("The Food-Calorie List is Full!");

    displayScreenPath(QUIT, screenPath, "ADD CALORIE INFO");
}



/******************************************************************************
    This function displays every entry stored in the array with a maximum
        of 10 entries being displayed in a single moment.
    Preconditions:
        1. The string screenPath is initialized.
        2. The list struct is initialized.

    @param list contains the entries to be displayed.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
viewCalorieChart(calorieList list,
                 string70 screenPath)
{
    int i, page = 0;
    int maxPage;
    int pageElem;
    bool changedPage = true;
    int ch;

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "VIEW CALORIE CHART");
    printf("\n\n");

    if (list.nElem == 0)
        maxPage = 1;
    else
        maxPage = (list.nElem - 1) / 10 + 1;

    do
    {
        if (changedPage)
        {
            printf("Displaying: Page %d of %d\n", page + 1, maxPage);

            printf("%-20s | %-15s | %-15s | %-15s\n", "Ingredient", "Quantity", "Unit", "Calories");

            if (page + 1 == maxPage)
                pageElem = list.nElem - (maxPage - 1) * 10;
            else
                pageElem = 10;

            for (i = 0; i < pageElem; i++)
            {
                printf("%-20s | ", list.calorieList[i + page * 10].item);
                printf("%.2f", list.calorieList[i + page * 10].quantity);
                moveCursorX(40);
                printf("| %-15s | ", list.calorieList[i + page * 10].unit);
                printf("%.2f\n", list.calorieList[i + page * 10].calorie);
            }

            printf("\n");

            changedPage = false;
        }

        ch = getch();

        if (ch == 0 || ch == 224)
        {
            switch (getch())
            {
                case UP_ARROW:
                    if (page > 0)
                    {
                        page--;
                        changedPage = true;
                    }
                    break;
                case DOWN_ARROW:
                    if (page < maxPage - 1)
                    {
                        page++;
                        changedPage = true;
                    }
                    break;
            }
        }

    } while (isInRange(page + 1, 1, maxPage) && ch != ESCAPE);

    displayScreenPath(QUIT, screenPath, "VIEW CALORIE CHART");
}



/******************************************************************************
    This function stores every entry stored in a file into calorieList struct.
    Preconditions:
        1. The string screenPath is initialized.
        2. The calories struct is initialized.

    @param calories is the struct where the information extracted is to be
        stored in.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
importCalorieInfo(calorieList *calories,
                  string70 screenPath)
{
    string20 fileName = "";

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "LOAD CALORIE INFO");
    printf("\n\n");

    do
    {
        printf("Enter the file name: ");
        getInput(CHARACTER, fileName, 20);
        printf("\n");
    } while (isFileNameValid(fileName, FILE_TYPE) == false);

    loadCalorieInfo(fileName, calories);

    displayScreenPath(QUIT, screenPath, "LOAD CALORIE INFO");
}



/******************************************************************************
    This function stores every entry stored in calorieList struct into a file.
    Preconditions:
        1. The string screenPath is initialized.
        2. The calories struct is initialized.

    @param calories is the struct contains the information to be written.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
exportCalorieInfo(calorieList calories,
                  string70 screenPath)
{
    string20 fileName = "";

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "SAVE CALORIE INFO");
    printf("\n\n");

    do
    {
        printf("Enter the file name: ");
        getInput(CHARACTER, fileName, 20);
        printf("\n");
    } while (isFileNameValid(fileName, FILE_TYPE) == false);

    saveCalorieInfo(fileName, calories);

    displayScreenPath(QUIT, screenPath, "SAVE CALORIE INFO");
}



/******************************************************************************
*                                                                             *
*                             Recipe Functions                                *
*                                                                             *
******************************************************************************/



/******************************************************************************
    This function stores every entry stored in a file into recipeList struct.
    Preconditions:
        1. The string screenPath is initialized.
        2. The calories struct is initialized.

    @param recipes is the struct where the information extracted is to be
        stored in.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
importRecipes(recipeList *recipes,
              string70 screenPath)
{
    string20 fileName = "";

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "LOAD RECIPES");
    printf("\n\n");

    do
    {
        printf("Enter the file name: ");
        getInput(CHARACTER, fileName, 20);
        printf("\n");
    } while (isFileNameValid(fileName, FILE_TYPE) == false);

    loadRecipes(fileName, recipes);

    displayScreenPath(QUIT, screenPath, "LOAD RECIPES");
}



/******************************************************************************
    This function stores every entry stored in recipeList struct into a file.
    Preconditions:
        1. The string screenPath is initialized.
        2. The calories struct is initialized.

    @param recipes is the struct contains the information to be written.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
exportRecipes(recipeList recipes,
              string70 screenPath)
{
    string20 fileName = "";

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "SAVE RECIPES");
    printf("\n\n");

    do
    {
        printf("Enter the file name: ");
        getInput(CHARACTER, fileName, 20);
        printf("\n");
    } while (isFileNameValid(fileName, FILE_TYPE) == false);

    saveRecipes(fileName, recipes);

    displayScreenPath(QUIT, screenPath, "SAVE RECIPES");
}



/******************************************************************************
    This function displays all of the recipe names stored in the struct.
    Preconditions:
        1. The string screenPath is initialized.
        2. The structure is initialized.

    @param recipes is the recipe structure that contains the names
        to be displayed.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
listRecipeTitle(recipeList *recipes,
                string70 screenPath)
{
    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "LIST RECIPE TITLE");
    printf("\n\n");

    displayRecipeList(recipes);

    displayScreenPath(QUIT, screenPath, "LIST RECIPE TITLE");
}



/******************************************************************************
    This function appends a new entry in an array of recipeType.
    Preconditions:
        1. The string screenPath is initialized.
        2. The structure is initialized.

    @param recipes contains the array to store the new entry.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
addRecipe(recipeList *recipes,
          string70 screenPath)
{
    bool exit = false;
    recipeType temp;
    optionType option;

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "ADD RECIPE");
    printf("\n\n");

    //initialization
    initializeRecipe(&temp);

    //recipe title
    do
    {
        printf("Enter recipe name: ");
        getInput(CHARACTER, temp.name, 20);
        printf("\n");
        if (strlen(temp.name) > 0)
            exit = true;
        else
            displayError("Must have at least 1 character!");
    } while (exit == false);

    exit = false;

    //classification
    strcpy(option.prompt, "Choose the recipe's classification:");
    option.nOptions = 3;
    strcpy(option.options[0], "Starter.");
    strcpy(option.options[1], "Main.");
    strcpy(option.options[2], "Dessert.");
    
    switch (displayOptions(option))
    {
        case STARTER:
            temp.class = STARTER;
            break;
        case MAIN:
            temp.class = MAIN;
            break;
        case DESSERT:
            temp.class = DESSERT;
            break;
    }

    //serving size
    do
    {
        printf("Enter serving size: ");
        scanf("%d", &temp.servings);

        if (isInRange(temp.servings, 1, INT_MAX))
            exit = true;
        else
            displayError("Input is outside of range! [1, INT_MAX].");
    } while (exit == false);

    exit = false;

    //add atleast one ingredient and instruction
    printf("\n");
    addIngredient(RECIPES, &temp.nIngredients, temp.ingredients);
    printf("\n");
    addInstruction(&temp);

    //Ingredients, Instructions, and saving
    strcpy(option.prompt, "Choose an option:");
    option.nOptions = 4;
    strcpy(option.options[0], "Add ingredient.");
    strcpy(option.options[1], "Add instruction.");
    strcpy(option.options[2], "Save recipe.");
    strcpy(option.options[3], "Discard recipe.");

    do
    {
        switch (displayOptions(option) - 1)
        {
            case 0: //add a new ingredient
                addIngredient(RECIPES, &temp.nIngredients, temp.ingredients);
                break;
            case 1: //add a new instruction
                addInstruction(&temp);
                break;
            case 2: //save the new recipe
                recipes->recipeList[recipes->nRecipes++] = temp;
                exit = true;
                break;
            case 3: //discard the information
                initializeRecipe(&temp);
                exit = true;
                break;
        }
    } while (exit == false);

    displayScreenPath(QUIT, screenPath, "ADD RECIPE");
}



/******************************************************************************
    This function allows the user to modify a specific recipe. It allows the
        user append a new ingredient/instruction or to remove an existing
        ingredient/instruction.
    Preconditions:
        1. The string screenPath is initialized.
        2. The structure is initialized.

    @param recipes contains the recipe to be modified.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
modifyRecipe(recipeList *recipes,
             string70 screenPath)
{
    bool exit = false;
    int index;
    recipeType temp;
    optionType option;

    initializeRecipe(&temp);

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "MODIFY RECIPE");
    printf("\n\n");

    displayRecipeList(recipes);

    printf("\nEnter the recipe title to be modified: ");
    getInput(CHARACTER, temp.name, 20);
    printf("\n");

    if ((index = recipeNameSearch(*recipes, temp.name)) != -1)
    {
        strcpy(option.prompt, "Choose an option:");
        option.nOptions = 6;
        strcpy(option.options[0], "Add ingredient.");
        strcpy(option.options[1], "Add instruction.");
        strcpy(option.options[2], "Delete ingredient.");
        strcpy(option.options[3], "Delete instruction.");
        strcpy(option.options[4], "Save recipe.");
        strcpy(option.options[5], "Discard recipe.");

        temp = recipes->recipeList[index];

        do
        {
            switch (displayOptions(option) - 1)
            {
                case 0: //add a new ingredient
                    addIngredient(RECIPES, &temp.nIngredients, temp.ingredients);
                    break;
                case 1: //add a new instruction
                    addInstruction(&temp);
                    break;
                case 2: //add a new ingredient
                    removeIngredient(&temp);
                    break;
                case 3: //add a new instruction
                    removeInstructions(&temp);
                    break;
                case 4: //save the new recipe
                    recipes->recipeList[index] = temp;
                    exit = true;
                    break;
                case 5: //discard the information
                    initializeRecipe(&temp);
                    exit = true;
                    break;
            }
        } while (exit == false);
    }
    else
        displayError("Recipe title does not exists!");

    displayScreenPath(QUIT, screenPath, "MODIFY RECIPE");
}



/******************************************************************************
    This function allows to remove an existing recipe.
    Preconditions:
        1. The string screenPath is initialized.
        2. The structure is initialized.

    @param recipes contains the recipe to be deleted.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
deleteRecipe(recipeList *recipes,
             string70 screenPath)
{
    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "DELETE RECIPE");
    printf("\n\n");

    removeRecipe(recipes);

    displayScreenPath(QUIT, screenPath, "DELETE RECIPE");
}



/******************************************************************************
    This function displays all stored entries in the structure one at a time.
    Preconditions:
        1. The string screenPath is initialized.
        2. The structure is initialized.

    @param recipes contains the entries to be displayed.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
scanRecipe(recipeList recipes,
           string70 screenPath)
{
    int page = 0;
    bool changedPage = true;
    int ch;

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "SCAN RECIPE");
    printf("\n\n");

    do
    {
        if (changedPage)
        {
            styleText(BOLD, true);
            printf("Showing recipe #%d of %d:\n", page + 1, recipes.nRecipes);
            styleText(BOLD, false);
            displayRecipe(recipes.recipeList[page]);
            printf("\n\n");
        }

        changedPage = false;

        ch = getch();

        if (ch == 0 || ch == 224)
        {
            switch (getch())
            {
                case LEFT_ARROW:
                    if (page > 0)
                    {
                        page--;
                        changedPage = true;
                    }
                    break;
                
                case RIGHT_ARROW:
                    if (page < recipes.nRecipes - 1)
                    {
                        page++;
                        changedPage = true;
                    }
                    break;
            }
        }
    } while (ch != ESCAPE && page < recipes.nRecipes);

    displayScreenPath(QUIT, screenPath, "SCAN RECIPE");
}



/******************************************************************************
    This function allows to user to search a recipe by its title. If the
        title exists, this displays all of the related information about
        that recipe.
    Preconditions:
        1. The string screenPath is initialized.
        2. The structure is initialized.

    @param recipes contains the recipes to be searched and displayed.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
searchByTitle(recipeList *recipes,
              string70 screenPath)
{
    int index;
    string20 key = "";

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "SEARCH TITLE");
    printf("\n\n");

    printf("\nEnter recipe title: ");
    getInput(CHARACTER, key, 20);
    printf("\n");

    if ((index = recipeNameSearch(*recipes, key)) != -1)
        displayRecipe(recipes->recipeList[index]);
    else
        displayError("Recipe title does not exists!");

    displayScreenPath(QUIT, screenPath, "SEARCH TITLE");
}



/******************************************************************************
    This function allows to user to search a recipe by its title. If the
        title exists, it would further ask the user for the number of
        servings. Afterwards, it would display the ingredients needed for
        the recipe and adjust its quantity according to the chosen serving
        size.
    Preconditions:
        1. The string screenPath is initialized.
        2. The structure is initialized.

    @param recipes contains all existing recipes.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
genShoppingList(recipeList recipes,
                string70 screenPath)
{
    bool exit = false;
    int index;
    int i;
    double qtyPerServing = 0.0;
    string20 servings = "";
    string20 name = "";

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "SHOPPING LIST");
    printf("\n\n");

    displayRecipeList(&recipes);

    printf("\nEnter a recipe: ");
    getInput(CHARACTER, name, 20);
    printf("\n");

    if ((index = recipeNameSearch(recipes, name)) != -1)
    {
        do
        {
            printf("\nEnter # of servings: ");
            getInput(INTEGER, servings, 20);
            printf("\n");

            if(isInRange(stringToInt(servings), 0, INT_MAX))
                exit = true;
            else
                displayError("Input must be a positive integer!");
        } while (exit == false);

        printf("\nShopping List:\n%-20s  |     Quantity     |  Unit\n", "Ingredient");

        for (i = 0; i < recipes.recipeList[index].nIngredients; i++)
        {
            if (recipes.recipeList[index].servings > 0)
            {
                qtyPerServing = recipes.recipeList[index].ingredients[i].quantity / recipes.recipeList[index].servings;
            }
            else
                qtyPerServing = 0.0;
            
            printf("%-20s  |  ", recipes.recipeList[index].ingredients[i].item);
            printf("%.2f", (double) stringToInt(servings) * qtyPerServing);
            moveCursorX(42);
            printf("|  %s\n", recipes.recipeList[index].ingredients[i].unit);
        }
    }
    else
        displayError("Recipe title does not exists!");

    displayScreenPath(QUIT, screenPath, "SHOPPING LIST");
}



/******************************************************************************
    This function allows to user to display only the recipes that contains
        a specific ingredient.
    Preconditions:
        1. The string screenPath is initialized.
        2. The structure is initialized.

    @param recipes contains all existing recipes.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
scanByIngredient(recipeList recipes,
                 string70 screenPath)
{
    int i;
    recipeList validRecipes;
    string20 ingredient = "";

    initializeRecipeList(&validRecipes);

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "SCAN BY INGREDIENT");
    printf("\n\n");

    printf("\nEnter ingredient: ");
    getInput(CHARACTER, ingredient, 20);
    printf("\n");

    for (i = 0; i < recipes.nRecipes; i++)
        if (ingredientNameSearch(recipes.recipeList[i].nIngredients, recipes.recipeList[i].ingredients, ingredient) != -1)
            validRecipes.recipeList[validRecipes.nRecipes++] = recipes.recipeList[i];

    if (validRecipes.nRecipes > 0)
    {
        sortRecipeList(INCREASING, &validRecipes);
        scanRecipe(validRecipes, screenPath);
    }
    else
        displayError("No recipes found with that ingredient!");

    displayScreenPath(QUIT, screenPath, "SCAN BY INGREDIENT");
}



/******************************************************************************
    This function allows to user input a username and password string. This
        returns TRUE if the entered strings matches "admin" and "ad1234"
        respectively. Returns FALSE otherwise.
    Preconditions:
        1. The string screenPath is initialized.

    @param screenPath is a string tracking which screen the user is currently.
    @return TRUE if the inputs are valid. FALSE otherwise.
******************************************************************************/
bool
accountLogin(string70 screenPath)
{
    bool success = false;
    userType user;
    userType input;

    strcpy(user.username, "admin");
    strcpy(user.password, "ad1234");
    user.type = ADMIN;

    strcpy(input.username, "");
    strcpy(input.password, "");

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "LOGIN");
    printf("\n\n");

    printf("Enter username: ");
    getInput(CHARACTER, input.username, 20);
    printf("\n");

    printf("Enter password: ");
    getInput(CHARACTER, input.password, 20);
    printf("\n");

    if (strcmp(user.username, input.username) == 0 && strcmp(user.password, input.password) == 0)
        success = true;
    else
        displayError("Invalid username or password.");

    displayScreenPath(QUIT, screenPath, "LOGIN");

    return success;
}



/******************************************************************************
    This function allows to user input a target calorie intake. This function
        would find random main, starter, and dessert recipes such that the
        total calories of these three recipes does not exceed the target.
    Preconditions:
        1. The string screenPath is initialized.
        2. The structure is initialized.

    @param recipes contains all existing recipes.
    @param screenPath is a string tracking which screen the user is currently.
******************************************************************************/
void
recommendedMenu(recipeList recipes,
                string70 screenPath)
{
    double maxCal;
    recipeList recommend;
    recipeType temp;
    string20 input = "";
    int i, j;

    initializeRecipeList(&recommend);
    initializeRecipe(&temp);

    printLine('-', MAX_SCREEN_LENGTH);
    printf("\n\n");
    displayScreenPath(ACCESS, screenPath, "RECOMMEND MENU");
    printf("\n\n");

    printf("Enter target calorie intake: ");
    getInput(FRACTION, input, 20);
    printf("\n");

    maxCal = stringToFloat(input);

    if (floatInRange(maxCal, 0.0, FLT_MAX))
    {
        temp = randRecipe(MAIN, recipes, &maxCal);

        if (strlen(temp.name) > 0)
            recommend.recipeList[recommend.nRecipes++] = temp;

        temp = randRecipe(STARTER, recipes, &maxCal);

        if (strlen(temp.name) > 0)
            recommend.recipeList[recommend.nRecipes++] = temp;

        temp = randRecipe(DESSERT, recipes, &maxCal);

        if (strlen(temp.name) > 0)
            recommend.recipeList[recommend.nRecipes++] = temp;

        for (i = 0; i < recommend.nRecipes; i++) //convert the recipe servings to 1
        {
            if (recommend.recipeList[i].servings > 0)
            {
                recommend.recipeList[i].totalCalories /= recommend.recipeList[i].servings;

                for (j = 0; j < recommend.recipeList[i].nIngredients; j++)
                {
                    recommend.recipeList[i].ingredients[j].quantity /= recommend.recipeList[i].servings;
                    recommend.recipeList[i].ingredients[j].calorie /= recommend.recipeList[i].servings;
                }

                recommend.recipeList[i].servings = 1;
            }
        }

        if (recommend.nRecipes > 0)
        {
            sortRecipeList(CLASS, &recommend);
            scanRecipe(recommend, screenPath);
        }
        else
            displayError("No recipe matches the requirements!");
    }
    else
        displayError("Invalid target calorie intake [0, FLT_MAX].");

    displayScreenPath(QUIT, screenPath, "RECOMMEND MENU");
}



#endif