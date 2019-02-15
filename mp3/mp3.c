#include <stdio.h>
#include <stdlib.h>
/* This program takes an integer input from the user and outs the row of Pascal's Triangle that corresponds to that number, using 0 as the first row
partners: cvauk2
*/

int main()
{
  int row;//row defined by user
  long num = 1;//final answer stored here

  printf("Enter a row index: ");//prompts user
  scanf("%d",&row);//stores response

  printf("1 "); //first line is always the same

  for (int n = 1; n <= row; n++){
    float x = 1;//defines the number for the current row and position
    for (int k = 1; k <= n; k++){
      int part = 1-k;//defines part of the numerator of the formula
      float numerator = ((float) row) +((float)part);//defines the rest of the numerator of the formula
      float temp  = numerator /k;//defines the denominator of the formula
      x = temp * x;//mulitplies with previous loop values
    }
    num = x;//makes x an long value
    printf("%ld",num);//prints the value
    printf(" ");//prints a space
  }
  return 0;
}
