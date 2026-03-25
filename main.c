#include <stdio.h>
#include <string.h>

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
	   int dishRow, 
	   int foodRow, 
	   int foodPage,
	   String20 username,
	   String20 password)
{
	int input;
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
			ImportRecipes(dish, &dishRow);
			Access(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 2:
			ListRecipeTitles(dish, dishRow);
			Access(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 3: 
			ScanRecipes(dish, dishRow);
			Access(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 4:
			SearchRecipeTitle(dish, dishRow);
			Access(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 5:
			GenerateShoppingList(dish, dishRow);
			Access(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 6:
			ScanRecipesByIngredient(dish, dishRow);
			Access(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 7:
			
			Access(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		default:
			Menu(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
	}
}

void
Update(DishType dish[], 
	   IngredientsType food[], 
	   int dishRow, 
	   int foodRow, 
	   int foodPage,
	   String20 username,
	   String20 password)
{
    int input; //status = 0;
    //loadAccount(username, password);
    //status = loginPage(username, password);
    
    //if (status==0) Menu(dish, food, dishRow, foodRow, foodPage, username, password);
    
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
    printf("[13] Return to Main Menu\n");
    printf("Input your choice: ");
    do 
	{
		myIntInput(&input);
		if (input < 1 || input > 13)
			printf("[Invalid] Enter another option: ");
	} while (input < 1 || input > 13);
	printf("\n");
	
	switch (input)
	{
		case 1:
			AddFoodCalorie(food, &foodRow);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 2:
			ViewFood(food, &foodRow, &foodPage);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 3:
			SaveCalorie(food, &foodRow);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 4:
			LoadCalories(food, &foodRow);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 5:
			AddRecipe(dish, food, &foodRow, &dishRow);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 6:
			ModifyRecipe(dish, food, foodRow, dishRow);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 7: 
			DeleteRecipes(dish, &dishRow);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 8: 
			ListRecipeTitles(dish, dishRow);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 9:
			ScanRecipes(dish, dishRow);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 10:
			SearchRecipeTitle(dish, dishRow);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 11:
			ExportRecipes(dish, &dishRow);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		case 12:
			ImportRecipes(dish, &dishRow);
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		default:
			Menu(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
	}
}

void 
Menu(DishType dish[], 
	 IngredientsType food[], 
	 int dishRow, 
	 int foodRow, 
	 int foodPage,
	 String20 username,
	 String20 password)
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
			Access(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		
		case 'U':
			Update(dish, food, dishRow, foodRow, foodPage, username, password);
			break;
		
		default:
			break;
	}
}

int
main()
{
	DishType dish[SIZE];
	IngredientsType food[SIZE];
	String20 username;
	String20 password;
    int foodPage = 0,
		foodRow = 0,
		dishRow = 0;

    Menu(dish, food, dishRow, foodRow, foodPage, username, password);
    return 0;
}
