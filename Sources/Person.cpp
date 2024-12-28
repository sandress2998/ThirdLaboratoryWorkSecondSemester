#include "Person.h"
#include "PersonData.h"

#include <random>
#include <string>

Person::Person(const std::string& name, int age, char gender, const std::string& country
, const std::string& maritalStatus, int quantityOfChildren, const std::string& job, int salary): 
name(name), age(age), gender(gender), country(country), maritalStatus(maritalStatus)
, quantityOfChildren(quantityOfChildren), job(job), salary(salary) {}

Person::Person(const Person& other): name(other.name), age(other.age), gender(other.gender), country(other.country)
, maritalStatus(other.maritalStatus), quantityOfChildren(other.quantityOfChildren), job(other.job)
, salary(other.salary) {}

std::string Person::getName() const {
    return name;
}

int Person::getAge() const {
    return age;
}

char Person::getGender() const {
    return gender;
}

std::string Person::getCountry() const {
    return country;
}

std::string Person::getMaritalStatus() const {
    return maritalStatus;
}

int Person::getQuantityOfChildren() const {
    return quantityOfChildren;
}

std::string Person::getJob() const {
    return job; 
}

int Person::getSalary() const {
    return salary;
}

Person generatePerson() {
    std::random_device rd;  // Источник энтропии (например, аппаратное случайное число)
    std::mt19937 gen(rd()); // Генератор на основе Mersenne Twister

    std::uniform_int_distribution<> nameGen(0, maleNameQuantity - 1);
    std::uniform_int_distribution<> ageGen(1, 80);
    std::uniform_int_distribution<> genderGen(0, 1);
    std::uniform_int_distribution<> countryGen(0, countryQuantity - 1);
    std::uniform_int_distribution<> maritalStatusGen(0, 4);
    std::uniform_int_distribution<> quantityOfChildrenGen(0, quantityOfChildren - 1);
    std::uniform_int_distribution<> jobGen(0, jobQuantity - 1);
    std::uniform_int_distribution<> salaryGen(1001, 5000);

    char gender;
    if (genderGen(gen) == 0) {
        gender = 'm';
    } else {
        gender = 'w';
    }

    std::string name;
    if (gender == 'm') {
        name = maleNamesStorage[nameGen(gen)];
    } else {
        name = femaleNamesStorage[nameGen(gen)];
    }

    int age = ageGen(gen);

    std::string country = countriesStorage[countryGen(gen)];

    std::string maritalStatus;
    if (age < 18) {
        maritalStatus = "Unmarried";
    } else {
        maritalStatus = maritalStatusesStorage[maritalStatusGen(gen)];
    }

    int quantityOfChildren;
    if (age < 18) {
        quantityOfChildren = 0;
    } else {
        quantityOfChildren = quantityOfChildrenGen(gen);
    }

    std::string job;
    if (age < 18) {
        job = "Unemployed";
    } else {
        job = jobsStorage[jobGen(gen)];
    }

    int salary;
    if (job == "Unemployed") {
        salary = 0;
    } else {
        salary = salaryGen(gen);
    }

    return Person(name, age, gender, country, maritalStatus, quantityOfChildren, job, salary);
}