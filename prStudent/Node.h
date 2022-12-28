#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

struct Student {
	string name, number, marks;
	unsigned int id;
};

struct Node {
	Student st;
	Node* next;
};

extern unsigned int ID;
void deleteList(Node** head, Node** tail);
bool checkStudent(Node* head, Student& s);
void addStudent(Node** head, Node** tail, Student& s);
void deleteStudent(Node** head, string name);
int searchByName(Node* head, string name, int& id);
bool contains5and4(string str);
void searchBy54Marks(Node** head);
void printList(Node* head);
void printListWithAverageScore(Node* head);
void editStudent(Node* head, string name);

