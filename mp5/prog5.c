/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/* This code takes in a user decided seed in order to create 4 random numbers that the user then must guess in 12 tries. after each 
guess the user will be supplied with the amount of perfect matches he has guessed as well as the number of misplaced matches.
partners: cvauk2
*/


#include <stdio.h>
#include <stdlib.h>
#include "prog5.h"

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;

/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
int seed, state;
char post[2];
//    The sscanf statement below reads the integer into seed. if mix of integers and characters returns 0 and asks again for a valid seed
state=sscanf (seed_str, "%d%1s", &seed, post);
if(state==1){
    srand(seed);
    return 1;
  }
 printf("set_seed: invalid seed\n");
 return 0;
}


/*
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
  *one=rand()%7+1;
  *two=rand()%7+1;
  *three=rand()%7+1; 
  *four=rand()%7+1; 
  solution1=(int)*one;
  solution2=(int)*two;
  solution3=(int)*three;
  solution4=(int)*four;
  guess_number=1;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 */
int
make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
 char post[2];
 int w,x,y,z,state, pair1=0, pair2=0, pair3=0, pair4=0, perfect=0, misplaced=0;
 int mis1=0, mis2=0, mis3=0, mis4=0;

 state= sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
//makes sure the input is valid as well as calculates number of perfect matches
 if(state==4){
   if(x>0 && x<9 && w>0 && w<9 && y>0 && y<9 && z>0 && z<9){
     *one=w;
     *two=x;
     *three=y;
     *four=z;
     if(*one==solution1){
       pair1=1;
       perfect++;
     }
     if(*two==solution2){
       pair2=1;
       perfect++;
     }     
     if(*three==solution3){
       pair3=1;
       perfect++;
     }     
     if(*four==solution4){
       pair4=1;
       perfect++;
     }


     //section for determining amount of misplaced matches
 
    if(pair1==0){
        if(pair2==0 && *one==solution2 && mis2==0){
            misplaced++;
            mis2=1;
        }
        if(pair3==0 && *one==solution3 && mis3==0){
            misplaced++;
            mis3=1;
        }        
        if(pair4==0 && *one==solution2 && mis4==0){
            misplaced++;
            mis4=1;
        }

     }   
    if(pair2==0){
        if(pair1==0 && *two==solution1 && mis1==0){
            misplaced++;
            mis1=1;
        }
        if(pair3==0 && *two==solution3 && mis3==0){
            misplaced++;
            mis3=1;
        }        
        if(pair4==0 && *two==solution4 && mis4==0){
            misplaced++;
            mis4=1;
        }

     }    
    if(pair3==0){
        if(pair1==0 && *three==solution1 && mis1==0){
            misplaced++;
            mis1=1;
        }  
        if(pair2==0 && *three==solution2 && mis2==0){
            misplaced++;
            mis2=1;
        }
        if(pair4==0 && *three==solution4 && mis4==0){
            misplaced++;
            mis4=1;
        }

     }    
     
    if(pair4==0){
        if(pair1==0 && *four==solution1 && mis1==0){
            misplaced++;
            mis1=1;
        }  
        if(pair2==0 && *four==solution2 && mis2==0){
            misplaced++;
            mis2=1;
        }
        if(pair3==0 && *four==solution3 && mis3==0){
            misplaced++;
            mis3=1;
        }        
     }    
    

       printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
       guess_number++;
  return 1;
   }
 }
printf("make_guess: invalid guess\n");
return 0;
}
