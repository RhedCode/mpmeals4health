/*
  funcInput provides a reusable scanf for "pausing" the program
  unless the user inputs a value.
*/
#include <stdio.h>
#include <string.h>

#define ROWS 50
#define COLUMN 4

typedef char String70[71];
typedef char String20[21];
typedef char String15[16];

struct IngredientsTag
{
	String20 item;
  	int quantity;
  	String15 unit;
  	int calories;
};
typedef struct IngredientsTag IngredientsType;

struct DishTag
{
	String20 dishName;
  	String15 classification; //starter, main, or dessert
  	int serving;
	IngredientsType ingredients[20];
	String70 instructions[15];
  	int ingCount;
  	int insCount;
};
typedef struct DishTag DishType;

//Helper Functions
void DeleteStructFood(IngredientsType food[], int count, int key);
void DeleteStructDish(DishType dish[], int count, int key);

int ComputeCalories(DishType dish);
void SwapStruct(DishType * dish1, DishType * dish2);
void SortAlphabetical(DishType dish[], int row);
void ViewRecipe(DishType dish);
int RecipeTitleExists(DishType dish[], String20 name, int row);

void getString70(String70 string);
void getString20(String20 string);
void toLower(String15 string);
int nextLine();
void myIntInput(int *dest);
void myCharInput(char *dest);
int isUniqueFood(IngredientsType food[], int row);
int isUniqueDish(DishType dish[], int row);
int isClassification(String15 classification);

//Main Functions
void AddFoodCalorie(IngredientsType food[], int *row);
void ViewFood(IngredientsType food[], int *row, int *page);
void SaveCalorie(IngredientsType food[], int *row);
void AddRecipe(DishType dish[], IngredientsType food[], int *foodRow, int *dishRow);
void AddIngredient(DishType *dish, IngredientsType food[], int foodRow);
void DeleteIngredient(IngredientsType food[], int *count);
void AddStep(DishType *dish);
void ModifyRecipe(DishType dish[], IngredientsType food[], int foodRow, int recipeRow);
void ListRecipeTitles(DishType dish[], int row);
void SearchRecipeTitle(DishType dish[], int row);

void Update();
void Access();