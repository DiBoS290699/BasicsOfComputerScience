// Лабораторная работа №2 (Борисов Дмитрий 30 вариант)
//#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

//-------------------------------------------------------------------------------------------------------------------------
/*Здесь расписана функция для удаления пробела из строки ввода*/
string space (string m)                 
{
    for (int i = 0; i < m.length(); i++)    //пробегаем по каждому символу строки
    {
        char space = ' ';               
        if (m[i] == space)          //вылавливание пробела и удаление его
        {
            m.erase (i,1);          //erase удаляет указанное количество элементов, начиная с i-ого элемента
            i--;                //длина строки стала на 1 меньше, следовательно уменьшаем счётчик на единицу
        }
    }
     return m;
}

//-------------------------------------------------------------------------------------------------------------------------
/*Данная функция проверяет введённые данные на соответствие типу,
 наличие пробелов, букв, недопустимых символов*/
double spc_dbl(double operand)
{
    while(!(cin >> operand) || (cin.peek() != '\n') || (cin.peek() == ' ')) {
        cin.clear();
            while(cin.get() != '\n') { }
            cout << "Incorrect operand! Input an operand again> ";
    }
    return operand;
}

//-------------------------------------------------------------------------------------------------------------------------

int main()
{
    double a = 0.0;
    string operation;
    string yas_no;
    string exit = "Continue? (Y/N)> ";
    double operand;

    while (cout << exit) {     //Используется бесконечный цикл, выйти из которго можно нажав 'n'
        getline (cin,yas_no);   //getline читает весь поток, включая пробелы, вводит это в строковую переменную 
        string m = yas_no;
            if (space (m) == "Y" || space (m) == "y") {           
                cout << "Input an operation (+/-/*//)> ";
        
                while (getline (cin,operation)) {       //Проверка введённого символа операции
                    m = operation;
                    if (space (m) == "+") {
                        cout << "Input an operand> ";
                        a += spc_dbl (operand);
                        cout << "Result: " << a << endl;
                        break;
                    }
            
                //--------------------------------------
            
                    if (space (m) == "-") {
                        cout << "Input an operand> ";
                        a -= spc_dbl (operand);
                        cout << "Result: " << a << endl;
                        break;
                    }
            
                //--------------------------------------
            
                    if (space (m) == "*") {
                        cout << "Input an operand> ";          
                        a *= spc_dbl (operand);
                        cout << "Result: " << a << endl;
                        break;
                    }
            
                //--------------------------------------
            
                    if (space (m) == "/") {
                        cout << "Input an operand> ";
                        a /= spc_dbl (operand);
                        cout << "Result: " << a << endl;
                        break;
                    }
            
                //--------------------------------------
            
                    else {
                        cout << "Incorrect operation! Input an operation again> ";
                    }
                }
            }
            else if (space (m) == "N" || space (m) == "n") {    //Выход из программы
                return 0;
            }
            else  {
                cout << "Wrong symbol!" << endl;
			    continue;
            }
            cin.ignore();
        /*cin.ignore используется для игнорирования перевода строки, 
        который остаётся после применения getline, 
        которая считывает и переносит в переменную все введённые символы до перевода строки, 
        в результате в потоке остаётся этот перевод*/
    }
}