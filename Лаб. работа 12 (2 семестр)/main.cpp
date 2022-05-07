#include <iostream>
#include <vector>
#include <memory>

class Student
{
public:
    Student(int age, std::string name)
    {
        m_name = name;
        m_age = age;
    }
    void Print_info()
    {
        std::cout << m_name << " " << m_age << "\n";
    }

private:
    int m_age;
    std::string m_name;
//    std::unique_ptr<Teacher> m_t;
};

class Teacher
{
public:
    Teacher(std::string name, int age, std::string subject)
    {
        m_name = name;
        m_age = age;
        m_subject = subject;
    }
    void Add_student(Student s)
    {
        m_students.push_back(std::make_unique<Student>(s));
    }
    void Print_student()
    {
        for (int i=0;i<m_students.size();i++)
        {
            m_students[i]->Print_info();
        }

    }

private:
    std::string m_name;
    int m_age;
    std::string m_subject;
    std::vector<std::unique_ptr<Student>> m_students; // Вектор ссылок на учеников
};




int main() {
    Student st1(20, "Nikita");
    Student st2(19, "Kita");
    Teacher tc1( "Shef", 70, "Geometry" );
    tc1.Add_student(st1);
    tc1.Add_student(st2);
    tc1.Print_student();
    return 0;
}
