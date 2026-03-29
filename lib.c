/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. I have
constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons, nor did I employ the use of AI in any part of the deliverable.
																Rhed Lanz C. Dela Cruz, DLSU ID# 12507253
*********************************************************************************************************/

#include "info.h"
#include "helper.c"

/* AddFoodCalorie displays and accepts user input on the Item name, quantity, 
   unit, & calories.
   
   @param food - Contains a struct array of max size 50.
   @param row - Contains the current size of food row.
*/

void
AddFoodCalorie(IngredientsType food[], 
			   int *row)
{	
	printf("[----------Add Food Calorie----------]\n");
	do 
	{
		printf("Item name: ");
		getString20(food[*row].item);
    	
    	/* Checks if there is an existing item and if item has no name. */
    	if (DuplicateFood(food, *row) != -1)
    	{
			printf("Duplicate item is already stored!\n");
			strcpy(food[*row].item, "");
		}
		else
			if (strlen(food[*row].item) < 1)
				printf("Item has no name!\n");

	} while (DuplicateFood(food, *row) != -1 || 
			 strlen(food[*row].item) < 1);
	
	/* User Inputs */
	printf("Quantity: ");
	myFloatInput(&food[*row].quantity);
		
	printf("Unit: ");
	scanf("%15s", food[*row].unit);
	
	printf("Calories: ");
	myIntInput(&food[*row].calories); 
	
	printf("\n");
	
	(*row)++;
}

/* ViewFood displays Food List of a maximum of 10 items per page. 
   
   @param food - Contains a struct array of max size 50.
   @param row - Contains the current size of food row.
*/

void 
ViewFood(IngredientsType food[], 
		 int row)
{
    char key;
    int page = 0; //Handles which page is currently being selected.

	DisplayFood(food, row, page);
	do
	{	
		myCharInput(&key);
		
		//Computes if the page has reached the current maximum page.
		if (key == 'N' && page != row/10) 
		{	
			page++;
			DisplayFood(food, row, page);
		}	
		//Computes if the page has reached the current minimum page, which is always 0.
		else if (key == 'P' && page != 0)
		{
			page--;
	   		DisplayFood(food, row, page);
	   	}
	   		
	   	//If either two of the conditions fail in terms of page, then a warning message is received.
	   	else if ((key == 'N' || key == 'P') && (page == row/10 || page == 0))
			printf("Exceeds page limit! ");
		else
			if (key != 'X')
	   			printf("[Invalid] Enter another input: ");

    } while (key != 'X');
    printf("\n");
}

/* SaveCalorie saves the current food struct array information in a text file.
   
   @param food - Contains a struct array of max size 50.
   @param row - Contains the current size of food row.
*/

void 
SaveCalorie(IngredientsType food[], 
			int row)
{
	FILE *fp_save;
	String20 fileName;
	int i;

	printf("[----------Save Food Calorie----------]\n");
	printf("Enter a text file name: ");
	getString20(fileName);
	
	fp_save = fopen(fileName, "w");

	if (fp_save == NULL || row == 0)
		printf("No data is detected to be saved!\n");
	else
	{
		for (i=0; i<row; i++)
		{
      		fprintf(fp_save, "%s\n", food[i].item);
	  		fprintf(fp_save, "%g %s %d\n", food[i].quantity, food[i].unit, food[i].calories);
	  		fprintf(fp_save, "\n");
      	}
      	fclose(fp_save);
	}
	printf("\n");
}

/* LoadCalories loads/appends the current food struct array information 
   from text file to the source code array of structs.
   
   @param food - Contains a struct array of max size 50.
   @param *row - Contains the current size of food row. 
*/

void
LoadCalories(IngredientsType food[], int *row)
{
	FILE *fp_load;
	String20 fileName, sBuff;
	int dupe, nBuff;
	char ch;
	
	printf("[----------Load Food Calorie----------]\n");
	printf("Enter a text file name: ");
	scanf("%s%c", fileName, &ch);
	
	fp_load = fopen(fileName, "r");
	
	if (fp_load == NULL)
		printf("ERROR: No file detected!\n");
	else
	{
		//Reads food name. Checks if file read is EOF (e.g. -1).
		while (getFileString20(food[*row].item, fp_load) != -1 && *row < 50)
		{
			//Checks if food is unique (e.g. -1).
			if ((dupe = DuplicateFood(food, *row)) == -1)
			{
				//Reads other food details (e.g. quantity, unit, and calories).
				if (fscanf(fp_load, "%f%s%d ", 	&food[*row].quantity, 
								   		  	    food[*row].unit, 
								   		  		&food[*row].calories) == 3)
					(*row)++;
			}
			//Checks if food is not unique (e.g. index of original food).
			else
			{
				printf("[Y/N] Do you wish to overwrite this data?\n");
				printf("Ingredient Duplicate: %s\n", food[*row].item);
				
				do
				{
					myCharInput(&ch);
					if (ch != 'Y' && ch != 'N')
						printf("[Invalid] Enter another input: ");
				} while (ch != 'Y' && ch != 'N');
				
				//Allows user to decide whether to replace the original or keep it.
				if (ch == 'Y')
				{
					strcpy(food[dupe].item, food[*row].item);
					strcpy(food[*row].item, "");
					fscanf(fp_load, "%f%s%d ", 	&food[dupe].quantity, 
										  	   	food[dupe].unit, 
										  	   	&food[dupe].calories);
				}
				else
				{
					strcpy(food[*row].item, "");
					fscanf(fp_load, "%d%s%d ", &nBuff, sBuff, &nBuff);
				}
			}
		}
		fclose(fp_load);
	}
	printf("\n");
}

/* AddRecipe displays and accepts user input regarding adding recipe information
   within a recipe/dish struct array.
   
   @param dish - Contains a struct array of recipe/dish of max size 50.
   @param food - Contains a struct array of food/ingredients of max size 50.
   @param *foodRow - Contains current food row count.
   @param *dishRow - Contains current dish row count.
*/

void
AddRecipe(DishType dish[], 
		  IngredientsType food[], 
		  int *foodRow, 
		  int *dishRow)
{
	char ch;
	
	printf("[----------Add Recipe----------]\n");
	printf("Dish name: ");
	do
	{
		getString20(dish[*dishRow].dishName);

		if (DuplicateDish(dish, *dishRow) != -1)
    		printf("Duplicate item is already stored!\n");
		else
			if (strlen(dish[*dishRow].dishName) < 1)
				printf("Item has no name!\n");

	} while(DuplicateDish(dish, *dishRow) != -1 || //Checks if recipe is unique.
			strlen(dish[*dishRow].dishName) < 1); //Checks if recipe has a name.

	printf("Classifaction of Dish [starter, main, dessert]: ");
	do
	{
		scanf("%s", dish[*dishRow].classification);
		
		//Converts inputted string to lowercase.
		toLower(dish[*dishRow].classification);

		//Checks if inputted text is "main", "starter", or "dessert".
		if (!isClassification(dish[*dishRow].classification))
			printf("Not a classification! Try another Input: ");
	} while (!isClassification(dish[*dishRow].classification));
	
	printf("Number of servings: ");
	myIntInput(&dish[*dishRow].serving);
	
	//Initializes the ingredient count of a recipe struct.
	dish[*dishRow].ingCount = 0;
	do
	{
		//Allows users to input ingredient information.
		AddIngredient(&dish[*dishRow], food, *foodRow);
		printf("[Y/N] Would you like to add more Ingredients: ");
		
		do 
		{
			myCharInput(&ch);
			if (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n')
				printf("[Invalid] Input another option: ");
		} while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
	} while (dish[*dishRow].ingCount<SIZE_ING &&
			 ch!='N' &&
			 ch!='n');
			 
	//Initializes the instruction count of a recipe struct.
	dish[*dishRow].insCount = 0;
	do 
	{
		//Allows users to input instructions information.
		AddStep(&dish[*dishRow]);
		printf("[Y/N] Would you like to add more Steps: ");
		
		do 
		{
			myCharInput(&ch);
			if (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n')
				printf("[Invalid] Input another option: ");
		} while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
	} while (dish[*dishRow].ingCount<SIZE_INS &&
			 ch!='N' &&
			 ch!='n');
	(*dishRow)++;
	
	printf("\n");
}

/* AddIngredient allows users to add an ingredient based on the same struct
   format information.
   
   @param dish - Contains a struct array of recipe/dish of max size 50.
   @param food - Contains a struct array of food/ingredients of max size 50.
   @param foodRow - Contains current food row count.
*/

void 
AddIngredient(DishType *dish, 
			  IngredientsType food[], 
			  int foodRow)
{
	int i, found = -1;
	String20 name;
	char ch;

	printf("Add Ingredient: ");
	do
	{
		getString20(name);
		
		if (strlen(food[dish->ingCount].item) < 1)
			printf("Item has no name!\n");
	} while (strlen(food[dish->ingCount].item) < 1);
	
	//Checks an existing ingredient in the food struct Array with the given input.
	for (i=0; i<foodRow && found==-1; i++)
		if (strcmp(food[i].item, name)==0)
			found = i;
			
	if (found != -1)
		//if existing ingredient was found, then use that ingredient for the recipe.
		dish->ingredients[dish->ingCount] = food[found];
	else	
	{
		//if not found, add ingredient to recipe with same code but 0 calories
		strcpy(dish->ingredients[dish->ingCount].item, name);
		
		printf("Quantity: ");
		myFloatInput(&dish->ingredients[dish->ingCount].quantity);
		
		printf("Unit: ");
		scanf("%15s%c", dish->ingredients[dish->ingCount].unit, &ch);
		
		printf("Calories: 0\n");
		dish->ingredients[dish->ingCount].calories = 0;
	}
	dish->ingCount++;
	printf("\n");
}

/* AddStep allows users to add an instruction with the given recipe.
   
   @param *dish - Contains a pointer of a single dish.
*/

void
AddStep(DishType *dish)
{
	int i, step;

	//Displays Instructions
	printf("List of Instructions\n");
	for (i=0; i<dish->insCount; i++)
		printf("	%d. %s\n", i+1, dish->instructions[i]);
	printf("\n");
	
	do
	{
		printf("Modify/Add a step number: ");
		myIntInput(&step);

		/* Checks if the user input > current instruction count to see if an
		instruction is skipped (+1 since input is 1-15, not 0-14). */
		if (step > dish->insCount+1)
			printf("You have skipped an instruction! Try again: \n");

	} while (step<1 || step>15 || step > dish->insCount+1);
	
	printf("\n[Edit] Instructions\n");
	printf("%d. ", step);
	/* Initializes an instruction in the case the user would overwrite 
	a current instruction. */
	strcpy(dish->instructions[step-1], "");
	getString70(dish->instructions[step-1]);

	//Checks if the inputted step is equal to instruction count, then it will increment.
	if (step == dish->insCount+1)
		dish->insCount++;
	printf("\n");
}

/* DeleteIngredient allows users to delete an ingredient from the food array struct.
   
   @param food - Contains a struct array of food/ingredients of max size 50.
   @param *count - Contains the current ingredient count of a recipe dish.
*/

void 
DeleteIngredient(IngredientsType food[], int *count)
{
	int i, input;

	printf("[----------Delete Ingredient----------]\n");
	if (*count > 1)
	{
		printf("List of Ingredients\n");
		for (i=0; i<*count; i++)
			printf("%d. %s\n", i+1, food[i].item);
		printf("\n");
		printf("[1-%d] Choose an Ingredient to Delete: ", *count);
		
		do
		{
			myIntInput(&input);
			
			if (!(input>=1 && input<=*count+1))
				printf("Selected ingredient does not exist! Try again: ");
		} while (!(input>=1 && input<=*count));
		
		//Deletes a food struct, and adjusts all the current values to the right.
		DeleteStructFood(food, *count, input);
		
		//Decrements total ingredient count.
		(*count)--;
	}
	else
		printf("Insufficient items to Delete!\n");
	printf("\n");
}

/* DeleteStep allows users to delete an instruction on the a given recipe.
   
   @param *dish - Contains a specific dish from the recipe dish array. 
*/

void
DeleteStep(DishType *dish)
{
	int i, input;
	
	printf("List of Instructions\n");
	for (i=0; i<dish->insCount; i++)
		printf("	%d. %s\n", i+1, dish->instructions[i]);
	
	if (dish->insCount>1)
	{
		printf("\nChoose a step to Delete: ");
		do
		{
			myIntInput(&input);
			
			if (!(input>=1 && input<=dish->insCount))
				printf("Selected step does not exist! Try again: ");
		} while(!(input>=1 && input<=dish->insCount));
		
		//A function that deletes a specific array
		DeleteArr(dish->instructions, dish->insCount, input);
		dish->insCount--;
	}
	else
		printf("Insufficient items to Delete!\n");
	printf("\n");
}

/* DeleteRecipes allows users to delete a recipe dish struct 
   on the given recipe dish struct array.
   
   @param *dish - Contains a specific dish from the recipe dish array. 
*/

void 
DeleteRecipes(DishType dish[], 
			  int *row)
{
	String20 key;
	int found;
	
	ListRecipeTitles(dish, *row);
	printf("Enter a recipe to Remove: ");
	getString20(key);
	
	found = RecipeTitleExists(dish, key, *row);
	
	if (found != -1)
	{
		DeleteStructDish(dish, *row, found);
		(*row)--;
	}
	else
		printf("Recipe not found!\n");
	printf("\n");
}

/* ModifyRecipe displays and allows users to choose a given modification option
   (e.g., AddStep, AddIngredient, DeleteStep, DeleteIngredient).
   
   @param dish - Contains a recipe/dish struct array of max size 50.
   @param food - Contains a food/ingredient struct array of max size 50.
   @param foodRow - Contains the current size of food row.
   @param dishRow - Contains the current size of dish row.
*/

void 
ModifyRecipe(DishType dish[], 
			 IngredientsType food[], 
			 int foodRow, 
			 int dishRow)
{
	String20 dishName;
	int choice, found, exit = 0;
	
	if (dishRow>0)
	{
		while (!exit)
		{
			printf("[----------Modify Recipe----------]\n");
			ListRecipeTitles(dish, dishRow);

			printf("Enter a Dish Name: ");
			do 
			{
				getString20(dishName);
		
				found = RecipeTitleExists(dish, dishName, dishRow);
				if (found == -1)
					printf("Recipe Title does not Exist! Try again: ");
			} while (found == -1);
	
			printf("[Recipe to Modify] %s\n", dishName);
			printf("[1] Add Ingredient\n");
			printf("[2] Delete Ingredient\n");
			printf("[3] Add Step\n");
			printf("[4] Delete Step\n");
			printf("[5] Return to Update Recipe Box Menu\n");
			printf("Input an Option: ");

			do
			{
				myIntInput(&choice);

				if (choice < 1 || choice > 5)
					printf("[Invalid] Enter another option: ");
			} while (choice < 1 && choice > 5);

			switch (choice)
			{
				case 1:
					AddIngredient(&dish[found], food, foodRow);	
					break;
				case 2:
					DeleteIngredient(dish[found].ingredients, &dish[found].ingCount);
					break;
				case 3:
					AddStep(&dish[found]);
					break;
				case 4:
					DeleteStep(&dish[found]);
					break;
				default:
					exit = 1;
					break;
			}
		}
	}
}

/* ListRecipeTitles displays all the recipes currrently available in the recipe/dish
   struct array.
   
   @param dish - Contains a recipe/dish struct array of max size 50.
   @param dishRow - Contains the current size of dish row.
*/

void 
ListRecipeTitles(DishType dish[], 
				 int row)
{
	int i;

	SortAlphabetical(dish, row);

	printf("[----------List Recipe Titles----------]\n");
	for (i=0; i<row; i++)
		printf("%d. %s\n", i+1, dish[i].dishName);
	printf("\n");
}

/* SearchRecipeTitle displays and asks for user input about which recipe to display
   all the information about (e.g., ingredients, steps, calories).
   
   @param dish - Contains a recipe/dish struct array of max size 50.
   @param dishRow - Contains the current size of dish row.
*/

void 
SearchRecipeTitle(DishType dish[], 
				  int row)
{
	String20 name;
	char buff;
	int found;

	ListRecipeTitles(dish, row);
	printf("Enter Recipe a you want to View: ");
	getString20(name);
	printf("\n");
	
	found = RecipeTitleExists(dish, name, row);
	if (found != -1)
		ViewRecipe(dish[found]);
	else
		printf("Not found!\n");
	
	printf("Press any key to continue... ");
	myCharInput(&buff);
	printf("\n");
}

/* ScanRecipes displays all recipe information per dish in a page by page 
   manner (e.g., Page 1: Adobo, Page 2: Sinigang, etc.).
   
   @param dish - Contains a recipe/dish struct array of max size 50.
   @param dishRow - Contains the current size of dish row.
   @param sort - A boolean value that determines if the function will sort the recipes or not.
*/

void
ScanRecipes(DishType dish[], 
			int row,
			int sort) //Displays each recipe one at a time
{
	int i = 0;
	char ch;
	
	printf("[----------Scan Recipes----------]\n");
	if (sort)
		SortAlphabetical(dish, row);
	ViewRecipe(dish[i]);
	
	do 
	{	
		myCharInput(&ch);
		if (ch == 'N' && i<row)
		{
			i++;
			if (i != row)
			{
				ViewRecipe(dish[i]);
				printf("[N] Next Page [P] Previous Page [X] Return to Menu ");
			}
		}
		else if (ch == 'P' && i>0)
		{
			i--;
			ViewRecipe(dish[i]);
		}
		else
			if (ch == 'P' && i<=0)
	  			printf("Page Limit Exceeded! ");
	  		else
	  			if (ch != 'X')
	  				printf("Invalid Input! Try another input: ");
	} while (ch != 'X' && i<row);
	
	printf("\n");
}

/* ScanRecipesByIngredient displays all recipe information per dish in a 
   page by page, with the condition that it will only display the recipe/dish 
   based on the inputted ingredient.
   
   @param dish - Contains a recipe/dish struct array of max size 50.
   @param dishRow - Contains the current size of dish row.
*/

void
ScanRecipesByIngredient(DishType dish[], 
						int row)
{
	int i = 0, found;
	char ch;
	String20 ingredient;
	
	printf("[----------Scan Recipes By Title----------]\n");
	printf("Search Ingredient: ");
	SortAlphabetical(dish, row);
	getString20(ingredient);	
	printf("\n");
	
	found = FindRecipeFromStart(dish, ingredient, i, row);
		
	if (found != -1)
	{
		i = found;
		do
		{				
			ViewRecipe(dish[i]);
			printf("[N] Next Page [P] Previous Page [X] Return to Menu ");
			myCharInput(&ch);
		
			if (ch == 'N')
			{
				/* Incorporates a search algorithm with n, such that i=n is 
				added or subtracted (refer to third parameter) for algorithm to 
				check the next list of scan recipes */
				found = FindRecipeFromStart(dish, ingredient, i+1, row);
			
				if (found != -1)
					i = found;
			}
			else if (ch == 'P' && i>=0)
			{
				found = FindRecipeFromEnd(dish, ingredient, i-1);
			
				if (found != -1)
					i = found;
			}
			else
				if (ch != 'X')
	  				printf("Invalid Input! Try another input: ");
	  			
		} while (ch != 'X' && found != -1);
	}	
	printf("\n");
}

/* GenerateShoppingList displays a shopping list based on the inputted recipe.
   Recomputes the ingredient information based on the original serving size
   of the recipe and the "new" serving size of the recipe.
   
   @param dish - Contains a recipe/dish struct array of max size 50.
   @param dishRow - Contains the current size of dish row.
*/

void
GenerateShoppingList(DishType dish[], int row)
{
	String20 name;
	float ratio;
	int i, found, size;
	char ch;
	
	printf("[----------Generate Shopping List----------]\n");
	ListRecipeTitles(dish, row);
	
	if (row > 0)
	{
		printf("Choose a Recipe: ");
		do
		{
			getString20(name);
			found = RecipeTitleExists(dish, name, row);
		
			if (found == -1)
				printf("Recipe not found! Try another input: ");
		} while (found == -1);
		
		printf("Input a serving size: ");
		myIntInput(&size);
		ratio = size*1.0/dish[found].serving;
		
		printf("Recipe: %s\n", dish[found].dishName);
		for (i=0; i<dish[found].ingCount; i++)
		{
			printf("%-20s ", dish[found].ingredients[i].item); 
			printf("%5.2f ", dish[found].ingredients[i].quantity * ratio);
			printf("%4s ", dish[found].ingredients[i].unit);
			printf("%5.2f\n", dish[found].ingredients[i].calories * ratio);
		}
	}
	else
		printf("No recipes available!\n");
	
	printf("\nPress any key to continue: ");
	myCharInput(&ch);
}

/* RecommendedMenu displays a the recommended courses that is under or equal to the target calorie
   intake. The order of recommendation are as follows: main, starter, then dessert. If the main
   course does not fully expend all the calories, then the succeeding courses will check if there
   is a dish that can still "eat" up those remaining calories.
   
   @param dish - Contains a recipe/dish struct array of max size 50.
   @param dishRow - Contains the current size of dish row.
*/

void
RecommendedMenu(DishType dish[],
				int row)
{
	DishType recommendation[3];
	int i, 
		temp[SIZE],
		tempCount, 
		recoCount = 0, 
		random,
		caloriePerServing, 
		calorie;
	
	printf("[----------Recommended Menu----------]\n");
	printf("Target Calorie Intake: ");
	myIntInput(&calorie);
	
	//Checks for main dishes under or equal to the calorie intake
	tempCount = 0;
	for (i=0; i<row; i++)
	{
		caloriePerServing = ComputeCalories(dish[i])/dish[i].serving;
		if (caloriePerServing <= calorie && //Divides it for servings more than 1 person
			strcmp(dish[i].classification, "main") == 0)
		{
			temp[tempCount] = i;
			tempCount++;
		}
	}
	
	if (tempCount > 0)
	{
		random = rand() % tempCount;
		recommendation[recoCount] = dish[temp[random]];
		caloriePerServing = ComputeCalories(recommendation[recoCount])/recommendation[recoCount].serving;
		calorie -= caloriePerServing;
		
		for (i=0; i<recommendation[recoCount].ingCount; i++)
		{
			recommendation[recoCount].ingredients[i].quantity *= (1/(recommendation[recoCount].serving*1.0));
			recommendation[recoCount].ingredients[i].calories /= recommendation[recoCount].serving;
		}
		recoCount++;
	}
	
	//Checks for starter dishes under or equal to the calorie intake
	tempCount = 0; //Resets temp count
	for (i=0; i<row; i++)
	{
		caloriePerServing = ComputeCalories(dish[i])/dish[i].serving;
		if (caloriePerServing <= calorie && 
			strcmp(dish[i].classification, "starter") == 0)
		{
			temp[tempCount] = i;
			tempCount++;
		}
	}
		
	if (tempCount > 0)
	{
		random = rand() % tempCount; //Range of random from 0 to tempCount
		recommendation[recoCount] = dish[temp[random]];
		caloriePerServing = ComputeCalories(recommendation[recoCount])/recommendation[recoCount].serving;
		calorie -= caloriePerServing;
		
		for (i=0; i<recommendation[recoCount].ingCount; i++)
		{
			recommendation[recoCount].ingredients[i].quantity *= (1/(recommendation[recoCount].serving*1.0));
			recommendation[recoCount].ingredients[i].calories /= recommendation[recoCount].serving;
		}
		recoCount++;
	}
	
	//Checks for dessert dishes under or equal to the calorie intake
	tempCount = 0;
	for (i=0; i<row; i++)
	{
		caloriePerServing = ComputeCalories(dish[i])/dish[i].serving;
		if (caloriePerServing <= calorie && 
			strcmp(dish[i].classification, "dessert") == 0)
		{
			temp[tempCount] = i;
			tempCount++;
		}
	}
		
	if (tempCount > 0)
	{
		random = rand() % tempCount;
		recommendation[recoCount] = dish[temp[random]];
		caloriePerServing = ComputeCalories(recommendation[recoCount])/recommendation[recoCount].serving;
		calorie -= caloriePerServing;
		
		for (i=0; i<recommendation[recoCount].ingCount; i++)
		{
			recommendation[recoCount].ingredients[i].quantity *= (1/(recommendation[recoCount].serving*1.0));
			recommendation[recoCount].ingredients[i].calories /= recommendation[recoCount].serving;
		}
		recoCount++;
	}
	
	ScanRecipes(recommendation, recoCount, 0);
}

/* ExportRecipes saves all the recipes currently with dish struct array in a
   text file.
   
   @param dish - Contains a recipe/dish struct array of max size 50.
   @param dishRow - Contains the current size of dish row.
*/
void 
ExportRecipes(DishType dish[], 
			  int row)
{
	FILE *fp_save;
	String20 fileName;
	int i;

	printf("[----------Export Recipes----------]\n");
	printf("Enter a text file name: ");
	getString20(fileName);
	
	fp_save = fopen(fileName, "w");

	if (fp_save == NULL || row == 0)
		printf("No data is detected to be saved!\n");
	else
	{
		for (i=0; i<row; i++)
		{
      		fprintf(fp_save, "%s\n", dish[i].dishName);
	  		fprintf(fp_save, "%d %s\n", dish[i].serving, dish[i].classification);
	  		SaveIngredients(fp_save, dish[i]);
	  		SaveSteps(fp_save, dish[i]);
	  		fprintf(fp_save, "\n");
      	}
      	fclose(fp_save);
	}
	printf("\n");
}

/* ImportRecipes loads all the recipes from text file to the dish struct
   array. Consider that for each recipe to be loaded, user is prompted if
   they will use the ingredient/measurements of an ingredient in the current
   food calorie count or will they use the measurements from the exported
   recipe.
   
   @param dish - Contains a recipe/dish struct array of max size 50.
   @param dishRow - Contains the current size of dish row.
*/
void
ImportRecipes(DishType dish[], 
			  IngredientsType food[],
			  int *dishRow,
			  int foodRow)
{
	FILE *fp_load;
	String20 fileName, sBuff;
	int dupe, nBuff;
	char ch;
	
	printf("\n");
	printf("[----------Import Recipes----------]\n");
	
	printf("Enter a text file name: ");
	scanf("%s%c", fileName, &ch);
	
	fp_load = fopen(fileName, "r");
	
	if (fp_load == NULL)
		printf("ERROR: No file detected!\n");
	else
	{
		while (getFileString20(dish[*dishRow].dishName, fp_load) != -1)
		{
			//If there is no duplicate dish.
			if ((dupe = DuplicateDish(dish, *dishRow)) == -1)
			{
				if (fscanf(fp_load, "%d%s%s%d", &dish[*dishRow].serving, 
								   		  		dish[*dishRow].classification, 
								   		  		sBuff,
												&dish[*dishRow].ingCount) == 4)
				{		
					toLower(dish[*dishRow].classification);
					ReadIngredients(fp_load, &dish[*dishRow], food, foodRow);
					fscanf(fp_load, "%s%d ", sBuff, &dish[*dishRow].insCount);
					ReadSteps(fp_load, &dish[*dishRow]);						
					(*dishRow)++;	
				}
			}
			else
			{
				printf("[Y/N] Do you wish to overwrite this data?\n");
				printf("Ingredient Duplicate: %s\n", dish[*dishRow].dishName);
				
				do
				{
					myCharInput(&ch);

					if (ch != 'Y' && ch != 'N')
						printf("Invalid Input! Try another Input: ");
				} while (ch != 'Y' && ch != 'N');
				
				if (ch == 'Y')
				{
					strcpy(dish[dupe].dishName, dish[*dishRow].dishName);
					strcpy(dish[*dishRow].dishName, "");
					
					if (fscanf(fp_load, "%d%s%s%d", &dish[dupe].serving, 
								   		  			dish[dupe].classification, 
								   		  			sBuff,
													&dish[dupe].ingCount) == 4)
					{
						toLower(dish[dupe].classification);
						ReadIngredients(fp_load, &dish[dupe], food, foodRow);
						fscanf(fp_load, "%s%d ", sBuff, &dish[dupe].insCount);
						ReadSteps(fp_load, &dish[dupe]);
					}
				}
				else
				{
					strcpy(dish[*dishRow].dishName, "");
					
					if (fscanf(fp_load, "%d%s%s%d", &nBuff, 
								   		  			sBuff, 
								   		  			sBuff,
													&nBuff) == 4)
					{
						ReadBuffIngredients(fp_load, dish[*dishRow].ingCount);
						fscanf(fp_load, "%s%d", sBuff, &nBuff);	
						ReadBuffSteps(fp_load, dish[*dishRow].insCount);
					}
				}
			}
		}
		fclose(fp_load);
	}
	printf("\n");
}