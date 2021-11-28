#pragma once
#include "Note.h"

class PhoneBook
{
	int numb;
	Note* pointer;
public:

	PhoneBook() : numb(0), pointer(nullptr) {}
	PhoneBook(int _numb, Note* _pointer) : numb(_numb), pointer(_pointer) {}
	~PhoneBook() { delete[] pointer; }
	PhoneBook& operator=(const PhoneBook&);
	PhoneBook& operator++();
	PhoneBook& operator-(int del_numb);

	void edit_note(int edit_numb);
	void sort_book();
	void output_book();
	void details_note();

	void export_book();
	//void export_book_2();
	void import_book();

	void find_note();
	void equalize_book();

	int getNumb() { return numb; }
	Note* getPointer() { return pointer; }

	void setNumb(int _numb) { this->numb = _numb; }
	void setPointer(Note* _pointer) { this->pointer = _pointer; }
};

