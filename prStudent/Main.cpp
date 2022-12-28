#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)										
#define new DEBUG_NEW																		
#endif

#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <string>
#include <fstream>

#include "InputAndCheck.h";
#include "Node.h";
#include "Sort.h";
using namespace std;


void sendStudentsToFile(Node* head, string path) {
	if (head == NULL){
		cout << "������ ����!\n";
		return;
	}
	ofstream fout;
	fout.open(path);
	Node* p = head;
	while (p) {
		fout << setw(15) << p->st.name << "|" << setw(8) << p->st.number << "|" << setw(8) << p->st.marks << "|" << endl;
		p = p->next;
	}
	fout.close();
	cout << "���������� ��������� � ���� " << path << endl;
}

void getStudentsFromFile(Node** head, Node** tail, string path) {
	ifstream fin;
	fin.open(path, ios_base::in);
	if (!fin.is_open()) {
		cout << "������ �������� �����!" << endl;
		exit(1);
	}

	int file_size;
	fin.seekg(0, ios::end);
	file_size = fin.tellg();
	if (file_size == 0)
	{
		cout << "���� ����!" << endl;
		fin.close();
		return;
	}
	else {
		fin.seekg(0, ios::beg);
		string name;
		string number;
		string marks;
		int delim = 0;
		while (!fin.eof()) {
			char ch = fin.get();
			if (ch == '\n' || fin.eof()) {
				if (delim == 3) {
					name.insert(name.length()-4, " ");
					if (checkNameFormat(name) && checkNumber(number) && checkMarks(marks)) {
						Student s{ name, number, marks };
						if (checkStudent(*head, s))
							addStudent(head, tail, s);
					}
				}
				delim = 0;
				name = number = marks = "";
				continue;
			}
			if (ch == '|') {
				delim++;
				continue;
			}

			if (ch != ' ') {
				switch (delim) {
				case 0: name.push_back(ch); break;
				case 1: number.push_back(ch); break;
				case 2: marks.push_back(ch); break;
				}
			}
		}
	}
	fin.close();
}

void exitProgram(Node** head, Node** tail) {
	cout << "�������, ��� ������ ����� �� ���������?\n������� ��/���: ";
	string answer;
	cin >> answer;
	while (answer != "��" && answer != "���") {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "������������ ����, ������� ��/���: ";
		cin >> answer;
	}
	if (answer == "��") {
		sendStudentsToFile(*head, "txtres.txt");
		deleteList(head, tail);
		cout << "������ � ���������� ���������" << endl;
		exit(0);
	}
}

void menu() {
	cout << setw(14) << "����" << endl;
	cout << "1. �������� ������� � ������" << endl;
	cout << "2. ������������� ����������" << endl;
	cout << "3. ������� ������� �� ������" << endl;
	cout << "4. ����� �������� � ������" << endl;
	cout << "5. ����������" << endl;
	cout << "6. ����� ������ �� �����" << endl;
	cout << "7. �������� �����" << endl;
	cout << "8. ��������� � �����" << endl;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string path = "info.txt";

	Node* head = NULL, * tail = NULL;
	getStudentsFromFile(&head, &tail, path);
	menu();

	int ch;
	string name, num, marks;
	while (true) {
		ch = getIntVariable("\n������� ����� ����� �� ����: ");
		while (ch > 8 || ch < 1) {
			cout << "����� ����� ��� ����� �� 1 �� 8!" << endl;
			ch = getIntVariable("������� ����� �����: ");
		}
		switch (ch) {
		case 1: {
			cout << "������� ���: ";
			getline(cin >> ws, name);
			name.erase(name.find_last_not_of(" \t\n") + 1);
			while (!checkNameFormat(name)) {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "������������ ����. ������� ���, ������ ������ �.�. : ";
				getline(cin >> ws, name);
				name.erase(name.find_last_not_of(" \t\n") + 1);
			}
			num = getInfo("������", 2);
			marks = getInfo("������������", 3);
			Student s{ name, num, marks };
			if (checkStudent(head, s)) {
				addStudent(&head, &tail, s);
				cout << "������� ��������" << endl;
			}
			else cout << "����� ������� ��� ���� � ������" << endl;
			break;
		}
		case 2:
			name = getInfo("���", 1);
			editStudent(head, name);
			break;
		case 3:
			name = getInfo("���", 1);
			deleteStudent(&head, name);
			break;
		case 4: {
			cout << "1. ����� �� ���\n2. ����� ��������� ������� ������ 4 � 5" << endl;
			int ans;
			ans = getIntVariable("������� ����� ������: ");
			while (ans > 2 || ans < 1) {
				cout << "����� ������ ��� ����� 1 ��� 2!" << endl;
				ans = getIntVariable("������� ����� ������: ");
			}
			switch (ans) {
			case 1:
				name = getInfo("���", 1);
				searchByName(head, name, ans);
				break;
			case 2:
				MergeSort(&head, 2);
				searchBy54Marks(&head);
				break;
			}
			break;
		}
		case 5: {
			cout << "1. ����������� �� �����\n2. ����������� �� ������������" << endl;
			int ans;
			ans = getIntVariable("������� ����� ����������: ");
			while (ans > 2 || ans < 1) {
				cout << "����� ���������� ��� ����� 1 ��� 2!" << endl;
				ans = getIntVariable("������� ����� ����������: ");
			}
			MergeSort(&head, ans);
			if (ans == 2) printListWithAverageScore(head);
			else printList(head);
			break;
		}
		case 6: printList(head); break;
		case 7: system("cls"); menu(); break;
		case 8: exitProgram(&head, &tail); break;
		}
	}
	cout << endl;


	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

	_CrtDumpMemoryLeaks();

}