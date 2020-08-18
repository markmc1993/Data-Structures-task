// HashTable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"

#include <cctype>
#include <iostream>
#include <string>
#include <cstring>

using namespace std; //saves having to write std:: on every cout

#define MAX_SIZE 10 
string hashed_Items[MAX_SIZE];
char unordered_Items1[][MAX_SIZE] = { "aardvark", "bison", "chimera", "dingo", "echidna", "falcon", "gharial", "hippo", "iguana", "tawny owl" }; //array where all should enter into hash table in 1 cycle
char unordered_Items2[][MAX_SIZE] = { "antelope", "aphid", "ameaba", "aardvark", "anaconda", "antelope", "aye-aye", "angelfish", "king crab", "kangaroo" }; //array which will be required to find next available slot to insert into hash table


bool isEmpty() { //boolean function to check if hashedItems is empty
	int count = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		if (hashed_Items[i].empty())
			count++;
	}
	if (count == MAX_SIZE)
		return true;
	else return false;
}

bool isAvailable(int location) //function to check if slot in hash table is empty
{
	return hashed_Items[location].empty();
}

int hashItems(char item[MAX_SIZE]) { //function to check if position of array is free, add string if available or find next available position and add
	bool stored = false;
	int inc = 0;


	char alpha = item[0];
	int num = alpha - 96;

	if (num < MAX_SIZE)
	{

		while (!stored)
		{
			if (num + inc >= 10)
				num -= 10;
			if (isAvailable(num + inc)) {
				hashed_Items[num + inc] = item;
				stored = true;
			}
			else
				inc += 1;
		}
	}
	else
	{
		num = num % MAX_SIZE;
		while (!stored)
		{
			if ((num + inc) >= 10)
				num -= 10;
			if (isAvailable(num + inc)) {
				hashed_Items[num + inc] = item;
				stored = true;
			}
			else
				inc += 1;
		}
	}
	return inc;

}

void clearArray() { //function to remove items from hashedItems if i is not empty
	if (isEmpty())
		cout << "Hash table is empty";
	else
	{
		for (int i = 0; i < MAX_SIZE; i++)
			hashed_Items[i] = "\0";
	}
}
void display() { //display function to check stack and display elements taking a new line for each one
	if (isEmpty())
		cout << "Hash table is empty" << endl;
	else {
		for (int i = 0; i < MAX_SIZE; i++) {
			if (!hashed_Items[i].empty())
			{
				cout << hashed_Items[i] << endl;
			}
			cout << endl;
		}
	}
}

int main()
{
	int steps;
	int totalSteps = 0;

	cout << "Testing Hash Table." << endl;



	display(); //run display to hash table to ensure empty


	for (int i = 0; i < MAX_SIZE; i++) {
		cout << "adding " << unordered_Items1[i] << endl;
		steps = hashItems(unordered_Items1[i]) + 1;
		cout << "item added in " << steps << " steps" << endl;
		totalSteps += steps;
	}
	display(); //display should display items in ordered position in hash table
	cout << "all items added to hash table in " << totalSteps<< " steps" << endl;
	cout << endl;

	cout << "emptying hash table" << endl;
	clearArray();
	cout << endl;


	display(); //run display to hash table to ensure empty
	totalSteps = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		cout << "adding " << unordered_Items2[i] << endl;
		steps = hashItems(unordered_Items2[i]) + 1;
		cout << "item added in " << steps << " steps" << endl;
		totalSteps += steps;
	}

	display(); //display should display items in ordered position in hash table
	cout << "all items added to hash table in " << totalSteps << " steps" << endl;
	cout << endl;

	cout << "emptying hash table" << endl;
	clearArray();

}
