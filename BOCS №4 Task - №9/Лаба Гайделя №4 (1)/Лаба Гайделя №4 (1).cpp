// Лаба Гайделя №4 (1).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

///////////////ЯВЛЯЕТСЯ ЛИ СИМВОЛ ЛАТИНИЦЕЙ///////////////
bool lat_ar(char alpha) 
{
	return ('a' <= alpha && alpha <= 'z') || ('A' <= alpha && alpha <= 'Z') || ('0' <= alpha && alpha <= '9');
}
//////////////////////////////////////////////////////////

////////////////ЯВЛЯЕТСЯ ЛИ СИМВОЛ РИМСКИМ////////////////
bool rom(char alpha)
{
	return alpha == 'I' || alpha == 'V' || alpha == 'X' || alpha == 'L' || alpha == 'C' || alpha == 'D' || alpha == 'M';
}
//////////////////////////////////////////////////////////

//////////////////ПРОВЕРКА ВВЕДЁННОГО Y_N/////////////////
string check_str(string &y_n) 
{
	while (getline(cin, y_n)) {
		if (y_n == "") {								//Проверка на пустую строку (необходима для getline()),
			continue;									//т. к. при повторном её использовании в потоке остаётся '\n' 
		}
		bool space = true;								//Проверка на то, если пользователь ввёл только пробелы, 
		for (int i = 0; i < y_n.length(); ++i) {		//Если найден "не пробел", то space становится false,
			if (y_n[i] != ' ') {						//значит в слове есть символы и дальше проверять незачем
				space = false;							
				break;									
			}										
		}
		if (space == true) {							//Вывод ошибки при одних пробелах
			cout << "Введены одни пробелы! "
				<< "Введите ответ заново> ";
			continue;
		}
		if (y_n.length() > 1) {							//Если ответ больше одного символа, то выводится ошибка.
			cout << "Ответ должен являться одной буквой. "
				<< "Пожалуйста, введите его ещё раз> ";
			continue;
		}
		else {
			return y_n;
		}
	}
}
//////////////////////////////////////////////////////////

/////////////ПЕРЕВОД РИМСКИХ ЧИСЕЛ В АРАБСКИЕ/////////////
int translate(const string& buff, int rim_start, int rim_end)
{
	int val = 0;
	for (int i = rim_start; i < rim_end; ++i) {

		if (buff[i] == 'M')
			val += 1000;

		if (buff[i] == 'D') {
			if (i + 1 < buff.length() && (buff[i + 1] == 'M'))
				val -= 500;
			else 
				val += 500;
		}

		if (buff[i] == 'C') {
			if (i + 1 < buff.length() && (buff[i + 1] == 'D' || buff[i + 1] == 'M'))
				val -= 100;
			else
				val += 100;
		}

		if (buff[i] == 'L') {
			if (i + 1 < buff.length() && (buff[i + 1] == 'C' || buff[i + 1] == 'D'|| buff[i + 1] == 'M'))
				val -= 50;
			else
				val += 50;
		}

		if (buff[i] == 'X') {
			if (i + 1 < buff.length() && (buff[i + 1] == 'L' || buff[i + 1] == 'C' || buff[i + 1] == 'D'
				|| buff[i + 1] == 'M'))
				val -= 10;
			else
				val += 10;
		}

		if (buff[i] == 'V')
			if (i + 1 < buff.length() && (buff[i + 1] == 'X' || buff[i + 1] == 'L' || buff[i + 1] == 'C' || buff[i + 1] == 'D'
				|| buff[i + 1] == 'M'))
				val -= 5;
			else
				val += 5;

		if (buff[i] == 'I') {
			if (i + 1 < buff.length() && (buff[i + 1] == 'V' || buff[i + 1] == 'X'
				|| buff[i + 1] == 'L' || buff[i + 1] == 'C' || buff[i + 1] == 'D' || buff[i + 1] == 'M'))
				val -= 1;
			else
				val += 1;
		}
	}
	return val;
}
//////////////////////////////////////////////////////////

int main() {
	setlocale(LC_ALL, "rus");
	string y_n, buff, input, edit = "(edited)";		//edited - отредактированный

	while (cout << "Продолжить? (Y || N)> ") {
		y_n = check_str(y_n);

		if (y_n == "Y" || y_n == "y") {
			cout << "Введите имя файла> ";
			getline(cin, input);			//Занесение имя файла в переменную input
			ifstream fin(input);			//Вызов файла для чтения
			if (!fin.is_open()) {		//Проверка на открытие файла
				cout << "Введённый файл не найден.\n";
				continue;
			}

			ofstream fout(edit + input);			//создаётся новый файл с припиской (edited)
			while (getline(fin, buff)){			//Заносим строки и редактируем их
				int k = 0;					//Счётчик k,
				int rim_start, rim_end;		//Индекс первой цифры римского числа, длина римского числа
				bool isrim = true;				//Присутствуют ли в строке римские числа
				while (k < buff.length()) {

					if (!rom(buff[k])) {	//если это не римский символ
						for (; lat_ar(buff[k]) && k < buff.length(); ++k) {
							fout << buff[k];		//заносим символы пока не будет найден символ "не латиницы и не цифры"
						}

						if (k == buff.length()) {	//если символ "не латиницы и не цифры" не найден
							isrim = false;	//не делаем преобразований и рассматриваем новую строку из файла
						}

						else if (k == buff.length() - 1) {	//Если последний символ - символ "не латиницы и не цифры"
							fout << buff[k];		//заносим символ 
							break;					//рассматриваем новую строку
						}

						else if (k + 1 < buff.length()) {		//если после символа "не латиницы и не цифры" есть ещё символы, 
							fout << buff[k];
							++k;							//то увеличиваем к на 1 и запускаем цикл заново
							continue;
						}
					}

					if (rom(buff[k])) {		//Если это римский символ,	
						rim_start = k;					//то записываем индекс начала этого римского числа
						for (; k < buff.length() && lat_ar(buff[k]) && rom(buff[k]); ++k) {}
						
						if (k == buff.length() || !lat_ar(buff[k]))	//Если слово закончилось или найден символ "не латиницы",
							rim_end = k;		//то записываем конец римского числа для редактирования этой части слова

						else {				//Если найден символ, не являющийся римским, 
							for (int i = rim_start; i < k; ++i) {	//то в файл заносятся все символы слова,
								fout << buff[i];			//имеющих индексы от rim_start до "к - 1".
							}							//Затем переходим к следующей итерации цикла while (k < buff.length()),
							continue;					//если "к" всё ещё удовлетворяет условию
						}
					}

					if (isrim) {		//Если в слове содержатся римские числа, то он переводится в арабское число
						fout << translate(buff, rim_start, rim_end);
					}
				}
				fout << '\n';
			}
			fin.close();			//Закрытие файла для чтения
			fout.close();		//Закрытие файла для редактирования
			cout << "Операция завершена успешно.\n";
		}
		else if (y_n == "N" || y_n == "n") {
			return 0;
		}

		else
			cout << "Неверный символ.\n";
	}
}