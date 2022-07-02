
#include "methods.hpp"
int main()
{
	Vector v(10);
	int * buf = new...;
	int x = buf[0];
	//x = v[0] error, НО! можно перегрузить operator[]
	//x = v.at(0) можно но неудобно
	//int x = v.operator[](0) правильная запись, но можно проще:
	//v[0] = 7 -бред тк равносильно v.operator[](0) = 7, решаем это ссылкой
	x = v[0];
	delete[] buf;
}
