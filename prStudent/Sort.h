#pragma once
#include<iostream>
#include"Node.h";
using namespace std;

void MergeSort(Node**, int);
Node* SortedMerge(Node* a, Node* b, bool (*cmp)(const Student&, const Student&));
void SplitList(Node* source, Node** frontRef, Node** backRef);

bool compareNumbers(const Student& st1, const Student& st2);
float averageScore(const string& str);
bool compareAverageMarks(const Student& st1, const Student& st2);


