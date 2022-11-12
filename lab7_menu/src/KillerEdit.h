/*
 * KillerEdit.h
 *
 *  Created on: 14 Oct 2022
 *      Author: Manish
 */

#ifndef KILLEREDIT_H_
#define KILLEREDIT_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include "wwdt_15xx.h"
#include <string>

class KillerEdit: public PropertyEdit {
public:
	KillerEdit(LiquidCrystal *lcd_, std::string editTitle, int minVal, int maxVal);
	virtual ~KillerEdit();
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
	LPC_WWDT_T *pWWDT;
};

#endif /* KILLEREDIT_H_ */
