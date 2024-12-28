#pragma once

#include "Person.h"
#include "PersonData.h"
// содержит функции для сбора статистических данных для класса Person

class PersonStatisticsAnalyzer;

// класс должен обрабатывать сразу по нескольким фронтам одного человека
// должны быть функция, принимающая одного человека на вход, и вызывающая другие функции для подсчета статистики,
// они должны принимать указатель или ссылку на Person.
class PersonStatistics {
friend class PersonStatisticsAnalyzer;
private:
    int quantityOfSubmittedPersons = 0;

    // списки для дальнейшего рассмотрения для подсчета статистики
    int maleNameStatistics[maleNameQuantity];
    int femaleNameStatistics[femaleNameQuantity];
    int ageStatistics[ageQuantity]; // возрастные категории с интервалом в 5 лет (от 1 до 80);
    int genderStatistics[2] = {0, 0};
    int countryStatistics[countryQuantity];
    int maritalStatusStatistics[5] = {0, 0, 0, 0, 0};
    int quantityOfChildrenStatistics[7] = {0, 0, 0, 0, 0, 0, 0};
    int jobStatistics[jobQuantity];
    int salaryStatistics[5] = {0, 0, 0, 0, 0};

    void handleName(const Person* person);
    void handleAge(const Person* person);
    void handleGender(const Person* person);
    void handleCountry(const Person* person);
    void handleMaritalStatus(const Person* person);
    void handleQuantityOfChildren(const Person* person);
    void handleJob(const Person* person);
    void handleSalary(const Person* person);

public:

    // явно заполняем все массивы нулями при вызове конструктора
    PersonStatistics();

    // обрабатываем нового человека
    void handlePerson(const Person* person);
};

class PersonStatisticsData {
public:
    int quantityOfSubmittedPersons;

    std::string mostCommonMaleName;
    std::string mostCommonFemaleName;
    std::string mostCommonAge;
    std::string mostCommonGender;
    std::string mostCommonCountry;
    std::string mostCommonMaritalStatus;
    std::string mostCommonQuantityOfChildren;
    std::string mostCommonJob;
    std::string mostCommonSalary;

    std::string leastCommonMaleName;
    std::string leastCommonFemaleName;
    std::string leastCommonAge;
    std::string leastCommonGender;
    std::string leastCommonCountry;
    std::string leastCommonMaritalStatus;
    std::string leastCommonQuantityOfChildren;
    std::string leastCommonJob;
    std::string leastCommonSalary;
};

// собирает рассмотренную информацию и делает выводы
class PersonStatisticsAnalyzer {
private:
    // передаем statistics для того, чтобы извлечь статистику, и data для того, чтобы записать в уже созданный объект
    // PersonStatisticsData полученные в ходе анализа данные
    void analyzeMaleName(const PersonStatistics* statistics, PersonStatisticsData* data);
    void analyzeFemaleName(const PersonStatistics* statistics, PersonStatisticsData* data);
    void analyzeAge(const PersonStatistics* statistics, PersonStatisticsData* data);
    void analyzeGender(const PersonStatistics* statistics, PersonStatisticsData* data);
    void analyzeCountry(const PersonStatistics* statistics, PersonStatisticsData* data);
    void analyzeMaritalStatus(const PersonStatistics* statistics, PersonStatisticsData* data);
    void analyzeQuantityOfChildren(const PersonStatistics* statistics, PersonStatisticsData* data);
    void analyzeJob(const PersonStatistics* statistics, PersonStatisticsData* data);
    void analyzeSalary(const PersonStatistics* statistics, PersonStatisticsData* data);

public:
    PersonStatisticsAnalyzer() = default;

    // при вызове этой функции вызываются другие функции, анализирующие статистику по конкретным аттрибутам
    PersonStatisticsData* analyzeStatistics(const PersonStatistics* statistics);
};

void printPersonStatisticsData(PersonStatisticsData* data);
