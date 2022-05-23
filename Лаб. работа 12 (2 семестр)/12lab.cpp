// 12lab.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <memory> 
#include <string>
#include <vector>


class Teacher;

class Student
{
public:
    Student(std::string name)
    {
        m_student = name;
    }
    ~Student()
    {
    }

    std::string nameStudent() { return m_student; }
    std::shared_ptr<Teacher> getTeacher() { m_teacher; }

    void addTeacher(std::shared_ptr<Teacher>& teacher)
    {
        m_teacher = teacher;
    }

private:
    std::string m_student;
    std::weak_ptr<Teacher> m_teacher; //количество ссылок не увеличивает
};

class Teacher
{
public:
    Teacher(const std::string& name)
    {
        m_name = name;
    }
    ~Teacher()
    {
    }

    friend void S_Teacher(std::shared_ptr<Teacher>& D, std::shared_ptr<Student>& S)
    {
        D->addStudent(S);
        S->addTeacher(D);
    }

    void addStudent(std::shared_ptr<Student>& student)
    {
        m_students.push_back(student);
    }

    void AllStudents()
    {
        if (!m_students.empty())
        {
            std::cout << m_name << " students: " << std::endl;

            for (const auto& student : m_students)
            {
                std::cout << student.lock()->nameStudent() << std::endl;
            }
        }
    }

private:
    std::string m_name;
    std::vector<std::weak_ptr<Student>> m_students;

};

int main()
{
    setlocale(LC_ALL, "Rus");
    auto teacher1{ std::make_shared<Teacher>("Shef") };
    auto student1{ std::make_shared<Student>("Nikita") };
    auto student2{ std::make_shared<Student>("Anton Sabaton") };


    S_Teacher(teacher1, student1);
    S_Teacher(teacher1, student2);

    std::cout << teacher1.use_count() << " " << student1.use_count() << std::endl;

    teacher1->AllStudents();

    return 0;
}