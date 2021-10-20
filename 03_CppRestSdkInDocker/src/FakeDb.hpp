#pragma once
#include <optional>
#include <vector>

#include "Student.hpp"

class FakeDB {
 public:
  FakeDB();

  const Student getStudentById(const int id) const;                 // GET
  void addStudent(Student &newStudent);                             // POST
  void removeStudent(const int id);                                 // DELETE
  void modifyStudentAtIndex(const int index, Student &newStudent);  // PUT
  const int getStudentCount() const;

 private:
  std::vector<Student> m_students;
};