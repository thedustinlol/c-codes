#include <stdio.h>
#define MAX 20

//FUNCTION PROTOTYPE
int divide(int,int);
int gcd(int,int);
int relativePrime(int,int); //Non-Recursive
void receiveInput(int array[],int); //Non-Recursive
int isSorted(int array[], int); //Non-Recursive
int binarySearch(int array[], int,int,int);

//Globally-Declared Variables
int n,num1,num2,n2,arr[MAX],n3;

int main()
{
     do{
        scanf("%i",&n);
    }while(n>3 || n<1);

    switch(n)
        {
            case 1:
            scanf("%i %i",&num1,&num2);
            printf("%i ", divide(num1,num2));
            break;

            case 2:
            scanf("%i %i",&num1,&num2);
            printf("%i",relativePrime(num1,num2));
            break;

            case 3:
            do{
                scanf("%i",&n2);
            }while(n2<2 || n2 > 20);
            receiveInput(arr,n2);
            scanf("%i",&n3);
            while(isSorted(arr,n2) == 0){
                printf("Array Not Sorted. Please try again.\n");
                receiveInput(arr,n2);
            }
            printf("%i",binarySearch(arr,0,n2-1,n3));
            break;
        }
    return 0;
}

int divide(int dividend, int divisor){
    if(dividend < divisor)
        return 0;
    else
        return 1 + divide(dividend-divisor,divisor);
}

int gcd(int num1, int num2){
   //Euclidean Algortihm(gets the gcd)
  if(num2 == 0)
        return num1;
  if(num1 < num2)
        return gcd(num2,num1);

  return gcd(num2,num1%num2);
}

int relativePrime(int num1, int num2){
    //Non-Recursive
    //Function that helps my gcd function return 1 or 0
    if(gcd(num1,num2) == 1)
        return 1;
    else
        return 0;
}

void receiveInput(int array[],int size){
    for(int i = 0; i<size; i++)
        scanf("%i",&array[i]);   
}

int isSorted(int array[], int size){

    for(int i = 0; i<size-1; i++){
        if(array[i] > array[i+1])
            return 0;
    }
    return 1;
}

int binarySearch(int array[], int minimum,int maximum,int numFound){
    int middle = (minimum + maximum)/2;

    if(minimum > maximum)
        return 0;
    else if(array[middle] == numFound)
        return 1;
    else if(array[middle] < numFound)
        return binarySearch(array,middle + 1,maximum,numFound);
    else if(array[middle] > numFound)
        return binarySearch(array,minimum,middle-1,numFound);

}
