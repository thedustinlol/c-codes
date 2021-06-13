#include <stdio.h>

int main()
{   
    int rows,columns,label = 1;

    //User Input
    scanf("%i",&rows);
    scanf("%i",&columns);
    //Stores the Maximum Number of Rows and Columns in the 2-d Array
    int grid[rows][columns]; 
    

    //Grid Input
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            scanf("%i",&grid[i][j]);
        }
    }

    //Checks Neighbors and gives them new label
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            //Condition 1: When the Loop is in the First Column while it's not in the first row
            if(j == 0 && i != 0){ 
                if(grid[i][j] == 1 && (grid[i-1][j] == 0 && grid[i-1][j+1] == 0)) // Checks if the two arrays (8-connectivity) is 0
                    if(grid[i][j+1] != 0) // Also checks if the next pixel is not 0
                        continue;
                    else  // If it's not 0, then we'll add a new label
                        grid[i][j] = label++;
            }
            //Condition 2: The Loop is Currently in the first Row
            else if(i == 0){
                if(grid[i][j] == 1 && j == 0) // If the loop is in grid[0][0]
                    grid[i][j] = label++;
                else if(grid[i][j] == 1 && grid[i][j-1] == 0){ //If it's not in grid[0][0], it checks the previous pixel if it's 0
                    if(grid[i+1][j-1] == 0 && grid[i+1][j] == 0 && grid[i+1][j+1] == 0) // Another condition that checks if the 3 pixels below them is 0 (8-connectivity)
                        grid[i][j] = label++;
                }
                else if(grid[i][j] == 1 && grid[i][j-1] == 1){ //If the present pixel and the previous pixel is 1, 
                        grid[i][j] = grid[i][j-1];             //then the label of the present pixel = label of the previous pixel
                        label = grid[i][j] + 1; 
                }
                        
            }//Condition 3: The Pixel is in the middle (Normal Scanning)
            //If the current Pixel is equal to 1, it checks its four neighbors(left,2 diagonals up, and top)
            else if((grid[i][j] == 1 && (grid[i][j-1] == 0 && grid[i-1][j-1] == 0
               && grid[i-1][j] == 0 && grid[i-1][j+1] == 0)))
                    grid[i][j] = label++;
            //Condition 4: The Pixel is in the last column
            // It checks its 3 neighbors(left, left diagonal up, top)
            else if(j == columns-1){
                if(grid[i][j] == 1 && grid[i][j-1] == 0 && grid[i-1][j-1] == 0 && grid[i-1][j] == 0)
                    grid[i][j] = label++;
            }
        }
            
    }   

    //Finding the Maximum in the Grid as it symbolizes the number of objects in a pixel
    int max = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if (max < grid[i][j])
                max = grid[i][j];
        }
    }
    printf("%i",max);  //Prints the Maximum
    return 0;
}
