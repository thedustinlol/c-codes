#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct StudentRecord{ // Node composing of different information
    char StudentNumber[15];
    char LastName[15];
    char FirstName[15];
    char Course[15];
    int Year;
    int Age;
    char Sex[15];
    int FinalGrade;

    struct StudentRecord* next;
}; typedef struct StudentRecord StudentRecord;

struct StudentRecordList{ // Linked List for student records
    StudentRecord* head;
    StudentRecord* tail;
    int size;
}; typedef struct StudentRecordList StudentRecordList;



//FUNCTION PROTOTYPES

//General Functions
void menu();
void initializeList(StudentRecordList* list);

//FUNCTIONS FOR MENU 1
StudentRecord* informationStudent(); 
int checkStudentNumber(char* studnum);
void insertStudent(StudentRecordList* list, int index, StudentRecord* student);
StudentRecord* getStudent(StudentRecordList* list, int index);
int isStudentHere(StudentRecord* student, StudentRecordList* list);

//FUNCTIONS FOR MENU 2 
int removeStudent(StudentRecordList* list, int index);
int indexoftheStudent(StudentRecordList* list, char* string);

//FUNCTIONS FOR MENU 3 
void editMenu();
void editStudent(StudentRecordList* list, int index, int choice);

//FUNCTIONS FOR MENU 4 
void printStudent(StudentRecordList* list);

//FUNCTIONS FOR FILTER MENUS
void filterFunctionStrings(StudentRecordList* list, char* input, int cases);
void filterFunctionIntegers(StudentRecordList* list, int intInput, int cases);
void printOnlyOneStudent(StudentRecord* student);

//FUNCTIONS USED FOR SORTING LINKED LIST
int studentNumberCompare(StudentRecord* student1, StudentRecord* student2);
int lastNameCompare(StudentRecord* student1, StudentRecord* student2);
StudentRecord* swap(StudentRecord* data1, StudentRecord* data2);
void sortData(StudentRecord* data, int cases, StudentRecordList* list);

int main()
{  
    int input, studentIndex, editChoice, filterInputInt;
    char tempInput[15], filterInput[15];
    StudentRecord* students;
    StudentRecordList lists;
    initializeList(&lists); // Initialize the List

    while(input != 14){
    do{ 
        menu();
        printf("? ");
        scanf("%i",&input);
    }while(input < 1 || input > 14);

    switch(input){
        case 1: // Enrol a student
        students = informationStudent(); // Prompt the user to enroll themselves

        // Checks if the student already is unique. If it's not, then the user will be asked to try again.
        if(isStudentHere(students,&lists) == 0){
            insertStudent(&lists,lists.size,students);
            printf("The student is successfully added.\n");
        }
        else
            printf("The inputted student number already exists. Please try again.\n");
        break;

        case 2: // Drop a student
           printf("Drop Student\n");
           printf("Enter the student number: ");
           scanf("%s",tempInput);

           if(checkStudentNumber(tempInput) == 0){
               printf("The student number is not valid. Please try again.\n");
               break;
           }
           else{
            studentIndex = indexoftheStudent(&lists,tempInput);

            if(studentIndex == -1)
                printf("The student does not exist.\n");
            else{
                removeStudent(&lists,studentIndex);
                printf("The student is removed successfully.");
            }
           }

        break;

        case 3: // Edit a student
            printf("\nEdit a student\n");
            printf("Enter the student number: ");
            scanf("%s", tempInput);

            if(checkStudentNumber(tempInput) == 0){
                printf("The student number is not valid. Please try again.\n");
                break;
            }
            else{
                studentIndex = indexoftheStudent(&lists,tempInput);
                
                if(studentIndex == -1)
                    printf("The student does not exist.\n");

                else{
                   while(editChoice != 9){
                        editMenu();
                        printf("Select a choice: ");
                        scanf("%i",&editChoice);
                        editStudent(&lists,studentIndex,editChoice);
                   }    

                }    
            }
        break;

        case 4: // Display all students
        if(lists.size == 0)
            printf("There are no students in the list.\n");
        else{
            printf("\nDisplaying %i out of %i student(s)\n", lists.size, lists.size);
            printStudent(&lists);
        }
            
        break;

        case 5: // Filter students by last name
        printf("Enter the Last Name: ");
        scanf("%s",filterInput);

        filterFunctionStrings(&lists,filterInput,1);
        break;

        case 6: // Filter students by student number
        printf("Enter Student Number: ");
        scanf("%s",filterInput);
        
        filterFunctionStrings(&lists,filterInput,2);
        break;

        case 7: // Filter students by year level
        printf("Enter Year Level: ");
        scanf("%i",&filterInputInt);

        
        filterFunctionIntegers(&lists,filterInputInt,1);
        break;

        case 8: // Filter students by course
        printf("Enter a course: ");
        scanf("%s",filterInput);

        filterFunctionStrings(&lists,filterInput,3);
        break;

        case 9: // Filter students by sex
        printf("Enter a sex: ");
        scanf("%s",filterInput);

        filterFunctionStrings(&lists,filterInput,4);
        break;

        case 10: // Filter students by passing
        filterFunctionIntegers(&lists,0,2);
        break;

        case 11: // Filter students by failing        
        filterFunctionIntegers(&lists,0,3);
        break;

        case 12: // Sort students by last name
        if(lists.size == 0)
            printf("There are no students in the system.\n");
        else{
            sortData(students,1,&lists);
            printStudent(&lists);
        }
        break;

        case 13: // Sort students by student number
        if(lists.size == 0)
            printf("There are no students in the system.\n");
        else{
            sortData(students,2,&lists);
            printStudent(&lists);
        }
        break;

        case 14: // Exit
        printf("Ok thanks, bye! :)\n");
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

void initializeList(StudentRecordList* list){
    list->head = 0;
    list->tail = 0;
    list->size = 0;

}

StudentRecord* informationStudent(){
    // Temporary Storage of Variables (from the Node Structure)
    StudentRecord* students;
    char StudentNumber[15]; char LastName[15]; char FirstName[15]; char Course[15];
    int Year; int Age; char Sex[15]; int FinalGrade;

    students = malloc(sizeof(StudentRecord));

    printf("Enrol\n");
    
    do{
        printf("Student Number: ");
        scanf("%s",StudentNumber);
    }while(checkStudentNumber(StudentNumber) == 0 || strlen(StudentNumber) > 15);

    do{
        printf("Last Name: ");
        scanf("%s", LastName);
    }while(strlen(LastName) > 15);

    do{
        printf("First Name: ");
        scanf("%s", FirstName);
    }while(strlen(FirstName) > 15);

    do{
        printf("Course: ");
        scanf("%s", Course);
    }while(strlen(Course) > 15);

    do{
        printf("Year level: ");
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
    }while(FinalGrade < 1 || FinalGrade > 100);

    //Assign the User Inputted Values to the Structure
    strcpy(students->StudentNumber,StudentNumber); 
    strcpy(students->LastName,LastName);
    strcpy(students->FirstName,FirstName); 
    strcpy(students->Course,Course);
    strcpy(students->Sex,Sex);
    students->Year = Year;
    students->Age = Age;
    students->FinalGrade = FinalGrade;
    students->next = 0;

    return students;
  
}

int checkStudentNumber(char* studnum){
    int hyphen = 0;

    for(int i = 0; studnum[i] != '\0'; i++){
        if(studnum[i] == '-')
            hyphen = 1;
        if(studnum[i] != '-' && (studnum[i] < '0' || studnum[i] > '9')){
            hyphen = 0;
            break;
        }        
    }

    if (hyphen == 1)  return 1; else return 0; // 1 being a valid student number
   
}

void insertStudent(StudentRecordList* list, int index, StudentRecord* student){
    if(index >= 0 && index <= list->size){
        
        if(index == 0){
            student->next = list->head;
            list->head = student;
        }

        if(index == list->size){
            if(list->tail != 0)
            list->tail->next = student;
            list->tail = student;
        }
        
        if(index > 0 && index < list->size){
            StudentRecord* previous = getStudent(list, index-1);
            student->next = previous->next;
            previous->next = student;
        } 
    }
    list->size++; //Increments the Size


}

StudentRecord* getStudent(StudentRecordList* list, int index){
    StudentRecord* current = list->head;

    if(index >= 0 && index < list->size){
        for(int i = 0; i < index; i++){
            current = current->next;
        }
    return current;
    }
}

int isStudentHere(StudentRecord* student, StudentRecordList* list){

    StudentRecord* current = list->head;
    int flag = 0;

    for(int i = 0; i < list->size; i++){
        if(strcmp(current->StudentNumber,student->StudentNumber) == 0){ // Compares the student number if it exists
            flag = 1;
            break;
        }
        current = current->next;
    }
    if(flag == 0){
        return 0;
    } 
    else 
        return 1; // 1 being an invalid student number
}

int removeStudent(StudentRecordList* list, int index){
    if(index >= 0 && index <= list->size -1){
        StudentRecord* toRemove;

        if(index == 0){
            toRemove = list->head;
            list->head = toRemove->next;
        }
        else{
            StudentRecord* previous = getStudent(list, index - 1);
            toRemove = previous->next;
            previous->next = toRemove->next;

            if(index == list->size - 1)
                list->tail = previous;
        }
    free(toRemove);
    list->size--;
    }
}

int indexoftheStudent(StudentRecordList* list, char* string){
    StudentRecord* current = list->head;
    int i;
    for(i = 0; i < list->size; i++){
        if(strcmp(current->StudentNumber,string) == 0)
            return i; // Returns the Index of the Student
            current = current->next;
    }
   return -1; // Returns an invalid index
}

void editMenu(){
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
}

void editStudent(StudentRecordList* list, int index, int choice){
    StudentRecord* studentData = getStudent(list,index);
    
    //Temporary Storage of Inputs
    char StudentNumber[15]; char LastName[15]; char FirstName[15]; char Course[15];
    int Year; int Age; char Sex[15]; int FinalGrade;

    switch(choice)
    {
        case 1: // Student Number
        printf("Student number (%s): ", studentData->StudentNumber);
        scanf("%s",StudentNumber);
        
        if(checkStudentNumber(StudentNumber) == 1){
            strcpy(studentData->StudentNumber, StudentNumber); 
            printf("Edited student number successfully.\n");
        }
             
        else
            printf("Invalid student number. Please try again.\n");
        break;
        
        case 2: // Last Name
        printf("Last Name (%s): ", studentData->LastName);
        scanf("%s",LastName);

        if(strlen(LastName) > 15)
            printf("Invalid Last Name. Please enter up to 15 characters only.\n");
        else{
            printf("Edited Last Name successfully.\n");
            strcpy(studentData->LastName,LastName);
        }
        break;

        case 3: // First Name
        printf("First Name (%s): ",studentData->FirstName);
        scanf("%s",FirstName);

        if(strlen(FirstName) > 15)
            printf("Invalid First Name. Please enter up to 15 characters only.\n");
        else{
            printf("Edited First Name successfully.\n");
            strcpy(studentData->FirstName,FirstName);
        }
            
        break;

        case 4: // Course
        printf("Course (%s): ",studentData->Course);
        scanf("%s",Course);

        if(strlen(Course) > 15)
            printf("Invalid Course. Please enter up to 15 characters only.\n");
        else{
            strcpy(studentData->Course,Course);
            printf("Edited course successfully.\n");
        }
        break;

        case 5: // Year Level
        printf("Year Level (%i): ", studentData->Year);
        scanf("%i",&Year);
        
        if(Year < 1)
            printf("Invalid year.\n");
        else{
            studentData->Year = Year;
            printf("Edited year successfully.\n");
        }
        break;

        case 6: // Age
        printf("Age (%i): ", studentData->Age);
        scanf("%i",&Age);

        if(Age < 1)
            printf("Invalid age.\n");
        else{
            studentData->Age = Age;
            printf("Edited age successfully.\n");
        }
        break;

        case 7: // Sex
        printf("Sex (%s): ", studentData->Sex);
        scanf("%s",Sex);

        if(strlen(Sex) > 15)
            printf("Invalid Sex. Please enter up to 15 characters only.\n");
        else{
            strcpy(studentData->Sex,Sex);
            printf("Edited sex successfully.\n");
        }
            
        break;

        case 8: // Final Grade
        printf("Final Grade (%i): ", studentData->FinalGrade);
        scanf("%i",&FinalGrade);

        if(FinalGrade < 0 || FinalGrade > 100)
            printf("Invalid Final Grade. Please try again.\n");
        else{
            studentData->FinalGrade = FinalGrade;
            printf("Edited the final grade successfully.\n");
        }
        break;

        case 9: // Back
        printf("Terminating the edit menu...\n");
        break;
    
    }
}
void printStudent(StudentRecordList* list){
    StudentRecord* head = list->head;
    
    for(int i = 0; i < list->size; i++){
        printf("====================\n");
        printf("[1] Student Number: %s \n",head->StudentNumber);
        printf("[2] Last Name: %s \n",head->LastName);
        printf("[3] First Name: %s \n",head->FirstName);
        printf("[4] Course: %s \n",head->Course);
        printf("[5] Year Level: %i \n",head->Year);
        printf("[6] Age: %i \n",head->Age);
        printf("[7] Sex: %s \n",head->Sex);
        printf("[8] Final Grade: %i \n",head->FinalGrade);
        printf("====================\n");
        
        head = head->next;
    }

}

void printOnlyOneStudent(StudentRecord* student){
        printf("====================\n");
        printf("[1] Student Number: %s \n",student->StudentNumber);
        printf("[2] Last Name: %s \n",student->LastName);
        printf("[3] First Name: %s \n",student->FirstName);
        printf("[4] Course: %s \n",student->Course);
        printf("[5] Year Level: %i \n",student->Year);
        printf("[6] Age: %i \n",student->Age);
        printf("[7] Sex: %s \n",student->Sex);
        printf("[8] Final Grade: %i \n",student->FinalGrade);
        printf("====================\n");
}

void filterFunctionStrings(StudentRecordList* list, char* input, int cases){
    StudentRecord* head = list->head;

    for(int i = 0; i < list->size; i++){

        if(cases == 1){ // Last Name
            if(strcmp(input,head->LastName) == 0)
                printOnlyOneStudent(head);     
        }

        else if(cases == 2){ // Student Number
            if(strcmp(input,head->StudentNumber) == 0)
                printOnlyOneStudent(head);
        }

        else if(cases == 3){ // Course
            if(strcmp(input,head->Course) == 0)
                printOnlyOneStudent(head);
        }
        
        else if(cases == 4){ // Sex
            if(strcmp(input,head->Sex) == 0)
                printOnlyOneStudent(head);       
        }
        head = head->next;
    }
}

void filterFunctionIntegers(StudentRecordList* list, int intInput, int cases){
    StudentRecord* head = list->head;

    for(int i = 0; i < list->size; i++){ // Year Level
        if(cases == 1){ 
            if(intInput == head->Year)
                printOnlyOneStudent(head);
        }

        else if(cases == 2){ // Passing Students
            if(head->FinalGrade >= 60)
                printOnlyOneStudent(head);      
        }

        else if(cases == 3){// Failing Students
          if(head->FinalGrade < 60)
            printOnlyOneStudent(head);
        }
        head = head->next;
    }
}

int studentNumberCompare(StudentRecord* student1, StudentRecord* student2){
    // Is student1 > student2?
    char temp1[15], temp2[15], temp3[15], temp4[15];
    int year1, year2, i;
    int year3,year4;
    for(i = 0; student1->StudentNumber[i] != '-' && student2->StudentNumber[i] != '-'; i++){
        temp1[i] = student1->StudentNumber[i];
        temp2[i] = student2->StudentNumber[i];
    }
    year1 = atoi(temp1);
    year2 = atoi(temp2);
    
    if(year1 > year2)
        return 1; // Valid
    else if(year1 < year2)
        return 0;
    else if(year2 == year1)
    {
        for(i; student1->StudentNumber[i] != '\0' && student2->StudentNumber[i] != '\0'; i++){
            temp3[i] = student1->StudentNumber[i];
            temp4[i] = student2->StudentNumber[i];
        }
        year3 = atoi(temp3);
        year4 = atoi(temp4);
    if(year3 > year4)
        return 1;
    else 
        return 0;
    }
    
}

int lastNameCompare(StudentRecord* student1, StudentRecord* student2){
    int length1 = strlen(student1->LastName), length2 = strlen(student2->LastName);
    int lengthFinal;

    for(int i = 0; student1->LastName[i] !='\0' || student2->LastName[i] !='\0'; i++){
        if(student1->LastName[i] > student2->LastName[i])
            return 1;
        else if(student1->LastName[i] < student2->LastName[i])
            return 0;
    }

    length1 = strlen(student1->FirstName); length2 = strlen(student2->FirstName);


    for(int i = 0; student1->FirstName[i]!= '\0' || student2->FirstName[i] !='\0' ; i++){
        if(student1->FirstName[i] > student2->FirstName[i])
            return 1;
        else if(student1->FirstName[i] < student2->FirstName[i])
            return 0;
    }
    return 0;
}

StudentRecord* swap(StudentRecord* data1, StudentRecord* data2){
    StudentRecord* tempStudent = data2->next;
    data2->next = data1;
    data1->next = tempStudent;
    return data2;
}

void sortData(StudentRecord* data, int cases, StudentRecordList* list){
   StudentRecord* current;
   StudentRecord* previous;
   StudentRecord* temp1, *temp2;
   int swapped;
    for(int i = 0; i < list->size; i++)
    {
        current = list->head;
        swapped = 0;

        for(int j = 0; j < list->size - i - 1; j++)
        {
            temp1 = current;
            temp2 = temp1->next;

            if(cases == 1) // Last Name
            { 
                if(lastNameCompare(temp1,temp2))
                {
                    current = swap(temp1,temp2);
                    swapped = 1;

                    if(j == 0)
                        list->head = current;
                    else if(j != 0)
                        previous->next = temp2;
                }
            } 
                else if(cases == 2) // StudentNumber
                {
                    if(studentNumberCompare(temp1,temp2))
                    {
                        current = swap(temp1,temp2);
                        swapped = 1;

                    if(j == 0)
                        list->head = current;
                    else if(j != 0)
                        previous->next = temp2;
                    }
                }
            previous = current;
            current = current->next;
        }
        if(swapped == 0)
            break;
     }
     
     current = list->head;

     for(int i = 0; i < list->size; i++) // Gets the Tail of the Linked List
        current = current->next;
        list->tail = current;    
}
