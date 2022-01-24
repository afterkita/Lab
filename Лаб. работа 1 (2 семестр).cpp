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
#include <vector>
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

#define N 5000
/* Лучшее время работы О = n
*  Худшее время работы O = n^2
*/
void BubbleSort(std::vector<int>& values)
{
    // Проверка условия
    int count = 0;
    for (int i = 0;i < N;i++)
    {
        count += values[i];
    }
    if (count > 1000)
    {
        int op, zm;

        std::cout << std::endl << "Условие выполненно" << std::endl;
        std::cout << "Начало пузырьковой сортировки " << std::endl;
        Timer t;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N - 1; j++)
            {
                if (values[j] > values[j + 1])
                {
                    int b = values[j];
                    values[j] = values[j + 1];
                    values[j + 1] = b;
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
}
void Shaker(std::vector<int>& values)
{
    int L = values.size();
    for (int i = 0;i < L;i++)
    {
        values[i] = rand() % 50;
    }
}
void Printer(std::vector<int>& values)
{
    int L = values.size();
    if (L <= 2000)
    {
        for (int i = 0;i < L;i++)
        {
            std::cout << values[i] << " ";
        }
    }
    
}
void MergeSortImpl(std::vector<int>& values, std::vector<int>& buffer, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        MergeSortImpl(values, buffer, l, m);
        MergeSortImpl(values, buffer, m + 1, r);

        int k = l;
        for (int i = l, j = m + 1; i <= m || j <= r; ) {
            if (j > r || (i <= m && values[i] < values[j])) {
                buffer[k] = values[i];
                ++i;
            }
            else {
                buffer[k] = values[j];
                ++j;
            }
            ++k;
        }
        for (int i = l; i <= r; ++i) {
            values[i] = buffer[i];
        }
    }
}
/* Лучшее время работы О = n*log(n)
*  Худшее время работы O = n*log(n)
*/
void MergeSort(std::vector<int>& values) {
    if (!values.empty()) {
        std::vector<int> buffer(values.size());
        MergeSortImpl(values, buffer, 0, values.size() - 1);
    }
}


int main()
{
    setlocale(LC_ALL, "Rus");
    srand(time(0));
    std::vector<int> arr; 
    int count = 0;
    for (int i = 0;i < N;i++)
    {
        arr.push_back(rand() % 50);
        count += arr[i];
    }
    if (count >= 1000)
    {
        Printer(arr);
        BubbleSort(arr);
        Printer(arr);
        Shaker(arr);
        Printer(arr);
        std::cout << "Начало сортировки слиянием " << std::endl;
        Timer t1;
        MergeSort(arr);
        std::cout << "Затраченное время: " << t1.elapsed() << std::endl;
        std::cout << "Конец сортировки " << std::endl;
        Printer(arr);
    }
    
}

