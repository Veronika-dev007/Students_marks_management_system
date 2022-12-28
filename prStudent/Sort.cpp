#include "Sort.h";

bool compareNumbers(const Student& st1, const Student& st2) {
	string s1 = st1.number;
	string s2 = st2.number;
	s1.pop_back(); s2.pop_back();
	int n1 = stoi(s1);
	int n2 = stoi(s2);
	if (n1 < n2) return true;
	else if (n1 > n2) return false;
	if (st1.number[4] < st2.number[4]) return true;
	return false;
}

float averageScore(const string& str) {
	float value = 0.0;
	for (int i = 0; i < 5; i++)
		value += str[i] - 48;
	return value / 5;
}

bool compareAverageMarks(const Student& st1, const Student& st2) {
	if (averageScore(st1.marks) >= averageScore(st2.marks)) return true;
	return false;
}

void MergeSort(Node** headRef, int ans)
{
	Node* head = *headRef;
	Node* left;
	Node* right;

	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	SplitList(head, &left, &right);

	MergeSort(&left, ans);
	MergeSort(&right, ans);

	switch (ans) {
	case 1: *headRef = SortedMerge(left, right, &compareNumbers); break;
	case 2: *headRef = SortedMerge(left, right, &compareAverageMarks); break;
	}

}

Node* SortedMerge(Node* left, Node* right, bool (*cmp)(const Student&, const Student&))
{
	Node* result = NULL;

	if (left == NULL)
		return (right);
	else if (right == NULL)
		return (left);

	if (cmp(left->st, right->st)) {
		result = left;
		result->next = SortedMerge(left->next, right, cmp);
	}
	else {
		result = right;
		result->next = SortedMerge(left, right->next, cmp);
	}
	return (result);
}

void SplitList(Node* source, Node** frontRef, Node** backRef)
{
	Node* fast = source->next;
	Node* slow = source;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}