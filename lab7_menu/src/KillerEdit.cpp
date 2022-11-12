/*
 * KillerEdit.cpp
 *
 *  Created on: 14 Oct 2022
 *      Author: Manish
 */

#include "KillerEdit.h"

#include <cstdio>

KillerEdit::KillerEdit(LiquidCrystal *lcd_, std::string editTitle, int minVal, int maxVal): lcd(lcd_), title(editTitle), minVal(minVal), maxVal(maxVal) {
	value = 0;
	edit = 0;
	focus = false;

}

KillerEdit::~KillerEdit() {
}

void KillerEdit::increment() {
	if(edit < maxVal) edit++;
}

void KillerEdit::decrement() {
	if(edit > minVal) edit--;
}

void KillerEdit::accept() {
	save();
}

void KillerEdit::cancel() {
	edit = value;
}


void KillerEdit::setFocus(bool focus) {
	this->focus = focus;
}

bool KillerEdit::getFocus() {
	return this->focus;
}

void KillerEdit::display() {
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


void KillerEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
	pWWDT->FEED = 0xAA;
	pWWDT->FEED = 0x1D; //invalid feed sequence
}


int KillerEdit::getValue() {
	return value;
}

void KillerEdit::setValue(int value) {
	if(value <= maxVal && value >= minVal){
		edit = value;
		save();
	}
}
