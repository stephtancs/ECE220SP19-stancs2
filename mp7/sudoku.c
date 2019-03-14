#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// This program analyzes and solves a sudoku puzzle.
// partner: cvauk2
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
  int j;
  assert(i>=0 && i<9);

  for(j=0; j<9; j++){
    if(sudoku[i][j]==val){
      return 1;
    }
  }
return 0;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
  int i;
  assert(j>=0 && j<9);

  for(i=0; i<9; i++){
    if(sudoku[i][j]==val){
      return 1;
    }
  }
return 0;
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
  int maxi, maxj, jclone, iclone, istart, jstart;
  assert(i>=0 && i<9 && j>=0 && j<9);
  //test to see what region is being tested then setting
  //start and end value of i and j respectivly to make sure only cells
  //in square are tested
  if(i<3){
    maxi=3;
    istart=0;
  }
  if(i>=3 && i<6){
    maxi=6;
    istart=3;
  }
  if(i>=6){
    maxi=9;
    istart=6;
  }
  if(j<3){
    maxj=3;
    jstart=0;
  }
  if(j>=3 && j<6){
    maxj=6;
    jstart=3;
  }
  if(j>=6){
    maxj=9;
    jstart=6;
  }
  //cycle through all cells in square testing for value
  for(iclone=istart; iclone<maxi; iclone++){
    for(jclone=jstart; jclone<maxj; jclone++){
      if(sudoku[iclone][jclone]==val){
	return 1;
      }
    }
  }
  return 0;
}
// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
  int box, row, col;
  assert(i>=0 && i<9 && j>=0 && j<9);
  //determines validity based on whether or not the number exists in 3 possible variable locations
  box=is_val_in_3x3_zone(val, i, j, sudoku);
  row=is_val_in_row(val, i, sudoku);
  col=is_val_in_col(val, j, sudoku);
  if(box==0 && row==0 && col==0){
    return 0;
  }

  return 1;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
  int i, j, iTemp, jTemp = 0; 
  int noZeros = 1;
  //loops through the entire puzzle and determines if there is a zero and where it is
  for(i = 0; i<9; i++){
    for(j = 0; j<9; j++){
      if(sudoku[i][j]==0){
	noZeros = 0;
	iTemp = i;
	jTemp = j;
	}
    }
  }
  //break case for recursion
  if(noZeros==1)
    return 1;
  //loops through possible values for the puzzle, determines validity of each
  for(int num = 1; num <=9; num++){	  
	if(sudoku[iTemp][jTemp] == 0){
	if(!(is_val_valid(num, iTemp, jTemp, sudoku))){
	    	sudoku[iTemp][jTemp]=num;
	    if(solve_sudoku(sudoku)){
	      return 1;
	    }
	    else
	      sudoku[iTemp][jTemp]=0;
	  }
    }
  }
  return 0;
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
