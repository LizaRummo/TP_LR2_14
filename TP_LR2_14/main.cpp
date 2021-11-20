#include <Windows.h>
//#include <string>
#include <iostream>
#include "PhoneBook.h"

using namespace std;

PhoneBook pb;

string in(string str) {
	do {
		getline(cin, str);
	} while (str.empty());
	return str;
}

//�������� ��� �����, ����������� - � .
string checkNames(string input) {	
	string buf = "", res = "";
	while (true) {
		int length = 0, ctr_err = 0;
		int first_letter = NULL, find_numb = 0;
		length = input.length();
		for (int i = 0; i <= length; i++) {
			if ((input[i] >= '!' && input[i] <= ',') ||
				(input[i] >= '/' && input[i] <= '@') ||
				input[i] == '\0' || input[i] == '\n') {
				if (!find_numb) {
					buf.assign(input, first_letter, i - (res.length() + ctr_err));
					res += buf;
					first_letter = NULL;
					find_numb = 1;
					ctr_err++;
				}
			}
			else
				if (find_numb) {
					first_letter = i;
					find_numb = 0;
				}
		}
		return res;
	}

}
//�������� ��� ����� �����
string checkNumber(string input) {
	string buf = "", res = "";
	while (true) {
		int length = 0, ctr_err = 0;
		int first_numb = NULL, find_err = 0;
		length = input.length();
		for (int i = 0; i <= length; i++) {
			if (input[i] < '0' || input[i] > '9' ||
				input[i] == '\0' || input[i] == '\n') {
				if (!find_err) {
					buf.assign(input, first_numb, i - (res.length() + ctr_err));
					res += buf;
					first_numb = NULL;
					find_err = 1;
					ctr_err++;
				}
			}
			else
				if (find_err) {
					first_numb = i;
					find_err = 0;
				}
		}
		return res;
	}

}
//�������� ��� ����� ������ (�������� ���� +7 ��� 8)
string checkPhone(string input) {
	string buf = "", res = "";
	while (true) {
		int length = 0, ctr_err = 0;
		int first_numb = NULL, find_err = 0;
		length = input.length();
		int plus=0;
		if (input[0] == '+') {
			//res += input[0];
			plus = 1;
		}
		for (int i = 0+plus; i <= length; i++) {
			if (input[i] < '0' || input[i] > '9' ||
				input[i] == '\0' || input[i] == '\n') {
				if (!find_err) {
					buf.assign(input, first_numb, i - (res.length() + ctr_err));
					res += buf;
					first_numb = NULL;
					find_err = 1;
					ctr_err++;
				}
			}
			else
				if (find_err) {
					first_numb = i;
					find_err = 0;
				}
		}
		return res;
	}

}
//�������� ����
bool correctDate(string _day, string _month, string _year) {
	int day, month, year;
	bool leap_year = 0, date_correct = 1;

	day = stoi(_day);
	month = stoi(_month);
	year = stoi(_year);

	if (year % 4 == 0) {leap_year = true;}
	if (day < 1 || day > 31) { cout << "�������� �������� ���" << endl; date_correct = false; }
	if (month < 1 || month > 12) { cout << "�������� �������� ������" << endl; date_correct = false;}
	if (month == 2 && day > 29 && leap_year == true) { cout << "�������� �������� ��� ������� � ���������� ����" << endl; date_correct = false;}
	if (month == 2 && day > 28 && leap_year == false) { cout << "�������� �������� ��� �������" << endl; date_correct = false;}
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30) { cout << "�������� �������� ��� ������ � 30 �����" << endl; date_correct = false;}
	}

	if (date_correct) { return 1; }
	else { cout << "��������� ����" << endl; return 0; }
}

int selection(int first, int last) {
	int input;
	string buf;
	while (true) {
		try
		{
			buf = in(buf);
			buf = checkNumber(buf);
			input = stoi(buf);
			//cin >> input;
			if (!(cin.fail() || input < first || input > last)) 
				return input;
			else throw "������ ������������� ����� ����";
		}
		catch (const char*) {
			cin.clear();
			cerr << "������ ������������� ����� ����. ���������� ����" << endl << "> ";
		}
		//cin.ignore(32767, '\n');
	}
	return input;
}

void statusbar() {
	cout << "PhoneBook"; 
	cout << endl << endl;
	//cout.width(30);
	cout << "���������� �������: ";
	//cout.width(2);
	cout << pb.getNumb() << endl;
	if (pb.getNumb() > 0) {
		Note* ptr = pb.getPointer();
		int nb = pb.getNumb();
		//cout.width(30);
		cout << "��������� ������: ";
		cout.width(15);
		cout << pb.getPointer()[pb.getNumb() - 1].getPhone();
		//cout << ptr[nb - 1].getPhone();
		cout << " " << pb.getPointer()[pb.getNumb() - 1].getName() << endl;
		cout << "...";
	}
	cout << endl;
	for (int i = 0; i < 99; i++) { cout << "�"; }
	cout << endl;
}

void print_menu() {
	system("cls");
	statusbar();
	//cout << "������� ����" << endl;
	cout << endl << "�������� ����� ����:" << endl;
	cout << "  1. ��������" << endl;
	cout << "  2. �������" << endl;
	cout << "  3. �������� ������" << endl;
	cout << "  4. ������� ������ ������" << endl;
	cout << "  ---" << endl;
	cout << "  5. ��������� � ����" << endl;
	cout << "  6. ��������� �� �����" << endl;
	cout << "  ---" << endl;
	cout << "  7. ����� �� �������" << endl;
	cout << "  8. 8 -> +7" << endl;
	cout << "  ---" << endl;
	cout << "  0. ����� �� ���������" << endl;
	cout << "  >> ";
}

void menu() {
	int point;
	while (1) {
		
		print_menu();
		switch (point = selection(0, 8)) {
		case 1:
		{
			++pb;
			//pb.add_note();
			//pb.sort_book();
		}
		break;
		case 2:
		{
			if (pb.getNumb() > 0) {
				pb.output_book();
				cout << "������� ������" << endl << "  >>";
				int del_number = selection(1, pb.getNumb());
				pb.del_note(del_number);
				cout << "���������� ������:" << endl;
				pb.output_book();
			}
			else cout << "������������ ������� ��� ��������" << endl;
			cout << endl;
			cout << "������� ����� �������, ����� ����������..." << endl;
			cin.get(); 
			//cin.get();
		}
		break;
		case 3:
		{
			if (pb.getNumb() > 0) {
				pb.output_book();
				cout << "������������� ������" << endl << "  [0 - ������ ��������������]" << endl << "  >> ";
				int number = selection(0, pb.getNumb());
				if (number != 0) {
					pb.edit_note(number);
					cout << "���������� ������:" << endl;
					pb.output_book();
				}
				else cout << "������ ��������������" << endl;
			}
			else cout << "������������ ������� ��� �������������" << endl;
			cout << endl;
			cout << "������� ����� �������, ����� ����������..." << endl;
			cin.get(); 
			//cin.get();
		}
		break;
		case 4:
		{
			if (pb.getNumb() > 0) {
				pb.output_book();
				pb.details_note();
			}
			else cout << "������������ ������� ��� ������" << endl;
			cout << endl;
			cout << "������� ����� �������, ����� ����������..." << endl;
			cin.get();
		}
		break;
		case 5:
		{
			if (pb.getNumb() > 0) {
				pb.export_book();
			}
			else cout << "������������ ������� ��� ����������" << endl;
			cout << endl;
			cout << "������� ����� �������, ����� ����������..." << endl;
			cin.get();
		}
		break;
		case 6:
		{
			pb.import_book();
		}
		break;
		case 7:
		{
			if (pb.getNumb() > 0) {
				pb.find_note();
			}
			else cout << "������������ ������� ��� ������" << endl;
			cout << endl;
			cout << "������� ����� �������, ����� ����������..." << endl;
			cin.get();
		}
		break;
		case 8:
		{
			if (pb.getNumb() > 0) {
				pb.equalize_book();
			}
			else cout << "������������ �������" << endl;
			cout << endl;
			cout << "������� ����� �������, ����� ����������..." << endl;
			cin.get();
		}
		break;
		case 0:
			exit(0);
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//cout << "����� ����������!" << endl;
	menu();
	return 0;
}