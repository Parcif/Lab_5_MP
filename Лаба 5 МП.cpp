#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <regex>
#include <cmath>
using namespace std;


class tirepressure
{
private:
	
	string date;
	double press1;
	double press2;
	double press3;
	double average;

	// Проверка ввода даты
	int days[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	string check_date()
	{
		cout << date;
		string inp;
		int day;
		int month;
		size_t ptr = 0;
		bool state = true;

		while (state)
		{
			getline(cin, inp);
			try
			{
				double check = stod(inp, &ptr);

				if (inp.size() != 5 || inp[2] != '.')
					throw runtime_error("\nError!!! Repeat the input!\n");

				regex regex("\\.");

				vector<string> out(sregex_token_iterator(inp.begin(), inp.end(), regex, -1), sregex_token_iterator());

				/*for (auto& inp : out) {
					std::cout << inp << std::endl;
				}*/

				day = stoi(out[0]);
				month = stoi(out[1]);

				if ((day > 0 && day <= days[month - 1]) && (inp.size() == ptr && inp.size() == 5))
				{
					state = false;
					return inp;
				}
				else
					cout << "\nError! Repeat the input!\n";

			}
			catch (invalid_argument)
			{
				cout << "\nError!!! Repeat the input!\n";
			}
			catch (runtime_error& e)
			{
				cout << e.what() << endl;
			}
		}
	}

	// Проверка ввода давления
	double check_press()
	{
		double res;
		string inp;
		size_t ptr = 0;
		bool state = true;

		while (state)
		{
			getline(cin, inp);
			try
			{
				res = stod(inp, &ptr);
				if ( (res > 0) && (inp.size() == ptr) )
				{
					state = false;
					return res;
				}
				else
					cout << "\nОшибка! Повторите ввод!\n";

			}
			catch (invalid_argument)
			{
				cout << "\nОшибка! Повторите ввод!\n";
			}

		}

	}

public:

	double averagepressure()  // Обработка
	{
		average = (press1 + press2 + press3) / 3; 
		return average;
	}

	tirepressure()  // Конструктор по умолчанию
	{
		date = "0"; press1 = 0; press2 = 0; press3 = 0;
	}

	tirepressure(string d, double pr1, double pr2, double pr3)  // Инициализирующий конструктор
	{
		cout << "\nВведите дату: ";
		d = check_date();
		date = d;

		cout << "Введите давление 1: ";
		pr1 = check_press();
		press1 = pr1;

		cout << "Введите давление 2: ";
		pr2 = check_press();
		press2 = pr2;

		cout << "Введите давление 3: ";
		pr3 = check_press();
		press3 = pr3;

		averagepressure();
	}

	//tirepressure(vector<double> vec)  // Считывающий из файла давление конструктор
	//{
	//	press1 = vec[0];
	//	press2 = vec[1];
	//	press3 = vec[2];
	//}

	tirepressure(string d, vector<double> vec) // Считывающий из файла конструктор
	{
		date = d; 
		press1 = vec[0];
		press2 = vec[1];
		press3 = vec[2];
	}

	friend ostream& operator<<(ostream& os, const tirepressure& point);
	friend istream& operator>>(istream& is, tirepressure& point);
};


int check_n(int min, string strln) // кол - во эл тов
{
	int res;
	string inp;
	bool state = true;
	cout << strln << endl;

	while (state)
	{
		getline(cin, inp);
		try
		{
			res = stoi(inp);
			if (inp.size() == to_string(res).size() && res > min)
			{
				state = false;
			}
			else
				cout << "\nОшибка! Повторите ввод!\n";

		}
		catch (invalid_argument)
		{
			cout << "\nОшибка! Повторите ввод!\n";
		}

	}
	return res;
}


char check_f_i() // f и i
{
	string inp;
	bool state = true;

	while (state)
	{
		getline(cin, inp);
		try
		{
			if (inp.size() == 1 && (inp[0] == 'f' || inp[0] == 'i'))
			{
				state = false;
			}
			else
				cout << "\nОшибка! Повторите ввод!\n";

		}
		catch (invalid_argument)
		{
			cout << "\nОшибка! Повторите ввод!\n";
		}

	}
	return inp[0];
}


char check_r_c() // r и c
{
	string inp;
	bool state = true;

	while (state)
	{
		getline(cin, inp);
		try
		{
			if (inp.size() == 1 && (inp[0] == 'r' || inp[0] == 'c'))
			{
				state = false;
				
			}
			else
				cout << "\nОшибка! Повторите ввод!\n";

		}
		catch (invalid_argument)
		{
			cout << "\nОшибка! Повторите ввод!\n";
		}

	}
	return inp[0];
}


void consOutput(vector<tirepressure>& vec, vector<double>& proc)  // Вывод массивов в консоль
{
	cout << "\nМассив объектов класса: [ ";
	
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i];
	}
	cout << "]" << endl;

	cout << "\nМассив результатов обработки: [ ";
	for (int i = 0; i < proc.size(); i++)
	{
		cout << proc[i] << " ";
	}
	cout << "]" << endl;

}

void fOutput(vector<tirepressure>& vec, vector<double>& proc)  // Вывод массивов в файл
{

	ofstream file; // создаем объект класса ofstream

	file.open("C:\\Users\\artem\\OneDrive\\Рабочий стол\\Лаба 5 МП записываем.txt");

	
	if (file.is_open())  // Проверка отрылся файл или нет
		cout << "\n\nВсе хорошо! Файл открыт! Записано в файл!\n" << endl;
	else
	{
		cout << "\nФайл не открыт!";
		throw runtime_error("\nЧто то пошло не так!\n");
	}

	file << "Массив объектов класса: [ ";
	for (int i = 0; i < vec.size(); i++)
	{
		file << vec[i];
	}
	file << "]" << endl;

	file << "\nМассив результатов обработки: [ ";
	for (int i = 0; i < proc.size(); i++)
	{
		file << proc[i] << " ";
	}
	file << "]" << endl;

	file.close();

}

ostream& operator<<(ostream& os, const tirepressure& point)
{
	os << point.date << " " << point.press1 << " " << point.press2 << " " << point.press3 << " ";
	return os;
}

istream& operator>>(istream& is, tirepressure& point)
{
	is >> point.date >> point.press1 >> point.press2 >> point.press3;
	return is;
}

double check_fileInp(string& str)
{
	double res;
	size_t ptr = 0;
	
	res = stod(str, &ptr);
	if ((res <= 0) && (str.size() != ptr))
	{
		throw runtime_error("\nОшибка! Некорректные данные в файле!\n");
	}
	else
	{
		
		return res;
	}
	
}

void check_fileInp2(string str, vector<double>& digits)
{	
	size_t ptr1 = 0; size_t ptr2 = 0; size_t ptr3 = 0;
	
	double press1;
	double press2;
	double press3;

	bool state = true;

	while (state)
	{
		if (isdigit(str[0]) == 0)									// выбрасываем ошибку если первый элемент не цифра
			throw runtime_error("\nError!!! Repeat the input!\n");

		regex regex("\\ ");

		vector<string> out(sregex_token_iterator(str.begin(), str.end(), regex, -1), sregex_token_iterator());

		/*for (auto& inp : out) {
			std::cout << inp << std::endl;
		}*/

		press1 = stod(out[0], &ptr1);
		press2 = stod(out[1], &ptr2);
		press3 = stod(out[2], &ptr3);

		
		if (((press1 > 0) && (out[0].size() == ptr1) && (press2 > 0) && (out[1].size() == ptr2) && (press3 > 0) && (out[2].size() == ptr3)))
		{
			state = false;
			digits.push_back(press1); 
			digits.push_back(press2); 
			digits.push_back(press3);
		}
		else
		{
			throw runtime_error("\nНекорректные данные в файле!\n");
		}
		
	}

}

void dateFileInput(string& str, string& date)
{
	size_t n = str.find(' ');
	date = (n != string::npos) ? str.substr(0, n) : "";

	str.erase(0, 6);
}

void fInput(vector<tirepressure>& obj, vector<double>& proc)  // Чтение из файла
{
	ifstream file;
	file.open("C:\\Users\\Artem1\\Desktop\\Лаба 5 МП читаем.txt");

	if (file.is_open())  // Проверка отрылся файл или нет
		cout << "\n\nВсе хорошо! Файл открыт!\n" << endl;
	else
	{
		cout << "\nФайл не открыт!";
		throw runtime_error("\nЧто то пошло не так!\n");
	}

	bool state2 = true;
	
	while (state2)
	{
		
		string str;
		getline(file, str);

		// Дата:

		string date;
		dateFileInput(str, date);
		//tirepressure d(date);
		//obj.push_back(d);

		// Давление:

		vector<double> digits;
		check_fileInp2(str, digits);
		tirepressure p(date, digits);
		obj.push_back(p);

		if (file.eof())
		{
			state2 = false;
		}
	}

	for (int i = 0; i < obj.size(); i++)
	{
		proc.push_back(obj[i].averagepressure());
	}

	file.close();	

}

void consInput(int& n, vector<tirepressure>& obj, vector<double>& proc)
{
	n = check_n(0, "\nВведите количество элементов массива: ");

	cout << "\nВведите объекты класса: " << endl;

	for (int i = 0; i < n; i++)
	{
		cout << "\nОбъект класса " << i + 1 << ":" << endl;
		obj.push_back(tirepressure("0", 0, 0, 0));
	}

	for (int i = 0; i < obj.size(); i++)
	{
		proc.push_back(obj[i].averagepressure());
	}

}

int main()
{
	setlocale(LC_ALL, "ru");
	setlocale(LC_NUMERIC, "eng");

	int n;
	vector<tirepressure> obj;
	vector<double> proc;

	cout << "\nВведите f, если хотите прочитать из файла, или i, если хотите ввести вручную!" << endl;
	char v = check_f_i();

	try
	{
		if (v == 'f')  // ЧТЕНИЕ ИЗ ФАЙЛА
		{
			fInput(obj, proc);
		}
		else if (v == 'i')  // РУЧНОЙ ВВОД
		{
			consInput(n, obj, proc);
		}


		cout << "\nВведите r, если хотите записать в файл, или c, если хотите вывести в консоль!" << endl;
		char ans = check_r_c();

		if (ans == 'r')  // ЗАПИСЬ В ФАЙЛ
		{
			fOutput(obj, proc);
		}
		else if (ans == 'c')  // ВЫВОД В КОНСОЛЬ
		{
			consOutput(obj, proc);
		}
	}
	catch (runtime_error& e)
	{
		cout << e.what();
	}
	catch (invalid_argument)
	{
		cout << "\nОшибка! Некорректные данные в файле!\n";
	}

}

