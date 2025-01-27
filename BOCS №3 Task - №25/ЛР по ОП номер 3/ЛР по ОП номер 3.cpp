// ЛР по ОП №3.cpp 
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>	//Необходим для sort()
using namespace std;

//////////////////ПРОВЕРКА ВВЕДЁННОГО Y_N/////////////////
string check_str(string &y_n) {
	while (getline(cin, y_n)) {
		if (y_n == "") {								//Проверка на пустую строку (необходима для getline()),
			continue;									//т. к. при повторном её использовании в потоке остаётся '\n' 
		}
		bool space = true;								//Проверка на то,
		for (int i = 0; i < y_n.length(); ++i) {		//если пользователь ввёл
			if (y_n[i] == ' ') {						//только пробелы. 
				continue;								//Если найден "не пробел", то
			}											//переменная space становится false.
			else {										//Если ответ состоит из одних пробелов,
				space = false;							//то space остаётся true.
				break;									//После чего выводится ошибка и
			}											//просьба повторить ввод.
		}
		if (space == true) {
			cout << "Введены одни пробелы! "
				<< "Введите ответ заново> ";
			continue;
		}
		while ((y_n[0] == ' ')							//Пока в начале и в конце стоят пробелы,
			|| (y_n[y_n.length() - 1] == ' ')) {		//они удаляются с помощью erase

			if (y_n[0] == ' ') {
				y_n.erase(0, 1);
			}

			else {
				y_n.erase(y_n.length() - 1, 1);
			}
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

//////////////////ПРОВЕРКА ЦЕЛОГО ЧИСЛА///////////////////
int check_int(int &rows) {								//Проверка на корректность введённых целых чисел.
	while (!(cin >> rows) || (cin.peek() != '\n')) {	//Если тип не совпадает или после правильно введённого числа
		cin.clear();									//стоит несоответсвующий типу символ, то 
		while (cin.get() != '\n') {}					//выводится ошибка и просьба повторить ввод.
		cout << "Некорректно введено целое число, "
			<< "введите его заново> ";
		continue;
	}
	return rows;
}
//////////////////////////////////////////////////////////

//////////////////ВЫВОД МАТРИЦЫ НА ЭКРАН//////////////////
void output(const vector<vector<int>> &matrix) {		//Функция, выводящая на экран каждый элемент матрицы.
	for (int i = 0; i < matrix.size(); ++i) {
		cout << '\n';									//Необходима для разделения строк 
		for (int j = 0; j < matrix[0].size(); ++j) {
			cout << matrix[i][j] << ' ';
		}
	}
}
//////////////////////////////////////////////////////////

int main()
{
	setlocale(LC_CTYPE, "rus");
	while (cout << "Продолжить? (Y/N)> ") {
		string y_n;
		y_n = check_str(y_n);					//проверка введённого y_n
		if (y_n == "Y" || y_n == "y") {

			cout << "Введите количество строк> ";
			int row = 0;
			row = check_int(row);

			if (row == 1) {
				cout << "Для сортировки необходимо более одной строки!\n";
				continue;
			}
			else if (row <= 0) {								//Ошибка при количестве строк меньше 0
				cout << "Некорректное количество строк!\n";
				continue;
			}

			cout << "Введите количество столбцов> ";
			int col = 0;
			col = check_int(col);

			if (col <= 0) {								//Ошибка при количестве столбцов меньше 0
				cout << "Некорректное количество столбцов!\n";
				continue;
			}

			vector<vector<int>> matrix(row, vector<int>(col));
			for (int i = 0; i < row; ++i) {				//матрица rowsXcolumns, rows векторов размерами columns
				for (int j = 0; j < col; ++j) {
					cout << "Введите элемент матрицы #(" << i + 1 << ',' << j + 1 << ")> ";
					int elem = 0;
					elem = check_int(elem);
					matrix[i][j] = elem;
				}
			}
			cout << "Инициализированная матрица:";
			output(matrix);
			cout << "\nСортированная матрица:";
			for (int a = 0; a < row; ++a) {		//количество проходов
				bool count = false;
				for (int i = 0; i < row - 1; ++i) {		//Пробег по каждому вектору и если 
					int j = 0;							//первый элемент данного вектора больше 
					if (matrix[i][j] > matrix[i + 1][j]) {		//соответствующего элемента следующего вектора, 
						swap(matrix[i], matrix[i + 1]);			//то они меняются местами.
						count = true;
					}
					else if (matrix[i][j] == matrix[i + 1][j] && col > 1) {	//Если соответствующие элементы равны,
						while (matrix[i][j] == matrix[i + 1][j]		//то происходит сравнение по второму элементу с 
							&& j < col - 1) {				//обменом местами по тому же принципу.
							++j;							//Это происходит до тех пор, пока соответствующие элементы 
							if (matrix[i][j] > matrix[i + 1][j]) {	//векторов равны.
								swap(matrix[i], matrix[i + 1]);
								count = true;
							}
						}
					}
				}
				if (!count)
					break;
			}
			output(matrix);
			cout << endl;
		}
		else if (y_n == "N" || y_n == "n") {
			return 0;
		}
		else {
			cout << "Неверный символ.\n";
		}
	}
}