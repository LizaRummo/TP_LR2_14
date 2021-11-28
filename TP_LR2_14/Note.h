#pragma once
#include <iostream>
#include <string>

using namespace std;

class Note
{
	string phone;
	string name;
	string date[3];
	string comment;
public:
	Note() :name("not set"), phone("not set"), date{"00","00","0000"}, comment(""){}
	Note(string _name, string _phone, string _day, string _month, string _year, string _comment) :name(_name), phone(_phone), date{ _day, _month, _year }, comment(_comment) {}

	~Note() {}

	void input_note();
	void output_note_by_block();
	void output_note_by_table();

	string getName() { return name; }
	string getPhone() { return phone; }
	string getDay() { return date[0]; }
	string getMonth() { return date[1]; }
	string getYear() { return date[2]; }
	string getComment() { return comment; }

	void setName(string _name) { this->name = _name; }
	void setPhone(string _phone) { this->phone = _phone; }
	void setDay(string _day) { this->date[0] = _day; }
	void setMonth(string _month) { this->date[1] = _month; }
	void setYear(string _year) { this->date[2] = _year; }
	void setComment(string _comment) { this->comment = _comment; }
};