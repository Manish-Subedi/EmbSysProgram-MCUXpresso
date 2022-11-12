/*
 * DecimalEdit.h
 *
 *  Created on: 13 Oct 2022
 *      Author: Manish
 */

#ifndef DECIMALEDIT_H_
#define DECIMALEDIT_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include <string>
#include <atomic>

class DecimalEdit: public PropertyEdit {
public:
	DecimalEdit(LiquidCrystal *lcd_, std::string editTitle, float minVal, float maxVal, float step);
	virtual ~DecimalEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	bool getFocus();
	void display();
	float getValue();
	void setValue(float value);
	static std::atomic<bool> saved_;
private:
	void save();
	void displayEditValue();
	LiquidCrystal *lcd;
	std::string title;
	float value;
	float edit;
	float minVal;
	float maxVal;
	float step;
	bool focus;
};



#endif /* DECIMALEDIT_H_ */
