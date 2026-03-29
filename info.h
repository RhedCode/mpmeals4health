/*
  funcInput provides a reusable scanf for "pausing" the program
  unless the user inputs a value.
*/
#include <stdio.h>
#include <string.h>

#define SIZE 50
#define SIZE_ING 20
#define SIZE_INS 15

typedef char String70[71];
typedef char String20[21];
typedef char String15[16];

struct IngredientsTag
{
	String20 item;
  	float quantity;
  	String15 unit;
  	int calories;
};
typedef struct IngredientsTag IngredientsType;

struct DishTag
{
	String20 dishName;
  	String15 classification; //starter, main, or dessert
  	int serving;
	IngredientsType ingredients[SIZE_ING];
	String70 instructions[SIZE_INS];
  	int ingCount;
  	int insCount;
};
typedef struct DishTag DishType;

/**************************** HELPER FUNCTIONS *****************************/
/* Recipe Helpers */
int DuplicateFood(IngredientsType food[], int row);
int DuplicateDish(DishType dish[], int row);
void DisplayFood(IngredientsType food[], int row, int page);

void SortAlphabetical(DishType dish[], int row);
void DeleteArr(String70 ins[], int count, int key);
void DeleteStructFood(IngredientsType food[], int count, int key);
void DeleteStructDish(DishType dish[], int count, int key);
void SwapStruct(DishType *dish1, DishType *dish2);

int CheckIngredient(DishType dish, String20 ingredient, int ingCount);
int ComputeCalories(DishType dish);
int FindCalorie(String20 foodItem, IngredientsType food[], int row);
int FindRecipeFromStart(DishType dish[], String20 ingredient, int start, int row);
int FindRecipeFromEnd(DishType dish[], String20 ingredient, int end);

void ViewRecipe(DishType dish);
int RecipeTitleExists(DishType dish[], String20 name, int row);

/* Save and Load System */
void SaveIngredients(FILE *fp, DishType dish);
void SaveSteps(FILE *fp, DishType dish);

/* Input Handlers */
void getString70(String70 string);
void getString20(String20 string);
void getFileString70(String70 string, FILE *fp);
int getFileString20(String20 string, FILE *fp);
int nextLine();
void toLower(String15 string);
void myIntInput(int *dest);
void myCharInput(char *dest);
void myFloatInput(float *dest);
void ReadIngredients(FILE *fp, DishType *dish, IngredientsType food[], int row);
void ReadBuffIngredients(FILE *fp, int count);
void ReadSteps(FILE *fp, DishType *dish);
void ReadBuffSteps(FILE *fp, int count);

/* Admin Page */
void loadAccount(String20 username, String20 password);
int loginPage(String20 username, String20 password);
void ChangePassword(String20 username, String20 password);
int isClassification(String15 classification);

/**************************** END OF HELPER FUNCTIONS *****************************/

/**************************** MAIN FUNCTIONS *****************************/
void AddFoodCalorie(IngredientsType food[], int *row);
void ViewFood(IngredientsType food[], int row);
void SaveCalorie(IngredientsType food[], int row);
void LoadCalories(IngredientsType food[], int *row);
void AddRecipe(DishType dish[], IngredientsType food[], int *foodRow, int *dishRow);
void AddIngredient(DishType *dish, IngredientsType food[], int foodRow);
void AddStep(DishType *dish);
void DeleteIngredient(IngredientsType food[], int *count);
void DeleteStep(DishType *dish);
void DeleteRecipes(DishType dish[], int *row);
void ModifyRecipe(DishType dish[], IngredientsType food[], int foodRow, int dishRow);
void ListRecipeTitles(DishType dish[], int row);
void SearchRecipeTitle(DishType dish[], int row);
void ScanRecipes(DishType dish[], int row, int sort);
void ScanRecipesByIngredient(DishType dish[], int row);
void GenerateShoppingList(DishType dish[], int row);
void RecommendedMenu(DishType dish[], int row);
void ExportRecipes(DishType dish[], int row);
void ImportRecipes(DishType dish[], IngredientsType food[], int *dishRow, int foodRow);

int 
Menu(DishType dish[], 
	 IngredientsType food[], 
	 int *dishRow, 
	 int *foodRow, 
	 String20 username,
	 String20 password,
	 int *status);
	 
void
Update(DishType dish[], 
	   IngredientsType food[], 
	   int *dishRow, 
	   int *foodRow, 
	   String20 username,
	   String20 password,
	   int *status);
	   
void
Access(DishType dish[], 
	   IngredientsType food[], 
	   int *dishRow, 
	   int foodRow);
	   
/**************************** END OF MAIN FUNCTIONS *****************************/