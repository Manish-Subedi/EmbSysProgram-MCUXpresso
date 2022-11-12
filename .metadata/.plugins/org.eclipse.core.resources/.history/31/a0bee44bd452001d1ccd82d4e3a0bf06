/*
 * DecimalEdit.cpp
 *
 *  Created on: 13 Oct 2022
 *      Author: Manish
 */

#include "DecimalEdit.h"
#include <cstdio>

std::atomic<bool> DecimalEdit::saved_{ false };

DecimalEdit::DecimalEdit(LiquidCrystal *lcd_, std::string editTitle, float minVal, float maxVal, float step): lcd(lcd_), title(editTitle),minVal(minVal),maxVal(maxVal),step(step) {
	value = minVal;
	edit = minVal;
	focus = false;
}

DecimalEdit::~DecimalEdit() {
}

void DecimalEdit::increment() {
	if(edit < maxVal) {
		edit += step;
		if(edit>maxVal) edit = maxVal;
	}
}

void DecimalEdit::decrement() {
	if(edit > minVal) {
		edit -= step;
		if(edit<minVal) edit = minVal;
	}
}

void DecimalEdit::accept() {
	save();
	saved_ = true;
}

void DecimalEdit::cancel() {
	edit = value;
}

void DecimalEdit::setFocus(bool focus) {
	this->focus = focus;
}

bool DecimalEdit::getFocus() {
	return this->focus;
}

void DecimalEdit::display() {
	lcd->clear();
	lcd->setCursor(0,0);
	lcd->print(title);
	lcd->setCursor(0,1);
	char s[17];
	if(focus) {
		snprintf(s, 17, "     [%3.1f]     ", edit);
	}
	else {
		snprintf(s, 17, "      %3.1f      ", edit);
	}
	lcd->print(s);
}

void DecimalEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
}

float DecimalEdit::getValue() {
	return value;
}

void DecimalEdit::setValue(float value) {
	edit = value;
	save();
}
