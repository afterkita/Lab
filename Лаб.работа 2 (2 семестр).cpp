// Лаб.работа 2 (2 семестр).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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

#define N 5000 // Количество случайно сгенерированных чисел для сортировки
/* Лучшее время работы О = n
*  Худшее время работы O = n^2
*/
// Пузырьковая сортировка
void BubbleSort(std::vector<int>& values)
{
    // Проверка условия
    int count = 0;
    for (int i = 0;i < N;i++)
    {
        count += values[i];
    }
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

// Функция для вывода вектора после сортировки
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
void MSort_B(std::vector<int>& values, std::vector<int>& buffer, int l, int r) 
{
    if (l < r) 
    {
        int m = (l + r) / 2;
        MSort_B(values, buffer, l, m);
        MSort_B(values, buffer, m + 1, r);

        int k = l;
        for (int i = l, j = m + 1; i <= m || j <= r; ) 
        {
            if (j > r || (i <= m && values[i] < values[j])) 
            {
                buffer[k] = values[i];
                ++i;
            }
            else {
                buffer[k] = values[j];
                ++j;
            }
            ++k;
        }
        for (int i = l; i <= r; ++i) 
        {
            values[i] = buffer[i];
        }
    }
}
/* Лучшее время работы О = n*log(n)
*  Худшее время работы O = n*log(n)
*/
// Сортировка слиянием
void MSort(std::vector<int>& values) 
{
    if (!values.empty()) 
    {
        std::vector<int> buffer(values.size());
        MSort_B(values, buffer, 0, values.size() - 1);
    }
}
int Medium(int a, int b, std::vector<int>& values)
{
    return (rand() % (b - a + 1) + a);
}
// Сортировка qsort
void QSort(int a,int b, std::vector<int>& values)
{
    if (a >= b)
    {
        return;
    }
    int m = Medium(a, b, values);
    int k = values[m];
    int l = a - 1;
    int r = b + 1;
    while (true)
    {
        do
        {
            l = l + 1;
        } while (values[l]<k);
        do
        {
            r = r - 1;
        } while (values[r] > k);
        if (l >= r)
        {
            break;
        }
        std::swap(values[l], values[r]);
    }
    r = l;
    l = l - 1;
    QSort(a, l, values);
    QSort(r, b, values);
}

int main()
{
    setlocale(LC_ALL, "Rus");
    srand(time(0));
    std::vector<int> arr;
    int count = 0;
    for (int i = 0;i < N;i++)
    {
        arr.push_back(rand() % 500);
        count += arr[i];
    }
    std::vector<int> victor = arr;
    // Bsort
    Printer(arr);
    BubbleSort(arr);
    Printer(arr);
    // MSort
    arr = victor;
    std::cout << "Начало сортировки слиянием " << std::endl;
    Timer t1;
    MSort(arr);
    std::cout << "Затраченное время: " << t1.elapsed() << std::endl;
    std::cout << "Конец сортировки " << std::endl;
    Printer(arr);
    // QSort
    arr = victor;
    std::cout << "Начало быстрой сортировки " << std::endl;
    Timer t2;
    QSort(0, arr.size() - 1, arr);
    std::cout << "Затраченное время: " << t2.elapsed() << std::endl;
    std::cout << "Конец сортировки " << std::endl;
    Printer(arr);

}