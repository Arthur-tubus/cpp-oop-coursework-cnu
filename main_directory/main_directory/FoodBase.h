#pragma once
#ifndef BASEDISH_H
#define BASEDISH_H

#include <string>
using namespace std;

class FoodBase
{

public:
	virtual ~FoodBase() = default;

	virtual string get_m_Category() const = 0;
	virtual string get_m_Name() const = 0;
	virtual double get_m_Price() const = 0;
	virtual double get_m_Weight() const = 0;
	virtual int get_m_AvailabilityCount() const = 0;
	virtual int get_m_CookingTime() const = 0;

	virtual void printInfo() const = 0;
};

#endif // !BASEDISH_H
