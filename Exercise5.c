#include <stdio.h>

int main()
{
    int n,tempSwap;
    int *ptrN = &n;

    //User Inputs the maximum number of arrays to input
    do{
        scanf("%i",ptrN);
    }while(*ptrN<1);
    
    int array[n]; //Declaring an array: The only time that the use of [] is allowed

    // User Inputs n number of arrays
    for(int i = 0; i < n; i++)
        scanf("%i",&*(array+i));

    //For Sorting, I decided to use Bubble Sort
    for(int i = 0; i < n-1; i++){ 
        for(int j = 0; j < n - i - 1; j++){ // This loop represents the number of swaps it will take per batch
            if(*(array+j) > *(array+j+1)){
                tempSwap = *(array+j);  //Used temp variable for swapping the two arrays
                *(array+j) = *(array+j+1);
                *(array+j+1) = tempSwap;
            }
        } 
    }
    //Print Sorted Array
    for(int i = 0; i < n; i++){
        printf("%i ", *(array+i));
    }

    return 0;    
}
