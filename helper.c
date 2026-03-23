int //Consumes the input buffer, fflush doesn't seem to work on cmd prompt
nextLine()
{
	int i = 0;
	char ch;
	
	do
	{
		scanf("%c", &ch);
		if (ch != '\n')
			i++;
	} while (ch != '\n');
	
	return i;
}

void 
myIntInput(int * dest)
{
	int buffer;
	
	do 
	{
		scanf("%d", dest);
		buffer = nextLine();
				
		if (buffer > 0)
			printf("Invalid Input. Try another Input: "); //Handles inputs like 1ABC
	} while (buffer > 0);
}

void
myCharInput(char * dest)
{
	int buffer;
	
	do
	{
		scanf("%c", dest);
		buffer = nextLine();
				
		if (buffer > 0)
			printf("Invalid Input. Try another Input: "); //Handles inputs like 1ABC
	} while (buffer > 0);
}


void
getString70(String70 string)
{
	int i = 0;
	char ch;
	
	do 
	{
		scanf("%c", &ch);
		
		if (ch != '\n')
		{
			string[i] = ch;
			i++;
		}
	} while (i<70 && ch != '\n');
	
	string[i] = '\0';
}

void
getString20(String20 string)
{
	int i = 0;
	char ch;
	
	do 
	{
		scanf("%c", &ch);
		
		if (ch != '\n')
		{
			string[i] = ch;
			i++;
		}
	} while (i<20 && ch != '\n');
	
	string[i] = '\0';
}

int
getFileString20(String20 string, FILE *fp)
{
	int i = 0, eof;
	char ch;
	
	do 
	{
		eof = fscanf(fp, "%c", &ch);
		
		if (ch != '\n' && eof != EOF)
		{
			string[i] = ch;
			i++;
		}
	} while (i<20 && ch != '\n' && eof != EOF);
	
	string[i] = '\0';
	
	return eof;
}

void
getFileString70(String70 string, FILE *fp)
{
	int i = 0, eof;
	char ch;
	
	do 
	{
		eof = fscanf(fp, "%c", &ch);
		
		if (ch != '\n' && eof != EOF)
		{
			string[i] = ch;
			i++;
		}
	} while (i<70 && ch != '\n' && eof != EOF);
	
	string[i] = '\0';
}

int 
isUniqueFood(IngredientsType food[], 
		 	 int row)
{
	int i, unique = 1;

	for (i=0; i<row && unique; i++)
		if (strcmp(food[row].item, food[i].item)==0 && row != i)
			unique = 0;
			
	return unique;
}

int 
isUniqueDish(DishType dish[], 
		 	 int row)
{
	int i, unique = 1;

	for (i=0; i<row && unique; i++)
		if (strcmp(dish[row].dishName, dish[i].dishName)==0 && row != i)
			unique = 0;
			
	return unique;
}

int 
DuplicateFood(IngredientsType food[], 
		 	 	int row)
{
	int i, duplicate = -1;

	for (i=0; i<row && duplicate == -1; i++)
		if (strcmp(food[row].item, food[i].item)==0 && row != i)
			duplicate = i;
			
	return duplicate;
}

void 
toLower(String15 string)
{
	int i;

	for (i=0; i<15; i++)
		if (string[i]>='A' && string[i]<='Z')
			string[i] += 32;
}

int
isClassification(String15 classification)
{
	return 	strcmp(classification, "starter") == 0 ||
		   	strcmp(classification, "main") == 0 ||
			strcmp(classification, "dessert") == 0;	
}

void 
DeleteStructFood(IngredientsType food[], 
			 	 int count, 
			 	 int key)
{
	int i;
	//60 66 67 68 69
	//66 67 68 69 garbage but we do not want this
	for (i=key-1; i<count-1; i++)
		food[i] = food[i+1];
}

void
DeleteStructDish(DishType dish[],
				 int count,
				 int key)
{
	int i;
	
	for (i=key; i<count-1; i++)
		dish[i] = dish[i+1];	
}

void
DeleteArr(String70 ins[], 
		  int count, 
		  int key)
{
	int i;
	
	for (i=key-1; i<count-1; i++)
		strcpy(ins[i], ins[i+1]);
}

void 
SwapStruct(DishType *dish1, 
		   DishType *dish2)
{
	DishType temp;
	temp = *dish1;
	*dish1 = *dish2;
	*dish2 = temp;
}

void
SortAlphabetical(DishType dish[], 
				 int row)
{
	int i, j, min;

	for (i=0; i<row-1; i++)
	{
		min = i;
		for (j=i+1; j<row; j++)
			if (strcmp(dish[min].dishName, dish[j].dishName) > 0)
				min = j;
		SwapStruct(&dish[i], &dish[min]);
	}
}

int
RecipeTitleExists(DishType dish[],  
				  String20 name,
				  int row)
{
	int i, found = -1;

	for (i=0; i<row && found==-1; i++) //debating if I should use binary search
		if (strcmp(dish[i].dishName, name) == 0)
			found = i;

	return found;
}

void 
ViewRecipe(DishType dish)
{
	int i;
	printf("[----------Recipe Info----------]\n");
	printf("Name: %s\n", dish.dishName);
	printf("Classification: %s\n", dish.classification);
	printf("Serving size: %d\n", dish.serving);
	printf("Total Calories: %d\n\n", ComputeCalories(dish) * dish.serving);

	printf("Ingredients\n");
	for (i=0; i<dish.ingCount; i++)
	{
		printf("	%d. %s\n", i+1, dish.ingredients[i].item);
		printf("		Quantity: %d %s\n", dish.ingredients[i].quantity, dish.ingredients[i].unit);
		printf("		Calories: %d\n", dish.ingredients[i].calories);
	}
	
	printf("Instructions\n");
	for (i=0; i<dish.insCount; i++)
		printf("	%d. %s\n", i+1, dish.instructions[i]);
	printf("\n");
}

int
ComputeCalories(DishType dish)
{
	int i, sum = 0;
	
	for (i=0; i<dish.ingCount; i++)
		sum += dish.ingredients[i].calories;
	
	return sum;
}

int 
CheckIngredient(DishType dish, String20 ingredient, int ingCount)
{
	int i, found = 0;
	
	for (i=0; i<ingCount && !found; i++)
		if (strcmp(dish.ingredients[i].item, ingredient) == 0)
			found = 1;
	
	return found;
}

int
FindRecipeFromStart(DishType dish[], String20 ingredient, int start, int row)
{
	int i, key = -1;
	
	for (i=start; i<row && key == -1; i++)
		if (CheckIngredient(dish[i], ingredient, dish[i].ingCount))
			key = i;
		
	return key;
}

int
FindRecipeFromEnd(DishType dish[], String20 ingredient, int end)
{
	int i, key = -1;
	
	for (i=end; i>=0 && key == -1; i--)
		if (CheckIngredient(dish[i], ingredient, dish[i].ingCount))
			key = i;
		
	return key;
}

void 
SaveIngredients(FILE *fp, DishType dish)
{
	int i;
	
	fprintf(fp, "Ingredients %d\n", dish.ingCount);
	for (i=0; i<dish.ingCount; i++)
		fprintf(fp, "%d %s %s\n", dish.ingredients[i].quantity, dish.ingredients[i].unit, dish.ingredients[i].item);
}

void
SaveSteps(FILE *fp, DishType dish)
{
	int i;
	
	fprintf(fp, "Steps %d\n", dish.insCount);
	for (i=0; i<dish.insCount; i++)
		fprintf(fp, "%s\n", dish.instructions[i]);
}

void
ReadIngredients(FILE *fp, DishType *dish)
{
	int i; 
	
	for (i=0; i<dish->ingCount; i++)
	{
		fscanf(fp, "%d%s ", &dish->ingredients[i].quantity,
							 dish->ingredients[i].unit);
		getFileString20(dish->ingredients[i].item, fp);
		dish->ingredients[i].calories = 0;
	}
}

void
ReadSteps(FILE *fp, DishType *dish)
{
	int i; 
	
	for (i=0; i<dish->insCount; i++)
		getFileString70(dish->instructions[i], fp);
}
