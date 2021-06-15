#include <iostream>
#include <string>
using namespace std;

class Fraction{

    private:
    int numerator;
    int denominator;

    public:

    // Constructor and Mutator
    
    Fraction(int nume, int deno){
        this->numerator = nume;
        this->denominator = deno;
    }

    // Accessors (since the numerator and denominator are private)
    int getNumerator(){
        return this->numerator;
    }

    int getDenominator(){
        return this->denominator;
    }

    Fraction addTwoFractions(Fraction toAdd){
        int answerNumerator, answerDenominator;

        // Denominators are equal
        if(toAdd.denominator == this->denominator){
            answerNumerator = this->numerator + toAdd.numerator;
            answerDenominator = this->denominator;
        }
        else{
            answerNumerator = (this->numerator * toAdd.denominator) + (this->denominator * toAdd.numerator);
            answerDenominator = this->denominator * toAdd.denominator;
        }   
        // Simplify fraction
        Fraction answer(answerNumerator,answerDenominator);
        answer = answer.simplify();

        return answer;
    }

    Fraction subtractTwoFractions(Fraction toSubtract){
        int answerNumerator, answerDenominator;

        // Denominators are equal
        if(toSubtract.denominator == this->denominator){
            answerNumerator = this->numerator - toSubtract.numerator;
            answerDenominator = this->denominator;
        }
        else{
            answerNumerator = (this->numerator * toSubtract.denominator) - (this->denominator * toSubtract.numerator);
            answerDenominator = this->denominator * toSubtract.denominator;
        }   
        // Simplify fraction
        Fraction answer(answerNumerator,answerDenominator);
        answer = answer.simplify();

        return answer;
    }

    Fraction multiplyTwoFractions(Fraction toMultiply){
        int answerNumerator, answerDenominator;

        answerNumerator = this->numerator * toMultiply.numerator;
        answerDenominator = this->denominator * toMultiply.denominator;

        // Simplify Fraction
        Fraction answer(answerNumerator,answerDenominator);
        answer = answer.simplify();

        return answer;
    }

    Fraction divideTwoFractions(Fraction toDivide){
        int answerNumerator, answerDenominator;

        answerNumerator = this->numerator * toDivide.denominator;
        answerDenominator = this->denominator * toDivide.numerator;

        // Simplify Fraction
        Fraction answer(answerNumerator,answerDenominator);
        answer = answer.simplify();

        return answer;
    }

    Fraction simplify(){
        // Euclidean Algorithm
        int num1 = this->numerator, num2 = this->denominator;
        int remainder;

        while(num1 % num2 > 0){
            remainder = num1 % num2;
            num1 = num2;
            num2 = remainder; // GCD
        }

        int answerNumerator, answerDenominator;
        answerNumerator = this->numerator / num2;
        answerDenominator = this->denominator / num2;
        
        Fraction answer(answerNumerator,answerDenominator);
        return answer;
    }

    Fraction FractionInput(){
        int numerator, denominator;
        char hyphen;
        

        cin >> numerator;
        scanf("%c",&hyphen);
        
        if(hyphen == '/')
            cin >> denominator;
        else
            denominator = 1;

        Fraction answer(numerator,denominator);
        return answer;
    }

};

int main(){
    int input;
    
    do{
        cin >> input; 
    }while(input > 5 || input < 1);

    int numerator[2] = {0,0}, denominator[2] = {0,0};
    char slash;

    // Declaring the fractions
    Fraction one(numerator[0],denominator[0]);
    Fraction two(numerator[1],denominator[1]);
    Fraction answer(0,0);
    
    if(input == 1) // Add two fractions   
    { 
        // Fraction Input
        one = one.FractionInput();
        two = two.FractionInput();

        answer = one.addTwoFractions(two);

        // Prints the sum of two numbers
        if(answer.getDenominator() != answer.getNumerator())
            cout << answer.getNumerator() << '/' << answer.getDenominator() << endl; 
        else if(answer.getDenominator() == answer.getNumerator())
            cout << answer.getNumerator() << endl;
      
    }

    else if(input == 2)
    {
        // Fraction Input
        one = one.FractionInput();
        two = two.FractionInput();

        answer = one.subtractTwoFractions(two);

        // Prints the difference of the two numbers
        if(answer.getDenominator() != answer.getNumerator())
            cout << answer.getNumerator() << '/' << answer.getDenominator() << endl; 
        else if(answer.getDenominator() == answer.getNumerator())
            cout << answer.getNumerator() << endl;
        

    }
    else if(input == 3)
    {
        // Fraction Input
        one = one.FractionInput();
        two = two.FractionInput();

        answer = one.multiplyTwoFractions(two);
    

        // Prints the product of the two numbers
        if(answer.getDenominator() != answer.getNumerator())
            cout << answer.getNumerator() << '/' << answer.getDenominator() << endl; 
        else if (answer.getDenominator() == answer.getNumerator())
            cout << answer.getNumerator() << endl;
        
    }
    else if(input == 4)
    {
        // Fraction Input
        one = one.FractionInput();
        two = two.FractionInput();

        answer = one.divideTwoFractions(two);

        // Prints the quotient of the two numbers
        if(answer.getDenominator() != answer.getNumerator())
            cout << answer.getNumerator() << '/' << answer.getDenominator() << endl; 
        else if (answer.getDenominator() == answer.getNumerator())
            cout << answer.getNumerator() << endl;
        
    }
    else if(input == 5)
    {
        one = one.FractionInput();

        answer = one.simplify();

        // Prints the lowest term of the two numbers
        if(answer.getDenominator() != answer.getNumerator())
            cout << answer.getNumerator() << '/' << answer.getDenominator() << endl; 
        else if (answer.getDenominator() == answer.getNumerator())
            cout << answer.getNumerator() << endl;
        
    }

}
