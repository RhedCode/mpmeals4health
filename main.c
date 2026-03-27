#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "lib.c"

/*
Meals4Health
Two Goals of this program
1. The person who creates the recipes (and EXCLUSIVE to them)
2. The person who will be choosing the recipe to use based on the nutritional facts

20 Ingredients
  - Quantity (can be fractional part but assume user inputs real number)
  - Unit (like grams, cups, teaspoon, etc.) *AT MOST 15 CHARACTERS*
  - Item (assume that this is a phrase) *AT MOST 20 CHARACTERS*
  
15 Instructions
  - Each instruction will be a phrase/sentence that DOESN'T exceed 70 characters.
  - Serving size is a WHOLE NUMBER, specifying for how many people it is for.

AT MOST 50 RECIPES
AT MOST 50 Food items
*/

void
Access(DishType dish[], 
	   IngredientsType food[], 
	   int *dishRow, 
	   int foodRow)
{
	int input, exit = 0;
	
	while (!exit)
	{
		printf("[----------Access Menu----------]\n");
		printf("[1] Import Recipes\n");
		printf("[2] List Recipe Titles\n");
		printf("[3] Scan Recipes\n");
		printf("[4] Search Recipe by Title\n");
		printf("[5] Generate Shopping List\n");  
    	printf("[6] Scan Recipes by Ingredient\n");
    	printf("[7] Recommended Menu\n");
    	printf("[8] Return to Main Menu\n");
    	printf("Input your choice: ");
    	do 
		{
			myIntInput(&input);
			if (input < 1 || input > 8)
				printf("[Invalid] Enter another option: ");
		} while (input < 1 || input > 8);
		printf("\n");
	
		switch (input)
		{
			case 1:
				ImportRecipes(dish, food, dishRow, foodRow);
				break;
			case 2:
				ListRecipeTitles(dish, *dishRow);
				break;
			case 3: 
				ScanRecipes(dish, *dishRow, 1);
				break;
			case 4:
				SearchRecipeTitle(dish, *dishRow);
				break;
			case 5:
				GenerateShoppingList(dish, *dishRow);
				break;
			case 6:
				ScanRecipesByIngredient(dish, *dishRow);
				break;
			case 7:
				RecommendedMenu(dish, *dishRow);
				break;
			default:
				exit = 1;
				break;
		}
	}
}

void
Update(DishType dish[], 
	   IngredientsType food[], 
	   int *dishRow, 
	   int *foodRow, 
	   String20 username,
	   String20 password,
	   int *status)
{
    int input, exit = 0;
    
    while (!exit)
    {
    	loadAccount(username, password);
    	if (*status == 0) 
    	{
    		*status = loginPage(username, password);
    		if (*status == 0)
				exit = 1;
		}
    
    	if (exit != 1)
    	{
    		printf("[----------Update Menu----------]\n");
    		printf("[1] Add Food-Calorie Info\n");
			printf("[2] View Food-Calorie Chart\n");
			printf("[3] Save Calorie Info\n");
			printf("[4] Load Calorie Info\n");
			printf("[5] Add Recipe\n");  
    		printf("[6] Modify Recipe\n");
    		printf("[7] Delete Recipe\n");
    		printf("[8] List Recipe Titles\n");
    		printf("[9] Scan Recipes\n");
    		printf("[10] Search Recipe by Title\n");
    		printf("[11] Export Recipes\n");
    		printf("[12] Import Recipes\n");
    		printf("[13] Change Password\n");
    		printf("[14] Return to Main Menu\n");
    		printf("Input your choice: ");
    		do 
			{
				myIntInput(&input);
				if (input < 1 || input > 14)
					printf("[Invalid] Enter another option: ");
			} while (input < 1 || input > 14);
			printf("\n");
	
			switch (input)
			{
				case 1:
					AddFoodCalorie(food, foodRow);
					break;
				case 2:
					ViewFood(food, *foodRow);
					break;
				case 3:
					SaveCalorie(food, *foodRow);
					break;
				case 4:
					LoadCalories(food, foodRow);
					break;
				case 5:
					AddRecipe(dish, food, foodRow, dishRow);
					break;
				case 6:
					ModifyRecipe(dish, food, *foodRow, *dishRow);
					break;
				case 7: 
					DeleteRecipes(dish, dishRow);
					break;
				case 8: 
					ListRecipeTitles(dish, *dishRow);
					break;
				case 9:
					ScanRecipes(dish, *dishRow, 1);
					break;
				case 10:
					SearchRecipeTitle(dish, *dishRow);
					break;
				case 11:
					ExportRecipes(dish, *dishRow);
					break;
				case 12:
					ImportRecipes(dish, food, dishRow, *foodRow);
					break;
				case 13:
					ChangePassword(username, password);
					*status = 0;
					exit = 1;
					break;
				default:
					*status = 0;
					exit = 1;
					break;
			}
		}
	}
}

int 
Menu(DishType dish[], 
	 IngredientsType food[], 
	 int *dishRow, 
	 int *foodRow, 
	 String20 username,
	 String20 password,
	 int *status)
{	
	char input;

	printf("[----------Food Tracker----------]\n");
	printf("[A] Access Recipes\n");
	printf("[U] Update Recipes\n");
	printf("[E] Exit\n");
	do
	{
		myCharInput(&input);
		if (input != 'A' && input != 'U' && input != 'E')
			printf("[Invalid] Enter another option: ");
	} while (input != 'A' && input != 'U' && input != 'E');
	printf("\n");
	
	switch (input)
	{
		case 'A':
			Access(dish, food, dishRow, *foodRow);
			break;
		
		case 'U':
			Update(dish, food, dishRow, foodRow, username, password, status);
			break;
		
		default:
			return 0;
			break;
	}
	return 1;
}

int
main()
{
	DishType dish[SIZE];
	IngredientsType food[SIZE];
	String20 username;
	String20 password;
    int status = 0,
		foodRow = 0,
		dishRow = 0;

	while (Menu(dish, food, &dishRow, &foodRow, username, password, &status));
    return 0;
}
