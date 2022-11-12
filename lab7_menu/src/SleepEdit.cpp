/*
 * SleepEdit.cpp
 *
 *  Created on: 14 Oct 2022
 *      Author: Manish
 */

#include "SleepEdit.h"
#include <cstdio>

SleepEdit::SleepEdit(LiquidCrystal *lcd_, std::string editTitle, int minVal, int maxVal): lcd(lcd_), title(editTitle), minVal(minVal), maxVal(maxVal) {
	value = 0;
	edit = 0;
	focus = false;
}

SleepEdit::~SleepEdit() {
}

void SleepEdit::increment() {
	if(edit < maxVal) edit++;
}

void SleepEdit::decrement() {
	if(edit > minVal) edit--;
}

void SleepEdit::accept() {
	save();
}

void SleepEdit::cancel() {
	edit = value;
}


void SleepEdit::setFocus(bool focus) {
	this->focus = focus;
}

bool SleepEdit::getFocus() {
	return this->focus;
}

void SleepEdit::display() {
	lcd->clear();
	lcd->setCursor(0,0);
	lcd->print(title);
	lcd->setCursor(0,1);
	char s[17];
	if(focus) {
		snprintf(s, 17, "     [%4d]     ", edit);
	}
	else {
		snprintf(s, 17, "      %4d      ", edit);
	}
	lcd->print(s);
}


void SleepEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
	sleep.Sleep(10000);
}


int SleepEdit::getValue() {
	return value;
}

void SleepEdit::setValue(int value) {
	if(value <= maxVal && value >= minVal){
		edit = value;
		save();

	}
}
