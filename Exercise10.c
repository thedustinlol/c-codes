#include <stdio.h>

struct Birthday{
    int day;
    int month;
    int year;
}; typedef struct Birthday Birthday; 

// FUNCTION PROTOTYPES
int getZodiacSign(Birthday bday);

int main()
{
    FILE *fp = fopen("data.for","r"); // Read
    FILE *fp2nd = fopen("data.in","a+"); // Append Extended
    char ZodiacSigns[12][15] = {"Aquarius", "Pisces", "Aries", "Taurus", "Gemini", "Cancer", "Leo",
                                "Virgo", "Libra", "Scorpio", "Sagittarius", "Capricorn"};
    Birthday userBirthday,temp;
    int personZodiacSign,countSameZodiac = 0 ,countNewLine = 0;
    char read;

    // Condition to check if the opening of files succeeded or not
    if(!(fp) || !(fp2nd)){ 
        printf("There is an error in opening the file(s).\n");
        return -1;
    }
    
    // User Input + Checking its input validity
    do{
        scanf("%d",&userBirthday.year);
    }while(userBirthday.year < 1);

    do{
        scanf("%d",&userBirthday.month);
    }while(userBirthday.month < 1 || userBirthday.month > 12);

    do{
        scanf("%d",&userBirthday.day);
    }while(userBirthday.day < 1 || userBirthday.day > 31);
  

    // Gets the Zodiac Sign and Prints it
    personZodiacSign = getZodiacSign(userBirthday); 
    printf("%s: ",ZodiacSigns[personZodiacSign]);

    
    // Reads the Data from the second file until its end of file marker
    // This will check how many total birthdays have the same zodiac sign
    while(fscanf(fp2nd,"%d-%d-%d",&temp.year,&temp.month,&temp.day) != EOF)
    {
        if(getZodiacSign(temp) == personZodiacSign) 
            countSameZodiac++; // Increments every time the scanned birthday from the file has the same zodiac sign
        if(countSameZodiac == 5) // Since there are only 5 fortunes per Zodiac Sign, the program will return to the starting index of the zodiac sign   
            countSameZodiac = 0;
    }

    // Prints the inputted data in the second file
    if(userBirthday.month < 10 && userBirthday.day < 10)
        fprintf(fp2nd,"%d-0%d-0%d\n", userBirthday.year,userBirthday.month,userBirthday.day);
    else if(userBirthday.month < 10)
        fprintf(fp2nd,"%d-0%d-%d\n", userBirthday.year,userBirthday.month,userBirthday.day);
    else if(userBirthday.day < 10)
        fprintf(fp2nd,"%d-%d-0%d\n", userBirthday.year,userBirthday.month,userBirthday.day);
    else
        fprintf(fp2nd,"%d-%d-%d\n", userBirthday.year,userBirthday.month,userBirthday.day);


    // Loop that reads the Data from the first file until its end of file marker
    while(fscanf(fp,"%c",&read) != EOF){
        if(countNewLine == personZodiacSign + (countSameZodiac * 12)) // Condition that checks if the reading of the data from the file is already in the exact line  
            printf("%c",read);
        if(read == '\n') // Increments whenever there is a new line
            countNewLine++;
    }


    // Closes the files used in the program    
    fclose(fp);
    fclose(fp2nd);

    return 0;
}

int getZodiacSign(Birthday bday){
    //Starts with index 0 (for array indexing)

    if((bday.month == 1 && bday.day >= 20) || (bday.month == 2 && bday.day <= 17)) // Aquarius
        return 0;
    else if((bday.month == 2 && bday.day >= 18) || (bday.month == 3 && bday.day <= 19)) // Pisces
        return 1;
    else if((bday.month == 3 && bday.day >= 20) || (bday.month == 4 && bday.day <= 19)) // Aries
        return 2;
    else if((bday.month == 4 && bday.day >= 20) || (bday.month == 5 && bday.day <= 20)) // Taurus
        return 3;
    else if((bday.month == 5 && bday.day >= 21) || (bday.month == 6 && bday.day <= 20)) // Gemini
        return 4;
    else if((bday.month == 6 && bday.day >= 21) || (bday.month == 7 && bday.day <= 22)) // Cancer
        return 5;
    else if((bday.month == 7 && bday.day >= 23) || (bday.month == 8 && bday.day <= 22)) // Leo
        return 6;
    else if((bday.month == 8 && bday.day >= 23) || (bday.month == 9 && bday.day <= 22)) // Virgo
        return 7;
    else if((bday.month == 9 && bday.day >= 23) || (bday.month == 10 && bday.day <= 22)) // Libra
        return 8;
    else if((bday.month == 10 && bday.day >= 23) || (bday.month == 11 && bday.day <= 21)) // Scorpio
        return 9;
    else if((bday.month == 11 && bday.day >= 22) || (bday.month == 12 && bday.day <= 21)) // Sagittarius
        return 10;
    else if((bday.month == 12 && bday.day >= 22) || (bday.month == 1 && bday.day <= 19)) // Capricorn
        return 11;      

}
