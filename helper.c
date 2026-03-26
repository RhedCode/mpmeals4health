/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. I have
constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons, nor did I employ the use of AI in any part of the deliverable.
																Rhed Lanz C. Dela Cruz, DLSU ID# 12507253
*********************************************************************************************************/

/* nextLine is a function that considers "eating" the "unread" inputs made
   by the user. In the case of input mismatch or char receives "abc123" similar
   inputs. 
     
   @return i is the number of "characters" that remains in the stdin until it reads
   '\n'.
*/
int
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

/* myIntInput is a integer specific input function used to check for any issues
   with the input (e.g., incorrect input format, exceeding number of input characters).
     
   @param *dest the variable where the input will be stored.
*/

void 
myIntInput(int *dest)
{
	int buffer;
	
	do 
	{
		scanf("%d", dest);
		buffer = nextLine();
				
		if (buffer > 0)
			printf("Invalid Input. Try another Input: ");
	} while (buffer > 0);
}

/* myFloatInput is a float specific input function used to check for any issues
   with the input (e.g., incorrect input format, exceeding number of input characters).
     
   @param *dest the variable where the input will be stored.
*/

void 
myFloatInput(float *dest)
{
	int buffer;
	
	do 
	{
		scanf("%f", dest);
		buffer = nextLine();
				
		if (buffer > 0)
			printf("Invalid Input. Try another Input: ");
	} while (buffer > 0);
}

/* myCharInput is a char specific input function used to check for any issues
   with the input (e.g., incorrect input format, exceeding number of input characters).
     
   @param *dest the variable where the input will be stored.
*/
void
myCharInput(char *dest)
{
	int buffer;
	
	do
	{
		scanf("%c", dest);
		buffer = nextLine();
				
		if (buffer > 0)
			printf("Invalid Input. Try another Input: ");
	} while (buffer > 0);
}

/* loadAccount loads the account details "registered" within the program.
     
   @param username is the variable where the username inputted by the user is stored.
   @param password is the variable where the password inputted by the user is stored.
*/

void
loadAccount(String20 username, String20 password)
{
	FILE *fp;
	String20 fileName = "admin.txt";
	
	fp = fopen(fileName, "r");	
	
	if (fp != NULL)
	{
		fscanf(fp, "%s%s", username, password);
		fclose(fp);
	}
	else 
		printf("File was not loaded!\n");
}

/* loginPage displays the login page where the user can "login" to the update menu.
     
   @param username is the variable where the username inputted by the user is stored.
   @param password is the variable where the password inputted by the user is stored.
*/
int 
loginPage(String20 username, String20 password)
{
    String20 userInput;
    String20 userPassword;
    
    printf("[----------Login Page----------]\n");
    printf("Enter username: ");
    scanf("%s", userInput);
    printf("Enter Password: ");
    scanf("%s", userPassword);
    
    if (strcmp(userInput, username) != 0 || strcmp(userPassword, password) != 0)
	{
        printf("Invalid username or password.\n");
        return 0;
    }
    
    return 1;
}

/* getString70 allows user to input "multiple words" with the given array string
   of size 70.
     
   @param string is the variable where the string will be stored.
*/

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

/* getString20 allows user to input "multiple words" with the given array string
   of size 20.
     
   @param string is the variable where the string will be stored.
*/

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

/* getFileString20 reads a file with "multiple words" that will be stored in a string
   variable of size 20.
     
   @param string is the variable where the string will be stored.
   @param *fp is the file that will be read.
   @return eof is the number that checks if the file that was read is already at the
   end of the file.
*/

int
getFileString20(String20 string, 
				FILE *fp)
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

/* getFileString70 reads a file with "multiple words" that will be stored in a string
   variable of size 70.
     
   @param string is the variable where the string will be stored.
   @param *fp is the file that will be read.
*/

void
getFileString70(String70 string, 
				FILE *fp)
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

/* DuplicateFood checks if a food struct name is already in the list.
     
   @param food is a food struct array of max size of 50.
   @param foodRow is the current food row in the area.
   @return duplicate returns the index of the original ingredient in the list.
*/

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

/* DuplicateDish checks if a dish struct name is already in the same list.
     
   @param dish is a dish struct array of max size of 50.
   @param dishRow is the current food row in the area.
   @return duplicate returns the index of the original recipe/dish in the list.
*/

int 
DuplicateDish(DishType dish[], 
			  int row)
{
	int i, duplicate = -1;

	for (i=0; i<row && duplicate == -1; i++)
		if (strcmp(dish[row].dishName, dish[i].dishName)==0 && row != i)
			duplicate = i;
			
	return duplicate;
}

/* DisplayFood is a function that displays the list of names of ingredient struct.
     
   @param food is a food struct array of max size 50.
   @param row is the number of current food items in the array.
   @param page is the current "page" being shown from 0-4. 
*/

void 
DisplayFood(IngredientsType food[], 
			int row, 
			int page)
{
	int i;
	
	printf("[----------View Food Calorie----------]\n");
	/* 
	   FOR LOOP LOGIC 
	   i is the starting value of the array.
	   First condition implies that the maximum number of items to display is 10.
	   Second condition implies that the actual number of items to display is n.
	*/
	for (i=page*10; i<10*(page+1) && i < row; i++)
	  	printf("%s %g %s %d\n", food[i].item, food[i].quantity, food[i].unit, food[i].calories);
	printf("\n");
	printf("Page: %d [N] Next Page [P] Previous Page [X] Return to Menu ", page+1);
}

/* toLower is a function that lowers converts a string into lower case characters.
     
   @param string is a variable that stores the result of size string 15.
*/

void 
toLower(String15 string)
{
	int i;

	for (i=0; i<15; i++)
		if (string[i]>='A' && string[i]<='Z')
			string[i] += 32;
}

/* isClassification is a function that checks if inputted value is either a starter, main, 
   or dessert.
     
   @param classification is a string that stores the inputted classification.
   @return 1 if either one of the classifications were entered.
   @return 0 if all of the classifications were not entered.
*/

int
isClassification(String15 classification)
{
	return 	strcmp(classification, "starter") == 0 ||
		   	strcmp(classification, "main") == 0 ||
			strcmp(classification, "dessert") == 0;	
}

/* DeleteStructFood is a function that "deletes" and readjusts the position of all
   food structs of food struct array to the position where the food was deleted.
     
   @param food is a food struct array with max size of 50.
   @param count is the ingredient count under a dish struct.
   @param key is the index of the struct to be deleted.
*/

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

/* DeleteStructDish is a function that "deletes" and readjusts the position of all
   dish structs of dish struct array to the position where the dish was deleted.
     
   @param dish is a dish struct array with a max size of 50.
   @param count is the dish count based on dishRow.
   @param key is the index of the struct to be deleted.
*/

void
DeleteStructDish(DishType dish[],
				 int count,
				 int key)
{
	int i;
	
	for (i=key; i<count-1; i++)
		dish[i] = dish[i+1];	
}

/* DeleteArr is a function that "deletes" and readjusts the position of all
   string of string arrays to the position where the string was deleted.
     
   @param ins is a string with a max size of 70.
   @param count is the dish count based on dishRow.
   @param key is the index of the struct to be deleted.
*/

void
DeleteArr(String70 ins[], 
		  int count, 
		  int key)
{
	int i;
	
	for (i=key-1; i<count-1; i++)
		strcpy(ins[i], ins[i+1]);
}

/* SwapStruct is a that swaps two given structures.
     
   @param dish1 is the dish to be swapped with another dish.
   @param dish2 is the other dish to be swapped with the previous dish.
*/

void 
SwapStruct(DishType *dish1, 
		   DishType *dish2)
{
	DishType temp;
	temp = *dish1;
	*dish1 = *dish2;
	*dish2 = temp;
}

/* SortAlphabetical is a function that rearranges the dishes using the dish name in terms of
   ASCII value.
     
   @param dish is the dish struct array of max size 50.
   @param dishRow is the current number of dishes in the array.
*/

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

/* RecipeTitleExist is a function that checks if recipe exists based on the string parameter 
   passed.
     
   @param dish is the dish struct array of max size 50.
   @param name is the name of the dish.
   @param dishRow is the current number of dishes in the array.
   @return -1 if recipe title does not exist. Otherwise, return index value of the position
   of the existing r
*/

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

/* ViewRecipe is a function that displays the recipe information (e.g., Name, Ingredients).
     
   @param dish is the dish struct of the dish.
*/

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
		printf("		Quantity: %g %s\n", dish.ingredients[i].quantity, dish.ingredients[i].unit);
		printf("		Calories: %d\n", dish.ingredients[i].calories);
	}
	
	printf("Instructions\n");
	for (i=0; i<dish.insCount; i++)
		printf("	%d. %s\n", i+1, dish.instructions[i]);
	printf("\n");
	printf("[N] Next Page [P] Previous Page [X] Return to Menu ");
}

/* ComputeCalories that calculates the total calories in the ingredient list.
     
   @param dish is the dish struct of the dish.
   @return the value of the sum of calories.
*/

int
ComputeCalories(DishType dish)
{
	int i, sum = 0;
	
	for (i=0; i<dish.ingCount; i++)
		sum += dish.ingredients[i].calories;
	
	return sum;
}

/* CheckIngredient checks if ingredient exists using the string passed in the function.
     
   @param dish is the dish struct of the dish.
   @param ingredient is the name of the ingredient.
   @param ingCount is the current count of the number of ingredients.
   @return found, which is 0 if ingredient is not found and 1 if it is found.
*/

int 
CheckIngredient(DishType dish, 
				String20 ingredient, 
				int ingCount)
{
	int i, found = 0;
	
	for (i=0; i<ingCount && !found; i++)
		if (strcmp(dish.ingredients[i].item, ingredient) == 0)
			found = 1;
	
	return found;
}

/* FindRecipeFromStart that incorporates a search algorithm that checks for a dish that has the
   specific ingredient based on the ingredient parameter. The starting index also adjusts based 
   on the provided start paramater.
     
   @param dish is the dish struct array of the dish with max 50 possible items.
   @param ingredient is the name of the ingredient.
   @param start is the starting index where the search will search.
   @param dishRow is the total number of available dishes in the current struct dish array.
   @return key returns the index of which dish in the dish struct array has the ingredient.
   Otherwise, it returns -1 if no dish has been found with given ingredient.
*/

int
FindRecipeFromStart(DishType dish[], 
					String20 ingredient, 
					int start, 
					int row)
{
	int i, key = -1;
	
	for (i=start; i<row && key == -1; i++)
		if (CheckIngredient(dish[i], ingredient, dish[i].ingCount))
			key = i;
		
	return key;
}

/* FindRecipeFromEnd that incorporates a search algorithm that checks for a dish that has the
   specific ingredient based on the ingredient parameter that start from the end or rightmost
   value of the array. The starting index also adjusts based on the provided end paramater.
     
   @param dish is the dish struct array of the dish with max 50 possible items.
   @param ingredient is the name of the ingredient.
   @param end is the current index of the array based on the FindRecipeFromStart.
   @return key returns the index of which dish in the dish struct array has the ingredient.
   Otherwise, it returns -1 if no dish has been found with given ingredient.
*/

int
FindRecipeFromEnd(DishType dish[], 
				  String20 ingredient, 
				  int end)
{
	int i, key = -1;
	
	for (i=end; i>=0 && key == -1; i--)
		if (CheckIngredient(dish[i], ingredient, dish[i].ingCount))
			key = i;
		
	return key;
}

/* SaveIngredients "saves" or writes the current information (e.g., Quantity, Unit, Items) from 
   the ingredient struct array inside of a dish struct into a file.
     
   @param *fp is the file to be written.
   @param dish is the given dish struct.
*/

void 
SaveIngredients(FILE *fp, 
				DishType dish)
{
	int i;
	
	fprintf(fp, "Ingredients %d\n", dish.ingCount);
	for (i=0; i<dish.ingCount; i++)
		fprintf(fp, "%g %s %s\n", dish.ingredients[i].quantity, dish.ingredients[i].unit, dish.ingredients[i].item);
}

/* SaveIngredients "saves" or writes the current infomation from the instructions string array 
   inside of a dish struct into a file.
     
   @param *fp is the file to be written.
   @param dish is the given dish struct.
*/

void
SaveSteps(FILE *fp, 
		  DishType dish)
{
	int i;
	
	fprintf(fp, "Steps %d\n", dish.insCount);
	for (i=0; i<dish.insCount; i++)
		fprintf(fp, "%s\n", dish.instructions[i]);
}

int 
FindCalorie(DishType dish, 
			IngredientsType food[],
			int row)
{
	int i, j, found = -1;
	
	for (i=0; i<dish.ingCount && found == -1; i++)	
		for (j=0; j<row && found == -1; j++)
			if (dish.ingredients[i].item == food[j].item)
				found = dish.ingredients[i].calories; 
	
	if (found == -1)
		return 0;
	else
		return found;
}

/* SaveIngredients "saves" or writes the current infomation from the instructions string array 
   inside of a dish struct into a file.
     
   @param *fp is the file to be written.
   @param dish is the given dish struct.
   @param foodRow is the current row/count of the food struct array.
*/

void
ReadIngredients(FILE *fp, 
				DishType *dish,
				IngredientsType food[],
				int row)
{
	int i; 
	
	for (i=0; i<dish->ingCount; i++)
	{
		fscanf(fp, "%f%s ", &dish->ingredients[i].quantity,
							 dish->ingredients[i].unit);
		getFileString20(dish->ingredients[i].item, fp);
		
		dish->ingredients[i].calories = FindCalorie(*dish, food, row);
	}
}
		
void
ReadSteps(FILE *fp, 
		  DishType *dish)
{                                 
	int i; 
	
	for (i=0; i<dish->insCount; i++)
		getFileString70(dish->instructions[i], fp);
}
