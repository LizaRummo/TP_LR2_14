#include "Note.h"

string in(string str);
string checkNames(string input);
string checkNumber(string input);
string checkPhone(string input);
bool correctDate(string _day, string _month, string _year);

//добавить проверки!
void Note::input_note() {
	string _name, _phone, _day, _month, _year, _comment, buf = "";
	cout << endl << "  [Добавление абонента]" << endl;
	do {
		cout << "    Номер телефона РФ *: ";
		_phone = in(_phone);
		phone = checkPhone(_phone);
		int plus = 0;
		
		if (!((phone[0] == '+' && phone[1] == '7' )||(phone[0] == '8'))) 
			cout <<"        Введенный номер не придлежит абоненту РФ" << endl << "        Повторите ввод." << endl;
		else {
			if (phone[0] == '+') plus = 1;
			if (phone.length() > 11 + plus) 
				cout << "        Номер содержит слишком большое колическтво символов для номера РФ" << endl << "        Повторите ввод." << endl;
			else break;
		}

	} while (true);
	cout << "    ФИО *: ";
	_name = in(_name);
	name = checkNames(_name);
	do {
		cout << "    Дата рождения: " << endl << "      День * [ДД]: ";
		_day = in(_day);
		_day = checkNumber(_day);
		cout << "      Месяц * [ММ]: ";
		_month = in(_month);
		_month = checkNumber(_month);
		cout << "      Год * [ГГГГ]: ";
		_year = in(_year);
		_year = checkNumber(_year);
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
	cout << "    Комментарий: ";
	getline(cin, _comment);
	comment = _comment;
}

void Note::output_note_by_block()
{
	cout << "+" << endl;
	cout << "|  Номер телефона: " << phone << endl;
	cout << "|  ФИО: " << name << endl;
	cout << "|  Дата рождения: " << date[0] << "." << date[1] << "." << date[2] << endl;
	cout << "|  Комментарий: " << comment << endl;
	cout << "+" << endl;
}

void Note::output_note_by_table()
{
	cout.width(15);
	cout << phone << "|";
	cout << " " << name << endl;
}
