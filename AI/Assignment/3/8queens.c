#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4
#define rep(i,a,b)  for(int i=a; i<b; i++)
#define rep0(i,b)  for(int i=0; i<b; i++)


void printBoard(int board[N][N]) {
	rep0(i,N) {
		rep0(j,N){
			printf("%d ",board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void printState(int* state){
 
    rep0(i,N) {
        printf("%d ", state[i]);
    }
    printf("\n");
}


void fill(int board[][N], int value) {
    rep0(i,N) {
        rep0(j,N){
            board[i][j] = value;
        }
    }
}

void copyState(int* state1, int* state2){
 
    rep0(i,N) {
        state1[i] = state2[i];
    }
}

void copyBoard(int board1[][N], int board2[][N]){
	rep0(i,N){
		rep0(j,N){
			board1[i][j] = board2[i][j];
		}
	}
}

void GenerateBoard(int board[][N], int* state){
 
    fill(board, 0);
      rep0(i,N){
        board[state[i]][i] = 1;
    }
}
   

void GenerateInitialState(int * state, int board[N][N]) {
	srand(time(0));

	rep0(i,N) {
		state[i] = rand()%N;
		board[state[i]][i] = 1;
	}
	printBoard(board);
	printState(state);

}


int CalculateObjectiveValue(int *state, int board[][N]){
	int attack = 0;
	int row,col;

	rep0(i,N){
		row = state[i];
		col = i;

		//left
		while(col >=0 ){

		if(col >=0 && board[row][col] ==1 ){
			attack++;
		}
			col--;
		}
		

		//right

		row = state[i], col = i+1;

		while(col<N){

		if(col<N && board[row][col] == 1){
			attack++;
		  }
			col++;
		}
		

		//diagonial left up

		row = state[i],col=i-1;
		while(col>=0 && row>0){

		if(col>=0 && row>=0 && board[row][col] ==1){
			attack++;
		 }
			col--;
			row--;
		}
		

		//diagonial right down 
		row= state[i], col = col+1;
		 while (col < N && row < N) {

		 if (col < N && row < N && board[row][col] == 1) {
            attack++;
         }
            col++;
            row++;
        }
        

        //diagonial left down
        row = state[i], col= col-1;
		 while (col>= 0 && row < N) {

		 if (col>= N && row < N && board[row][col] == 1) {
            attack++;
         }
            col--;
            row++;
        }
        

        //diagonial right up
        row= state[i], col = col+1;
		 while (col < N && row>=0) {

		  if (col < N && row >=0 && board[row][col] == 1) {
            attack++;
          }
            col++;
            row--;
        }
       

	}

	return (int)(attack/2);
}

int compareState(int *state1, int * state2){
	rep0(i,N){
		if(state1[i] != state2[i]) return 0;
	}

	return 1;
}

void GenerateSuccessorState(int *state, int board[][N], int objvalue){

	// int NeighbourBoard[N][N];
 //    int NeighbourState[N];

 //    copyState(NeighbourState,state);
 //    GenerateBoard(NeighbourBoard,state);

	rep0(i,N){
		rep0(j,N){
			if(j != state[i]){
				int temp = state[i];
				state[i] = j;
				board[state[i]][i] = 1;
				board[temp][i] = 0;

				int succesorobjvalue = CalculateObjectiveValue(state,board);
				int deltaE  = objvalue - succesorobjvalue;
				if(deltaE < 0){
					board[state[i]][i] = 0; 
					board[temp][i] = 1;
					state[i] = temp;
				}else{
					// printf("succesor\n");
					return;
				}	

				
			}
		}
	}

}


void StocahsticHillClimbing(int * state, int board[][N]){
	int SuccesorState[N] = {};
	int SuccesorBoard[N][N] = {} ;
	copyState(SuccesorState,state);
	copyBoard(SuccesorBoard,board);
		do {
			printf("do\n");
			int objvalue = CalculateObjectiveValue(state,board);
			GenerateSuccessorState(SuccesorState,SuccesorBoard,objvalue);
			if(compareState(state,SuccesorState)){// convergence
				printBoard(board);
				printf("\n");
				printBoard(SuccesorBoard);
				printf("done\n");
				break;
			}else {
					copyState(state,SuccesorState);
					copyBoard(board, SuccesorBoard);
				}	
			
		}while(1);

}


int main(){
	int state[N] = {};
	int board[N][N] = {};

	GenerateInitialState(state,board);

	StocahsticHillClimbing(state,board);
	
	return 0;
}