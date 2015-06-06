#include<iostream>

class Test {
	public:
	int date;
	int date2;
	int getDate(){ return date;}
	int getDate2(){ return date2;}
};

int main(){
	int Test::*d = &Test::date;        // Testクラスのメンバー変数へのポインタ
	int (Test::*g)() = &Test::getDate; // Testクラスのメンバー関数へのポインタ

	Test t1;
	Test t2;

	t1.*d = 10;
	int g_date = (t1.*g)();

	d = &Test::date2;
	g = &Test::getDate2;

	std::cout << g_date << std::endl;

	t2.*d = 20;
	g_date = (t2.*g)();

	std::cout << g_date << std::endl;

	return 0;
}