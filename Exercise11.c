#include <stdio.h>
#include <string.h>


struct StudentRecord{ 
    int StudentNumber; //  1-300
    char LastName[15];
    char FirstName[15];
    char Course[15];
    int Year;
    int Age;
    char Sex[15];
    int FinalGrade;

}; typedef struct StudentRecord StudentRecord;

// FUNCTION PROTOTYPES
void menu();

// FUNCTIONS FOR MENU 1
void enrolStudent();
int isStudentHere(int student);

// FUNCTION FOR MENU 2
void dropStudent();

// FUNCTION FOR MENU 3
void editStudent();

// FUNCTION FOR MENU 4
void displayStudents();
void printData(StudentRecord* students);

// FILTER FUNCTIONS
void filterStrings(int cases);
void filterIntegers(int cases);

// SORTING FUNCTIONS & SOME ADDITIONAL FUNCTION
int compareLastName(char* one, char* two, char* three, char* four);
void sort(int cases);

int main()
{
    int input;

    while(input != 14){

        // User Input + Validity
        do{
            menu();
            printf("? ");
            scanf("%i",&input);
        }while(input > 14 || input < 1); 

        switch(input)
        {
            case 1: // Enrol a student
            enrolStudent();
            break;

            case 2: // Drop a student
            dropStudent();
            break;

            case 3: // Edit a student
            editStudent();
            break;

            case 4: // Display all students
            displayStudents();
            break;

            case 5: // Filter students by last name
            filterStrings(1);
            break;

            case 6: // Filter students by student number
            filterIntegers(1);
            break;

            case 7: // Filter students by year level
            filterIntegers(2);
            break;

            case 8: // Filter students by course
            filterStrings(2);
            break;

            case 9: // Filter students by sex
            filterStrings(3);
            break;

            case 10: // Filter students by passing
            filterIntegers(3);
            break;

            case 11: // Filter students by failing
            filterIntegers(4);
            break;

            case 12: // Sort students by last name
            sort(1);
            break;

            case 13: // Sort students by student number
            sort(2);
            break;

            case 14: // Exit
            printf("Ok thanks. Bye! :))\n");
            return 0;
            break;
        }

    } 

    return 0;
}


void menu(){

    printf("\n\nStudent Information System\n");
    printf("[1] Enrol a student\n");
    printf("[2] Drop a student\n");
    printf("[3] Edit a student\n");
    printf("[4] Display all students\n");
    printf("[5] Filter students by last name\n");
    printf("[6] Filter students by student number\n");
    printf("[7] Filter students by year level\n");
    printf("[8] Filter students by course\n");
    printf("[9] Filter students by sex\n");
    printf("[10] Filter students by passing\n");
    printf("[11] Filter students by failing\n");
    printf("[12] Sort students by last name\n");
    printf("[13] Sort students by student number\n");
    printf("[14] Exit\n");

}

void enrolStudent()
{
    FILE* fp = fopen("studentinformation.bin","a+"); // Append Extended to automatically create the .bin file

    if(!fp){
        printf("Error opening the file.\n");
        return; 
    }
    // Temporary Storage of Variables
    int StudentNumber; char LastName[15]; char FirstName[15]; char Course[15];
    int Year; int Age; char Sex[15]; int FinalGrade;

    StudentRecord students;

    printf("Enrol\n");
    do{
        printf("Student Number: ");
        scanf("%i",&StudentNumber);
    }while(isStudentHere(StudentNumber) == 1 || isStudentHere(StudentNumber) == -1
            || (StudentNumber > 300 || StudentNumber < 1));

    do{
        printf("Last Name: ");
        scanf("%s",LastName);
    }while(strlen(LastName) > 15);

    do{
        printf("First Name: ");
        scanf("%s",FirstName);
    }while(strlen(FirstName) > 15);

    do{
        printf("Course: ");
        scanf("%s",Course);
    }while(strlen(Course) > 15);

    do{
        printf("Year Level: ");
        scanf("%i",&Year);
    }while(Year < 1);

    do{
        printf("Age: ");
        scanf("%i",&Age);
    }while(Age < 1);

    do{
        printf("Sex: ");
        scanf("%s",Sex);
    }while(strlen(Sex) > 15);

    do{
        printf("Final Grade: ");
        scanf("%i",&FinalGrade);
    }while(FinalGrade < 0 || FinalGrade > 100);

    // Assigning the temporary variables to the StudentRecord
    students.StudentNumber = StudentNumber;
    strcpy(students.LastName,LastName);
    strcpy(students.FirstName,FirstName);
    strcpy(students.Course,Course);
    students.Year = Year;
    students.Age = Age;
    strcpy(students.Sex,Sex);
    students.FinalGrade = FinalGrade;
    
    printf("%i enrolled!\n",students.StudentNumber);

    // Write the binary data to the file
    fseek(fp,sizeof(StudentRecord)*(students.StudentNumber-1), SEEK_SET);
    fwrite(&students,sizeof(StudentRecord),1,fp);

    fclose(fp);
}

int isStudentHere(int student){

    FILE* fp = fopen("studentinformation.bin","r"); // Read 
    StudentRecord dataStudent;  

    if(!fp){
        printf("Error opening the file.\n");
        return -1;
    }

    while(fread(&dataStudent,sizeof(StudentRecord),1,fp) && !(feof(fp)))
    {
        if(student == dataStudent.StudentNumber){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void dropStudent()
{
    StudentRecord student;
    FILE* fp = fopen("studentinformation.bin","rb+");
    char temp[15];

    if(!fp){
        printf("Error opening the file.\n");
        return;
    }

    printf("Enter student number: ");
    scanf("%i",&student.StudentNumber);

    if(isStudentHere(student.StudentNumber))
    { // Removes the data of the strings
        for(int i = 0; temp[i] != '\0'; i++)
        {
            student.LastName[i] = temp[i];
            student.FirstName[i] = temp[i];
            student.Course[i] = temp[i];
            student.Sex[i] = temp[i];
        }
        // Removes the data of the integers by setting them to 0
        student.Year = 0;
        student.Age = 0;
        student.FinalGrade = 0;

        fseek(fp,sizeof(StudentRecord)*(student.StudentNumber-1),SEEK_SET);
        fwrite(&student,sizeof(StudentRecord),1,fp);
        printf("%i dropped!\n",student.StudentNumber);
    }
    else{
        printf("Student not found\n");
    }
    fclose(fp);
}

void editStudent()
{
    FILE* fp = fopen("studentinformation.bin","rb+");
    StudentRecord student,tempStudent;
    int input, choice;

    // Temporary Storage of Variables
    int StudentNumber; char LastName[15]; char FirstName[15]; char Course[15];
    int Year; int Age; char Sex[15]; int FinalGrade;


    if(!fp){
        printf("Error opening the file.\n");
        return;
    }

    printf("Student Number: ");
    scanf("%i",&input);

    if(isStudentHere(input) == 1)
    {
       while(fread(&tempStudent,sizeof(StudentRecord),1,fp) && !(feof(fp)))
        {
            if(tempStudent.StudentNumber == input)
                student = tempStudent;              
        }

        while(choice != 9){
        do{
            printf("\nEdit\n");
            printf("[1] Student Number\n");
            printf("[2] Last Name\n");
            printf("[3] First Name\n");
            printf("[4] Course\n");
            printf("[5] Year Level\n");
            printf("[6] Age\n");
            printf("[7] Sex\n");
            printf("[8] Final Grade\n");
            printf("[9] Back\n");
            printf("Select a choice: ");
            scanf("%i",&choice);
        }while(choice > 9 || choice < 1);

        switch(choice)
        {
            case 1: // Student Number
            printf("Student Number (%i): ", student.StudentNumber);
            scanf("%i",&StudentNumber);
            
            if(isStudentHere(StudentNumber) == 1)
            {
                printf("This student number already exists. Please try again.\n");
                break;
            }

            else
            {
                student.StudentNumber = StudentNumber;
                printf("Student number updated successfully.\n");
            }
            break;

            case 2: // Last Name
            printf("Last Name (%s): ",student.LastName);
            scanf("%s",LastName);
            strcpy(student.LastName,LastName);
            printf("Last Name updated successfully.\n");

            break;

            case 3: // First Name
            printf("First Name (%s): ",student.FirstName);
            scanf("%s",FirstName);
            strcpy(student.FirstName,FirstName);
            printf("First Name updated successfully.\n");

            break;

            case 4: // Course
            printf("Course (%s): ",student.Course);
            scanf("%s",Course);
            strcpy(student.Course,Course);
            printf("Course updated successfully.\n");

            break;

            case 5: // Year Level
            printf("Year Level (%i): ",student.Year);
            scanf("%i",&Year);
            student.Year = Year;
            printf("Year level updated successfully.\n");

            break;

            case 6: // Age
            printf("Age (%i): ",student.Age);
            scanf("%i",&Age);
            student.Age = Age;
            printf("Age updated successfully.\n");
            break;

            case 7: // Sex
            printf("Sex (%s): ",student.Sex);
            scanf("%s",Sex);
            strcpy(student.Sex,Sex);
            printf("Sex updated successfully.\n");
            break;

            case 8: // Final Grade

            do{
            printf("Final Grade (%i): ",student.FinalGrade);
            scanf("%i",&FinalGrade);
            }while(FinalGrade < 0 || FinalGrade > 100);
            
            student.FinalGrade = FinalGrade;
            printf("Final Grade updated successfully.\n");

            break;

            case 9: // Back
            printf("Terminating the edit menu...\n");
            break;
            }
        }
    }
    else 
       printf("The student does not exist.\n");
    
    fseek(fp,sizeof(StudentRecord) * (student.StudentNumber - 1), SEEK_SET);
    fwrite(&student,sizeof(StudentRecord),1,fp);

    fclose(fp);
}

void printData(StudentRecord* students){

        printf("====================\n");
        printf("[1] Student Number: %i \n",students->StudentNumber);
        printf("[2] Last Name: %s \n",students->LastName);
        printf("[3] First Name: %s \n",students->FirstName);
        printf("[4] Course: %s \n",students->Course);
        printf("[5] Year Level: %i \n",students->Year);
        printf("[6] Age: %i \n",students->Age);
        printf("[7] Sex: %s \n",students->Sex);
        printf("[8] Final Grade: %i \n",students->FinalGrade);
        printf("====================\n");
}


void displayStudents(){
    FILE* fp = fopen("studentinformation.bin","rb+");

    if(!fp){
        printf("Error opening the file.\n");
        return;
    }
    StudentRecord student;

    while(fread(&student,sizeof(StudentRecord),1,fp) && !(feof(fp)))
        printData(&student);

    fclose(fp);
}

void filterStrings(int cases){
    char temp[15];
    int flag;
    StudentRecord student;
    FILE* fp = fopen("studentinformation.bin","rb+");

    if(!fp){
        printf("Error opening the file.\n");
        return;
    }
    switch(cases)
    {
        case 1: // Last Name
        printf("Enter last name:");
        scanf("%s",temp);
        
        while(fread(&student,sizeof(StudentRecord),1,fp) && !(feof(fp))){
            if(strcmp(temp,student.LastName) == 0)
            {
                printData(&student);
                flag = 1;
            }
        }
        if(flag == 0)
            printf("Last name not found.\n");

        break;


        case 2: // Course
        printf("Enter course: ");
        scanf("%s",temp);

        while(fread(&student,sizeof(StudentRecord),1,fp) && !(feof(fp))){
            if(strcmp(temp,student.Course) == 0)
            {
                printData(&student);
                flag = 1;
            }
        }
        if(flag == 0)
            printf("Course not found.\n");

        break;

        case 3: // Sex
        printf("Enter sex: ");
        scanf("%s",temp);
        
        while(fread(&student,sizeof(StudentRecord),1,fp) && !(feof(fp))){
            if(strcmp(temp,student.Sex) == 0)
            {
                printData(&student);
                flag = 1;
            }
        }
        if(flag == 0)
            printf("Sex not found.\n");
        break;

    }
    fclose(fp);
}

void filterIntegers(int cases){
    int temp;
    int flag;
    StudentRecord student;
    FILE* fp = fopen("studentinformation.bin","rb+");

     if(!fp){
        printf("Error opening the file.\n");
        return;
    }

    switch(cases)
    {
        case 1: // Student Number
        printf("Enter student number: ");
        scanf("%i",&temp);

        while(fread(&student,sizeof(StudentRecord),1,fp) && !(feof(fp))){
            if(temp == student.StudentNumber)
            {
                printData(&student);
                flag = 1;
            }
        }
        if(flag == 0)
            printf("Student Number not found.\n");
        break;

        case 2: // Year Level
        printf("Enter year level: ");
        scanf("%i",&temp);

        while(fread(&student,sizeof(StudentRecord),1,fp) && !(feof(fp))){
            if(temp == student.Year)
            {
                printData(&student);
                flag = 1;
            }
        }
        if(flag == 0)
            printf("Year level inputted not found.\n");
        break;

        case 3: // Passing Final Grade
    
        while(fread(&student,sizeof(StudentRecord),1,fp) && !(feof(fp))){
            if(student.FinalGrade >= 60)
            {
                printData(&student);
            }
        }
        break;

        case 4: // Failing Final Grade
        while(fread(&student,sizeof(StudentRecord),1,fp) && !(feof(fp))){
            if(student.FinalGrade < 60)
            {
                printData(&student);
            }
        }
        break;
    }
    fclose(fp);
}

void sort(int cases){
    FILE* fp = fopen("studentinformation.bin","rb+");
    int arraySize = 0, i = 0;
    StudentRecord student,temp;

    if(!fp){
        printf("Error opening the file.\n");
        return;
    }
    // Counts how many students are currently enrolled in the system

    while(fread(&student,sizeof(StudentRecord),1,fp) && (!feof(fp))){
         if(student.StudentNumber >= 1 && student.StudentNumber <= 300) // The valid student number is from 1-300
            arraySize++;     
     }
    

    fseek(fp,0,SEEK_SET);

    StudentRecord list[arraySize];
    while(fread(&student,sizeof(StudentRecord),1,fp) && (!feof(fp))){
        if(student.StudentNumber >= 1 && student.StudentNumber <= 300){
            list[i] = student;
            i++;
        }
    }
    
    switch(cases)
    {
        case 1: // Last Name
        for(int i = 0; i < (arraySize - 1); i++)
        {
            for(int j = 0; j < (arraySize - i - 1); j++)
            {
                if(compareLastName(list[j].LastName,list[j+1].LastName,list[j].FirstName,list[j+1].FirstName) == 1){
                    temp = list[j];
                    list[j] = list[j+1];
                    list[j+1] =temp;
                }
            
            }
        }
        break;

        case 2: // Student Number
        for(int i = 0; i < (arraySize - 1); i++)
        {
            for(int j = 0; j < (arraySize - i - 1); j++)
            {
                if(list[j].StudentNumber > list[j+1].StudentNumber){
                    temp = list[j];
                    list[j] = list[j+1];
                    list[j+1] =temp;
                }
            
            }
        }
        break;
    }

    for(int i = 0; i < arraySize; i++)
    {
        printf("====================\n");
        printf("[1] Student Number: %i \n",list[i].StudentNumber);
        printf("[2] Last Name: %s \n",list[i].LastName);
        printf("[3] First Name: %s \n",list[i].FirstName);
        printf("[4] Course: %s \n",list[i].Course);
        printf("[5] Year Level: %i \n",list[i].Year);
        printf("[6] Age: %i \n",list[i].Age);
        printf("[7] Sex: %s \n",list[i].Sex);
        printf("[8] Final Grade: %i \n",list[i].FinalGrade);
        printf("====================\n");
    }
    fclose(fp);
}

int compareLastName(char* one, char* two, char* three, char* four){

   
    for(int i = 0; one[i] !='\0' || two[i] !='\0'; i++){
        if(one[i] > two[i])
            return 1;
        else if(one[i] < two[i])
            return 0;
    }

 
    for(int i = 0; three[i] != '\0' || four[i] !='\0' ; i++){
        if(three[i] > four[i])
            return 1;
        else if(three[i] < four[i])
            return 0;
    }
    return 0;
}
