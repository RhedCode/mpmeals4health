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


int
main()
{
    int foodPage = 0;
    int foodRow = 0;
    int dishRow = 0;
      
    IngredientsType food[50];
    DishType dish[50];
    
    //ViewFood(food, &foodRow, &foodPage);
    ImportRecipes(dish, &dishRow);
    ModifyRecipe(dish, food, foodRow, dishRow);
    SearchRecipeTitle(dish, dishRow);
    ScanRecipes(dish, dishRow);
	ExportRecipes(dish, &dishRow);
      /*
      while (loop)
      {

      }
      */
      
    return 0;
}
