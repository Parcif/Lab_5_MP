#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <typeinfo>
#include <typeinfo>

using namespace std;


class tirepressure
{
private:
	
	string date;
	double press1;
	double press2;
	double press3;
	double average;

public:

	double averagepressure()  // Обработка
	{
		average = (press1 + press2 + press3) / 3; 
		return average;
	}

	tirepressure()  // Конструктор по умолчанию
	{
		date = "0"; press1 = 0; press2 = 0; press3 = 0; average = 0;
	}

	friend ostream& operator<<(ostream& os, const tirepressure& point);
	friend istream& operator>>(istream& is, tirepressure& point);
};


char check_f_i() // f и i
{
	string inp;
	bool state = true;

	while (state)
	{
		getline(cin, inp);
		
		if (inp.size() == 1 && (inp[0] == 'f' || inp[0] == 'i'))
		{
			state = false;
		}
		else
			cout << "\nОшибка! Повторите ввод: ";

	}
	return inp[0];
}


string check_dateInput()  // Проверка ввода даты
{
	int days[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
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
			if (inp.size() != 5 || inp[2] != '.')
				throw runtime_error("\nОшибка!!! Повторите ввод: ");

			double check = stod(inp, &ptr);

			regex regex("\\.");

			vector<string> out(sregex_token_iterator(inp.begin(), inp.end(), regex, -1), sregex_token_iterator());

			day = stoi(out[0]);
			month = stoi(out[1]);

			if ((day > 0 && day <= days[month - 1]) && (month > 0 && month <= 12) && (inp.size() == ptr))
			{
				state = false;
			}
			else
				cout << "\nОшибка! Повторите ввод: ";

		}
		catch (runtime_error& e)
		{
			cout << e.what();
		}
		catch (invalid_argument)
		{
			cout << "\nОшибка!!! Повторите ввод: ";
		}
		
	}
	return inp;
}

double check_pressInput()  // Проверка ввода давления
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
			for (int i = 0; i < inp.size(); i++)
			{
				if((inp[i] != '.') && (isdigit(inp[i]) == 0))
					throw runtime_error("\nОшибка!!! Повторите ввод: ");
			}

			res = stod(inp, &ptr);
			if ((inp.size() == ptr) && (inp[0] != '.'))
			{
				state = false;
			}
			else
				cout << "\nОшибка! Повторите ввод: ";

		}
		catch (runtime_error& e)
		{
			cout << e.what();
		}
		catch (invalid_argument)
		{
			cout << "\nОшибка!!! Повторите ввод: ";
		}
		catch (out_of_range)
		{
			cout << "\nО нет, выход за пределы максимально возможного значения!!! Повторите ввод: ";
		}
	}
	return res;
}

void check_dateFileInput(string& str, string& date)
{
	size_t n = str.find(' ');
	date = (n != string::npos) ? str.substr(0, n) : "";

	if (date.size() != 5 || date[2] != '.')
		throw runtime_error("\nНекорректные данные в файле!\n");

	size_t ptr = 0;
	int day;
	int month;
	int days[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };

	double check = stod(date, &ptr);

	regex regex("\\.");

	vector<string> out(sregex_token_iterator(date.begin(), date.end(), regex, -1), sregex_token_iterator());

	day = stoi(out[0]);
	month = stoi(out[1]);

	if ((day <= 0 || day > days[month - 1]) || (month <= 0 || month > 12) || (date.size() != ptr))
	{
		throw runtime_error("\nНекорректные данные в файле!\n");
	}
	else
		str.erase(0, 6);
}

void check_pressureFileInput(string str, vector<double>& digits)
{
	size_t ptr1 = 0; size_t ptr2 = 0; size_t ptr3 = 0;

	double press1;
	double press2;
	double press3;
			
	regex regex("\\ ");

	vector<string> out(sregex_token_iterator(str.begin(), str.end(), regex, -1), sregex_token_iterator());

	if (out.size() != 3)
		throw runtime_error("\nНекорректные данные в файле!\n");

	press1 = stod(out[0], &ptr1);
	press2 = stod(out[1], &ptr2);
	press3 = stod(out[2], &ptr3);

	if ((press1 > 0) && (out[0].size() == ptr1) && (out[0][0] != '.') && (press2 > 0) && (out[1].size() == ptr2) && (out[1][0] != '.') && (press3 > 0) && (out[2].size() == ptr3) && (out[2][0] != '.'))
	{
		digits.push_back(press1);
		digits.push_back(press2);
		digits.push_back(press3);
	}
	else
	{
		throw runtime_error("\nНекорректные данные в файле!\n");
	}

}

istream& operator>>(istream& is, tirepressure& c)  // Перегрузка ввода
{
	if (typeid(is) == typeid(cin))
	{
		cout << "\nВведите дату: ";
		c.date = check_dateInput();

		cout << "Введите давление 1: ";
		c.press1 = check_pressInput();

		cout << "Введите давление 2: ";
		c.press2 = check_pressInput();

		cout << "Введите давление 3: ";
		c.press3 = check_pressInput();
		
	}
	else 
	{
		string str;
		getline(is, str);

		string date;
		check_dateFileInput(str, date);

		vector<double> digits;
		check_pressureFileInput(str, digits);

		c.date = date;
		c.press1 = digits[0];
		c.press2 = digits[1];
		c.press3 = digits[2];
		
	}
	return is;
}


void fInput(vector<tirepressure>& obj, vector<double>& proc)  // Чтение из файла
{
	ifstream file;
	file.open("C:\\Users\\Artem1\\Desktop\\Лаба 5 МП читаем.txt");

	if (file.is_open())  // Проверка отрылся файл или нет
		cout << "\n\nВсе хорошо! Файл открыт!" << endl;
	else
	{
		cout << "\nФайл не открыт!";
		throw runtime_error("\nЧто то пошло не так!\n");
	}

	bool state = true;

	while (state)
	{
		tirepressure e;
		file >> e;  // Перегруженный ввод
		obj.push_back(e);

		if (file.eof())
		{
			state = false;
		}
	}

	file.close();

	for (int i = 0; i < obj.size(); i++)
	{
		proc.push_back(obj[i].averagepressure());
	}

}


int check_n(string str) // кол - во эл тов
{
	cout << str;
	int res;
	string inp;
	bool state = true;

	while (state)
	{
		getline(cin, inp);
		try
		{
			res = stoi(inp);
			if (inp.size() == to_string(res).size() && res > 0)
			{
				state = false;
			}
			else
				cout << "\nОшибка! Повторите ввод: ";

		}
		catch (invalid_argument)
		{
			cout << "\nОшибка! Повторите ввод: ";
		}
		catch (out_of_range)
		{
			cout << "\nО нет, выход за пределы максимально возможного значения!!! Повторите ввод: ";
		}

	}
	return res;
}

void consInput(vector<tirepressure>& obj, vector<double>& proc)
{
	int n = check_n("\nВведите количество элементов массива: ");

	cout << "\nВведите объекты класса: " << endl;

	for (int i = 0; i < n; i++)
	{
		cout << "\nОбъект класса " << i + 1 << ":" << endl;
		tirepressure e;
		cin >> e;	// Перегруженный ввод
		obj.push_back(e);
	}

	for (int i = 0; i < obj.size(); i++)
	{
		proc.push_back(obj[i].averagepressure());
	}

}


char check_r_c() // r и c
{
	string inp;
	bool state = true;

	while (state)
	{
		getline(cin, inp);

		if (inp.size() == 1 && (inp[0] == 'r' || inp[0] == 'c'))
		{
			state = false;
		}
		else
			cout << "\nОшибка! Повторите ввод: ";

	}
	return inp[0];
}


ostream& operator<<(ostream& os, const tirepressure& point)	 // Перегрузка вывода
{
	os << point.date << " " << point.press1 << " " << point.press2 << " " << point.press3 << " ";
	return os;
}

void fOutput(vector<tirepressure> obj, vector<double> proc)  // Вывод массивов в файл
{
	ofstream file; // создаем объект класса ofstream
	file.open("C:\\Users\\Artem1\\Desktop\\Лаба 5 МП записываем.txt");

	if (file.is_open())  // Проверка отрылся файл или нет
		cout << "\n\nВсе хорошо! Файл открыт! Записано в файл!" << endl;
	else
	{
		cout << "\nФайл не открыт!";
		throw runtime_error("\nЧто то пошло не так!\n");
	}

	file << "Массив объектов класса: [ ";
	for (int i = 0; i < obj.size(); i++)
	{
		file << obj[i];	 // перегруженный вывод
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

void consOutput(vector<tirepressure> obj, vector<double> proc)  // Вывод массивов в консоль
{
	cout << "\nМассив объектов класса: [ ";
	
	for (int i = 0; i < obj.size(); i++)
	{
		cout << obj[i];	 // перегруженный вывод
	}
	cout << "]" << endl;

	cout << "\nМассив результатов обработки: [ ";
	for (int i = 0; i < proc.size(); i++)
	{
		cout << proc[i] << " ";
	}
	cout << "]" << endl;

}


int main()
{
	setlocale(LC_ALL, "ru");
	setlocale(LC_NUMERIC, "eng");

	vector<tirepressure> obj;
	vector<double> proc;

	cout << "\nВведите f, если хотите прочитать из файла, или i, если хотите ввести вручную: ";
	char v = check_f_i();

	try
	{
		if (v == 'f')  // ЧТЕНИЕ ИЗ ФАЙЛА
		{
			fInput(obj, proc);
		}
		else if (v == 'i')  // РУЧНОЙ ВВОД
		{
			consInput(obj, proc);
		}


		cout << "\nВведите r, если хотите записать в файл, или c, если хотите вывести в консоль: ";
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
		cout << "\nНекорректные данные в файле!\n";
	}
	catch (out_of_range)
	{
		cout << "\nО нет, выход за пределы максимально возможного значения!!!\n";
	}

}