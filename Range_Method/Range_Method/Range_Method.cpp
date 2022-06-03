// Range_Method.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Сюда прописываем любую ф-ию
double f(double x)
{
	return sin(x);
}

// Наш журнал значений размера шага(h), кол-во шагов(n) и конечного значения Интеграла
void Buffer_h(string str, double h)
{
	string print_Value_h = "Value_h.txt";
	ofstream fin_h;
	fin_h.open(print_Value_h, ofstream::app);
	fin_h << h << '\n';
}

void Buffer_n(string str, int n)
{
	string print_Value_n = "Value_n.txt";
	ofstream fin_n;
	fin_n.open(print_Value_n, ofstream::app);
	fin_n << n << '\n';
}

void Buffer_Integral(string str, double Integral)
{
	string print_Value_Integral = "Value_Integral.txt";
	ofstream fin_Integral;
	fin_Integral.open(print_Value_Integral, ofstream::app);
	fin_Integral << Integral << '\n';
}

int main()
{
	setlocale(LC_ALL, "rus");

	double Integral_prev = 0, // Значение интеграла на предыдущем шаге
		Integral_current,    // Значение интеграла на текущем шаге
		eps,                // Заданная точность
		x0,                // Начальная точка, т.е. А
		xn,               // Конечная точка, т.е. В
		h,               // Шаг интегрирования
		x,			    // Значнеие
		F;			   // Принимаем значение ф-ии f(x)

	int method_p,    // Выбор порядка
		n = 2;      // Начальное число шагов 

	// Задаём начальные данные
	cout << "Начальная точка: "; cin >> x0;
	cout << "Конечная точка: ";  cin >> xn;
	cout << "Допустимая погрешность: "; cin >> eps;
	cout << "Метод порядка 1 или 2: ";  cin >> method_p;

	if (method_p > 2 || method_p < 1)
	{
		cout << "Вы не можете выбрать другой порядок!" << endl;
		return 0;
	}
	cout << endl;

	// Моя программа - Мои правила (если они не перечут условию задачи)
	if (xn < x0)
	{
		cout << "Конечная точка не может быть меньше первоначальной!" << endl;
		return 0;
	}

	// Преобразуем число в строку
	ostringstream ostr_h;
	ostringstream ostr_n;
	ostringstream ostr_Integral;
	
	ostr_n << n;

	string str_h = ostr_h.str();
	string str_n = ostr_n.str();
	string str_Integral = ostr_Integral.str();

	// Формула 1-го порядка прямоугольников. (Левых или Правых)
	while (n > 0)
	{
		Buffer_n(str_n, n);

		h = (xn - x0) / n;
		ostr_h << h;
		Buffer_h(str_h, h);

		x = x0 + method_p * h;
		Integral_current = 0;

		F = f(x);
		Integral_current += F;
		x += h;
		Integral_current *= h;

		if (abs(Integral_current - Integral_prev) <= (pow(2, method_p) - 1) * eps)
		{
			cout << "Конечное число шагов: " << n << endl;
			cout << "Интеграл: " << Integral_current << endl;
			ostr_Integral << Integral_current;
			Buffer_Integral(str_Integral, Integral_current);
			return 0;
		}
		else
		{
			Integral_prev = Integral_current;
			n *= 2;
		}
	}

	system("pause");
	return 0;
}