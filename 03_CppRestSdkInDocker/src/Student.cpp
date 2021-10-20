#include "Student.hpp"

#include <iostream>

Student::Student(const int id, std::string name, std::string surname, int age)
    : m_id(id)
    , m_name(name)
    , m_surname(surname)
    , m_age(age)
{
    std::cout << "Constructing student " << id << " - " << name << " - "
              << surname << " - " << age << std::endl;
}

Student::Student(const web::json::value& student)
{
    if (student.has_integer_field("id")) {
        this->m_id = student.at("id").as_integer();
    }

    if (student.has_string_field("name")) {
        this->m_name = student.at("name").as_string();
    }

    if (student.has_string_field("surname")) {
        this->m_surname = student.at("surname").as_string();
    }

    if (student.has_integer_field("age")) {
        this->m_age = student.at("age").as_integer();
    }
}

const web::json::value Student::toJson() const
{
    // No checking whether it is bool, int or string
    web::json::value student;
    student["id"] = this->m_id;
    student["name"] = web::json::value::string(this->m_name);
    student["surname"] = web::json::value::string(this->m_surname);
    student["age"] = this->m_age;

    std::cout << student.serialize() << std::endl; //serialize == to_string

    return student;
}