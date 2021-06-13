#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int nume, deno;
}Fraction;


//FUNCTION PROTOTYPES
Fraction* fractionInput(Fraction*);
void displayFraction(Fraction*);
int gcd(Fraction*);
Fraction* addFraction(Fraction*,Fraction*);
Fraction* subFraction(Fraction*,Fraction*);
Fraction* mulFraction(Fraction*,Fraction*);
Fraction* divFraction(Fraction*,Fraction*);

int main(){

    int choice,gcdValue;
    Fraction *fraction1, f1; 
    Fraction *fraction2, f2;
    Fraction* answer, a;

    //Address Assigning
    fraction1 = &f1;
    fraction2 = &f2;
    answer = &a;


    //Asking for choice input
    do{
        scanf("%i",&choice);
    }while (choice > 5 || choice < 1);

    switch(choice)
    {
        // [1] Prints out the result of A + B
        case 1:
        fraction1 = fractionInput(fraction1);
        fraction2 = fractionInput(fraction2);
        answer = addFraction(fraction1,fraction2);
        
        displayFraction(answer);
        free(fraction1);
        free(fraction2);

        break;

        // [2] Prints out the result of A - B
        case 2:
        fraction1 = fractionInput(fraction1);
        fraction2 = fractionInput(fraction2);
        answer = subFraction(fraction1,fraction2);
        
        displayFraction(answer);
        free(fraction1);
        free(fraction2);
        
        break;

        // [3] Prints out the result of A * B
        case 3:
        fraction1 = fractionInput(fraction1);
        fraction2 = fractionInput(fraction2);
        answer = mulFraction(fraction1,fraction2);

        displayFraction(answer);
        free(fraction1);
        free(fraction2);

        break;
        
        // [4] Prints out the result of A / B
        case 4:
        fraction1 = fractionInput(fraction1);
        fraction2 = fractionInput(fraction2);
        answer = divFraction(fraction1,fraction2);

        displayFraction(answer);
        free(fraction1);
        free(fraction2);

        break;

        // [5] Prints out the simplified fraction of A
        case 5:
        fraction1 = fractionInput(fraction1);
        gcdValue = gcd(fraction1);
        
        fraction1->nume /= gcdValue;
        fraction1->deno /= gcdValue;

        displayFraction(fraction1);
        free(fraction1);

        break;
    }

    return 0;
}

Fraction* fractionInput(Fraction* inputFraction){
    //This function will ask the user to input a fraction with '/'

    //Dynamic Memory Allocation for the Inputted Fraction
    inputFraction = (Fraction*) malloc(sizeof(Fraction));
    char slotForSlash;

    //Asks for the numerator and a slash
    scanf("%i",&inputFraction->nume);
    scanf("%c",&slotForSlash); 

    // If the user enters a slash, it means that they will input a denominator for that
    if(slotForSlash == '/') 
        scanf("%i",&inputFraction->deno);
        
    //If its not a slash, then we can say that the denominator is 1
    else
        inputFraction->deno = 1;

    return inputFraction;
    
}

void displayFraction(Fraction* answer){
    //This function displays the Fraction with '/'

    //If the denominator is 1, then we don't need to print it. 
    if(answer->deno == 1) 
        printf("%i\n",answer->nume);

    //If it's not, then we will print both the numerator and the denominator
    else
        printf("%i/%i\n",answer->nume,answer->deno);

}

int gcd(Fraction* fracSimplify){
    //Euclidean Algorithm
    int num1 = fracSimplify->nume, num2 = fracSimplify->deno;
    int remainder;

    while(num1%num2 > 0){
        remainder = num1%num2;
        num1 = num2;
        num2 = remainder;
    }
    return num2; //Returns the GCD
}


Fraction* addFraction(Fraction* firstFraction, Fraction* secondFraction){
    //This function will add both fractions
    Fraction* sumFraction, s;
    sumFraction = &s;
    int simplify;

    /* If both Fraction1's and Fraction2's denominator != to each other, then
        we'll add in a normal fashion */
    if(firstFraction->deno != secondFraction->deno){
        sumFraction->nume = (firstFraction->nume * secondFraction->deno) +
                           (secondFraction->nume * firstFraction->deno);
        sumFraction->deno = (firstFraction->deno * secondFraction->deno);
    }

    //If both denominators are equal, then we'll just add the numerator and the denominator is still the same.
    else{
        sumFraction->nume = (firstFraction->nume + secondFraction->nume);
        sumFraction->deno = firstFraction->deno;
    }

    //Simplifying the Fraction
        simplify = gcd(sumFraction);
        sumFraction->nume /= simplify;
        sumFraction->deno /= simplify;

    return sumFraction;    
}

Fraction* subFraction(Fraction* firstFraction, Fraction* secondFraction){
    //This function will subtract both fractions
    Fraction* diffFraction, sub;
    diffFraction = &sub;
    int simplify;

    /* If both Fraction1's and Fraction2's denominator != to each other, then
        we'll subtract in a normal fashion */
    if(firstFraction->deno != secondFraction->deno){
        diffFraction->nume = (firstFraction->nume * secondFraction->deno) -
                           (secondFraction->nume * firstFraction->deno);
        diffFraction->deno = (firstFraction->deno * secondFraction->deno);
    }

    //If both denominators are equal, then we'll just subtract the numerator and the denominator is still the same.
    else{
        diffFraction->nume = (firstFraction->nume - secondFraction->nume);
        diffFraction->deno = firstFraction->deno;
    }

    //Simplifying the Fraction
        simplify = gcd(diffFraction);
        diffFraction->nume /= simplify;
        diffFraction->deno /= simplify;

    return diffFraction;    
}

Fraction* mulFraction(Fraction* firstFraction, Fraction* secondFraction){
    Fraction* multFraction, prod;
    multFraction = &prod;
    int simplify;

    //Multiplying the two fractions in a normal fashion
    multFraction->nume = firstFraction->nume * secondFraction->nume;
    multFraction->deno = firstFraction->deno * secondFraction->deno;

    //Simplifying the Fraction
    simplify = gcd(multFraction);
    multFraction->nume /= simplify;
    multFraction->deno /= simplify;

    return multFraction;
}

Fraction* divFraction(Fraction* firstFraction, Fraction* secondFraction){
    Fraction* divFraction,quot;
    divFraction = &quot;
    int simplify;

    //Multiplying the with the Reciprocal
    if(secondFraction->nume != 0){
        divFraction->nume = firstFraction->nume * secondFraction->deno;
        divFraction->deno = secondFraction->nume * firstFraction->deno;
    }

    //Simplifying the Fraction
    simplify = gcd(divFraction);
    divFraction->nume /= simplify;
    
