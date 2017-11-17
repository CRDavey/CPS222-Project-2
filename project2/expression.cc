/*
 * expression.cc - Implementation of a class representing simple arithmetic
 *                 expressions, as declared in expression.h.  Part of CPS222
 *                 Project 2.
 *
 * Skeleton copyright (c) 2001, 2013 - Russell C. Bjork
 *
 */
 
#include "expression.h"
#include <iostream> //for debugging purposes
#include <stack>
using namespace std;
       
/* The following methods are to be written by students, and constitute
 * CPS222 Project 2.
 * @author Cody Davey, Kenneth Burgess
 * @date 2/24/15
 */

//Determine if a char is an operand
bool isOperand(char c)
{
  if(c >= '0' && c <= '9'){	//If char is a character between 0 and 9
    return true;		//Return true
  }
  return false;			//Otherwise return false
}

//Determine is a char is an operator
bool isOperator(char c)
{
  if(c == '+' || c == '-' || c == '*' || c == '/'){	//If char is any operator
    return true;		//Return true
  }
  return false;			//Otherwise return false
}

//Get the precedence of an operator
int precedence(char c){
	int op = 0;		//initialize operator precedence (op) to 0
	if(c == '+' || c == '-'){	//If operator is '+' or '-' set op to 1
		op = 1;
	}
	else if(c == '*' || c == '/'){	//If operator is '*' or '/' set op to 2
		op = 2;
	}
	else if(c == '('){		//If operator is '(' return 0
		op = 0;
	}
	else if(c == '#'){
		op = 3;
	}
	return op;
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

//convert the infix string to postfix
string Expression::convertToPostfix(string infix) const throw (SyntaxError)
{
  string postfix=""; //Initialize the postfix as empty
  stack <char> st; 	//Declaring stack from the STL in C++

  enum Type { OPERAND, OPERATOR };
  Type expected = OPERAND; //initialize first expected infix value to OPERAND

  for(int i = 0; i<infix.length(); i++) //Loop to go through infix expression
  {
    if (expected == OPERAND) {
      if (isOperand(infix[i])) {
	expected = OPERATOR;
      }
      else if (isOperator(infix[i])){
	if (infix[i]=='-'){
	  infix[i] = '#';
	}
	else {
	  throw SyntaxError(i, "Operand expected");
        }
      }
      else if (infix[i]=='('){}
      else if (infix[i]==')'){
	throw SyntaxError(i, "Operand expected");
      }
      else{
	throw SyntaxError(i, "Invalid character");
      }
    }
    else { // program expects an operator
      if (isOperand(infix[i])) {
	throw SyntaxError(i, "Operator expected");
      }
      else if (isOperator(infix[i])){
	expected = OPERAND;
      }
      else if (infix[i]=='('){
	throw SyntaxError(i, "Operator expected");
      }
      else if (infix[i]==')'){}
      else{
	throw SyntaxError(i, "Invalid character");
      }
    }
    switch(infix[i])
    {	//Switch for current character
      case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':	//Case for operand
        postfix += infix[i];		//Output immediately to postfix
	break;	
      case '+': case '-': case '*': case '/':	//Case for operator
	//While stack is not empty and precedence of top of stack is
	//greater than the current character
	while(! st.empty() && precedence(st.top()) >= precedence(infix[i])){
	  postfix += st.top();		//Output top of stack to postfix
	  st.pop();			//Pop the top of the stack
	}
	st.push(infix[i]);		//Push operator to stack
	break;
      case '(':				//Case for when current char is '('
	st.push(infix[i]);		//Immediately push onto stack
	break;		
      case ')':				//Case for when current char is ')'
	if (st.empty()){
	  throw SyntaxError(i, "'(' expected");
	}
	while(st.top() != '('){		//While top of stack is not '('
	  postfix += st.top();		//Output top of stack to postfix
	  st.pop();			//Pop top of stack
	  if (st.empty()){
	    throw SyntaxError(i, "'(' expected");
	  }
	}
	st.pop(); 			//pops the '('
	break;
      case '#':
	st.push(infix[i]);
	break;
    }		
  }
  if (expected == OPERAND){
    throw SyntaxError(infix.size(), "Operand expected");
  }
  while(! st.empty()){	//While the stack is still not empty
      if(st.top() == '('){
	throw SyntaxError(postfix.length(), "')' expected");
      }
      postfix += st.top();		//Output top to postfix
      st.pop();			//And pop the top of the stack
  }
  return string(postfix); 
} 

//evaluate the postfix expression
int Expression::evaluate(string postfix) const throw (DivideByZeroError)
{
  stack <int> evalStack;
  int value=0;
  for(int i = 0; i< postfix.length(); i++){	//Loop to go through postfix expression
    if(postfix[i] >= '0' && postfix[i] <= '9'){		//If current postfix character is an operand 0-9
      evalStack.push(postfix[i]-'0');	//Immediately push to stack (subtract 0 to convert from char to int value)
    }
    else if (isOperator(postfix[i])){ //it's an operator
      int second = evalStack.top();			//set top of stack to x
      evalStack.pop();				//pop top of stack
      int first = evalStack.top();			//set top of stack to y
      evalStack.pop();				//pop top of stack
      if (postfix[i] == '/' && second == 0){
	throw DivideByZeroError(i);
      }
      value = caseEval(first, second, postfix[i]);		//Evaluate popped variables
      evalStack.push(value);			//Push value back onto stack
    }
    else { //negate the previous value (since it is a '#')
      int toBeNegated = evalStack.top();
      evalStack.pop();
      evalStack.push(-toBeNegated); //negates the value
    }
  }
  return evalStack.top();
}

//convert the postfix string to prefix
string Expression::convertToPrefix(string postfix) const
{
  int length = postfix.length();
  int operandsNeeded = 1;
  string negatives = "";  //string to keep track of the number of negatives before an operand
  string prefix = postfix.substr(length-1,1); //add last char of postfix to prefix
  //decrement length and postfix (so as not to double count characters
  length -= 1; //keep track of postfix length
  postfix = postfix.substr(0,length); //remove last char from postfix
  for (int i = length-1; i>=0; i--){ //scan expression right to left
    if (isOperand(postfix[i])){
      operandsNeeded -= 1; //we need one less operand
    }
    else if (isOperator(postfix[i])){ //another operator is located...
      operandsNeeded += 1;	      //thus we require another operand before splitting
    }
    else if (postfix[i] == '#'){ //store negatives
      negatives += postfix.substr(i,1);
      postfix = postfix.substr(0,i) + postfix.substr(i,length);
      length = length-1; 
    }
    if (operandsNeeded == 0){ //operator has two operands, can convert to prefix and continue
      if (negatives != "") {
	prefix += negatives; //place negatives before the final operand
	negatives = ""; //reset negative count
      }
      prefix += convertToPrefix(postfix.substr(i,(length-i))); //convert first subpostfix expression to prefix
      if (i != 0) { //special case avoidance 
	prefix += convertToPrefix(postfix.substr(0,i)); //convert second postfix expression to prefix
      }
      return prefix;
    }
  }
  return prefix; 
} 


