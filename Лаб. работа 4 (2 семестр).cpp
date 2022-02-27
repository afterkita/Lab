// Лаб. работа 4 (2 семестр).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
Лабораторная работа №4
«Односвязный список»

Для реализации задач используйте односвязный список, который мы рассматривали на лекции.
Вариант 8.
Создайте односвязный список из 10000 целых чисел и реализуйте в нем операцию вставки элемента х в позицию k. Выполните M = 1000 запросов на удаление.
Реализуйте такую же операцию для массива. Сравните производительность.

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

struct T_List
{
    T_List* next;
    int age;
};
void ADD(T_List* head, int age)
{
    T_List* p = new T_List;
    p->age = age;
    p->next = head->next;
    head->next = p;
}
void PRINT(T_List* head)
{
	T_List* p = head->next;
	int count = 0;
	while (p != nullptr)
	{
		std::cout << count<<" - "<< p->age << std::endl;
		p = p->next;
		count++;
	}
}
void DELETE(T_List* head)
{
	T_List* tmp;
	T_List* p = head;
	while (p->next != nullptr)
	{
		if (p->next->age % 2 == 0)
		{
			tmp = p->next;
			p->next = p->next->next;
			delete tmp;
		}
		else
			p = p->next;
	}
}
void CLEAR(T_List* head)
{
	T_List* tmp;
	T_List* p = head->next;
	while (p != nullptr)
	{
		tmp = p;
		p = p->next;
		delete tmp;
	}
}
void DUPLICATE(T_List* head)
{
	T_List* p = head->next;
	while (p != nullptr)
	{
		if (p->age % 2 == 1)
		{
			T_List* q = new T_List;
			q->next = p->next;
			p->next = q;
			q->age = p->age;
			p = p->next;
		}
		p = p->next;
	}
}
void SWAPSORT(T_List* head)
{
	
	T_List* p = head->next;
	while (p->next->next != nullptr)
	{
		T_List* q = p->next;
		while (q->next != nullptr)
		{
			if (p->age > q->age)
				std::swap(p->age, q->age);
			q = q->next;
		}
		p = p->next;
	}
}
// Вставка с замещением
void INSERT_1(T_List* head, int age, int position)
{
	T_List* p = new T_List;
	p->age = age;
	//
	int count = 0;
	T_List* q = head->next;
	while (q != nullptr)
	{
		if (count == position-2)
		{
			p->next = q->next->next;
			q->next = p;
		}
		q = q->next;
		count++;
	}
	//
	

}
// Вставка без замещения
void INSERT_2(T_List* head, int age, int position)
{
	ADD(head, age);
	T_List* p = head->next;
	T_List* q = head->next;
	int count = 0;
	while (p != nullptr)
	{
		if (count == position-1)
		{
			head->next = q->next;
			q->next = p->next;
			p->next = q;
		}
		p = p->next;
		count++;
	}

}
void INSERT_ARR(int& N, int*& arr, int index, int age)
{
	int* new_arr = new int[N + 1];

	for (int i = 0; i < index; i++)
		new_arr[i] = arr[i];
	new_arr[index] = age;

	for (int i = index + 1; i < N + 1; i++)
		new_arr[i] = arr[i - 1];

	N++;

	delete[] arr;
	arr = new_arr;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	int N = 100000; // Использую 100000 а не 10000 т.к. только так видна разница
	srand(time(0));
	T_List* head = new T_List;
	head->next = nullptr;
	
	for (int i = 0;i < N;i++) // Почему сортировка теряет последние число?
	{
		ADD(head, i+1);
	}
	Timer t1;
	INSERT_2(head, 100, 456);
	std::cout << t1.elapsed() << " Затраченное время" << std::endl;
	//PRINT(head);
	CLEAR(head);
	delete head;
	std::cout << std::endl;
	int* arr = new int[N];
	for (int i = 0;i < N;i++)
	{
		arr[i] = i;
	}
	Timer t2;
	INSERT_ARR(N, arr, 5, 101);
	std::cout << t2.elapsed() << " Затраченное время" << std::endl;
	/*for (int i = 0;i < N ;i++)
	{
		std::cout << arr[i] << " ";
	}*/
	
	delete[] arr;
	return 0;

}

