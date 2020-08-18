// shunting_yard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <cctype>
#include <iostream>
#include <list>
#include <string>
#include <queue>

using namespace std;
#define MAX_SIZE 20

//string rightArray[MAX_SIZE] = { "(", "4", "+", "6", ")" ,"*", "(", "2", "*", "(", "6", "-", "3", ")", ")" };
//string rightArray[MAX_SIZE] = {"(" ,"4", "-", "(", "6", "/", "2", ")", ")", "+", "18"};
string rightArray[MAX_SIZE] = { "(", "3", "*", "(", "6", "*", "2", ")", ")", "/", "18" };
queue<string> myqueue;

struct node { //create node structure for linked list
	string data;
	node *next;
}*top = NULL; //top pointer set to null for keeping track of top of stack

void bottomAdd(string);
void leftAdd(string);
void bottomLeftAdd();
int maths(int, int, char);
void push(string);
bool isEmpty();
void pop();

void initShunt() { //inital shunt function to move number to left, operand to bottom or if ')' move operands from bottom to left in reverse order until '(' found
	int loc = 0;

	while (!rightArray[loc].empty() && loc < MAX_SIZE)
	{
		
		if (rightArray[loc] == "(" || rightArray[loc] == "+" || rightArray[loc] == "-" || rightArray[loc] == "*" || rightArray[loc] == "/")
		{
			std::cout << "Moving " << rightArray[loc] << " to bottom track" << endl;
			push(rightArray[loc]);
			rightArray[loc].erase();
			loc++;
			
		}
		else if (rightArray[loc].find_first_not_of( "0123456789") == string::npos)
		{
			std::cout << "Moving " << rightArray[loc] << " to left track" << endl;
			myqueue.push(rightArray[loc]);
			rightArray[loc].erase();
			loc++;
			
		}
		else
		{
			std::cout << "Track element is a " << rightArray[loc] << " moving bottom track to left until '(' is found" << endl;
			pop();			
			rightArray[loc].erase();
			loc++;
			
		}
	}
	while (!isEmpty()) {
		pop(); //to move last of operands to left
	}
	std::cout << endl;

}

bool isEmpty() { //boolean function to check if stack is empty
	if (top == NULL)
		return true;
	else return false;
}

void push(string value) { //push function to add string to stack
	node *ptr = new node();
	ptr->data = value;
	ptr->next = top;
	top = ptr;
}

void pop() { //pop function to remove item from stack if stack is not empty and if data is not "(" to run pop again
	if (isEmpty())
		cout << "Stack is empty";
	else
	{
		
		node *ptr = top;
		
			if (ptr->data != "(") {
				cout << "Moving " << ptr->data << " to left array" << endl;
				myqueue.push(ptr->data);
				top = top->next;
				delete(ptr);
				pop();
			}
			else
			{
				top = top->next;
				delete(ptr);
			}
		
		
	}
}






void leftToRight() //move elements from left back to right
{
	int queueSize = myqueue.size();
	for (int i = 0; i < queueSize; i++)
	{
		
			rightArray[i] = myqueue.front();
			myqueue.pop();
		
	}
}

int popNum() //take data from stack, convert to int and return
{
	node *ptr = top;
	int num = std::stoi(ptr->data);
	top = top->next;
	delete(ptr);
	return num;
}

void displayStack() { //display function to check stack and display elements taking a new line for each one
	if (isEmpty())
		cout << "Stack is empty" << endl;
	else {
		node *temp = top;
		while (temp != NULL)
		{
			cout << temp->data << endl;
			temp = temp->next;
		}
		cout << endl;
	}
}

//if it is number, move to bottom. if operand, last 2 numbers added to bottom are turned into int and sent to maths() with the operand
void solve()
{
	
	int loc = 0;
	while (!rightArray[loc].empty())
	{
		if (rightArray[loc].find_first_not_of("0123456789") == string::npos)
		{
			push(rightArray[loc]);
			rightArray[loc].erase();
			loc++;
		}
		else
		{
			
			int firstNum = 0;
			int secondNum = 0;
			char c = rightArray[loc][0];
			firstNum = popNum();		
			secondNum = popNum();
			
			
			std::cout << secondNum << " " << c << " " << firstNum << endl;
			push(to_string(maths(firstNum, secondNum, c)));
			rightArray[loc].erase();
			loc++;
			
		}
	}
	
	
}

int maths(int a, int b, char operand) //do correct equation on operand sent
{
	switch (operand)
	{
	case '+': return b + a;
	case '-': return b - a;
	case '*': return b * a;
	case '/': return b / a;
	default: return 0;
	}
}

int main()
{
	std::cout << "Equation to be solved: ";
	//display contents of right array which should be equation
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (!rightArray[i].empty())
		{
			std::cout << rightArray[i];
		}
	}
	std::cout << endl;
	std::cout << "Doing first shunt" << endl;

	initShunt();

	leftToRight();
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (!rightArray[i].empty())
		{
			std::cout << rightArray[i];
		}
	}
	std::cout << endl;
	solve();

	//final number remaining is the solution
	cout << "Equation solution = "; 
	displayStack();
}
