#include <stdio.h>
#include <stdlib.h> // For malloc() function
#include <string.h> // For strlen() function

//Vector Initialization
typedef struct{
    int size;
    int capacity;
    char *stringInput;
}Vector;

//FUNCTION PROTOTYPES

//[1] VECTOR FUNCTIONS
void initVector(Vector*);  //Initializes the Vector
void resize(Vector*, int); // Resizes the Vector when needed
void insertCharacter(Vector*, int, char);
char getCharacter(Vector*,int);

//[2] REQUIRED FUNCTIONS
void initString(Vector* , char*); //Function that accepts the string and inserts all the characters in the vector
void concatenate(Vector*, Vector*, Vector*); //Function that links 2 strings and put it in an empty vector
void slice(Vector*, Vector*, int, int); //Function that takes prints the characters from int to int-1

int main()
{
    Vector one,two,three;
    int n,integer1,integer2;
    char string1[15],string2[15];

    do{
        scanf("%i",&n);
    }while(n < 1 || n > 2);

    switch(n)
    {
        //[1] Concatenate
        case 1:
        //Asks for the first string input
        scanf("%s",string1);

        //Checks if the string has a maximum characters of 15    
        if(strlen(string1) <= 15)
            initString(&one,string1);
        else
            break; //If not, the program stops

        //Asks for the second string input
        scanf("%s",string2);

        //Checks the string length (again)
        if(strlen(string2) <= 15)
            initString(&two,string2);
        else
            break;

        //Concatenating the two strings
        concatenate(&three,&one,&two);

        //Printing the Strings
        for(int i = 0; i < three.size; i++)
            printf("%c",getCharacter(&three,i));
        break;

        //[2] Slice
        case 2:
        //Asks for the First String
        scanf("%s",string1);
        initString(&one,string1);

        //Asks for the Two Start and End Integers
        scanf("%i",&integer1);
        scanf("%i",&integer2);

        //Performs the Slicing
        slice(&three,&one,integer1,integer2);

        //Printing the Vector
        for(int i = 0; i < three.size; i++)
            printf("%c",getCharacter(&three,i));
        break;

    }
    return 0;
}

// [1] Vector Functions

void initVector(Vector* myVector){
    //Initializing the Vector
    myVector->size = 0;
    myVector->capacity = 10; // Reasonable size of capacity 
    myVector->stringInput = (char*) malloc(sizeof(char) * myVector->capacity);
}

void resize(Vector* resizeVector, int size){
    int newSize = size * 2; //Multiplies the original size by 2
    //Borrows a Memory from the heap with size*2
    char* newVector = (char*) malloc(sizeof(char)*newSize);

    //Loop that transfers the characters to the new array
    for(int i = 0; i < resizeVector->size; i++)
        newVector[i] = resizeVector->stringInput[i];
 
    //Changing the Values of the Vector
    resizeVector->capacity = newSize;
    free(resizeVector->stringInput); //Letting go the initial borrowed memory from the heap
    resizeVector->stringInput = newVector;

}

void insertCharacter(Vector* myVector, int vectorIndex, char character){
    int size = myVector->capacity;
    if(vectorIndex >= 0 && vectorIndex <= myVector->size){
        if(myVector->size == myVector->capacity)
            resize(myVector,size);

        for(int i = myVector->size; i > vectorIndex; i--)
            myVector->stringInput[i] = myVector->stringInput[i-1];
    }
    myVector->stringInput[vectorIndex] = character;
    myVector->size++;
}

char getCharacter(Vector* myVector, int vectorIndex){
    if((vectorIndex >= 0) && (vectorIndex <= myVector->size - 1))
        return myVector->stringInput[vectorIndex];
}

//[2] REQUIRED FUNCTIONS

void initString(Vector* myVector, char* string){

    //Using initVector function to initialize the inputted Vector
    initVector(myVector); 

    int stringSize = strlen(string);

    //Resizing the caapcity of myVector in case the stringSize is greater than it
    if(stringSize > myVector->capacity)
        resize(myVector,stringSize);
    
    //Loop that inserts all the inputted characters in a string
    //Using the Set Character Function to Initialize the Vector
    for(int i = 0; i < stringSize; i++)
        insertCharacter(myVector,i,string[i]);
}

void concatenate(Vector* combined, Vector* a, Vector* b){

    //Initializing the Combined Vector
    initVector(combined);

    while(combined->capacity < (a->size + b-> size))
        resize(combined, a->size + b->size);
    
    //Puts the characters in Vector A to the Combined Vector
    for(int i = 0; i < a ->size; i++)
        insertCharacter(combined,i,a->stringInput[i]);
        

    for(int i = a->size, j = 0; i < (a->size+b->size); i++,j++)
        insertCharacter(combined,i,b->stringInput[j]);
      
}

void slice(Vector* sliced, Vector* source, int start, int end){
    initVector(sliced);

    //Iterates until the capacity is greater than end - start (the size that the sliced vector should have)
    while(sliced->capacity < end - start)
        resize(sliced,end-start);
    
    //Loop that Puts the Characters of the source vector in sliced vector
    for(int i = start, j = 0; i < end; i++,j++)
        insertCharacter(sliced,j,source->stringInput[i]);
}
