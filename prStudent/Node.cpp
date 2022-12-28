#include "Node.h";
#include "Sort.h";
#include "InputAndCheck.h";

unsigned int ID = 0;

void deleteList(Node** head, Node** tail) {
	if (*head == NULL)
		return;
	Node* p = *head;
	Node* p1;
	while (p) {
		p1 = p;
		p = p->next;
		delete p1;
	}
	*head = *tail = NULL;
}

bool checkStudent(Node* head, Student& s) {
	Node* p = head;
	while (p) {
		if (p->st.name == s.name && p->st.number == s.number && p->st.marks == s.marks)
			return false;
		p = p->next;
	}
	return true;
}

void addStudent(Node** head, Node** tail, Student& s) {
	Node* tmp = new Node;
	tmp->st = s;
	tmp->st.id = ++ID;
	tmp->next = NULL;

	if (*head == NULL)
		*head = *tail = tmp;
	else {
		(*tail)->next = tmp;
		*tail = (*tail)->next;
	}
}

int searchByName(Node* head, string name, int& id) {
	if (head == NULL) {
		cout << "Список пуст!" << endl;
		return -1;
	}
	int count = 0;
	Node* p = head;
	while (p) {
		if ((p->st.name).find(name) != string::npos) {
			cout << "Номер: " <<setw(3)<< p->st.id << ", ФИО: " << p->st.name << ", Группа: " << p->st.number << ", Успеваемость: " << p->st.marks << endl;
			count++;
			if (count == 1) id = p->st.id;
		}
		p = p->next;
	}
	if (!count) {
		cout << "Студента с таким ФИО в списке нет" << endl;
		return 0;
	}
	return count;
}

bool contains5and4(string str) {
	for (int i = 0; i < str.length(); i++)
		if (str[i] != '5' && str[i] != '4')
			return false;
	return true;
}

void searchBy54Marks(Node** head) {
	cout << setw(15) << "ФИО" << "|" << setw(10) << "ГРУППА" << "|" << setw(15) << "УСПЕВАЕМОСТЬ" << "|" << endl;
	Node* p = *head;
	bool flag = false;
	while (p) {
		if (contains5and4(p->st.marks)) {
			cout << setw(15) << p->st.name << "|" << setw(10) << p->st.number << "|" << setw(15) << p->st.marks << "|" << endl;
			flag = true;
		}
		p = p->next;
	}
	if (!flag) cout << "В списке нет студентов, у которых оценки 4 и 5! ";
}

void deleteStudent(Node** head, string name) {
	int id;
	int count = searchByName(*head, name, id);
	if (count == 0 || count == -1) return;
	else if (count > 1) id = getIntVariable("Введите номер студента для удаления: ");

	Node* p = *head;
	if (p == *head && p->st.id == id) {
		*head = p->next;
		delete p;
	}
	else {
		Node* next_p = p->next;
		while (next_p) {
			if (next_p->st.id == id) {
				p->next = next_p->next;
				delete next_p;
				break;
			}
			p = next_p;
			next_p = next_p->next;
		}
	}
	cout << "Запись удалена" << endl;
}

void printList(Node* head) {
	cout << setw(15) << "ФИО" << "|" << setw(10) << "ГРУППА" << "|" << setw(13) << "УСПЕВАЕМОСТЬ" << "|" << endl;
	Node* p = head;
	while (p != NULL) {
		cout << setw(15) << p->st.name << "|" << setw(10) << p->st.number << "|" << setw(13) << p->st.marks << "|" << endl;
		p = p->next;
	}
}

void printListWithAverageScore(Node* head) {
	cout << setw(15) << "ФИО" << "|" << setw(10) << "ГРУППА" << "|" << setw(13) << "УСПЕВАЕМОСТЬ" << "|"<< setw(9) << "CР. БАЛЛ" << "|" << endl;
	Node* p = head;
	while (p != NULL) {
		cout << setw(15) << p->st.name << "|" << setw(10) << p->st.number << "|" << setw(13) << p->st.marks << "|" << setw(9) << setprecision(1) << fixed<< averageScore(p->st.marks)<< "|"<<  endl;
		p = p->next;
	}
}

void editStudent(Node* head, string name) {
	int id;
	int count = searchByName(head, name, id);
	if (count == 0 || count == -1) return;
	else if (count > 1) id = getIntVariable("Введите номер студента для редоктирования: ");

	Node* p = head;
	while (p) {
		if (p->st.id == id) break;
		p = p->next;
	}
	Student s{ p->st.name, p->st.number, p->st.marks};
	int ans = getIntVariable("Выбирете номер поля для редакции:\n1. ФИО\n2. Группа\n3. Успеваемость\n");
	switch (ans) {
	case 1: {
		cout << "Введите ФИО: ";
		getline(cin >> ws, name);//
		name.erase(name.find_last_not_of(" \t\n") + 1);//erase(pos) стираеет все символы после pos, find_last_not_of(" \t\n") Он ищет в строке первый символ, начиная с конца строки, который не соответствует ни одному из символов, указанных в его аргументах.
		while (!checkNameFormat(name)) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "Неуорректный ввод. Введите ФИО, формат Иванов И.И. : ";
			getline(cin >> ws, name);
			name.erase(name.find_last_not_of(" \t\n") + 1);
		}
		s.name = name;
		if (checkStudent(head, s)) {
			p->st.name = name;
			cout << "Изменеия добавлены" << endl;
		}
		else cout << "Изменение невозможно! Такой студент уже есть в списке" << endl;
		break;
	}
	case 2: {
		string num = getInfo("группу", 2);
		s.number = num;
		if (checkStudent(head, s)) {
			p->st.number = num;
			cout << "Изменеия добавлены" << endl;
		}
		else cout << "Изменение невозможно! Такой студент уже есть в списке" << endl;
		break;
	}
	case 3: {
		string marks = getInfo("успеваемость", 3);
		s.marks = marks;
		if (checkStudent(head, s)) {
			p->st.marks = marks;
			cout << "Изменеия добавлены" << endl;
		}
		else cout << "Изменение невозможно! Такой студент уже есть в списке" << endl;
		break;
	}
	}
}
