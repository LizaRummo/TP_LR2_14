#include "PhoneBook.h"

string checkNames(string input);
string checkNumber(string input);
bool correctDate(string _day, string _month, string _year);

PhoneBook& PhoneBook::operator=(const PhoneBook& PB) {
	if (this == &PB) return *this;

	numb = PB.numb;

	delete[] pointer;
	pointer = new Note[PB.numb];
	numb = PB.numb;
	for (int i = 0; i < PB.numb; i++)
		pointer[i] = PB.pointer[i];

	return *this;
}

PhoneBook& PhoneBook::operator++()
{
	Note nt;
	nt.input_note();
	Note* buf = pointer;
	numb++;

	pointer = new Note[numb];
	for (int i = 0; i < numb - 1; i++)
	{
		pointer[i] = buf[i];
	}
	pointer[numb - 1] = nt;
	return *this;
	// TODO: вставьте здесь оператор return
}

void PhoneBook::add_note() {
	Note nt;
	nt.input_note();
	Note* buf = pointer;
	numb++;

	pointer = new Note[numb];
	for (int i = 0; i < numb - 1; i++)
	{
		pointer[i] = buf[i];
	}
	pointer[numb - 1] = nt;
}

void PhoneBook::del_note(int del_numb) {
	Note* s_buf;
	s_buf = new Note[numb];
	for (int i = 0; i < numb; i++)
	{
		s_buf[i] = pointer[i];
	}
	if (numb != 0) {
		pointer = new Note[numb - 1];
		for (int j = 0; j < numb - 1; j++)
		{
			if (j < del_numb - 1) pointer[j] = s_buf[j];
			else pointer[j] = s_buf[j + 1];
		}
		numb--;
	}
}

void PhoneBook::edit_note(int edit_numb) {
	string _name, _phone, _day, _month, _year, _comment, empty = "";
	cout << "  [Редактирование данных абонента]" << endl << "    Номер телефона: ";
	getline(cin, _phone);
	getline(cin, _phone);
	_phone = checkNumber(_phone);
	if (_phone != empty)	pointer[numb - 1].setPhone(_phone);
	cout << "    ФИО: ";
	getline(cin, _name);
	_name = checkNames(_name);
	if (_name != empty)	pointer[numb - 1].setName(_name);
	do {
		cout << "    Дата рождения: " << endl << "      День: ";
		getline(cin, _day);
		_day = checkNumber(_day);
		if (_day == empty) _day = pointer[numb - 1].getDay();
		cout << "      Месяц: ";
		getline(cin, _month);
		_month = checkNumber(_month);
		if (_month == empty) _month = pointer[numb - 1].getMonth();
		cout << "      Год: ";
		getline(cin, _year);
		_year = checkNumber(_year);
		if (_year == empty) _year = pointer[numb - 1].getYear();
		if (!correctDate(_day, _month, _year)) { cout << "        Повторите ввод всей даты. Текущее значение: " << _day << "." << _month << "." << _year << endl;}
	} while (!correctDate(_day, _month, _year));
	pointer[numb - 1].setDay(_day);
	pointer[numb - 1].setMonth(_month);
	pointer[numb - 1].setYear(_year);
	cout << "    Комментарий: ";
	getline(cin, _comment);
	_comment = checkNames(_comment);
	if (_comment != empty)	pointer[numb - 1].setComment(_comment);
}

void PhoneBook::sort_book() {
	Note buf;
	for (int i = 0; i < numb; i++) {
		for (int j = i + 1; j < numb; j++) {
			if (pointer[i].getPhone() > pointer[j].getPhone()) {
				buf = pointer[i];
				pointer[i] = pointer[j];
				pointer[j] = buf;
			}
		}
	}
}

void PhoneBook::output_book() {
	if (!numb) cout << "Телефонная книга пуста" << endl;
	else {
		sort_book();
		cout << endl;
		cout.width(3);
		cout << "№" << "|";
		cout.width(15);
		cout << "Номер" << "|";
		cout << " ФИО" << endl;
		for (int i = 0; i <= numb - 1; i++) {
			cout.width(3);
			cout << i + 1 << "|";
			pointer[i].output_note_by_table();
		}
		cout << endl;
	}
}
