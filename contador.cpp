#include "contador.hpp"

contador::contador(){
	reset();
	reset_estadistica();
}
contador::~contador(){}

void contador::incremento(){
	cont++;
}

void contador::reset_estadistica(){
	max = 0;
	min = INT_MAX;
	acc = 0;
	cont = 0;
}

void contador::reset(){ cont = 0; }

int contador::get(){
	if (cont < min){ min = cont; }
	if (cont > max){ max = cont; }
	acc += cont;
	return cont;
}

void contador::imprimir_estadistica(int vec){
	int media = acc / vec;
	cout << "MAXIMO | MINIMO | MEDIA" << endl;
	cout << max << "        " << min << "        " << media << endl;
}
int contador::get_acc(){ return acc; }
