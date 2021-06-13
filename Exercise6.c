#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int rows, columns;
} Player;

typedef struct{
    int startPositionRows, startPositionColumns,
        endPositionRows, endPositionColumns;
}Obstacles;

//FUNCTION PROTOTYPES(INITIALIZATION)
void assign(int,int,char*);
void initializeBoard( char *);
void initializePositions(Player*);
void randomPosition(char *, char , char, Obstacles*);
void resetPosition(Obstacles*, char*);
void board(char *, char *);

//FUNCTION PROTOTYPES(INSIDE THE GAME)
void displayMessage(char);
int randomDice(char);
void moveCharacter(char, char*, int, Player*,int,int);
void obstaclesLand(char, Player*, Obstacles*, Obstacles*,char*,int,int,int,int);
int isPlayerWinning(char,Player*,int,int);
char playerSwitch(char);

int main()
{
    int gameState;
    char *obstacles, *grid, arr[400],arr2[400]; //Using 1d array to allocate memory for 2d array
    obstacles = arr; grid = arr2; //The pointer will be equal to the array to copy its size
    int rolledDice;
    char userEnter, userEnter2;
    char players = 'a';
    Player * positionsPlayers, p[4]; // Stores the array for position
    positionsPlayers = p; 
    Obstacles* snakes, s[3]; snakes = s;
    Obstacles* ladders, l[3];ladders = l;
    
    printf("ESPONILLA, Dustin Jed Wesley P.\n");
    printf("CMSC21 - C (Exercise 6 - Snakes and Ladders)\n");
    srand(time(NULL));
    //INTIALIZATION(things to do before starting the game)
        assign(10,40,obstacles);
        assign(10,40,grid);
        initializeBoard(obstacles);
        initializeBoard(grid);
        initializePositions(positionsPlayers);
        randomPosition(obstacles,'s','S',snakes);
        randomPosition(obstacles,'L','l',ladders);
        //Position Initialization for A,B,C,D and #
        *(grid + (positionsPlayers+0)->rows * 40 + (positionsPlayers+0)->columns) = 'a';
        *(grid + (positionsPlayers+1)->rows * 40 + (positionsPlayers+1)->columns) = 'b';
        *(grid + (positionsPlayers+2)->rows * 40 + (positionsPlayers+2)->columns) = 'c';    
        *(grid + (positionsPlayers+3)->rows * 40 + (positionsPlayers+3)->columns) = 'd';
        *(obstacles+0*40+0) = '#'; //'#' sign for winning the game
        board(obstacles,grid);
        

    /* I added a new feature that asks the users if the snakes and ladders are complete. 
       If the user says that it's not complete, then the program will randomize the position again and again 
       until the users are satisfied with the snakes and ladders. 
       Since it is randomized, then users will be given a liberty to say if they are satisfied with the 
       randomized snakes and ladders or not. 
       If not, then they can just ask to randomize it again.
    */
    printf("Are you satisfied with the snakes and ladders?\n");
    printf("Remember, there are 3 snakes and 3 ladders.(3 's' and 3 'S') and (3 'L' and 3 'l')\n");
    printf("There must be no snakes and ladders at the same tile and in the 100th tile itself.\n");
    printf("Are they complete? Type <1>. If not, then press <Enter>\n");
    scanf("%c",&userEnter);
    
    if(userEnter == '\n'){
         do{
            printf("Okay. Randomizizng them again. :)\n");
            resetPosition(snakes,obstacles); resetPosition(ladders,obstacles);
            randomPosition(obstacles,'s','S',snakes);
            randomPosition(obstacles,'L','l',ladders);
            board(obstacles,grid);
            printf("Is this okay now? Type <1> if yes.\nIf not, then press enter.\n");
            scanf("%c",&userEnter2);
            printf("\n\n");
        }while(userEnter2 !='1');
    }
    
    //INSIDE THE GAME(the functions that will make the game run)
    // Order: Press Enter, Roll Dice, Move to the Position, and Player Exchange Turns
        do{
            displayMessage(players);
            rolledDice = randomDice(players);
            if(players == 'a'){
                 moveCharacter(players,grid,rolledDice,positionsPlayers,0,36);
                 obstaclesLand(players,positionsPlayers,snakes,ladders,grid,0,3,0,3);
                 gameState = isPlayerWinning(players,positionsPlayers,0,0);
            }
            else if(players == 'b'){
                 moveCharacter(players,grid,rolledDice,positionsPlayers,1,37);
                 obstaclesLand(players,positionsPlayers,snakes,ladders,grid,1,2,1,2);
                 gameState = isPlayerWinning(players,positionsPlayers,1,1);
            }

            else if(players == 'c'){
                 moveCharacter(players,grid,rolledDice,positionsPlayers,2,38);
                 obstaclesLand(players,positionsPlayers,snakes,ladders,grid,2,1,2,1);
                 gameState = isPlayerWinning(players,positionsPlayers,2,2);
            }

            else if(players == 'd'){
                 moveCharacter(players,grid,rolledDice,positionsPlayers,3,39);
                 obstaclesLand(players,positionsPlayers,snakes,ladders,grid,3,0,3,0);
                 gameState = isPlayerWinning(players,positionsPlayers,3,3);
            }
            board(obstacles,grid);
            printf("%c rolls a %i!\n",players,rolledDice);
            players = playerSwitch(players);
        }while(gameState != 1);
       
        
        
    return 0;
}

void assign(int row, int column, char *array){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            *(array+i*column+j) = i + j; //Using One pointer to do 2d array
        }
    }
}

void initializeBoard(char *arr){
    //Puts spaces in every characters
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 40; j++){
        *(arr+i*40+j) = ' ';  
        }
    }                 
}
void initializePositions(Player* position){
    
    (position+0)->rows = 9; (position+0)->columns = 0; //For Player A
    (position+1)->rows = 9; (position+1)->columns = 1; //For Player B
    (position+2)->rows = 9; (position+2)->columns = 2; //For Player C
    (position+3)->rows = 9; (position+3)->columns = 3; //For Player D
}

void randomPosition(char *array, char label1, char label2, Obstacles* obs){
    int randomColumn;
    srand(time(NULL));

    //Random Position for Snakes
    if(label1 == 's' && label2 == 'S'){
        for(int i = 0; i < 3; i++){
            //Randomize Rows
    
            (obs+i)->startPositionRows = 4 + rand() % 5; //The starting position must be in the lower row
            (obs+i)->endPositionRows = rand() % 4;
           
            //Randomizing Columns
            do{
                (obs+i)->startPositionColumns = rand() % 40;
                (obs+i)->endPositionColumns = rand() % 40;
            }while(((obs+i)->startPositionColumns + 1) % 4 != 0 ||
                    ((obs+i)->endPositionColumns + 1 ) % 4 != 0 );
            //The indexes of Snakes' column is divisible by 4 when added to 1.
        }  
    }

    //Random Position For Ladders
    else{
        for(int i = 0; i < 3; i++){
            //Randomize Rows
            (obs+i)->startPositionRows = 4 + rand() % 5; //The starting position must be in the lower row
            (obs+i)->endPositionRows = rand() % 4;
            
            //Randomizing Columns
            do{
                (obs+i)->startPositionColumns = rand() % 40;
                (obs+i)->endPositionColumns = rand() % 40;
            }while((obs+i)->startPositionColumns % 4 != 0 ||
                   (obs+i)->endPositionColumns  % 4 != 0 );
            //The indexes of Ladders' column is divisible by 4.
        }
    }
    //Assigning the Randomized Rows and Columns to the array
    for(int i = 0; i < 3; i++){
        *(array+(obs+i)->startPositionRows * 40 + (obs+i)-> startPositionColumns) = label1;
        *(array+(obs+i)->endPositionRows * 40 + (obs+i)-> endPositionColumns) = label2;
    }

}

void resetPosition(Obstacles* obs, char* array){
    //Assigning them Spaces again to reset the position
    for(int i = 0; i < 3; i++){
        *(array+(obs+i)->startPositionRows * 40 + (obs+i)-> startPositionColumns) = ' ';
        *(array+(obs+i)->endPositionRows * 40 + (obs+i)-> endPositionColumns) = ' ';
    }
}


void displayMessage (char playerTurn){
    printf("\n%c's turn!\n",playerTurn);
    char playerInput;
    
    fflush(stdin);
    do{ 
        printf("%c, press <enter> to roll!",playerTurn);
        scanf("%c",&playerInput);
    }while(playerInput != '\n');  
}

int randomDice(char playerTurn){
    int rolledDice;
    //Now the random dice generator will be initiated. 
    rolledDice = 1 + rand() % 6;
    return rolledDice;
}

void moveCharacter(char playerTurn, char *grid, int rolledDice, Player* position, int index, int endPosition){
    int move = rolledDice * 4;
    int num = 0;

     *(grid + (position+index)->rows * 40 + (position+index)->columns) = ' ';
        //If the player's position is still in the first 10 cells
        if((position+index)->rows == 9 && (position+index)->columns <= endPosition){
            (position+index)->columns += move;

            if((position+index)->columns > endPosition && (position+index)->rows != 0){
                while((position+index)->columns != endPosition){
                    (position+index)->columns -= 4;
                    num++;
                }
            (position+index)->rows--;
            (position+index)->columns -= (num-1)*4;
            }
        }
        else if((position+index)->rows != 9 && (position+index)->columns <= endPosition
                && (position+index)-> rows % 2 == 0){
            (position+index)->columns -= move;

            //If the row number is num+1 % 4 == 0
            if((position+index)->columns < 0 && (position+index)->rows != 0 ){
                while((position+index)->columns < 0){
                    (position+index)->columns += 4;
                    num++;
                }
            (position+index)->rows--;
            (position+index)->columns += (num-1)*4;
            }
        }

        // If the row number is num % 4 == 0
        // Same with the first row (from the bottom), this will increment by 4.
        else if((position+index)->columns <= endPosition && (position+index)->rows != 0 
                && ((position+index)-> rows + 1) % 2 == 0){
                (position+index)->columns += move;

                if((position+index)->columns > endPosition && (position+index)->rows != 0){
                   while((position+index)->columns != endPosition){
                        (position+index)->columns -= 4;
                        num++;
                    }
                (position+index)->rows--;
                (position+index)->columns -= (num-1)*4;
            }
        }
    *(grid + (position+index)->rows * 40 + (position+index)->columns) = playerTurn;
}
        



void obstaclesLand(char playerTurn, Player* positions, Obstacles* snake, Obstacles* ladder, char* grid, int index, int addSnake, int addLadder, int subSnake){
    //Checks if the Player Landed on a snake or a ladder
    //Checks if the player landed on a snake or not
        for(int i = 0; i < 3; i++){
            if((snake+i)->endPositionRows == ((positions+index)->rows) && 
                (snake+i)->endPositionColumns == ((positions+index)->columns + addSnake)){
                    //Assigns the Value to the new coordinates
                    *(grid + (positions+index)->rows * 40 + (positions+index)->columns) = ' ';
                    (positions+index)->rows = ((snake+i)->startPositionRows);
                    (positions+index)->columns = ((snake+i)->startPositionColumns - subSnake);
                     *(grid + (positions+index)->rows * 40 + (positions+index)->columns) = playerTurn;
                    printf("Player %c lands on a snake and goes down.. :(\n",playerTurn);
                    break;
                }
            //Checks if the player landed on a ladder or not
            if((ladder+i)->startPositionRows == ((positions+index)->rows) && 
                (ladder+i)->startPositionColumns == ((positions+index)->columns - addLadder)){
                    //Assigns the Value to the new coordinates
                     *(grid + (positions+index)->rows * 40 + (positions+index)->columns) = ' ';
                    (positions+index)->rows = ((ladder+i)->endPositionRows);
                    (positions+index)->columns = ((ladder+i)->endPositionColumns+addLadder);
                     *(grid + (positions+index)->rows * 40 + (positions+index)->columns) = playerTurn;
                    printf("Player %c lands on a ladder and goes up.. Yey!\n",playerTurn);
                    break;
                
            }
    }
}

int isPlayerWinning(char playerTurn, Player* position, int index, int columns){
    if((position+index)->rows == 0 && (position+index)->columns <= columns){
            printf("Player %c wins the game! Yey!\n",playerTurn);
            return 1;
        }
    else
        return 0;
}

char playerSwitch(char playerTurn){
    
    //Now, the player will switch turns using the ASCII code
    // Remember, 'a' = 97 and 'd' = 100
    if(playerTurn == 100)
        playerTurn = 97;
    else
        playerTurn++;

    return playerTurn;
}

void board(char *arr1, char *arr2){
    int columns;
    for(int i = 0; i<10; i++){ //Loop for number of rows
        for(int j = 0; j<=50; j++){
            if(j == 0 || j % 5 == 0)
                printf("+");
            else
                printf("-");
        }
        printf("\n");
        columns = 0;
        for(int k = 0; k <= 50; k++){
            if(k == 0 || k % 5 == 0)
                    printf("|");
                else{
                    printf("%c",*(arr1+i*40+columns)); //space
                                 //arr[i][columns]
                    columns++;
                }
                    
            }
            printf("\n");

        columns = 0; 
        for(int k2 = 0; k2 <= 50; k2++){
            if(k2 == 0 || k2 % 5 == 0)
                    printf("|");
                else{
                    printf("%c",*(arr2+i*40+columns)); //space
                                 //arr2[i][columns];
                    columns++;
                }
                    
            }
            printf("\n");

        if(i == 9){
            for(int l = 0; l <=50; l++){
                if(l == 0 || l % 5 == 0 )
                    printf("+");
                else
                    printf("-");
        }
        printf("\n");
        }
    }
}
