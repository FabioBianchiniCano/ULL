#include "DNI.hpp"

contador DNI::count;

DNI::DNI(){ num = rand() % 89999999 + 10000000; }

DNI::~DNI(){}

int DNI::get_num(){
	return num;
}

bool DNI::operator<(const DNI& x){
	count.incremento();
	return num<x.num;
}
bool DNI::operator>(const DNI& x){
	count.incremento();
	return num>x.num;
}
bool DNI::operator<=(const DNI& x){
	count.incremento();
	return num<=x.num;
}
bool DNI::operator=(const DNI& x){
	count.incremento();
	num = x.num;
}
