#pragma once

#include <optional>
#include <string>
#include <vector>

struct Animal
{
    std::string name;
    std::optional<int> legCount{false};
};

class FakeDb
{
public:
    void addItem(const Animal &animal);
    void removeItem();
    std::vector<Animal> getAll();
};