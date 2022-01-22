// Лаб. работа 1 (2 семестр).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Лабораторная работа №1
«Оценка сложности алгоритма»
Оцените сложность алгоритма в лучшем, среднем и худшем случае. Рассчитайте примерное время работы алгоритма. 
Запрограммируйте его. Определите реальное время работы 
(воспользуйтесь классом Timer https://ravesli.com/urok-129-tajming-koda-vremya-vypolneniya-programmy/)
и сравните с расчетным.
Ввод и вывод данных в расчете не учитывать. Считать, что 0 < N <= 10000. 

Вариант 8.
Дана последовательности из N чисел. Если их сумма больше 1000, отсортируйте по возрастанию.

*/

#include <iostream>
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

#define N 10000
int main()
{
    setlocale(LC_ALL, "Rus");
    srand(time(0));
    int arr[N]; // Создание и заполнение массива
    for (int i = 0;i < N;i++)
    {
        arr[i] = rand() % 50;
        if (N < 2000)
        {
            std::cout << arr[i] << " ";
        }
        
    }
    // Проверка условия
    int count = 0;
    for (int i = 0;i < N;i++)
    {
        count += arr[i];
    }
    if (count > 1000)
    {
        int op, zm;

        std::cout << std::endl << "Условие выполненно" << std::endl;
        std::cout <<  "Начало сортировки " << std::endl;
        Timer t;
        
        for (int i = 0; i < N; i++) 
        {
            for (int j = 0; j < N-1; j++) 
            {
                if (arr[j] > arr[j + 1]) 
                {
                    int b = arr[j];
                    arr[j] = arr[j + 1]; 
                    arr[j + 1] = b; 
                }
            }
        }
        
        std::cout << "Затраченное время: " << t.elapsed() << std::endl;
        std::cout << "Конец сортировки " << std::endl;
    }
    else
    {
        std::cout << std::endl << "Условие не выполненно" << std::endl;
    }
    for (int i = 0;i < N;i++)
    {
        if(N < 2000)
        {
            std::cout << arr[i] << " ";
        }
    }
}
// O = N^2 Так как использовалась пузырьковая сортировка
// Ожидаемое время работы сортировки при N = 20
