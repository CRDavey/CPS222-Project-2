/*
 * expression.h - Declaration for a class representing simple arithmetic
 *                expressions.  Part of CPS222 Project 2.
 *
 * An expression is constructed from its infix form, which may consist of
 * one-digit integers, the operators +, -, *, /, and parentheses, with no other
 * characters (including spaces) allowed.  Public methods are provided to return the 
 * postfix and prefix forms of the expression, and to evaluate it - as well as to 
 * report errors if any of the above is impossible due to a syntax or arithmetic error.
 * Private methods are provided to convert from infix to postfix and from postfix to
 * prefix, as well as to evaluate the postfix.
 *
 * Copyright (c) 2001, 2003, 2013, 2015 - Russell C. Bjork
 *
 */
 
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
using namespace std;

// The constructor of class Expression throw an exception of this type

class SyntaxError
{
    public:
    
        // Constructor
        // Parameter: position - where the error occurred
        // Parameter: description - descriptive text about the error
        
        SyntaxError(int position, const char * description)
        : _position(position), _description(description)
        { }
    
        // Get the position where the error occurred on the line
        
        int getPosition() const
        { return _position; }
        
        // Get a text message describing the error
        
        const char * getDescription() const
        { return _description; }
        
    private:
    
        int _position;
        const char * _description;
};

// The code for evaluating an expression throws this if division by zero is
// attempted

class DivideByZeroError
{
    public:
    
        // Constructor
        // Parameter: position - where the error occurred in the postfix
 
        DivideByZeroError(int position)
        : _position(position)
        { }
      
        // Get the position where the error occurred in the postfix
        
        int getPosition() const
        { return _position; }
        
    private:
    
        int _position;
};

class Expression
{
    public:
    
        // Constructor.  Parameter is infix form of the expression (a string)
        
        Expression(string infix) throw (SyntaxError)
        : _infix(infix), _postfix(string("")), _prefix(string(""))
        { }
        
        // Return infix form of the expression
        
        string getInfix() const
        { 
           return _infix; 
        }
        
        // Return postfix form of the expression.  If the postfix form of
        // the expression is not yet known, it is calculated and stored in
        // the instance variable _postfix
        // A SyntaxError is thrown if conversion to postfix is needed and the
        // infix syntax is invalid
        string getPostfix() throw(SyntaxError)
        { 
        	if (_postfix.length() == 0)
        		_postfix = convertToPostfix(_infix);
        	return _postfix;
        }
        
        // Return value of the expression.  
        // Precondition: conversion to postfix has already been done
        // A DivideByZeroError is thrown if division by zero is attempted
        int getValue() throw(SyntaxError, DivideByZeroError)
        {
            return evaluate(_postfix);
        }
       
        // Return prefix form of the expression.  If the prefix form of
        // the expression is not yet known, it is calculated and stored in
        // the instance variable _prefix
        // Precondition: conversion to postfix has already been done
        string getPrefix()
        { 
        	if (_prefix.length() == 0)
        		_prefix = convertToPrefix(_postfix);
        	return _prefix;
        }
		
        
    private:
    
        // Construct postfix form from infix form
        // Parameter is the infix form of the expression (a string)
        // Return value is the postfix form of the expression (a string)
        // A SyntaxError is thrown if infix syntax is invalid
        
        string convertToPostfix(string infix) const throw (SyntaxError);
        
        // Evaluate postfix form
        // Parameter is the postfix form of the expression (a string)
        // Return value is the value of the expression
        // A DivideByZeroError is thrown if division by zero is attempted
        
        int evaluate(string postfix) const throw (DivideByZeroError);
        
        // Construct prefix form of the expresion from postfix form
        // Parameter is the postfix form of the expression (a string)
        // Return value is the prefix form of the expression (a string)
        // No errors are possible if the postfix form is valid
    
        string convertToPrefix(string postfix) const;
		
        string _infix, _postfix, _prefix;
};

#endif      
 
