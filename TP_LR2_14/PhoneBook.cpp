#include <fstream>
#include "PhoneBook.h"

string in(string str);
string checkNames(string input);
string checkNumber(string input);
string checkPhone(string input);
bool correctDate(string _day, string _month, string _year);
int selection(int first, int last);

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
}
PhoneBook& PhoneBook::operator-(int del_numb) {
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
	return *this;
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
	cout << endl << "  [Редактирование данных абонента]" << endl << "    Номер телефона: ";
	getline(cin, _phone);
	getline(cin, _phone);
	_phone = checkNumber(_phone);
	if (_phone != empty)	pointer[edit_numb - 1].setPhone(_phone);
	cout << "    ФИО: ";
	getline(cin, _name);
	_name = checkNames(_name);
	if (_name != empty)	pointer[edit_numb - 1].setName(_name);
	do {
		cout << "    Дата рождения: " << endl << "      День: ";
		getline(cin, _day);
		_day = checkNumber(_day);
		if (_day == empty) _day = pointer[edit_numb - 1].getDay();
		cout << "      Месяц: ";
		getline(cin, _month);
		_month = checkNumber(_month);
		if (_month == empty) _month = pointer[edit_numb - 1].getMonth();
		cout << "      Год: ";
		getline(cin, _year);
		_year = checkNumber(_year);
		if (_year == empty) _year = pointer[numb - 1].getYear();
		if (!correctDate(_day, _month, _year)) { cout << "        Повторите ввод всей даты. Текущее значение: " << _day << "." << _month << "." << _year << endl;}
	} while (!correctDate(_day, _month, _year));
	pointer[edit_numb - 1].setDay(_day);
	pointer[edit_numb - 1].setMonth(_month);
	pointer[edit_numb - 1].setYear(_year);
	cout << "    Комментарий: ";
	getline(cin, _comment);
	if (_comment != empty)	pointer[edit_numb - 1].setComment(_comment);
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
	sort_book();
	cout << endl;
	cout.width(3);
	cout << "№" << "|";
	cout.width(15);
	cout << "Номер" << "|";
	cout << " ФИО" << endl;
	for (int i = 0; i < 40; i++) { cout << "—"; }
	cout << endl;
	for (int i = 0; i <= numb - 1; i++) {
		cout.width(3);
		cout << i + 1 << "|";
		pointer[i].output_note_by_table();
	}
	cout << endl;
}

void PhoneBook::details_note()
{
	if (numb != 0) {
		cout << "Посмотреть подробности записи: " << endl << "  [0 - пропустить]" << endl << "  >> ";
		int number = selection(0, numb);
		while (number != 0) {
			pointer[number - 1].output_note_by_block();
			cout << "Посмотреть подробности другой записи: " << endl << "  [0 - пропустить]" << endl << "  >> ";
			number = selection(0, numb);
		}
	}

}

void PhoneBook::export_book() {
		string file_name;
		cout << endl;
		cout << "Введите имя файла [формат имя.тип]: " << endl << "  ";
		file_name = in(file_name);
		while (1) {
			if (!(file_name.find(".txt") + 1 || file_name.find(".dat") + 1 || file_name.find(".csv") + 1)) { cout << "Неверный тип файла" << endl << "[.txt / .dat / .csv]" << endl; }
			else if (file_name.length() >= 255 || file_name.length() <= 4) { cout << "Недопустимая длина имени файла" << endl; }
			else if ((file_name.find("<") + 1)) { cout << "Недопустимые символы в имени файла" << endl; }
			else break;
			cout << "Введите имя файла [формат имя.тип]: " << endl << "  ";
			getline(cin, file_name);
		}
		ofstream fout(file_name);		// запись в файл
		if (!fout.is_open())										// если файл не открыт
			cout << "Файл не может быть открыт!" << endl;		// сообщить об этом
		else {
			sort_book();
			for (int i = 0; i <= getNumb() - 1; i++) {
				fout << pointer[i].getPhone() << " "
					<< pointer[i].getName() << " "
					<< pointer[i].getDay() << "."
					<< pointer[i].getMonth() << "."
					<< pointer[i].getYear() << " "
					<< pointer[i].getComment() << endl;
			}

			fout.close();
			cout << "Данные сохранены в " << file_name << endl;
		}
}

//void PhoneBook::export_book_2() {
//	string file_name;
//	cout << "Введите имя файла [формат имя.тип]: " << endl << "  ";
//	file_name = in(file_name);
//	while (1) {
//		if (!(file_name.find(".txt") + 1 || file_name.find(".dat") + 1 || file_name.find(".csv") + 1)) { cout << "Неверный тип файла" << endl << "[.txt / .dat / .csv]" << endl; }
//		else if (file_name.length() >= 255 || file_name.length() <= 4) { cout << "Недопустимая длина имени файла" << endl; }
//		else if ((file_name.find("<") + 1)) { cout << "Недопустимые символы в имени файла" << endl; }
//		else break;
//		cout << "Введите имя файла [формат имя.тип]: " << endl << "  ";
//		getline(cin, file_name);
//	}
//	ofstream fout(file_name);		// запись в файл
//	if (!fout.is_open())										// если файл не открыт
//		cout << "Файл не может быть открыт!" << endl;		// сообщить об этом
//	else {
//		sort_book();
//		for (int i = 0; i <= getNumb() - 1; i++) {
//			fout << " - Абонент " << i + 1 << ":" << endl;
//			fout << "  Номер телефона: " << getPointer()[i].getPhone() << endl;
//			fout << "  ФИО: " << getPointer()[i].getName() << endl;
//			fout << "  Дата рождения: " << endl; 
//			fout << "    День: " << getPointer()[i].getDay() << endl;
//			fout << "    Месяц: " << getPointer()[i].getMonth() << endl;
//			fout << "    Год: " << getPointer()[i].getYear() << endl;
//			fout << "  Комментарий: " << getPointer()[i].getComment() << endl;
//		}
//		
//		fout.close();
//		cout << "Данные сохранены в " << file_name << endl;
//	}
//}

void PhoneBook::import_book()
{
	string file_name;
	cout << endl;
	cout << "Введите имя файла [формат имя.тип]: " << endl << "  ";
	file_name = in(file_name);
	while (1) {
		if (!(file_name.find(".txt") + 1 || file_name.find(".dat") + 1 || file_name.find(".csv") + 1)) { cout << "Неверный тип файла" << endl << "[.txt / .dat / .csv]" << endl; }
		else if (file_name.length() >= 255 || file_name.length() <= 4) { cout << "Недопустимая длина имени файла" << endl; }
		else if ((file_name.find("<") + 1)) { cout << "Недопустимые символы в имени файла" << endl; }
		else break;
		cout << "Введите имя файла [формат имя.тип]: " << endl << "  ";
		file_name = in(file_name);
	}
	ifstream fin(file_name);		// вывод из файла

	if (!fin.is_open())										// если файл не открыт
		cout << "Файл не может быть открыт!" << endl;		// сообщить об этом
	else {
		while (!(fin.eof())/*||(buf!=empty)*/) {
			string input, buf, empty = "";
			string findCategory = " - ", findValue = ": ", findSep = ".";
			
			int length = 0;

			getline(fin, buf);

			//getline(fin, buf);
			//getline(fin, buf);
			//cout << buf << endl;
			int pos = 0;
			pos = buf.find(findCategory);
			if (pos > -1) {
				if (buf[pos + 3] == 'А') {
					Note nt;
					int numb = getNumb();
					numb++;
					//string s_name, s_organization, s_topic, s_annotation;
					//cout << "Выступающий " << numb << " найден" << endl;
					for (int i = 0; i < 7; i++) {
						do {
							getline(fin, buf);
						} while (buf.empty());
						length = buf.length();
						//int j = 0;
						pos = buf.find(findValue);
						input.assign(buf, pos + 2, length-(pos + 2));
						if (i == 0) { input = checkPhone(input);  nt.setPhone(input); input.clear(); }
						if (i == 1) { input = checkNames(input); nt.setName(input); input.clear(); }
						if (i == 2) {}
						if (i == 3) { input = checkNumber(input); nt.setDay(input); input.clear(); }
						if (i == 4) { input = checkNumber(input); nt.setMonth(input); input.clear(); }
						if (i == 5) { input = checkNumber(input); nt.setYear(input); input.clear(); }
						if (i == 6) { nt.setComment(input); input.clear(); }
						//cout << endl;
					}
					Note* buf_ptr = getPointer();
					setNumb(numb);
					setPointer(new Note[numb]);
					Note* pointer = getPointer();
					for (int i = 0; i < numb - 1; i++)
					{
						pointer[i] = buf_ptr[i];
					}
					pointer[numb - 1] = nt;
					sort_book();
				}
			}
			else break;
		}
	}
}

void PhoneBook::find_note()
{
	cout << endl;
	cout << "Введите фамилию для поиска: ";
	string surname, to_find;
	int pos = -2, find=0;
	surname = in(surname);
	
	for (int i = 0; i < numb; i++) {
		to_find = pointer[i].getName();
		pos = to_find.find(surname);
		if (pos > -1) {
			pointer[i].output_note_by_block();
			find++;
		}
	}
	if (!find) cout << "Совпадений не найдено" << endl;
}

void PhoneBook::equalize_book()
{
	string correct = "+7", to_edit;
	int find = 0;

	for (int i = 0; i < numb; i++) {
		to_edit = pointer[i].getPhone();
		if (to_edit[0]=='8') {
			to_edit.replace(0, 1, correct);
			pointer[i].setPhone(to_edit);
			find++;
		}
	}
	if (!find) cout << "Ни одна запись не была изменена" << endl;
	else cout << "Изменения применены" << endl;
}

