#pragma once
#include <iostream>
#include <string>

using namespace std;

class Note
{
	string phone;
	string name;
	string date[3];
public:
	Note() :name("not set"), phone("not set"), date{"00","00","0000"} {}
	Note(string _name, string _phone, string _day, string _month, string _year) :name(_name), phone(_phone), date{ _day, _month, _year } {}
	//Note(int _day, int _month, int _year) : date{ _day, _month, _year } {}

	~Note() {}

	void input_note();
	void output_note();

	string getName() { return name; }
	string getPhone() { return phone; }
	//string getDate() { return date[3]; }
	string getDay() { return date[0]; }
	string getMonth() { return date[1]; }
	string getYear() { return date[2]; }

	void setName(string _name) { this->name = _name; }
	void setPhone(string _phone) { this->phone = _phone; }
	//void setDate(int _date[3]) { this->date[3] = _date[3]; }
	void setDay(string _day) { this->date[0] = _day; }
	void setMonth(string _month) { this->date[1] = _month; }
	void setYear(string _year) { this->date[2] = _year; }
};