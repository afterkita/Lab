// Лаб. работа 6 (2 семестр).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
Лабораторная работа №6
«Алгоритмы и структуры данных»

Это коллективная работа, которую можно выполнять вдвоем. Но также можно и одному.

Условия:
1.Подобрать наиболее эффективный алгоритм или структуру данных под условие вашей задачи. Стоит учесть сложность по операциям и сложность в реализации. Решений может быть не одно. Умейте обосновать ваш выбор.
2.При коллективной реализации необходимо использовать инструменты гита: ветки и слияния. При индивидуальной – желательно.
3.Реализацию алгоритмов можно взять из ваших лабораторных работ, либо использовать уже готовые, например, std::list, std::map из стандартной библиотеки.
4.При коллективной реализации работа засчитывается обоим участникам, если оба смогут ответить на вопросы.
5.Необходимо реализовать алгоритм или структуру данных и продемонстрировать работу функционала вашей программы. Оценить сложность.

Подобрать структуру для хранения данных, над которой будут осуществляться операции поиска. 
Добавление и удаление не предусмотрены.

Возможные варианты
Массив
Вектор
Односвязный список
Дерево

*/

#include <iostream>
#include <fstream>
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
using namespace std;
#define N 100000 // Количество элементов
#define K 20000 // Количество поисковых запросов
struct Elem
{
    int data;
    Elem* left;
    Elem* right;
    Elem* parent;
};
Elem* MAKE(int data, Elem* p)
{
    Elem* q = new Elem;
    q->data = data;
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;
    return q;
}
void ADD(int data, Elem*& root)
{
    if (root == nullptr) {
        root = MAKE(data, nullptr);
        return;
    }
    Elem* v = root;
    while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))
        if (data < v->data)
            v = v->left;
        else
            v = v->right;
    if (data == v->data)
        return;
    Elem* u = MAKE(data, v);
    if (data < v->data)
        v->left = u;
    else
        v->right = u;
}
void PASS(Elem* v)
{
    if (v == nullptr)
        return;
    PASS(v->left);
    std::cout << v->data << std::endl;
    PASS(v->right);
}
Elem* SEARCH(int data, Elem* v)
{
    if (v == nullptr)
        return v;
    if (v->data == data)
        return v;
    if (data < v->data)
        return SEARCH(data, v->left);
    else
        return SEARCH(data, v->right);
}
void DELETE(int data, Elem*& root)
{
    //   .  
    Elem* u = SEARCH(data, root);
    if (u == nullptr)
        return;
    if (u->parent == nullptr)
    {
        std::cout << " Удаление корня ";
        root == nullptr;
        return;
    }
    //   ( )
    if (u->left == nullptr && u->right == nullptr && u == root)
    {
        root = nullptr;
        return;
    }

    //    
    if (u->left != nullptr && u->right != nullptr)
    {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    Elem* t;
    if (u->left == nullptr)
        t = u->right;
    else
        t = u->left;
    if (u->parent->left == u)
        u->parent->left = t;
    else
        u->parent->right = t;
    if (t != nullptr)
        t->parent = u->parent;
}

// Бинарный поиск для вектора
int Search_Vector(std::vector<int>& victor, int key)
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
// Бинарный поиск для массива
int Search_Array(int* victor, int key, int r)
{
    bool flag = false;
    int l = 0;
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
// Сортировка слиянием
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
void MSort(std::vector<int>& values)
{
    if (!values.empty())
    {
        std::vector<int> buffer(values.size());
        MSort_B(values, buffer, 0, values.size() - 1);
    }
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "Rus");
    // Файл выхода с общими данными
    ofstream out("results.txt");
    out << "Количество элементов: " << N << endl;
    out << "Количество посковых запросов: " << K << endl;
    ifstream in("input.txt");
    int arr[N]; // Тестовый массив
    vector<int> victor; // Тестовый вектор
    Elem* root = nullptr; // Тестовое дерево

    int itr;
    // Заполнение вектора
    for (int i = 0;i < N;i++) 
    {
        in >> itr;
        victor.push_back(i);
    }
    // Заполнение дерева
    for (int i = 0;i < N;i++) 
    {
        ADD(victor[i], root);
    }
    // Сортировка вектора и заполнение массива
    Timer t1;
    MSort(victor);
    out << t1.elapsed() << " Затраченное на сортировку время" << std::endl;
    for (int i = 0;i < N;i++)
    {
        arr[i]=victor[i];
    }
    // Проверка массива
    t1.reset();
    for (int j = 0;j < K;j++)
    {
        Search_Array(arr, rand() % N , N);
    }
    out << t1.elapsed() << " Затраченное время сортированным массивом "  << std::endl;
    // Проверка вектора
    t1.reset();
    for (int j = 0;j < K;j++)
    {
        Search_Vector(victor, rand() % N );
    }
    out << t1.elapsed() << " Затраченное время сортированным вектором " << std::endl;
    // Проверка дерева
    t1.reset();
    for (int j = 0;j < K;j++)
    {
        SEARCH(rand() % (N/10), root);
    }
    out << t1.elapsed() << " Затраченное время деревом " << std::endl;
    /*
    Blender(victor);
    for (int i = 0;i < N;i++)
    {

        if (i % 25 == 0)
        {
            out << victor[i] << " \n";
        }
        else
        {
            out << victor[i] << " ";
        }
    }
    */
}

