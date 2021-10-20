#include "FakeDb.hpp"

FakeDB::FakeDB()
{
    m_students.push_back({ 0, "Jan", "Holy", 32 });
    m_students.push_back({ 1, "Jozef", "Vrtky", 30 });
    m_students.push_back({ 2, "Ema", "Vysoka", 28 });
    m_students.push_back({ 3, "Helena", "Trojska", 34 });
}

const Student FakeDB::getStudentById(const int id) const
{
    // std::cout << "Returning student of id " << id << std::endl;
    // Far away from being safe, but this is only demonstration
    return m_students[id];
}

void FakeDB::addStudent(Student& newStudent)
{
    m_students.push_back(newStudent);
}

void FakeDB::removeStudent(const int id)
{
    if (id < m_students.size()) {
        m_students.erase(m_students.begin() + id);
    } else {
        throw std::runtime_error("Index out of range");
    }
}

void FakeDB::modifyStudentAtIndex(const int index, Student& newStudent)
{
    m_students[index] = newStudent;
}

const int FakeDB::getStudentCount() const
{
    std::cout << "FakeDB has " << m_students.size() << " students" << std::endl;
    return m_students.size();
}