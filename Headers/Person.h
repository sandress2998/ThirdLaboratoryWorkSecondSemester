#pragma once

#include <string>

class Person {
private:
    std::string name;
    int age;
    char gender; // либо w, либо m
    std::string country;
    std::string maritalStatus;
    int quantityOfChildren;
    std::string job;
    int salary;

public: 
    Person() = default;

    Person(const std::string& name, int age, char gender, const std::string& country
    , const std::string& maritalStatus, int quantityOfChildred, const std::string& job, int salary);

    Person(const Person& other);
    
    std::string getName() const;
    int getAge() const;
    char getGender() const;
    std::string getCountry() const;
    std::string getMaritalStatus() const;
    int getQuantityOfChildren() const;
    std::string getJob() const;
    int getSalary() const;
};

Person generatePerson();
