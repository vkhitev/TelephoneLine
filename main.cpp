/**
*
* \brief Здесь находится главная функция программы, которая запускает
* моделирование телефонной линии.
*
* \author Хитёв Владислав
*
* \version 8.0
*
* \date 2015/12/23
*
* Contact: vkhitev@gmail.com
*
*/

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "Application.h"
#include <iostream>

void printAuthorInfo()
{
	using std::cout;
	using std::endl;
	cout << "*************************************************" << endl;
	cout << "\"Telephone Line\" project, v.8.0" << endl << endl;
	cout << "Author:" << endl;
	cout << "Khitev Vlad, student of group IS-41" << endl;
	cout << "FICT | ASOIU | NTUU \"KPI\"" << endl << endl;
	cout << "Contacts:" << endl;
	cout << "mail: vkhitev@gmail.com" << endl;
	cout << "tel: (067)882-47-71" << endl;
	cout << "*************************************************" << endl << endl;
}

int main(int argc, char *argv[])
{
	printAuthorInfo();
	try
	{
		std::string firstNumber, secondNumber;
		std::cout << "Enter number of 1st telephone: ";
		std::cin >> firstNumber;
		std::cout << "Enter number of 2nd telephone: ";
		std::cin >> secondNumber;

		auto found1 = std::find_if(cbegin(firstNumber), cend(firstNumber), isalpha);
		auto found2 = std::find_if(cbegin(secondNumber), cend(secondNumber), isalpha);

		if (found1 != cend(firstNumber) || found2 != cend(secondNumber))
		{
			throw std::runtime_error("Wrong input numbers");
		}
		if (found1 == found2)
		{
			throw std::runtime_error("Input numbers are equal");
		}

		Application(firstNumber, secondNumber).run();
	}
	catch (std::exception& e)
	{
		std::cerr << "EXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}