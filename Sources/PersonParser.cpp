#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

#include "Person.h"
#include "PersonParser.h"
#include "PersonData.h"

void checkNameValid(const std::string& name, char gender);
void checkAgeValid(int age);
void checkGenderValid(char gender);
void checkCountryValid(const std::string& country);
void checkMaritalStatusValid(const std::string& maritalStatus);
void checkQuantityOfChildrenValid(int quantityOfChildren);
void checkJobValid(const std::string& job);
void checkSalaryValid(int salary);

Person parsePerson(const std::string& str) {
    std::istringstream stream(str);
    std::string word;
    std::vector<std::string> words;
    
    // Читаем каждое слово, разделяя строку по пробелам
    while (stream >> word) {
        words.push_back(word);
    }

    try {
        // gender проверяем перед именем, чтобы проверить корректность соотношения имени и пола
        char gender = *(words[2]).c_str();
        checkGenderValid(gender);

        std::string name = words[0];
        checkNameValid(name, gender);

        int age = std::stoi(words[1]);
        checkAgeValid(age);

        std::string country = words[3];
        checkCountryValid(country);

        std::string maritalStatus = words[4];
        checkMaritalStatusValid(maritalStatus);

        int quantityOfChildren = std::stoi(words[5]);
        checkQuantityOfChildrenValid(quantityOfChildren);

        std::string job = words[6];
        checkJobValid(job);

        int salary = std::stoi(words[7]);
        checkSalaryValid(salary);
    
        return Person(name, age, gender, country, maritalStatus, quantityOfChildren, job, salary);
    } catch (const std::exception& ex) {
        std::string invalidStringFormat = "Invalid string format: " + std::string(ex.what());
        throw std::invalid_argument(invalidStringFormat);
    }
}

void checkNameValid(const std::string& name, char gender) {
    if (gender == 'm') {
        for (int i = 0; i < maleNameQuantity; ++i) {
            if (name == maleNamesStorage[i]) {
                return;
            }
        }
    } else if (gender == 'w') {
        for (int i = 0; i < femaleNameQuantity; ++i) {
            if (name == femaleNamesStorage[i]) {
                return;
            }
        }
    }
    throw std::invalid_argument("The wrong name was entered.\n");
}

void checkAgeValid(int age) {
    if (age > 0 && age <= 80) {
        return;
    }
    throw std::invalid_argument("The wrong age was entered.\n");
}

void checkGenderValid(char gender) {
    if (gender == 'm' or gender == 'w') {
        return;
    }
    throw std::invalid_argument("The wrong gender was entered.\n");
}

void checkCountryValid(const std::string& country) {
    for (int i = 0; i < countryQuantity; ++i) {
        if (country == countriesStorage[i]) {
            return;
        }
    }
    throw std::invalid_argument("The wrong country was entered.\n");
}

void checkMaritalStatusValid(const std::string& maritalStatus) {
    for (int i = 0; i < maritalStatusesQuantity; ++i) {
        if (maritalStatus == maritalStatusesStorage[i]) {
            return;
        }
    }
    throw std::invalid_argument("The wrong marital status was entered.\n");
}

void checkQuantityOfChildrenValid(int thisQuantityOfChildren) {
    if (thisQuantityOfChildren >= 0 && thisQuantityOfChildren < quantityOfChildren) {
        return;
    }
    throw std::invalid_argument("The wrong quantity of children was entered.\n");
}

void checkJobValid(const std::string& job) {
    for (int i = 0; i < jobQuantity; ++i) {
        if (job == jobsStorage[i]) {
            return;
        }
    }
    throw std::invalid_argument("The wrong job was entered.\n");
}

void checkSalaryValid(int salary) {
    if ((salary >= 1001 && salary <= 5000) || salary == 0) {
        return;
    }
    throw std::invalid_argument("The wrong salary was entered.\n");
}
