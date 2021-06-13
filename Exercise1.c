#include <stdio.h>

//NOTE: Outputs the Day of the Given date from year 1400 to the year 2599 only


//FUNCTION PROTOTYPES
void userInput();
int isLeapYear(int);
void numDays(int);
int checkMonthDayYear(int,int,int);
void monthChart(int);
void centuryChart(int);
int extractYearDigit(int,int);
void calculateDay(int,int,int,int);
void weekChart(int);

//Globally-Declared Variables
int year,month,day,monthValue,yearValue,lastTwoDigits = 0,dayCalculate,weekValue,finalValue;
int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; 

int main()
{
    userInput();
    isLeapYear(year);

    while(checkMonthDayYear(month,day,year) == 0){
        printf("Invalid Month/Day Input\n");
        userInput();
    }

    //Gets The Values for Computation
    monthChart(month);
    centuryChart(year);
    int num = extractYearDigit(year,2);
 
    //Computes the Day
    calculateDay(day,monthValue,yearValue,num);
    weekChart(finalValue);
    numDays(day);
    
}

void userInput(){
    scanf("%i %i %i", &year, &month, &day);
}

int isLeapYear(int year){
    if(year % 4 == 0 || (year % 100 != 0 && year % 400 == 0)){
        monthDays[1] = 29;
        return 1;
    }
    else
        return 0;
}

void numDays(int days){
    int answer = days;
    for(int i = 0; i<month-1; i++)
        answer += monthDays[i];
    if(extractYearDigit(answer,1) == 1)
        printf(" %ist day of the year\n",answer);
    else if(extractYearDigit(answer,1) == 2)
        printf(" %ind day of the year\n",answer);
    else if(extractYearDigit(answer,1) == 3)
        printf(" %ird day of the year\n",answer);
    else 
        printf(" %ith day of the year\n",answer);
}

int checkMonthDayYear(int month, int day, int year){
    if((month > 12 || month < 1) || (day > monthDays[month-1] || day < 1) || (year < 1400))
        return 0;
    else
        return 1;
}

void monthChart(int month){
    if(month == 1 || month == 10)
        monthValue = 0;
    else if(month == 2 || month == 3 || month == 11)
        monthValue =  3;
    else if(month == 4 || month == 7)
        monthValue =  6; 
    else if(month == 5)
        monthValue =  1;
    else if(month == 6)
        monthValue = 4;
    else if(month == 9 || month == 12)
        monthValue = 5;
}

void centuryChart(int year){
    if((year >= 1400 && year < 1500) || (year >= 1800 && year < 1900) || (year >= 2200 && year < 2300))
        yearValue = 2;
    else if((year >= 1500 && year < 1600) || (year >= 1900 && year < 2000) || (year >= 2300 && year < 2400))
        yearValue = 0;
    else if((year >= 1600 && year < 1700) || (year >= 2000 && year < 2100) || (year >= 2400 && year < 2500))
        yearValue = 6;
    else if((year >= 1700 && year < 1800) || (year >= 2100 && year < 2200) || (year >= 2500 && year < 2600))
        yearValue = 4;
} 

int extractYearDigit(int year, int n){
    int ten = 1,divide,remainder,lastTwoDigits = 0;
    for(int i = 0; i<n; i++){
        remainder = year % 10;
        lastTwoDigits = lastTwoDigits + (ten*remainder); //Value
        ten *= 10;
        divide = year/10;
        year = divide;
    }
    return lastTwoDigits;
}

void calculateDay(int day, int monthValue, int yearValue, int lastTwoDigits){
    dayCalculate = day + monthValue + yearValue + lastTwoDigits + (lastTwoDigits/4);
    finalValue = dayCalculate % 7;
}

void weekChart(int finalValue){
    switch(finalValue)
    {
        case 0:
        printf("Sunday,");
        break;
        
        case 1:
        printf("Monday,");
        break;

        case 2:
        printf("Tuesday,");
        break;

        case 3:
        printf("Wednesday,");
        break;

        case 4:
        printf("Thursday,");
        break;

        case 5:
        printf("Friday,");
        break;

        case 6:
        printf("Saturday,");
        break;
    }
}



