// Лаб. работа 3 (2 семестр).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
1.Реализуйте алгоритм бинарного поиска, о котором шла речь на лекции. 
Решите задачу выполнения M (0<M<10000) поисковых запросов над массивом из N (0<N<100000) элементов, 
используя проход по массиву циклом и бинарный поиск. Сравните время работы этих двух подходов.
2.Найдите корень уравнения x^2 - 10 = 0 на отрезке [0; +беск] с точностью до 10^-4 с помощью бисекции.
*/

#include <iostream>
#include <vector>
#include <chrono>
class Timer
{
private:
    // Псевдонимы типов используются для удобного доступа к вложенным типам
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;
    std::chrono::time_point<clock_t> m_beg;
public:
    Timer() : m_beg(clock_t::now())
    {
    }
    void reset()
    {
        m_beg = clock_t::now();
    }
    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};
#define N 100000
using namespace std;
// Перемешивание вектора
void Blender(vector<int>& victor)
{
    srand(time(0));
    int l = victor.size();
    int r = 0;
    for (int i = 0;i < l;i++)
    {
        r = rand() % l;
        if (r != i)
        {
            swap(victor[i], victor[r]);
        }
    }
}
// Функция для вывода вектора после сортировки
void Printer(std::vector<int>& victor)
{
    int l = victor.size();
    if (l <= 2000)
    {
        for (int i = 0;i < l;i++)
        {
            std::cout << victor[i] << " ";
        }
    }
    cout << endl << endl;
}
// Поиск перебором
int Slow_Search(std::vector<int>& victor, int key)
{
    int l = victor.size();
    for (int i = 0;i < l;i++)
    {
        if (victor[i] == key)
        {
            return 1;
        }
    }
    return -1;
}
// Бинарный поиск
int Search(std::vector<int>& victor,int key)
{
    bool flag = false;
    int l = 0; 
    int r = victor.size();
    int m;

    while ((l <= r) && (flag != true)) {
        m = (l + r) / 2; 

        if (victor[m] == key) flag = true; 
        if (victor[m] > key) r = m - 1; 
        else l = m + 1;
    }
    if (flag) return 1;
    else return -1;
}

// Бисекция для x^2 - 10 = 0
double f(double x)
{
    return x*x - 10;
}
double Bisection(double a, double b, double e) // функция, которая ищет ноль на промежутке от a до b
{
    while (b - a > e) // пока не будет достигнута необходимая точность
    {
        if (f(a) * f((b + a) / 2) == 0)
            break;
        else if (f(a) * f((b + a) / 2) > 0)
            a = (b + a) / 2;
        else
            b = (b + a) / 2;
    }
    return (b + a) / 2;
}
    

int main()
{
    setlocale(LC_ALL, "Rus");
    srand(time(0));
    std::vector<int> varr; // N значений массива
    int count = 0;
    for (int i = 0;i < N;i++)
    {
        varr.push_back(i);
    }
    std::vector<int> vkey = varr; // N/10 ключей поиска
    Blender(vkey);
    for (int i = 0;i < (N - (N / 10));i++)
    {
        vkey.erase(vkey.begin());
    }  
    //Printer(vkey);
    std::cout << "Начало бинарного поиска " << std::endl;
    Timer t1;
    for (int i = 0;i < vkey.size();i++)
    {
        if (Search(varr, vkey[i]) == 1)
        {
            //cout << "Элемент" << vkey[i] << " найден" << endl;
        }
    }
    std::cout << "Затраченное время: " << t1.elapsed() << std::endl;
    std::cout << "Начало поиска перебором " << std::endl;
    Timer t2;
    for (int i = 0;i < vkey.size();i++)
    {
        if (Slow_Search(varr, vkey[i]) == 1)
        {
            //cout << "Элемент" << vkey[i] << " найден" << endl;
        }
    }
    std::cout << "Затраченное время: " << t2.elapsed() << std::endl;
    cout << endl << Bisection(0, 100,0.0001); // Ответ 3.16224
    


    
}
