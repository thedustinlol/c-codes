#include <stdio.h>
#define PLAYER1 'X'
#define PLAYER2 'O'

// 1 - Winner
// 0 - No Winner
// 2 - Draw

//FUNCTION PROTOTYPES
void initializeBoard();
void showBoard();
void boardInput(char);
int checkMarker(int,int);
int boardMarker(int,int);
int winConditions();
char playerChange(char);

//GLOBALLY-DECLARED VARIABLES
int row,column;
char board[3][3],player = PLAYER1; // Player 1 is the first player to play

int main()
{  
  int game = 0;
  printf("Tic-Tac Toe Game\n");
  initializeBoard(); //Puts spaces in every array of the board
  do{
    showBoard();
    boardInput(player);

    //Checks if the inputted Row and Column is Occupied or not
    if(checkMarker(row,column) == 1)
        boardMarker(row,column);
    else{
        printf("(%i,%i) Occupied!\n",row,column);
        continue;
    }

    game = winConditions();
    player = playerChange(player);
    
  }while(game != 1 && game != 2);

    showBoard();
    if(game == 1)
        printf("\n%c is the winner! Congratulations!\n",playerChange(player));
    else
        printf("\nDraw. No Winner\n");
 
  return 0;
}

void initializeBoard(){
    //Puts spaces in every characters
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            board[i][j] = ' ';
        }
    }
}

void showBoard(){

    //Shows the board to the players
    printf("\n\n");   
    printf("\t\t\t  %c |  %c  | %c  \n", board[0][0], board[0][1], board[0][2]); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  %c |  %c  | %c  \n", board[1][0], board[1][1], board[1][2]); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  %c |  %c  | %c  \n", board[2][0], board[2][1], board[2][2]);  
}


void boardInput(char player){
    //User Input of Row and Column

   printf("%c's turn\n\n",player);
   do{
       printf("Row: ");
       scanf("%i",&row);
   }while(row < 1 || row > 3);

    do{
        printf("Column: ");
        scanf("%i",&column);
    }while(column < 1 || column > 3);
}

int checkMarker(int row, int column){
    row--;
    column--;

    if (board[row][column] == 'X' || board[row][column] == 'O' )
        return 0;
    else
        return 1;
}

int boardMarker(int row, int column){
    //Decrement both Row and Column since the index starts with 0
    row--;
    column--;

    //Plots the given input by the player
    if(row == 0 && column == 0)
        board[0][0] = player;
    else if (row == 0 && column == 1)
        board[0][1] = player; 
    else if (row == 0 && column == 2)
        board[0][2] = player; 
    else if (row == 1 && column == 0)
        board[1][0] = player; 
    else if (row == 1 && column == 1)
        board[1][1] = player; 
    else if (row == 1 && column == 2)
        board[1][2] = player;
    else if (row == 2 && column == 0)
        board[2][0] = player;  
    else if (row == 2 && column == 1)
        board[2][1] = player; 
    else if (row == 2 && column == 2)
        board[2][2] = player; 
    else
        printf("(%i,%i) Occupied!\n",row,column);
    
}

int winConditions(){
    // Win Through Rows 
    if (board[0][0] == board[0][1] && board[0][1] == board[0][2] &&  board[0][0] != ' ')
        return 1;
    else if (board[1][0] == board[1][1] && board[1][1] == board[1][2] &&  board[1][0] != ' ')
        return 1;
    else if (board[2][0] == board[2][1] && board[2][1] == board[2][2] &&  board[2][0] != ' ')
        return 1;
    // Win Through Columns
    else if (board[0][0] == board[1][0] && board[1][0] == board[2][0] &&  board[0][0] != ' ')
        return 1;
    else if (board[0][1] == board[1][1] && board[1][1] == board[2][1] &&  board[0][1] != ' ')
        return 1;
    else if (board[0][2] == board[1][2] && board[1][2] == board[2][2] &&  board[0][2] != ' ')
        return 1;
    //Win through diagonals
    else if (board[0][0] == board[1][1] && board[1][1] == board[2][2] &&  board[0][0] != ' ')
        return 1;
    else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] &&  board[0][2] != ' ')
        return 1;
    else if(board[0][0] != ' ' && board[0][1] != ' ' && board[0][2] != ' ' &&
            board[1][0] != ' ' && board[1][1] != ' ' && board[1][2] != ' ' &&
            board[2][0] != ' ' && board[2][1] != ' ' && board[2][2] != ' ')
       return 2;
    else
        return 0;
}
char playerChange(char player){
    if(player == PLAYER1)
        return PLAYER2;
    else
        return PLAYER1;
}
