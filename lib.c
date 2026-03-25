/*
  funcInput provides a reusable scanf for "pausing" the program
  unless the user inputs a value.
*/
#include "info.h"
#include "helper.c"

//isUnique checks if food has not been added to the list.
void
AddFoodCalorie(IngredientsType food[], 
			   int *row)
{	
	printf("[----------Add Food Calorie----------]\n");
	do 
	{
		printf("Item name: ");
		getString20(food[*row].item);
    	
    	if (DuplicateFood(food, *row) != -1)
			printf("Duplicate item is already stored!\n");

		if (strlen(food[*row].item)<1)
			printf("Item has no name!\n");

	} while (DuplicateFood(food, *row) != -1 || 
			 strlen(food[*row].item) < 1);
	
	printf("Quantity: ");
	myFloatInput(&food[*row].quantity);
		
	printf("Unit: ");
	scanf("%15s", food[*row].unit);
	
	printf("Calories: ");
	myIntInput(&food[*row].calories);
	
	printf("\n");
	
	(*row)++;
}

void 
ViewFood(IngredientsType food[], int *row, int *page)
{
    char key;

	//Page is 0,1,2,3
	//Row is 0,1,2,3,4,5,6...49
	DisplayFood(food, row, page);
	do
	{	
		myCharInput(&key);
		if (key == 'N' && *page != *row/10)
		{
			(*page)++;
			DisplayFood(food, row, page);
		}
		else if (key == 'P' && *page != 0)
		{
	   		(*page)--;
	   		DisplayFood(food, row, page);
	   	}
	   	else if ((key == 'N' || key == 'P') && (*page == *row/10 || *page == 0))
			printf("Exceeds page limit! ");
		else
			if (key != 'X')
	   			printf("[Invalid] Enter another input: ");

    } while (key != 'X');
    
	*page = 0;
}


void 
SaveCalorie(IngredientsType food[], int *row)
{
	FILE *fp_save;
	String20 fileName;
	int i;

	printf("[----------Save Food Calorie----------]\n");
	printf("Enter a text file name: ");
	getString20(fileName);
	
	fp_save = fopen(fileName, "w");

	if (fp_save == NULL || *row == 0)
		printf("No data is detected to be saved!\n");
	else
	{
		for (i=0; i<*row; i++)
		{
      		fprintf(fp_save, "%s\n", food[i].item);
	  		fprintf(fp_save, "%g %s %d\n", food[i].quantity, food[i].unit, food[i].calories);
	  		fprintf(fp_save, "\n");
      	}
      	fclose(fp_save);
	}
	printf("\n");
}


void
LoadCalories(IngredientsType food[], int *row)
{
	FILE *fp_load;
	String20 fileName, sBuff;
	int dupe, nBuff;
	char ch;
	
	printf("\n");
	printf("[----------Load Food Calorie----------]\n");
	
	printf("Enter a text file name: ");
	scanf("%s", fileName);
	
	fp_load = fopen(fileName, "r");
	
	if (fp_load == NULL)
		printf("ERROR: No file detected!\n");
	else
	{
		while (getFileString20(food[*row].item, fp_load) != -1)
		{
			if ((dupe = DuplicateFood(food, *row)) != -1)
			{
				if (fscanf(fp_load, "%f%s%d ", &food[*row].quantity, 
								   		  	   food[*row].unit, 
								   		  	  &food[*row].calories) == 3)
					(*row)++;
			}
			else
			{
				printf("[Y/N] Do you wish to overwrite this data?\n");
				printf("Ingredient Duplicate: %s\n", food[*row].item);
				scanf("%c", &ch);

				do
				{
					myCharInput(&ch);

					if (ch != 'Y' && ch != 'N')
						printf("[Invalid] Enter another input: ");
				} while (ch != 'Y' && ch != 'N');
				
				if (ch == 'Y')
				{
					strcpy(food[dupe].item, food[*row].item);
					strcpy(food[*row].item, "");
					fscanf(fp_load, "%f%s%d ", &food[dupe].quantity, 
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


void
AddRecipe(DishType dish[], 
		  IngredientsType food[], 
		  int * foodRow, 
		  int * dishRow)
{
	char ch;
	
	printf("[----------Add Recipe----------]\n");
	printf("Dish name: ");
	do
	{
		getString20(dish[*dishRow].dishName);

		if (DuplicateDish(dish, *dishRow) != -1)
    		printf("Duplicate item is already stored!\n");

		if (strlen(dish[*dishRow].dishName)<1)
			printf("Item has no name!\n");

	} while(DuplicateDish(dish, *dishRow) != -1 ||
			strlen(dish[*dishRow].dishName)<1);

	printf("Classifaction of Dish [starter, main, dessert]: ");
	do
	{
		scanf("%s", dish[*dishRow].classification);
		toLower(dish[*dishRow].classification);

		if (!isClassification(dish[*dishRow].classification))
			printf("Not a classification! Try another Input: ");
	} while (!isClassification(dish[*dishRow].classification));
	
	printf("Number of servings: ");
	myIntInput(&dish[*dishRow].serving);
	
	//Add Ingredient System
	dish[*dishRow].ingCount = 0;
	do
	{
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
			 
	//Add Instruction System
	dish[*dishRow].insCount = 0;
	do 
	{
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
	printf("\n");
	
	(*dishRow)++;
}

void 
AddIngredient(DishType *dish, 
			  IngredientsType food[], 
			  int foodRow)
{
	//check food-calorie first with dish name
	int i, found = -1;
	String20 name;
	char ch;

	printf("Add Ingredient: ");
	getString20(name);
	for (i=0; i<foodRow && found==-1; i++)
		if (strcmp(food[i].item, name)==0)
			found = i;

	if (found != -1)
		dish->ingredients[dish->ingCount] = food[found];
	else	
	{
	//if it is not found, add ingredient to recipe with same code but 0 calories
		strcpy(dish->ingredients[dish->ingCount].item, name);
		//printf("Item name: %s\n", dish->ingredients[dish->ingCount].item);
		
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

void
AddStep(DishType *dish)
{
	int i, step;

	//User can add a step anywhere from 1-15
	//But user cannot skip so if the recipe only has 1 step
	//AKA, the first step, user cannot add at the end and
	//Needs to be reprompted for a valid step
	printf("List of Instructions\n");
	for (i=0; i<dish->insCount; i++)
		printf("	%d. %s\n", i+1, dish->instructions[i]);
	printf("\n");
	
	do
	{
		printf("Modify/Add a step number: ");
		myIntInput(&step);

		if (step > dish->insCount+1) //Using count as my basis
			printf("You have skipped an instruction! Try again: \n");

	} while (step<1 || step>15 || step > dish->insCount+1);
	
	printf("\n[Edit] Instructions\n");
	printf("%d. ", step);
	strcpy(dish->instructions[step-1], "");
	getString70(dish->instructions[step-1]);

	if (step == dish->insCount+1)
		dish->insCount++;
	printf("\n");
}

void 
DeleteIngredient(IngredientsType food[], int *count)
{
	//Check for infinite loops if a char is inputted on an int value
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
		
		DeleteStructFood(food, *count, input);
		(*count)--;
	}
	else
		printf("Insufficient items to Delete!\n");
	printf("\n");
}

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
		
		DeleteArr(dish->instructions, dish->insCount, input);
		dish->insCount--;
	}
	else
		printf("Insufficient items to Delete!\n");
	printf("\n");
}

void 
ModifyRecipe(DishType dish[], IngredientsType food[], int foodRow, int dishRow)
{
	String20 dishName;
	int choice, found;
	
	if (dishRow>0)
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
		printf("\n");
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
				ModifyRecipe(dish, food, foodRow, dishRow);
				break;
			case 2:
				DeleteIngredient(dish[found].ingredients, &dish[found].ingCount);
				ModifyRecipe(dish, food, foodRow, dishRow);
				break;
			case 3:
				AddStep(&dish[found]);
				ModifyRecipe(dish, food, foodRow, dishRow);
				break;
			case 4:
				DeleteStep(&dish[found]);
				ModifyRecipe(dish, food, foodRow, dishRow);
				break;
			default:
				break;
		}
	}
}

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

void 
SearchRecipeTitle(DishType dish[], 
				  int row)
{
	String20 name;
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
	printf("\n");
}

void
ScanRecipes(DishType dish[], 
			int row) //Displays each recipe one at a time
{
	int i = 0;
	char ch;
	
	printf("[----------Scan Recipes----------]\n");
	SortAlphabetical(dish, row);
	ViewRecipe(dish[i]);
	
	do 
	{	
		printf("[N] Next Page [P] Previous Page [X] Return to Menu ");
		myCharInput(&ch);
		if (ch == 'N' && i<row)
		{
			i++;
			if (i!=row)
				ViewRecipe(dish[i]);
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
}

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
		ratio = size/dish[found].serving;
		
		printf("Recipe: %s\n", dish[found].dishName);
		for (i=0; i<dish[found].ingCount; i++)
		{
			printf("%s ", dish[found].ingredients[i].item); 
			printf("%g ", dish[found].ingredients[i].quantity * ratio);
			printf("%.1g\n", dish[found].ingredients[i].calories * ratio);
		}
	}
	else
		printf("No recipes available!\n");
	
	printf("\nPress any key to continue: ");
	myCharInput(&ch);
}

void
RecommendMenu()
{
	int calorie;
	
	printf("[----------Recommended Menu----------]\n");
	myIntInput(&calorie);
	
	//<=calories;
}

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
	
	if (CheckIngredient(dish[i], ingredient, dish[i].ingCount))
		ViewRecipe(dish[i]);
	else
	{
		found = FindRecipeFromStart(dish, ingredient, i, row);
		
		if (found != -1)
			i = found;
	}
			
	do
	{		
		ViewRecipe(dish[i]);
		printf("[N] Next Page [P] Previous Page [X] Return to Menu ");
		myCharInput(&ch);
		
		if (ch == 'N')
		{
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
	  			
	} while ((ch == 'N' || ch == 'P') && ch != 'X' && i != -1);
}

void 
ExportRecipes(DishType dish[], int *row)
{
	FILE *fp_save;
	String20 fileName;
	int i;

	printf("[----------Export Recipes----------]\n");
	printf("Enter a text file name: ");
	getString20(fileName);
	
	fp_save = fopen(fileName, "w");

	if (fp_save == NULL || *row == 0)
		printf("No data is detected to be saved!\n");
	else
	{
		for (i=0; i<*row; i++)
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

void
ImportRecipes(DishType dish[], int *row)
{
	FILE *fp_load;
	String20 fileName, sBuff;
	int dupe, nBuff;
	char ch;
	
	printf("\n");
	printf("[----------Import Recipes----------]\n");
	
	printf("Enter a text file name: ");
	scanf("%s", fileName);
	
	fp_load = fopen(fileName, "r");
	
	if (fp_load == NULL)
		printf("ERROR: No file detected!\n");
	else
	{
		while (getFileString20(dish[*row].dishName, fp_load) != -1)
		{
			if (DuplicateDish(dish, *row) != -1)
			{
				if (fscanf(fp_load, "%d%s%s%d", &dish[*row].serving, 
								   		  		dish[*row].classification, 
								   		  		sBuff,
												&dish[*row].ingCount) == 4)
				{		
					ReadIngredients(fp_load, &dish[*row]);
					fscanf(fp_load, "%s%d ", sBuff, &dish[*row].insCount);
					ReadSteps(fp_load, &dish[*row]);						
					(*row)++;	
				}
			}
			/*else
			{
				printf("[Y/N] Do you wish to overwrite this data?\n");
				printf("Ingredient Duplicate: %s\n", food[*row].item);
				scanf("%c", &ch);
				dupe = DuplicateFood(food, *row);
				do
				{
					myCharInput(&ch);

					if (ch != 'Y' && ch != 'N')
						printf("Invalid Input! Try another Input: ");
				} while (ch != 'Y' && ch != 'N');
				
				if (ch == 'Y')
				{
					strcpy(food[dupe].item, food[*row].item);
					strcpy(food[*row].item, "");
					fscanf(fp_load, "%d%s%d", &food[dupe].quantity, 
										  	  food[dupe].unit, 
										  	  &food[dupe].calories);
				}
				else
				{
					strcpy(food[*row].item, "");
					fscanf(fp_load, "%d%s%d", &nBuff, sBuff, &nBuff);
				}
			}
		}*/
		}
		scanf("%c", &ch);
		//if (dupe == -1)
			//scanf("%c", &ch);
		fclose(fp_load);
	}
	printf("\n");
}