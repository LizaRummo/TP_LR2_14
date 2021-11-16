#include <Windows.h>
//#include <string>
#include <iostream>
#include "PhoneBook.h"

using namespace std;

PhoneBook pb;

//�������� ��� �����, ����������� - � .
string checkNames(string input) {	
	string buf = "", res = "";
	while (true) {
		int length = 0, ctr_err = 0;
		//getline(cin, input);
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
		//getline(cin, input);
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
	while (true) {
		try
		{
			cin >> input;
			if (!(cin.fail() || input < first || input > last)) return input;
			else throw "������ ������������� ����� ����";
		}
		catch (const char*) {
			cin.clear();
			cerr << "������ ������������� ����� ����. ���������� ����" << endl << "> ";
		}
		cin.ignore(32767, '\n');
	}
	return input;
}

void print_menu() {
	//system("cls");
	//statusbar();
	//cout << "������� ����" << endl;
	cout << endl << "�������� ����� ����:" << endl;
	cout << "  1. ��������" << endl;
	cout << "  2. �������" << endl;
	cout << "  3. �������� ������" << endl;
	cout << "  4. ������� ������ ������" << endl;
	cout << "  ---" << endl;
	cout << "  0. ����� �� ���������" << endl;
	cout << "  >> ";
}

void menu() {
	int point;
	while (1) {
		print_menu();
		switch (point = selection(0, 4)) {
		case 1:
		{
			pb.add_note();
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
			cout << "������� ����� �������, ����� ����������..." << endl;
			cin.get(); cin.get();
		}
		break;
		case 3:
		{
			pb.output_book();
			cout << "������������� ������" << endl << "  [0 - ������ ��������������]" << endl << "  >> ";
			int number = selection(0, pb.getNumb());
			if (number != 0) {
				pb.edit_note(number);
				cout << "���������� ������:" << endl;
				pb.output_book();
			}
			else cout << "������ ��������������" << endl;
			cout << "������� ����� �������, ����� ����������..." << endl;
			cin.get(); cin.get();
		}
		break;
		case 4:
		{
			pb.output_book();
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
	cout << "����� ����������!" << endl;
	menu();
	return 0;
}