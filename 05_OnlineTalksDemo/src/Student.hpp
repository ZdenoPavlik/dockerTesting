#pragma once

#include "stdafx.h"

class Student {
public:
    Student(const int id, std::string name, std::string surname, int age);
    Student(const web::json::value& student);
    const web::json::value toJson() const;

private:
    int m_id;
    std::string m_name;
    std::string m_surname;
    int m_age;
};