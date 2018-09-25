/***********************************
Author: Maurice Robert Sivanesan
Program: Question_4_TMA_2.c,
***********************************/
#include "stdafx.h" 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void getInput(char *in) {//fgets(char *in, int n, FILE *stream) reads a line from the specified stream
	fgets(in, 20, stdin);//and stores it into the string pointed to by in. It stops when either (n-1) 
}                        //characters are read, the newline character is read, or the end-of-file is reached.
                           
int isOperator(char p) {  //utility function to find value of operator
	if (p == '+' || p == '-' || p == '*' || p == '/') return p;
	else return 0;     }

int performOperator(int a, int b, char p) { //this function checks the operator type
	switch (p) {                            //switch case depends on operator type
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/':
		if (b == 0) { printf("Can't divide by 0\n"); exit(1); } //check if divide by zero
		return a / b;
	default:
		puts("Bad value\n");
		break;
	}
	return 0;}

char isDigit(char p) {//A utility function to check if a given character is a number
	if (p >= '0' && p <= '9') return 1;
	else return 0;}

int isNumber(char * p) { //if p is a number, return 1
	while (*p) {
		if (!isDigit(*p)) return 0;
		p++;             //if not, increment p until find number
	}
	return 1;}

int len(char * p)   {   // Check if string is empty
	return (int)strlen(p);}

int isMDGRoup(char *p) //Check if got both multiple and divide in one operation
{
	for (; *p; p++)
	{
		if (!isDigit(*p) && *p != '/' && *p != '*') return 0;
	}
	return 1;}

int getLeftOperand(char * p, char * l) {// Grab the left operand in p, put it in l,	
	int i = 0;                          //and return the index where it ends.	
	if (isMDGRoup(p)) {                
		while (1) {
			if (*p == '*' || *p == '/') break;
			l[i++] = *p++;
		}
		return i;
	}

	while (1) { // Operand is a number
		if (!isDigit(*p)) break;
		l[i++] = *p++;
	}
	l[i] = '\0';
	return i;
}

int getOperator(char * p, int index, char * op) {
	*op = p[index];
	return index + 1;}

int getRightOperand(char * p, char * l) {            //Grab the left operand in p, put it in l,	
	while (*p && (isDigit(*p) || isOperator(*p))) {  //and return the index where it ends.
		*l++ = *p++;
	}
	*l = '\0';
	return 0;
}

int isEmpty(char * p) {          //Check if string is empty	
	if (len(p) == 0) return 1;
	else return 0;
}

int calcExpression(char *p) {                                //ACTUAL FUNCTION
	if (isNumber(p)) return atoi(p);                         //if p is a number: return atoi(p)	
															 //so atoi is only performed on number characters
	char leftOperand[20] = "", rightOperand[20] = "", op;    

	int leftOpIndex = getLeftOperand(p, leftOperand);        //Get left operand and store in index
	int operatorIndex = getOperator(p, leftOpIndex, &op);    //Operator index = left and Operator from p
	int rightOpIndex = getRightOperand(p + operatorIndex, rightOperand); //Get right operand
																		 // if p is a number, return it
	if (isEmpty(rightOperand)) 
		return calcExpression(leftOperand);//function calcExpression on leftOperand
	return performOperator(           //Perform Operator function 
		calcExpression(leftOperand),  //leftOperand is a
		calcExpression(rightOperand), //rightOperand is b
		op);                          //op is operator sent to char p
}                                   

int main()
{
	char answer;
	do {		
			char in[20] = "\0";
			printf("Enter a simple mathematical operation: \n");
			getInput(in);                             //getInput function, reads input from user	
			int result = calcExpression(in);          // Performs calculation
			printf("The result of %s is %d\n", in, result);			
			printf("Do you want to try again? (Y/N): ");
			scanf_s(" %c", &answer);		
	}
	while (answer == 'y');
	printf("Bye...\n");	
	return 0;
}
