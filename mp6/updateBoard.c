		
//these three functions are used within the game of life that have alive cells and dead cells
//when a dead cell is surounded by 3 alive neighbors is brought to life
//when an alive cell is surounded by less than 2 neighbors it dies due to under population
//when an alive cell is surounded by more than 3 neighbors it dies from over population
//if an alive cell has exactly 2 or 3 neighbors it survives
//the game goes by in turns with each of these rules being applied every turn
//the first function below is responsible for counting the number of alive neighbor for any give cell
//the next function is responsible for implementing the rules above for each turn
//the last function will end the game if it detects there has been no chnages in a turn
//partner:stancs2




/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors.
 */
int countLiveNeighbor(int* copyboard, int boardRowSize, int boardColSize, int row, int col){
  int neigh_row=0, neigh_col=0, alive=0, value, position;
  //starting position will be the bottom right of the cells neighbors
 neigh_row=(row+1);
 //starting from bottom right work way along to bottom left
  for(neigh_col=(col+1); neigh_col>=col-1; neigh_col--){
    //makes sure the neighboring cell is within bounds
    if(neigh_col<boardColSize && neigh_col>=0 && neigh_row>=0 && neigh_row<boardRowSize){
      //use formula to calculate cells position that was given on wiki
      position=(neigh_row*boardColSize)+neigh_col;
      value=copyboard[position];
      //if neighbors cell is alive increment alive
      if(value==1){
	alive++;
	}
    }
  }
  //starting from directly left work way up to top left corner
  for(neigh_col=neigh_col+1, neigh_row=neigh_row-1; neigh_row>=row-1; neigh_row--){
    if(neigh_row<boardRowSize && neigh_row>=0 && neigh_col>=0 &&neigh_col<boardColSize){
    position=(neigh_row*boardColSize)+neigh_col;
      value=copyboard[position];
      if(value==1){
	alive++;
	}
    }
  }
  //starting from directly above work to top right corner
  for(neigh_row=neigh_row+1, neigh_col=neigh_col+1; neigh_col<=col+1; neigh_col++){
    if(neigh_col<boardColSize && neigh_col>=0 && neigh_row>=0 && neigh_row<boardRowSize){
    position=(neigh_row*boardColSize)+neigh_col;
      value=copyboard[position];
      if(value==1){
	alive++;
	}
    }
  }
  //only test the direct right cell
  for(neigh_col=neigh_col-1, neigh_row=neigh_row+1; neigh_row<row+1; neigh_row++){
    if(neigh_row<boardRowSize && neigh_row>=0 && neigh_col>=0 && neigh_col<boardColSize){
    position=(neigh_row*boardColSize)+neigh_col;
      value=copyboard[position];
      if(value==1){
	alive++;
	}
    }
  }
  //return number of alive neighbors
return alive;

}



/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int col, row, alive=0, position=0, i;
  int copyboard[boardRowSize*boardColSize];
  //make copy of board for testing
  for (i=1; i<=(boardRowSize*boardColSize); i++){
    copyboard[i]=board[i];
  }
  //cycle through all cells on board
 for(row=0; row<boardRowSize; row++){
   for(col=0; col<boardColSize; col++){
     alive=countLiveNeighbor(copyboard, boardRowSize, boardColSize, row, col);
     position=(row*boardColSize)+col;
     //if cell is dead and has three neighbors next turn it is alive
     if((copyboard[position]==0) && alive==3){
	board[position]=1;
       }
     //if an alive cell has less than 2 neighbors it will die next turn
     if(alive<2 && copyboard[position]==1){
       board[position]=0;
     }
     //if a cell has more than 3 neighbors it will die next turn
     if(alive>3 && copyboard[position]==1){
       board[position]=0;
       //if an alive cell has exactly 2 or 3 neighbors it will remain alive next turn 
     }
   }
 }
}


/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step through variable change.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  int col, row, alive=0, position=0, i, change=1;
  int copyboard[boardRowSize*boardColSize];
  //this loop is used to make a copy of the board for testing purposes//
  for (i=1; i<=(boardRowSize*boardColSize); i++){
    copyboard[i]=board[i];
  }
  //these two loops cycle through every cell first by going through the x axis
  //then incrementing y and repeating the first step
 for(row=0; row<boardRowSize; row++){
   for(col=0; col<boardColSize; col++){
     alive=countLiveNeighbor(copyboard, boardRowSize, boardColSize, row, col);//alive is used to keep track of alive neighbors
     position=(row*boardColSize)+col;//position is the location of current cell
     //if any of the rules are tripped then board is changed
     if((copyboard[position]==0) && alive==3){
	change=0;
       }
     if(alive<2 && copyboard[position]==1){
       change=0;
     }
     if(alive>3 && copyboard[position]==1){
       change=0;
     }
   }
 }
 //return 1 if nothing changed and 0 if something did
 return change;
}				
