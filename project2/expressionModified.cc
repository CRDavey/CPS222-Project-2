/*
 * expression.cc - Implementation of a class representing simple arithmetic
 *                 expressions, as declared in expression.h.  Part of CPS222
 *                 Project 2.
 *
 * Skeleton copyright (c) 2001, 2013 - Russell C. Bjork
 *
 */
 
#include "expression.h"
#include <stack>
#include <iostream>
using namespace std;
        
/* The following methods are to be written by students, and constitute
 * CPS222 Project 2.
 */
 

//Determine if a char is an operand
bool isOperand(char c)
{
	if(c >= '0' && c <= '9'){	//If char is a character between 0 and 9
		return true;			//Return true
	}
	return false;				//Otherwise return false
}

//Determine is a char is an operator
bool isOperator(char c)
{
	if(c == '+' || c == '-' || c == '*' || c == '/'){	//If char is any operator
		return true;									//Return true
	}
	return false;										//Otherwise return false
}

//Function to deal with the different possibilities in evaluate
int caseEval(int x, int y, char c)
{
	switch(c){
	case '+':
		return x + y;
		break;
	case '-':
		return x - y;
		break;
	case '*':
		return x * y;
		break;
	case '/':
		return x / y;
		break;
	}
}
 
//Get the precedence of an operator
int precedence(char c){

	int op = 0;		//initialize operator precedence (op) to 0
	
	if(c == '+' || '-'){		//If operator is '+' or '-' set op to 1
		op = 1;
	}
	else if(c == '*' || '/'){	//If operator is '*' or '/' set op to 2
		op = 2;
	}
	else if(c == '('){			//If operator is '(' return 0
		op = 0;
	}
	
	return op;
	
 }
 
string Expression::convertToPostfix(string infix) const throw (SyntaxError)
{

	stack <char> pStack; 						//Declaring stack from the STL in C++
    string postfix = "";								//Initialize the postfix as empty
	
	for(int i = 0; i<infix.length(); i++){		//Loop to go through infix expression
		switch(infix[i]){						//Switch for current character
		case isOperand(infix[i]):				//Case for operand
			postfix += infix[i];				//Output immediately to postfix
			break;
		
		case isOperator(infix[i]):				//Case for operator
			//While stack is not empty and precedence of top of stack is
			//greater than the current character
			while(!pStack.empty() && precedence(pStack.top()) >= precedence(infix[i])){
				postfix += pStack.top();		//Output top of stack to postfix
				pStack.pop();						//Pop the top of the stack
			}
			pStack.push(infix[i]);				//Push operator to stack
			break;
			
		case '(':								//Case for when current char is '('
			pStack.push(infix[i]);				//Immediately push onto stack
			break;
			
		case ')':								//Case for when current char is ')'
			while(pStack.top() != '('){			//While top of stack is not '('
				postfix += pStack.top();		//Output top of stack to postfix
				pStack.pop();					//Pop top of stack
			}
			pStack.pop();						//Pop top if stack = '('
		}		
	while(!pStack.empty()){							//While the stack is still not empty
		postfix += pStack.top();				//Output top to postfix
		pStack.pop();							//And pop the top of the stack
	}
	}
	
	return(postfix);
}

int Expression::evaluate(string postfix) const throw (DivideByZeroError)
{

	stack <int> evalStack;
	int value;
	
	for(int i = 0; i< postfix.length(); i++){				//Loop to go through postfix expression
		
		if(postfix[i] >= '0' && postfix[i] <= '9'){			//If current postfix character is an operand 0-9
			evalStack.push(postfix[i]);						//Immediately push to stack
		}
		else if(postfix[i] == '+' || '-' || '*' || '/'){	//If current postfix character is an operator
			int x = evalStack.top();						//set top of stack to x
			evalStack.pop();								//pop top of stack
			int y = evalStack.top();						//set top of stack to y
			evalStack.pop();										//pop top of stack
			caseEval(x, y, postfix[i]);						//Evaluate popped variables
			evalStack.push(value);							//Push value back onto stack
		}
	}
}	
	
string Expression::convertToPrefix(string postfix) const
{ return string(""); }  // Students: replace return code and remove this comment

int main()
{
	string infix;
	cout << "Enter Infix Expression: " << endl;  //Enter your infix expression
	cin >> infix;
	_postfix = convertToPostfix(infix);
	cout << "Infix: "<<infix<< endl;			 //Output the infix expression
	cout << "Postfix: "<<_postfix<< endl;		 //Output the postfix expression
}

