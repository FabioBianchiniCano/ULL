#pragma once

#include <iostream>
#include <climits>

using namespace std;

class contador{

private:
	unsigned int cont;
	int max, min, acc;

public:

	contador();
	~contador();

	void incremento();
	void reset_estadistica();
	void reset();
	int get();
	int get_acc();
	void imprimir_estadistica(int vec);

};
