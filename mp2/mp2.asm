;this program is a reverse polish calculator able to do calculations involving +, -, *, /, and ^.
;in order to use it first type the numbers you would like to use in the calculation seperated by a space
;next seperated by another space select what oprend you would like to do and once the equation is complete
;use = to see the resulting value in hexadecimal
;the calculator has an order of operation so (2+5)^3= 2 5 + 3 ^
;cvauk2, stancs2

.ORIG x3000

AND R2, R2, #0
AND R6, R6, #0	;use r6 to keep track of amount of digits on stack to prevent underflow
BRnzp BEGINING

LOOP 
ADD R7, R6, #-1	
BRn NOTPOWER
BEGINING
GETC	;get first character
OUT
LD R5, HEX30
ADD R0, R0, R5		;subtract 48  to get real digit
BRn NOTNUM
ADD R5, R0, #-9		;testing to see if input was a digit
BRp TRASH
ADD R2, R2, #0		;testing to see if previous thing pushed was a digit
BRz NUM
BRp TWODIGIT

BRnzp LOOP











;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PRINT
;R5 IS THE REGISTOR THAT IS PRINTED
LDI R5, STACK_START
LD R0, XFORHEX
OUT
AND R1, R1, #0		;INT digit counter (how many hexadecimal value printed)
AND R2, R2, #0		;INT bit counter (how many bits added from R3 to R0)
AND R4, R4, #0		;INT test to see if the loops went four times
ADD R4, R4, #-4		;set test to -4
AND R6, R6, #0		;INT R6 as histogram pointer
BRnzp START

PRINTOUT 
ADD R3, R0, #-9		;see if value in R0 is letter or number
BRzp LETTER
BRnzp NUMBER

START
NEXT
AND R2, R2, #0
ADD R5, R5, #0
BRz DONE
AND R0, R0, #0		;INT digit (the hexadecimal value trying to be printed)
ADD R3, R4, R1		;test to see if all hex has been printed
BRz PRINTDONE		

TEST 
ADD R5, R5, #0
BRzp ZERO
ADD R0, R0, #1		;add one to end of digit since r5 was negative
ZERO 
ADD R2, R2, #1
ADD R5, R5, R5		;shift hex value to left
ADD R3, R4, R2		;test to see if four digits have been added to R0
BRz PRINTOUT
ADD R0,R0,R0 		;shift the digit value left
BRnzp TEST

LETTER
LD R3, A_OFFSET
ADD R0, R0, R3		;convert decimal value to hex value of letter
OUT
BRnzp NEXT

NUMBER
LD R3, O_OFFSET
ADD R0, R0, R3
OUT
BRnzp NEXT

PRINTDONE
BRnzp LOOP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
EVALUATE

TRASH
;;;;;;;;;;;;;;;;;;;;;;;;;
AND R2, R2, #0
ADD R0, R0, #-13
BRz PRINT
ADD R0, R0, #-3
ADD R0, R0, #16
ADD R0, R0, #-14		;subtract 46 to test to see if char is ^
BRnp NOTPOWER
JSR POWER
NOTPOWER
BRz VALID
LEA R0, BADINPUT		;if not ^ then print BADINPUT
PUTS
BRnzp DONE
VALID
BRnzp LOOP

NUM
;;;;;;;PUSH DIGIT TO STACK
ADD R2, R2, #1		;set r2 to 1 to make sure the system looks for new space next
JSR PUSH
BRnzp LOOP

NOTNUM
;;;;;;;;;;;;;;;;;;;;;;; TEST TO SEE IF /
ADD R0, R0, #1	;add one since if it was a divide it would be at -1 now
BRn NOTDIV
JSR DIV
BRnzp LOOP

NOTDIV
;;;;;;;;;;;;;;;;;;;;;;;;;TEST TO SEE IF -
ADD R0, R0, #2		;add 2 to see if - since - would be -2 here
BRn NOTSUB
JSR SUB
BRnzp LOOP

NOTSUB
;;;;;;;;;;;TEST TO SEE IF +
ADD R0, R0, #2
BRn NOTADD
JSR PLUS
BRnzp LOOP

NOTADD
;;;;;;;TEST TO SEE IF *
ADD R0, R0, #1
BRn SPACE
JSR  MULT
SPACE
AND R2, R2, #0
BRnzp LOOP


;;PLUS LOOP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;out R0
PLUS	
ST R7, R7_SAVE
AND R1, R1, #0
JSR POP
ADD R1, R0, #0		;store first digit in r1
JSR POP
ADD R0, R1, R0		;add first digit in r1 to new digit just poped
JSR PUSH			;push final digit to stack
LD R7, R7_SAVE
RET

;;SUB LOOP	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;out R0
SUB
AND R1, R1, #0
ST R7, R7_SAVE
JSR POP
NOT R0, R0
ADD R0, R0, #1	;get the inverse of the second number
ADD R1, R0, R1	;store in r1
JSR POP
ADD R0, R1, R0	;add to second digit
JSR PUSH		;push result
LD R7, R7_SAVE
RET
	
;MULTILPICATION LOOP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;iR1 is counter R0 is running total while r3 is base number that is added to total each loop
;out R0
MULT
ST R7, R7_SAVE
ST R3, R3_SAVE
ST R1, R1_SAVE
AND R1, R1, #0		;clear r1
AND R3, R3, #0		;initalize r3
JSR POP
ADD R0, R0, #-1		;subtract one from loop counter bc 1*anything is just anything
ADD R1, R1, R0		;put counter in r1
JSR POP
ADD R3, R0, #0		;store base number in r3
MULTLOOP
ADD R0, R0, R3		;add base number to running total
ADD R1, R1, #-1		;decrment counter by 1
BRp MULTLOOP
JSR PUSH
LD R7, R7_SAVE
LD R3, R3_SAVE
LD R1, R1_SAVE
RET



;DIVISION LOOP	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 is running count of how many times R3 can be subtracted from R1
;out R0
DIV	
ST R7, R7_SAVE
ST R3, R3_SAVE
AND R1, R1, #0		;clear r1
AND R3, R3, #0		;initalize r3
JSR POP
NOT R0, R0
ADD R0, R0, #1		;compute negative version of second number
ADD R3, R0, #0		;put negative in R3
JSR POP
ADD R1, R0, #0		;put numerator in r1
AND R0, R0, #0		;clear r0 to use as counter
DIVLOOP
ADD R1, R3, R1		;add two number together and see if its negative yet
BRn REMAINDER		;when negative this means the numerator is no long divisbale by denominator
ADD R0, R0, #1		;incrament counter by 1
BRnzp DIVLOOP
REMAINDER
JSR PUSH
LD R7, R7_SAVE
LD R3, R3_SAVE
RET


;EXPONENT LOOP	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3 as multloop counter and r4 as powerloop counteR and r5 to keep track of original digit
;R1 is the new digit that need to be multiplied by the base while r0 is running total
;out R0
POWER
ST R3, R3_SAVE
ST R4, R4_SAVE
ST R7, R7_SAVE
AND R3, R3, #0		;INITALIZE REGISTORS
AND R4, R4, #0
AND R5, R5, #0
JSR POP
ADD R4, R0, #0		;store exponent in r4
JSR POP
ADD R5, R0, #0		;store base digit in r5

POWERLOOP
AND R1, R1, #0		;clear r1
ADD R1, R0, #0		;set r1 to running total
ADD R3, R5, #0		;reset the multcounter to base number so that running total can be * by it
ADD R3, R3, #-1		;decrament powerloop counter and subtract one from multloop counter so that it
ADD R4, R4, #-1		;does not attempt 1*x multiplication
BRz POWERDONE

MULTPOWERLOOP
ADD R0, R0, R1		;add digit to running total
ADD R3, R3, #-1		;decrament multloop counter
BRz POWERLOOP
BRp MULTPOWERLOOP

POWERDONE
JSR PUSH
LD R3, R3_SAVE
LD R4, R4_SAVE
LD R7, R7_SAVE
AND R5, R5, #0
RET


	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;



TWODIGIT
AND R1, R1, #0		;clear R1 to store second digit in
ADD R1, R1, R0
AND R0, R0, #0
ADD R0, R0, #10		;set r0 to ten so the digit already in stack can move a place over aka 2 now equals 20
JSR PUSH
JSR MULT
AND R0, R0, #0
ADD R0, R1, R0		;put second digit back in r0
JSR PUSH
JSR PLUS			;add second digit to first that has been left shifted by 1 now
BRnzp LOOP



PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	ADD R6, R6, #1
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R4
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	ADD R6, R6, #-1
	RET


HEX .FILL xFF06
A_OFFSET .FILL x37
O_OFFSET .FILL x30
R7_SAVE .FILL x0
R3_SAVE .FILL x0
R4_SAVE .FILL x0
R1_SAVE .FILL x0
XFORHEX .FILL x78
POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
HEX30 .FILL x-30
BADINPUT .STRINGZ "INVALID INPUT"

DONE

.END
