#pragma once
#include <string>
#include <stdexcept>
#include "MutableSegmentedDeque.h"
#include "Person.h"
#include "PersonHandler.h"
#include "Dictionary.h"

// здесь будет задан класс такой, что Dictionary<std::string, PersonStatisticsData>
// Будет извлекаться объект PersonStatistics, и по нему обрабатываться количество человек

// класс, который будет отвечать за выбор параметра и обработку последовательности Person в зависимости от параметра
class ParameterSelection {
private:
    MutableSegmentedDeque<Person>* deque;

    IDictionary<std::string, PersonStatisticsData*>* sortByMaleName(std::string parameter);
    IDictionary<std::string, PersonStatisticsData*>* sortByFemaleName(std::string parameter);
    IDictionary<std::string, PersonStatisticsData*>* sortByAge(std::string parameter);
    IDictionary<std::string, PersonStatisticsData*>* sortByGender(std::string parameter);
    IDictionary<std::string, PersonStatisticsData*>* sortByCountry(std::string parameter);
    IDictionary<std::string, PersonStatisticsData*>* sortByMaritalStatus(std::string parameter);
    IDictionary<std::string, PersonStatisticsData*>* sortByQuantityOfChildren(std::string parameter);
    IDictionary<std::string, PersonStatisticsData*>* sortByJob(std::string parameter);
    IDictionary<std::string, PersonStatisticsData*>* sortBySalary(std::string parameter);
public:
    ParameterSelection(MutableSegmentedDeque<Person>* deque);

    IDictionary<std::string, PersonStatisticsData*>* sort(std::string parameter);
};