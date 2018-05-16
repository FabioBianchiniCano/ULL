#pragma once
#include <iostream>
#include <cstdlib>

#include "contador.cpp"

using namespace std;

class DNI{

private:
	int num;
	contador colision;
public:

	static contador count;

	DNI();
	~DNI();

	int get_num();


	bool operator<(const DNI& x);
	bool operator>(const DNI& x);
	bool operator=(const DNI& x);
	bool operator<=(const DNI& x);
};
