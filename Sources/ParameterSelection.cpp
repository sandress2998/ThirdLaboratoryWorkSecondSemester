#include "ParameterSelection.h"
#include "MutableSegmentedDeque.h"
#include "PersonHandler.h"
#include "Person.h"
#include "Dictionary.h"
#include "PersonData.h"

#include <iostream>

ParameterSelection::ParameterSelection(MutableSegmentedDeque<Person>* deque): deque(deque) {}

IDictionary<std::string, PersonStatisticsData*>* ParameterSelection::sort(std::string parameter) {

    if (parameter == "maleName") {
        return sortByMaleName(parameter); 
    } else if (parameter == "femaleName") {
        return sortByFemaleName(parameter);
    } else if (parameter == "age") {
        return sortByAge(parameter);
    } else if (parameter == "gender") {
        return sortByGender(parameter);
    } else if (parameter == "country") {
        return sortByCountry(parameter);
    } else if (parameter == "maritalStatus") {
        return sortByMaritalStatus(parameter);
    } else if (parameter == "quantityOfChildren") {
        return sortByQuantityOfChildren(parameter);
    } else if (parameter == "job") {
        return sortByJob(parameter);
    } else if (parameter == "salary") {
        return sortBySalary(parameter);
    } else {
        throw std::invalid_argument("The wrong parameter");
    }
}

IDictionary<std::string, PersonStatisticsData*>* ParameterSelection::sortByMaleName(std::string parameter) {
    // надо создать список, где ключом будет являться мужское имя, а PersonStatisticData - аналитика по личностям,
    // попадающих в конкретное множество
    Dictionary<std::string, PersonStatisticsData*>* result = new Dictionary<std::string, PersonStatisticsData*>();
    MutableSegmentedDeque<PersonStatistics>* statisticsDeque = new MutableSegmentedDeque<PersonStatistics>();
    std::string name;
    for (int i = 0; i < maleNameQuantity; ++i) {
        statisticsDeque->append(PersonStatistics());
    }

    // заполняем статистику
    for (int i = 0; i < deque->getLength(); ++i) {
        // если человек женского пола, то пропускаем его
        if (deque->get(i).getGender() == 'w') {
            continue;
        }

        for (int j = 0; j < maleNameQuantity; ++j) {
            if (deque->get(i).getName() == maleNamesStorage[j]) {
                ((*statisticsDeque)[j]).handlePerson(&(deque->get(i)));
                break;
            }
        }
    }

    PersonStatisticsAnalyzer analyzer;
    
    // для каждого объекта PersonStatistics, который, в свою очередь, соответствует одному мужскому имени, 
    // анализируем статистику и создаем элемент в словаре: "имя": результат обработки статистики 
    for (int i = 0; i < maleNameQuantity; ++i) {
        result->append(maleNamesStorage[i], analyzer.analyzeStatistics(&statisticsDeque->get(i)));
    }

    delete statisticsDeque;
    return result;
}

IDictionary<std::string, PersonStatisticsData*>* ParameterSelection::sortByFemaleName(std::string parameter) {
    Dictionary<std::string, PersonStatisticsData*>* result = new Dictionary<std::string, PersonStatisticsData*>();
    MutableSegmentedDeque<PersonStatistics>* statisticsDeque = new MutableSegmentedDeque<PersonStatistics>();

    for (int i = 0; i < femaleNameQuantity; ++i) {
        statisticsDeque->append(PersonStatistics());
    }

    for (int i = 0; i < femaleNameQuantity; ++i) {
        if (deque->get(i).getGender() == 'm') {
            continue;
        }

        for (int j = 0; j < femaleNameQuantity; ++j) {
            if (deque->get(i).getName() == femaleNamesStorage[j]) {
                ((*statisticsDeque)[j]).handlePerson(&(deque->get(i)));
                break;
            }
        }
    }

    PersonStatisticsAnalyzer analyzer;
    
    // для каждого объекта PersonStatistics, который, в свою очередь, соответствует одному мужскому имени, 
    // анализируем статистику и создаем элемент в словаре: "имя": результат обработки статистики 
    for (int i = 0; i < femaleNameQuantity; ++i) {
        result->append(femaleNamesStorage[i], analyzer.analyzeStatistics(&statisticsDeque->get(i)));
    }


    delete statisticsDeque;
    return result;
}

IDictionary<std::string, PersonStatisticsData*>* ParameterSelection::sortByAge(std::string parameter) {
    Dictionary<std::string, PersonStatisticsData*>* result = new Dictionary<std::string, PersonStatisticsData*>();
    MutableSegmentedDeque<PersonStatistics>* statisticsDeque = new MutableSegmentedDeque<PersonStatistics>();

    for (int i = 0; i < ageQuantity; ++i) {
        statisticsDeque->append(PersonStatistics());
    }

    // растасовываем людей по группам и учитываем их в статистике соответствующей группы
    for (int i = 0; i < deque->getLength(); ++i) {
        (*statisticsDeque)[(deque->get(i).getAge() - 1) / 5].handlePerson(&(deque->get(i)));
    }

    PersonStatisticsAnalyzer analyzer;
    
    // для каждого объекта PersonStatistics, который, в свою очередь, соответствует одной возрастной категории, 
    // к примеру, 6 - 10 лет, 16-20 лет, 61 - 65 лет, анализируем статистику и создаем элемент в словаре:
    // "возрастная категория": результат обработки статистики 
    for (int i = 0; i < ageQuantity; ++i) {
        result->append(std::to_string(i * 5 + 1) + " - " + std::to_string((i + 1) * 5), analyzer.analyzeStatistics(&statisticsDeque->get(i)));
    }

    delete statisticsDeque;
    return result;
}

IDictionary<std::string, PersonStatisticsData*>* ParameterSelection::sortByGender(std::string parameter) {
    Dictionary<std::string, PersonStatisticsData*>* result = new Dictionary<std::string, PersonStatisticsData*>();
    MutableSegmentedDeque<PersonStatistics>* statisticsDeque = new MutableSegmentedDeque<PersonStatistics>();

    for (int i = 0; i < 2; ++i) {
        statisticsDeque->append(PersonStatistics());
    }

    for (int i = 0; i < deque->getLength(); ++i) {
        if (deque->get(i).getGender() == 'm') {
            (*statisticsDeque)[0].handlePerson(&(deque->get(i)));
        } else {
            (*statisticsDeque)[1].handlePerson(&(deque->get(i)));
        }
    }

    PersonStatisticsAnalyzer analyzer;

    result->append("male", analyzer.analyzeStatistics(&statisticsDeque->get(0)));
    result->append("female", analyzer.analyzeStatistics(&statisticsDeque->get(1)));

    delete statisticsDeque;
    return result;
}

IDictionary<std::string, PersonStatisticsData*>* ParameterSelection::sortByCountry(std::string parameter) {
    Dictionary<std::string, PersonStatisticsData*>* result = new Dictionary<std::string, PersonStatisticsData*>();
    MutableSegmentedDeque<PersonStatistics>* statisticsDeque = new MutableSegmentedDeque<PersonStatistics>();

    for (int i = 0; i < countryQuantity; ++i) {
        statisticsDeque->append(PersonStatistics());
    }

    for (int i = 0; i < deque->getLength(); ++i) {
        for (int j = 0; j < countryQuantity; ++j) {
            if (deque->get(i).getCountry() == countriesStorage[j]) {
                (*statisticsDeque)[j].handlePerson(&deque->get(i));
                break;
            }
        }
    }

    PersonStatisticsAnalyzer analyzer;

    for (int i = 0; i < countryQuantity; ++i) {
        result->append(countriesStorage[i], analyzer.analyzeStatistics(&statisticsDeque->get(i)));
    }

    delete statisticsDeque;
    return result;
}

IDictionary<std::string, PersonStatisticsData*>* ParameterSelection::sortByMaritalStatus(std::string parameter) {
    Dictionary<std::string, PersonStatisticsData*>* result = new Dictionary<std::string, PersonStatisticsData*>();
    MutableSegmentedDeque<PersonStatistics>* statisticsDeque = new MutableSegmentedDeque<PersonStatistics>();

    for (int i = 0; i < maritalStatusesQuantity; ++i) {
        statisticsDeque->append(PersonStatistics());
    }

    for (int i = 0; i < deque->getLength(); ++i) {
        for (int j = 0; j < maritalStatusesQuantity; ++j) {
            if (deque->get(i).getMaritalStatus() == maritalStatusesStorage[j]) {
                (*statisticsDeque)[j].handlePerson(&deque->get(i));
                break;
            }
        }
    }

    PersonStatisticsAnalyzer analyzer;

    for (int i = 0; i < maritalStatusesQuantity; ++i) {
        result->append(maritalStatusesStorage[i], analyzer.analyzeStatistics(&statisticsDeque->get(i)));
    }

    delete statisticsDeque;
    return result;
}

IDictionary<std::string, PersonStatisticsData*>* ParameterSelection::sortByQuantityOfChildren(std::string parameter) {
    Dictionary<std::string, PersonStatisticsData*>* result = new Dictionary<std::string, PersonStatisticsData*>();
    MutableSegmentedDeque<PersonStatistics>* statisticsDeque = new MutableSegmentedDeque<PersonStatistics>();

    for (int i = 0; i < quantityOfChildren; ++i) {
        statisticsDeque->append(PersonStatistics());
    }
    
    for (int i = 0; i < deque->getLength(); ++i) {
        (*statisticsDeque)[deque->get(i).getQuantityOfChildren()].handlePerson(&deque->get(i));
    }

    PersonStatisticsAnalyzer analyzer;

    for (int i = 0; i < quantityOfChildren; ++i) {
        result->append(std::to_string(i), analyzer.analyzeStatistics(&statisticsDeque->get(i)));
    }

    delete statisticsDeque;
    return result;
}

IDictionary<std::string, PersonStatisticsData*>* ParameterSelection::sortByJob(std::string parameter) {
    Dictionary<std::string, PersonStatisticsData*>* result = new Dictionary<std::string, PersonStatisticsData*>();
    MutableSegmentedDeque<PersonStatistics>* statisticsDeque = new MutableSegmentedDeque<PersonStatistics>();

    for (int i = 0; i < jobQuantity; ++i) {
        statisticsDeque->append(PersonStatistics());
    }

      for (int i = 0; i < deque->getLength(); ++i) {
        for (int j = 0; j < jobQuantity; ++j) {
            if (deque->get(i).getJob() == jobsStorage[j]) {
                (*statisticsDeque)[j].handlePerson(&deque->get(i));
                break;
            }
        }
    }

    PersonStatisticsAnalyzer analyzer;

    for (int i = 0; i < jobQuantity; ++i) {
        result->append(jobsStorage[i], analyzer.analyzeStatistics(&statisticsDeque->get(i)));
    }


    delete statisticsDeque;
    return result;
}

IDictionary<std::string, PersonStatisticsData*>* ParameterSelection::sortBySalary(std::string parameter) {
    Dictionary<std::string, PersonStatisticsData*>* result = new Dictionary<std::string, PersonStatisticsData*>();
    MutableSegmentedDeque<PersonStatistics>* statisticsDeque = new MutableSegmentedDeque<PersonStatistics>();

    for (int i = 0; i < 5; ++i) {
        statisticsDeque->append(PersonStatistics());
    }
    
    for (int i = 0; i < deque->getLength(); ++i) {
        if (deque->get(i).getSalary() == 0) {
            (*statisticsDeque)[0].handlePerson(&deque->get(i));
        } else {
            (*statisticsDeque)[(deque->get(i).getSalary() - 1) / 1000].handlePerson(&deque->get(i));
        }
    }

    PersonStatisticsAnalyzer analyzer;

    for (int i = 0; i < 5; ++i) {
        result->append(std::to_string(i), analyzer.analyzeStatistics(&statisticsDeque->get(i)));
    }

    delete statisticsDeque;
    return result;
}

