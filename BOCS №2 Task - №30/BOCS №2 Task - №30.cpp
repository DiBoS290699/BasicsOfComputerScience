// ������������ ������ �2 (������� ������� 30 �������)
//#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

//-------------------------------------------------------------------------------------------------------------------------
/*����� ��������� ������� ��� �������� ������� �� ������ �����*/
string space (string m)                 
{
    for (int i = 0; i < m.length(); i++)    //��������� �� ������� ������� ������
    {
        char space = ' ';               
        if (m[i] == space)          //������������ ������� � �������� ���
        {
            m.erase (i,1);          //erase ������� ��������� ���������� ���������, ������� � i-��� ��������
            i--;                //����� ������ ����� �� 1 ������, ������������� ��������� ������� �� �������
        }
    }
     return m;
}

//-------------------------------------------------------------------------------------------------------------------------
/*������ ������� ��������� �������� ������ �� ������������ ����,
 ������� ��������, ����, ������������ ��������*/
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

    while (cout << exit) {     //������������ ����������� ����, ����� �� ������� ����� ����� 'n'
        getline (cin,yas_no);   //getline ������ ���� �����, ������� �������, ������ ��� � ��������� ���������� 
        string m = yas_no;
            if (space (m) == "Y" || space (m) == "y") {           
                cout << "Input an operation (+/-/*//)> ";
        
                while (getline (cin,operation)) {       //�������� ��������� ������� ��������
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
            else if (space (m) == "N" || space (m) == "n") {    //����� �� ���������
                return 0;
            }
            else  {
                cout << "Wrong symbol!" << endl;
			    continue;
            }
            cin.ignore();
        /*cin.ignore ������������ ��� ������������� �������� ������, 
        ������� ������� ����� ���������� getline, 
        ������� ��������� � ��������� � ���������� ��� �������� ������� �� �������� ������, 
        � ���������� � ������ ������� ���� �������*/
    }
}