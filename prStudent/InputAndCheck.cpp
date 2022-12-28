#include "InputAndCheck.h";

bool checkNameFormat(string str) {//����� ��������� ����� � ���������
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
		if ((str[i] < '�' || str[i]>'�') && str[i]!='�' && str[i] != '�')
			return false;
		if ((str[i] >= '�' && str[i] <= '�') || str[i] == '�') {
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
		if ((str[i] < '�' || str[i]>'�') && str[i] != '�' && str[i] != '�')
			return false;
	}
	return true;
}

bool checkNumber(string str) {
	if (str.length() != 5) return false;
	if ((str[4] < '�' || str[4]>'�') && str[4]!='�') return false;
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
		cout << "������������ ����." << s;
		cin >> n;
	}
	return n;
}

string getInfo(string str, int n) {
	string s;
	cout << "������� " << str << " ��������: ";
	while (true) {
		switch (n) {
		case 1:
			getline(cin >> ws, s);//������� ��������� �������
			formatString(s);
			if (checkName(s)) return s;
			cout << "�� ���������� ����. �������� ������� ����� ������ " << endl;
			break;
		case 2:
			cin >> s;
			if (checkNumber(s)) return s;
			cout << "�� ���������� ����. ������ ������ ������: 1234A" << endl;
			break;
		case 3:
			cin >> s;
			if (checkMarks(s)) return s;
			cout << "�� ���������� ����. ������ ������������: ����� �� 1 �� 5, ������� ��� ��������" << endl;
			break;
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "��������� ����: ";
	}
}

void formatString(string& name) {
	name.erase(name.find_last_not_of(" \t") + 1);//������� ������� � �����
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
