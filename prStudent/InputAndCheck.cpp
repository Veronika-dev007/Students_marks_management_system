#include "InputAndCheck.h";

bool checkNameFormat(string str) {//важны заглавные буквы в инициалах
	int point = 0;
	int countUp = 0;
	int countSpace = 0;
	if (str.empty()) return false;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			countSpace++;
			continue;
		}
		if (str[i] == '.') {
			point++;
			if (point == 3) return false;
			continue;
		}
		if ((str[i] < 'А' || str[i]>'я') && str[i]!='Ё' && str[i] != 'ё')
			return false;
		if ((str[i] >= 'А' && str[i] <= 'Я') || str[i] == 'Ё') {
			countUp++;
			if (countUp == 4) return false;
		}
	}
	if (point < 2) return false;
	if (countUp < 3) return false;
	if (countSpace != 1) return false;
	return true;
}

bool checkName(string str) {
	if (str.empty()) return false;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '.' || str[i]==' ') continue;
		if ((str[i] < 'А' || str[i]>'я') && str[i] != 'Ё' && str[i] != 'ё')
			return false;
	}
	return true;
}

bool checkNumber(string str) {
	if (str.length() != 5) return false;
	if ((str[4] < 'А' || str[4]>'Я') && str[4]!='Ё') return false;
	for (int i = 0; i < str.length() - 1; i++)
		if (!isdigit(str[i]))
			return false;
	return true;
}

bool checkMarks(string str) {
	if (str.length() != 5) return false;
	for (int i = 0; i < str.length(); i++)
		if (str[i] < 49 || str[i] > 53)
			return false;
	return true;
}

int getIntVariable(string s) {
	int n;
	cout << s;
	cin >> n;
	while (cin.fail() || cin.get() != '\n') {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Некорректный ввод." << s;
		cin >> n;
	}
	return n;
}

string getInfo(string str, int n) {
	string s;
	cout << "Введите " << str << " студента: ";
	while (true) {
		switch (n) {
		case 1:
			getline(cin >> ws, s);//очищаем начальные пробелы
			formatString(s);
			if (checkName(s)) return s;
			cout << "Не корректный ввод. Инициалы вводите через пробел " << endl;
			break;
		case 2:
			cin >> s;
			if (checkNumber(s)) return s;
			cout << "Не корректный ввод. Формат номера группы: 1234A" << endl;
			break;
		case 3:
			cin >> s;
			if (checkMarks(s)) return s;
			cout << "Не корректный ввод. Формат успеваимости: цифры от 1 до 5, вводить без пробелов" << endl;
			break;
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Повторите ввод: ";
	}
}

void formatString(string& name) {
	name.erase(name.find_last_not_of(" \t") + 1);//удаляем пробелы в конце
	bool up = false;
	name[0] = toupper(name[0]);
	for (int i = 1; i < name.length(); i++) {
		if (name[i] == ' ') {
			up = true;
			continue;
		}
		if(up) name[i] = toupper(name[i]);
		else name[i] = tolower(name[i]);
	}
}
