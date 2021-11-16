#include "Note.h"

string checkNames(string input);
string checkNumber(string input);
bool correctDate(string _day, string _month, string _year);

//�������� ��������!
void Note::input_note()
{
	string _name, _phone, _day, _month, _year, buf = "";
	cout << "  [���������� ��������]" << endl << "    ����� ��������: ";
	getline(cin, _phone);
	getline(cin, _phone);
	phone = checkNumber(_phone);
	cout << "    ���: ";
	getline(cin, _name);
	name = checkNames(_name);
	do {
		cout << "    ���� ��������: " << endl << "      ���� [��]: ";
		getline(cin, _day);
		_day = checkNumber(_day);
		cout << "      ����� [��]: ";
		getline(cin, _month);
		_month = checkNumber(_month);
		cout << "      ��� [����]: ";
		getline(cin, _year);
		_year = checkNumber(_year);
		//if (!correctDate(_day, _month, _year)) {}
	} while (!correctDate(_day, _month, _year));
	if (_day.length() < 2) {
		buf += '0';
		buf += _day;
		_day = buf;
		buf = "";
	}
	setDay(_day);
	if (_month.length() < 2) {
		buf += '0';
		buf += _month;
		_month = buf;
		buf = "";
	}
	setMonth(_month);
	setYear(_year);
}

void Note::output_note()
{
	cout << "  ����� ��������: " << phone << endl;
	cout << "  ���: " << name << endl;
	cout << "  ���� ��������: " << date[0] << "." << date[1] << "." << date[2] << endl;
}
