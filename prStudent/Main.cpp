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
		cout << "Список пуст!\n";
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
	cout << "Результаты сохранены в файл " << path << endl;
}

void getStudentsFromFile(Node** head, Node** tail, string path) {
	ifstream fin;
	fin.open(path, ios_base::in);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		exit(1);
	}

	int file_size;
	fin.seekg(0, ios::end);
	file_size = fin.tellg();
	if (file_size == 0)
	{
		cout << "Файл пуст!" << endl;
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
	cout << "Уверены, что хотите выйти из программы?\nВведите да/нет: ";
	string answer;
	cin >> answer;
	while (answer != "да" && answer != "нет") {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Некорректный ввод, введите да/нет: ";
		cin >> answer;
	}
	if (answer == "да") {
		sendStudentsToFile(*head, "txtres.txt");
		deleteList(head, tail);
		cout << "Работа с программой завершена" << endl;
		exit(0);
	}
}

void menu() {
	cout << setw(14) << "МЕНЮ" << endl;
	cout << "1. Добавить элемент в список" << endl;
	cout << "2. Редактировать информацию" << endl;
	cout << "3. Удалить элемент из списка" << endl;
	cout << "4. Поиск элемента в списке" << endl;
	cout << "5. Сортировка" << endl;
	cout << "6. Вывод списка на экран" << endl;
	cout << "7. Очистить экран" << endl;
	cout << "8. Сохранить и выйти" << endl;
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
		ch = getIntVariable("\nВведите номер опции из меню: ");
		while (ch > 8 || ch < 1) {
			cout << "Номер опции это число от 1 до 8!" << endl;
			ch = getIntVariable("Введите номер опции: ");
		}
		switch (ch) {
		case 1: {
			cout << "Введите ФИО: ";
			getline(cin >> ws, name);
			name.erase(name.find_last_not_of(" \t\n") + 1);
			while (!checkNameFormat(name)) {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Некорректный ввод. Введите ФИО, формат Иванов И.И. : ";
				getline(cin >> ws, name);
				name.erase(name.find_last_not_of(" \t\n") + 1);
			}
			num = getInfo("группу", 2);
			marks = getInfo("успеваемость", 3);
			Student s{ name, num, marks };
			if (checkStudent(head, s)) {
				addStudent(&head, &tail, s);
				cout << "Студент добавлен" << endl;
			}
			else cout << "Такой студент уже есть в списке" << endl;
			break;
		}
		case 2:
			name = getInfo("ФИО", 1);
			editStudent(head, name);
			break;
		case 3:
			name = getInfo("ФИО", 1);
			deleteStudent(&head, name);
			break;
		case 4: {
			cout << "1. Поиск по ФИО\n2. Поиск студентов имеющих оценки 4 и 5" << endl;
			int ans;
			ans = getIntVariable("Введите номер поиска: ");
			while (ans > 2 || ans < 1) {
				cout << "Номер поиска это число 1 или 2!" << endl;
				ans = getIntVariable("Введите номер поиска: ");
			}
			switch (ans) {
			case 1:
				name = getInfo("ФИО", 1);
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
			cout << "1. Сортировать по гуппе\n2. Сортировать по успеваемости" << endl;
			int ans;
			ans = getIntVariable("Введите номер сортировки: ");
			while (ans > 2 || ans < 1) {
				cout << "Номер сортировки это число 1 или 2!" << endl;
				ans = getIntVariable("Введите номер сортировки: ");
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