/*
  funcInput provides a reusable scanf for "pausing" the program
  unless the user inputs a value.
*/
#include "info.h"
#include "helper.c"

void
Menu()
{
	int loop = 1;
	char input;

	printf("[A] Access Recipes\n");
	printf("[U] Update Recipes\n");
	printf("[E] Exit\n");

	do
	{
		scanf(" %c", &input);
		if (input != 'A' && input && 'U' && input != 'E')
			printf("[Invalid] Enter another option: ");
	} while (loop && input != 'A' && input && 'U' && input != 'E');
	
	if (input == 'E')
	{
		loop = 0;
		//Update();
	}
}

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
    	
    	if (!isUniqueFood(food, *row))
			printf("Duplicate item is already stored!\n");

		if (strlen(food[*row].item)<1)
			printf("Item has no name!\n");

	} while (!isUniqueFood(food, *row) || 
			 strlen(food[*row].item) < 1);
	
	printf("Quantity: ");
	myIntInput(&food[*row].quantity);
		
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
	int i;

	//Page is 0,1,2,3
	//Row is 0,1,2,3,4,5,6...49

	printf("[----------View Food Calorie----------]\n");
	for (i=*page*10; i<10+*page && i < *row; i++)
	  	printf("%s %d %s %d\n", food[i].item, food[i].quantity, food[i].unit, food[i].calories);
	printf("\n");
	printf("Page: %d [N] Next Page [P] Previous Page [X] Return to Menu ", *page+1);
	
	do
	{
		myCharInput(&key);
		printf("\n");
		if (key == 'N' && *page != *row/10)
		{
	   		(*page)++;
	   		ViewFood(food, row, page);
	   	}
		else if (key == 'P' && *page != 0)
		{
	   		(*page)--;
	   		ViewFood(food, row, page);
		}
	   	else if ((key == 'N' || key == 'P') && (*page == *row/10 || *page == 0))
			printf("Exceeds page limit!\n");
		else
			if (key != 'X')
	   			printf("Invalid Input! Try another input: ");

    } while (key != 'X');
    
	*page = 0;
	printf("\n");
	return; //Update();
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
	  		fprintf(fp_save, "%d %s %d\n", food[i].quantity, food[i].unit, food[i].calories);
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
	int dupe = -1, nBuff;
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
			if (isUniqueFood(food, *row))
			{
				if (fscanf(fp_load, "%d%s%d", &food[*row].quantity, 
								   		  	   food[*row].unit, 
								   		  	  &food[*row].calories) == 3)
					(*row)++;
			}
			else
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
		}
		if (dupe == -1)
			scanf("%c", &ch);
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

		if (!isUniqueDish(dish, *dishRow))
    		printf("Duplicate item is already stored!\n");

		if (strlen(dish[*dishRow].dishName)<1)
			printf("Item has no name!\n");

	} while(!isUniqueDish(dish, *dishRow) ||
			strlen(dish[*dishRow].dishName)<1);

	printf("Classifaction of Dish [starter, main, dessert]: ");
	do
	{
		scanf("%s", dish[*dishRow].classification);
		toLower(dish[*dishRow].classification);

		if (!isClassification(dish[*dishRow].classification))
			printf("Not a classification!\n");
	} while (!isClassification(dish[*dishRow].classification));
	
	printf("Number of servings: ");
	myIntInput(&dish[*dishRow].serving);
	
	//Add Ingredient System
	dish[*dishRow].ingCount = 0;
	do
	{
		AddIngredient(&dish[*dishRow], food, *foodRow);
		printf("[Y/N] Would you like to add more Ingredients: ");
		myCharInput(&ch);
		printf("\n");
	} while (dish[*dishRow].ingCount<20 &&
			 ch!='N' &&
			 ch!='n');
			 
	//Add Instruction System
	dish[*dishRow].insCount = 0;
	do 
	{
		AddStep(&dish[*dishRow]);
		printf("[Y/N] Would you like to add more Steps: ");
		myCharInput(&ch);
	} while (dish[*dishRow].ingCount<15 &&
			 ch!='N' &&
			 ch!='n');
	printf("\n");
	
	(*dishRow)++;
	//Update();
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
		myIntInput(&dish->ingredients[dish->ingCount].quantity);
		
		printf("Unit: ");
		scanf("%15s%c", dish->ingredients[dish->ingCount].unit, &ch);
		
		printf("Calories: 0\n");
		dish->ingredients[dish->ingCount].calories = 0;
	}
	dish->ingCount++;
}

void 
DeleteIngredient(IngredientsType food[], int *count)
{
	//Check for infinite loops if a char is inputted on an int value
	int i, input;

	if (*count > 1)
	{
		printf("List of Ingredients\n");
		for (i=0; i<*count; i++)
			printf("%d. %s\n", i+1, food[i].item);
		printf("Choose an Ingredient to Delete: ");
		
		do
		{
			myIntInput(&input);
			
			if (!(input>=1 && input<=*count))
				printf("Selected ingredient does not exist! Try again: ");
		} while (!(input>=1 && input<=*count));
		
		DeleteStructFood(food, *count, input);
		(*count)--;
	}
	else
		printf("Insufficient items to Delete!\n");
}

void
AddStep(DishType *dish)
{
	int i, step, skipped;

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
		skipped = 0;
		printf("Modify/Add a step number: ");
		myIntInput(&step);

		if (step > dish->insCount+1) //Using count as my basis
			skipped = 1;

		if (skipped)
			printf("You have skipped an instruction! Try again: \n");

	} while (step>=1 && step<=15 && skipped);
	
	printf("\n[Edit] Instructions\n");
	printf("%d. ", step);
	strcpy(dish->instructions[step-1], "");
	getString70(dish->instructions[step-1]);
	
	if (step == dish->ingCount+1)
		dish->insCount++;
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
}

void 
ModifyRecipe(DishType dish[], IngredientsType food[], int foodRow, int recipeRow)
{
	String20 dishName;
	int choice, found;
	
	if (recipeRow<1) Update();
	printf("[----------Modify Recipe----------]\n");
	ListRecipeTitles(dish, recipeRow);

	printf("Enter a Dish Name: ");
	do 
	{
		getString20(dishName); //No need to retype after entered
		
		found = RecipeTitleExists(dish, dishName, recipeRow);
		if (found == -1)
			printf("Recipe Title does not Exist! Try again: ");
	} while (found == -1);
	
	printf("[Recipe to Modify] %s\n", dishName);
	printf("	[1] Add Ingredient\n");
	printf("	[2] Delete Ingredient\n");
	printf("	[3] Add Step\n");
	printf("	[4] Delete Step\n");
	printf("	[5] Return to Update Recipe Box Menu\n");
	printf("\n");
	printf("Input an Option: ");

	do
	{
		myIntInput(&choice);

		if (!(choice >= 1 && choice <= 5))
			printf("[Invalid] Enter another option: ");
	} while (!(choice >= 1 && choice <= 5));

	switch (choice)
	{
		case 1:
			AddIngredient(&dish[found], food, foodRow);
			ModifyRecipe(dish, food, foodRow, recipeRow);
			break;
		case 2:
			DeleteIngredient(dish[found].ingredients, &dish[found].ingCount);
			ModifyRecipe(dish, food, foodRow, recipeRow);
			break;
		case 3:
			AddStep(&dish[found]);
			ModifyRecipe(dish, food, foodRow, recipeRow);
			break;
		case 4:
			DeleteStep(&dish[found]);
			ModifyRecipe(dish, food, foodRow, recipeRow);
			break;
		case 5:
			break;
	} while (choice != 5);

	Update();
}

void 
DeleteRecipes(DishType dish[], 
			  int *row)
{
	String20 key;
	int found;
	
	ListRecipeTitles(dish, *row);
	getString20(key);
	
	found = RecipeTitleExists(dish, key, *row);
	
	if (found != -1)
	{
		DeleteStructDish(dish, *row, found);
		(*row)--;
	}
	else
		printf("Recipe not found!\n");
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
		//Access
	else
		printf("Not found!\n\n");
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
	//Update();
}

/*
void
GenerateShoppingList(DishType dish[], int row)
{
	String20 name;
	int i, found;
	
	printf("[----------Generate Shopping List----------]\n");
	ListRecipeTitles(dish, row);
	printf("Which of these recipes to generate a shopping list for?\n");
	getString20(name);
	
	found = RecipeTitleExists(dish, name, row);
	
	if (found != -1)
		printf("%s\n", dish[i].dishName);
		//Access
	else
		printf("Not found!");
	
	//Access()
}
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
	
	if (CheckIngredient(dish[i], ingredient, dish[i].ingCount))
		ViewRecipe(dish[i]);
	else
	{
		found = FindRecipeFromStart(dish, ingredient, i, row);
		
		if (found != -1)
			i = found;
		//else
			//Access();
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
	int dupe = -1, nBuff;
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
			if (isUniqueDish(dish, *row))
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

void
Update()
{
	String20 username = "admin";
    String20 password = "ad1234";
    String20 userInput;
    String20 userPassword;
    int input;
      
    printf("Enter username: ");
    scanf("%s", userInput);
    printf("Enter Password: ");
    scanf("%s", userPassword);
         
    if (strcmp(userInput, username) != 0 || strcmp(userPassword, password) != 0)
    {
        printf("Invalid username or password.\n");
        Menu();
    }
    
    printf("[----------Menu----------]\n");
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
    myIntInput(&input);
}