// Лаб. работа 5 (2 семестр).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
Лабораторная работа №5
«Бинарное дерево поиска»

Дана последовательность операций «добавить вершину», «удалить вершину» и «найти ключ» над бинарным деревом поиска. 
Выполнить эти операции.

Вход
Во входном файле записана последовательность команд вида “+x” или “-x” или “?x” или “E”. Здесь x – натуральное 
число не более 10^9. Команда "+x" означает "добавить в дерево число x", команда "-x" означает "удалить из дерева 
число x", команда "?x" - "найти в дереве слово x". Команда "E" означает "завершить операции с деревом". Каждая 
команда записана в отдельной строке, начиная с первой позиции, и не содержит пробелов.

Выход
В выходной файл запишите результаты выполнения команд "?x" в том порядке, в котором они присутствуют во входном 
файле. Если слово найдено, записать в файл его глубину в дереве, в противном случае - символ 'n'.

*/
#include <iostream>
#include <fstream>
using namespace std;
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

int main()
{
    setlocale(LC_ALL, "Rus");
    ifstream in("input.txt");

    Elem* root = nullptr;
    char c = 'E';
    while (in >> c )
    {
        if (c == 'E')
        {
            break;
        }
        
        int p;
        in >> p;
        
        if (c == '+')
        {
            ADD(p, root);
        }
        else if (c == '?')
        {
            Elem* u = SEARCH(p, root);
            if (u == nullptr)
            {
                cout << "n" << " ";
            }
            else
            {
                int y = 0;
                while (u->parent != nullptr)
                {
                    y++;
                    u = u->parent;
                }
                cout << y << " ";
            }
        }
        else if (c == '-')
        {
            DELETE(p, root);
        }
    }
    


    return 0;
}
