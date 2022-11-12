/*
 * SleepEdit.h
 *
 *  Created on: 14 Oct 2022
 *      Author: Manish
 */

#ifndef SLEEPEDIT_H_
#define SLEEPEDIT_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include <string>
#include "SleepMilli.h"

class SleepEdit: public PropertyEdit {
public:
	SleepEdit(LiquidCrystal *lcd_, std::string editTitle, int minVal, int maxVal);
	virtual ~SleepEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	bool getFocus();
	void display();
	int getValue();
	void setValue(int value);
private:
	void save();
	void displayEditValue();
	LiquidCrystal *lcd;
	std::string title;
	int value;
	int edit;
	bool focus;
	int minVal;
	int maxVal;
	SleepMilli sleep;
};

#endif /* SLEEPEDIT_H_ */
