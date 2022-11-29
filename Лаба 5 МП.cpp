#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <regex>
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

                if (inp[2] != '.')
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

    void objoutput()
    {
        cout << date << " ";
        cout << press1 << " ";
        cout << press2 << " ";
        cout << press3 << " ";
    }

    void objFoutput(ofstream &file)
    {
        file << date << " ";
        file << press1 << " ";
        file << press2 << " ";
        file << press3 << " ";
    }

    void averageoutput()
    {
        cout << average << " ";
    }

    void averageFoutput(ofstream &file)
    {
        file << average << " ";
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
                return inp[0];
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
                return inp[0];
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
    file.open("C:\\Users\\artem\\OneDrive\\Рабочий стол\\Лаба 5 МП записываем.txt"); // открываем файл для записи

    if (file.is_open())  // Проверка отрылся файл или нет
        cout << "\nВсе хорошо! Файл открыт!" << endl;
    else 
    {
        cout << "\nФайл не открыт!" << endl;
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
        file << proc[i];
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


int main()
{
    setlocale(LC_ALL, "ru");
    setlocale(LC_NUMERIC, "eng");

    int n;
    vector<tirepressure> obj;
    vector<double> proc;

    cout << "\nВведите f, если хотите прочитать из файла, или i, если хотите ввести вручную!" << endl;
    char v = check_f_i();


    if (v == 'f')  // ЧТЕНИЕ ИЗ ФАЙЛА
    {
        ifstream file;
        file.open("C:\\Users\\artem\\OneDrive\\Рабочий стол\\Лаба 5 МП читаем.txt");

        if (file.is_open())  // Проверка отрылся файл или нет
            cout << "\nВсе хорошо! Файл открыт!" << endl;
        else
        {
            cout << "\nФайл не открыт!" << endl;
            throw runtime_error("\nЧто то пошло не так!\n");
        }

        while (true)
        {
            tirepressure c;
            file >> c;
            obj.push_back(c);

            if (file.eof())
            {
                break;
            }
        }

        for (int i = 0; i < obj.size(); i++)
        {
            proc.push_back(obj[i].averagepressure());
        }

    }
    else if (v == 'i')  // РУЧНОЙ ВВОД
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


    cout << "\nВведите r, если хотите записать в файл, или c, если хотите вывести в консоль!" << endl;
    char ans = check_r_c();

    if (ans == 'r')
    {
        try
        {
            fOutput(obj, proc);
        }
        catch(runtime_error& g)
        {
            cout << g.what() << endl;
        }

    }
    else if (ans == 'c')
    {
        consOutput(obj, proc);
    }
    



}

