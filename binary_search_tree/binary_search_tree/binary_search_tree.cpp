// binary search.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <array>
// set up best and worst arrays, counter number to be checked in binary tree and bool for search
int bestArray[31] = { 16,24,20,22,18,17,19,21,23,27,25,26,29,28,30,31,8,4,2,1,3,6,5,7,12,10,9,11,14,13,15 };
int worstArray[31] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 };
int loops;
int checkNum;
bool found;
int maxSteps = 0;

//setup node
struct node {
	int data;
	struct node* left;
	struct node* right;
};

//setup functions
struct node * insert(int, struct node*);
void inorder(struct node* node);
void isInTree(int, struct node* root);

int main()
{
	for (int i = 1; i < 32; i++) {
		loops = 0;
		checkNum = i;
		//create tree
		struct node * tree = nullptr;
		std::cout << "tree = " << tree << std::endl;
		//set tree root to first item of array
		tree = insert(bestArray[0], tree);
		std::cout << "tree = " << tree << std::endl;
		inorder(tree);
		//for loop to insert the rest of the array into the binary tree
		for (int i = 1; i < 31; i++)
		{
			tree = insert(bestArray[i], tree);
		}
		std::cout << "tree = " << tree << std::endl;
		//display tree in order and number of times insert function ran
		inorder(tree);
		std::cout << "Got Here in " << loops << " steps! " << std::endl;

		//search for number specified in tree and display how many steps required to find number
		std::cout << "searching for " << checkNum << " in binary tree." << std::endl;
		loops = 0;
		isInTree(checkNum, tree);
		if (found)
		{
			if (loops > maxSteps)
				maxSteps = loops;
			std::cout << "Number " << checkNum << " is in tree, found in " << loops << " steps." << std::endl;
		}
		else
		{
			std::cout << "Number is not in tree" << std::endl;
		}
	}
	std::cout << "maximum number of steps taken in number search: " << maxSteps << std::endl;
}

//add numbers to tree in next nullptr depending on number in relation to surrounding numbers
struct node * insert(int data, struct node* node)
{
	loops++;
	struct node* newnode;
	std::cout << "started insert node = " << node << std::endl;
	if (node == nullptr)
	{
		std::cout << "new node branch " << std::endl;
		newnode = new(struct node);
		newnode->data = data;
		newnode->left = nullptr;
		newnode->right = nullptr;
		return (newnode);
	}
	else
	{
		std::cout << "started descent node = " << node << std::endl;
		if (data > node->data)
			node->right = insert(data, node->right);
		else
			node->left = insert(data, node->left);
		return node;
	}
}

//function to display the tree in numerical order
void inorder(struct node* node)
{
	if (node->left != nullptr)
		inorder(node->left);
	std::cout << node->data << std::endl;
	if (node->right != nullptr)
		inorder(node->right);
}

//function to check from root of tree to find if number is in tree
void isInTree(int searchNum, struct node* root)
{
	loops++;
	if (searchNum > root->data) {
		if (root->right != nullptr)
			isInTree(searchNum, root->right);
		else found = false;
	}
	else if (searchNum < root->data) {
		if (root->left != nullptr)
			isInTree(searchNum, root->left);
		else found = false;
	}
	else
		found = true;


}
