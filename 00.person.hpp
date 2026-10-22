#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <utility>

class person;

namespace set
{
    void FullName(person& owner, const std::string& newName, const std::string& newSurname);
    void Name(person& owner, const std::string& newName);
    void Surname(person& owner, const std::string& newSurname);
    void Age(person& owner, int newAge);
}

namespace get
{
    std::string Name(const person& owner);
    std::string Surname(const person& owner);
    std::pair<std::string, std::string> FullName(const person& owner);
    int Age(const person& owner);
}

class person
{
private:
    std::string name;
    std::string surname;
    int age;

    friend void set::FullName(person&, const std::string&, const std::string&);
    friend void set::Name(person&, const std::string&);
    friend void set::Surname(person&, const std::string&);
    friend void set::Age(person&, int);
    friend std::string get::Name(const person&);
    friend std::string get::Surname(const person&);
    friend std::pair<std::string, std::string> get::FullName(const person&);
    friend int get::Age(const person&);

public:
    person() : name("Unknown"), surname("Unknown"), age(0) {}

    person(const std::string& name, const std::string& surname, int age)
        : name(name), surname(surname), age(age) {}
};

namespace set
{
    inline void FullName(person& owner, const std::string& newName, const std::string& newSurname)
    {
        owner.name = newName;
        owner.surname = newSurname;
    }

    inline void Name(person& owner, const std::string& newName)
    {
        owner.name = newName;
    }

    inline void Surname(person& owner, const std::string& newSurname)
    {
        owner.surname = newSurname;
    }

    inline void Age(person& owner, int newAge)
    {
        owner.age = newAge;
    }
}

namespace get
{
    inline std::string Name(const person& owner)
    {
        return owner.name;
    }

    inline std::string Surname(const person& owner)
    {
        return owner.surname;
    }

    inline std::pair<std::string, std::string> FullName(const person& owner)
    {
        return {owner.name, owner.surname};
    }

    inline int Age(const person& owner)
    {
        return owner.age;
    }
}

#endif