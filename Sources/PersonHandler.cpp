#include "PersonHandler.h"
#include "Person.h"
#include "PersonData.h"
#include <stdexcept>

#include <iostream>

// PersonStatistics

PersonStatistics::PersonStatistics() {
    int i = 0;
    //int maxIndex = std::max({maleNameQuantity, femaleNameQuantity, ageQuantity, countryQuantity, jobQuantity});
    int maxIndex = 0;
    int quantities[5] = {maleNameQuantity, femaleNameQuantity, ageQuantity, countryQuantity, jobQuantity};
    for (int i = 0; i < 5; ++i) {
        if (maxIndex < quantities[i]) {
            maxIndex = quantities[i];
        }
    }

    for (; i < maxIndex;) {
        if (i < maleNameQuantity) {
            maleNameStatistics[i] = 0;
        }
        if (i < femaleNameQuantity) {
            femaleNameStatistics[i] = 0;
        }
        if (i < ageQuantity) {
            ageStatistics[i] = 0;
        }
        if (i < countryQuantity) {
            countryStatistics[i] = 0;
        }
        if (i < jobQuantity) {
            jobStatistics[i] = 0;
        }
        ++i;
    }
}

void PersonStatistics::handlePerson(const Person* person) {
    ++quantityOfSubmittedPersons;

    handleName(person);
    handleAge(person);
    handleGender(person);
    handleCountry(person);
    handleMaritalStatus(person);
    handleQuantityOfChildren(person);
    handleJob(person);
    handleSalary(person);
}

void PersonStatistics::handleName(const Person* person) {
    std::string name = person->getName();
    if (person->getGender() == 'm') {
        for (int i = 0; i < maleNameQuantity; ++i) {
            if (name == maleNamesStorage[i]) {
                ++(maleNameStatistics[i]);
                return;
            }
        }
    } else if (person->getGender() == 'w') {
        for (int i = 0; i < femaleNameQuantity; ++i) {
            if (name == femaleNamesStorage[i]) {
                ++(femaleNameStatistics[i]);
                return;
            }
        }
    }

    if (person->getGender() != 'w' && person->getGender() != 'm') {
        throw std::invalid_argument("The wrong gender: " + person->getGender());
        return;
    }

    throw std::invalid_argument("Unknown name: " + person->getName()); // хотя немного странно, имя ведь может быть любым в теории
}

void PersonStatistics::handleAge(const Person* person) {
    if (person->getAge() > 80 || person->getAge() <= 0) {
        throw std::invalid_argument("The wrong age: " + person->getAge());
    }
    ++(ageStatistics[(person->getAge() - 1) / 5]);
}

void PersonStatistics::handleGender(const Person* person) {
    if (person->getGender() == 'm') {
        ++(genderStatistics[0]);
        return;
    } else if (person->getGender() == 'w') {
        ++(genderStatistics[1]);
        return;
    } else {
        throw std::invalid_argument("The wrong gender: " + person->getGender());
    }
}

void PersonStatistics::handleCountry(const Person* person) {
    std::string country = person->getCountry();
    for (int i = 0; i < countryQuantity; ++i) {
        if (country == countriesStorage[i]) {
            ++(countryStatistics[i]);
            return;
        }
    }
    throw std::invalid_argument("The wrong country: " + person->getCountry());
}

void PersonStatistics::handleMaritalStatus(const Person* person) {
    if (person->getAge() < 18) return; // не учитываем детей

    std::string maritalStatus = person->getMaritalStatus();
    for (int i = 0; i < 5; ++i) {
        if (maritalStatus == maritalStatusesStorage[i]) {
            ++(maritalStatusStatistics[i]);
            return;
        }
    }
    throw std::invalid_argument("The wrong marital status: " + person->getMaritalStatus());
}

void PersonStatistics::handleQuantityOfChildren(const Person* person) {
    if (person->getAge() < 18) return; // не учитываем детей
    
    if (person->getQuantityOfChildren() > 6 || person->getQuantityOfChildren() < 0) {
        throw std::invalid_argument("The wrong quantity of children: " + person->getQuantityOfChildren());
    }

    ++(quantityOfChildrenStatistics[person->getQuantityOfChildren()]);
}

void PersonStatistics::handleJob(const Person* person) {
    if (person->getAge() < 18) return; // не учитываем детей 
    // НО НАДО ИМЕТЬ В ВИДУ, ЧТО ДЕТИ ВООБЩЕ НЕ РАССМАТРИВАЮТСЯ КАСАТЕЛЬНО JOB (даже не учитывается, что они безработные)

    std::string job = person->getJob();
    for (int i = 0; i < jobQuantity; ++i) {
        if (job == jobsStorage[i]) {
            ++(jobStatistics[i]);
            return;
        }
    }
    throw std::invalid_argument("The wrong job: " + person->getJob());
}

void PersonStatistics::handleSalary(const Person* person) {
    if (person->getAge() < 18) return; // не учитываем детей

    if (person->getSalary() == 0) {
        ++(salaryStatistics[0]);
        return;
    }

    if (person->getSalary() <= 1000 || person->getSalary() > 5000) {
        throw std::invalid_argument("The wrong salary: " + person->getSalary());
    }

    ++(salaryStatistics[(person->getSalary() - 1) / 1000]);
}



// PersonStatisticsAnalyzer

PersonStatisticsData* PersonStatisticsAnalyzer::analyzeStatistics(const PersonStatistics* statistics) {
    PersonStatisticsData* data = new PersonStatisticsData();

    data->quantityOfSubmittedPersons = statistics->quantityOfSubmittedPersons;

    analyzeMaleName(statistics, data);
    analyzeFemaleName(statistics, data);
    analyzeAge(statistics, data);
    analyzeGender(statistics, data);
    analyzeCountry(statistics, data);
    analyzeMaritalStatus(statistics, data);
    analyzeQuantityOfChildren(statistics, data);
    analyzeJob(statistics, data);
    analyzeSalary(statistics, data);

    return data;
}


void PersonStatisticsAnalyzer::analyzeMaleName(const PersonStatistics* statistics, PersonStatisticsData* data) {
    int indexMostCommonMaleName = 0; // сюда записываем индекс наиболее часто встречающихся мужских имен
    int indexLeastCommonMaleName = 0; // сюда записываем индекс наименее часто встречающихся мужских имен

    int quantityMostCommonMaleName = 0; // сюда записываем индекс наиболее часто встречающихся мужских имен
    int quantityLeastCommonMaleName = 1000000000; // сюда записываем индекс наименее часто встречающихся мужских имен

    for (int i = 0; i < maleNameQuantity; ++i) {
        if (statistics->maleNameStatistics[i] > quantityMostCommonMaleName) {
            indexMostCommonMaleName = i;
            quantityMostCommonMaleName = statistics->maleNameStatistics[i];
        }

        if (statistics->maleNameStatistics[i] < quantityLeastCommonMaleName) {
            indexLeastCommonMaleName = i;
            quantityLeastCommonMaleName = statistics->maleNameStatistics[i];
        }
    }

    data->mostCommonMaleName = maleNamesStorage[indexMostCommonMaleName];
    data->leastCommonMaleName = maleNamesStorage[indexLeastCommonMaleName];
}

void PersonStatisticsAnalyzer::analyzeFemaleName(const PersonStatistics* statistics, PersonStatisticsData* data) {
    int indexMostCommonFemaleName = 0; // сюда записываем индекс наиболее часто встречающихся мужских имен
    int indexLeastCommonFemaleName = 0; // сюда записываем индекс наименее часто встречающихся мужских имен

    int quantityMostCommonFemaleName = 0; // сюда записываем индекс наиболее часто встречающихся мужских имен
    int quantityLeastCommonFemaleName = 1000000000; // сюда записываем индекс наименее часто встречающихся мужских имен

    for (int i = 0; i < femaleNameQuantity; ++i) {
        if (statistics->femaleNameStatistics[i] > quantityMostCommonFemaleName) {
            indexMostCommonFemaleName = i;
            quantityMostCommonFemaleName = statistics->femaleNameStatistics[i];
        }

        if (statistics->femaleNameStatistics[i] < quantityLeastCommonFemaleName) {
            indexLeastCommonFemaleName = i;
            quantityLeastCommonFemaleName = statistics->femaleNameStatistics[i];
        }
    }

    data->mostCommonFemaleName = femaleNamesStorage[indexMostCommonFemaleName];
    data->leastCommonFemaleName = femaleNamesStorage[indexLeastCommonFemaleName];
}

void PersonStatisticsAnalyzer::analyzeAge(const PersonStatistics* statistics, PersonStatisticsData* data) {
    int indexMostCommonAge = 0;
    int indexLeastCommonAge = 0;

    int quantityMostCommonAge = 0;
    int quantityLeastCommonAge = 100000000;

    for (int i = 0; i < ageQuantity; ++i) {
        if (statistics->ageStatistics[i] > quantityMostCommonAge) {
            indexMostCommonAge = i;
            quantityMostCommonAge = statistics->ageStatistics[i];
        }

        if (statistics->ageStatistics[i] < quantityLeastCommonAge) {
            indexLeastCommonAge = i;
            quantityLeastCommonAge = statistics->ageStatistics[i];
        }
    }

    data->mostCommonAge = "from " + std::to_string(indexMostCommonAge * 5 + 1) + " to " 
    + std::to_string((indexMostCommonAge + 1) * 5);
    data->leastCommonAge = "from " + std::to_string(indexLeastCommonAge * 5 + 1) + " to " 
    + std::to_string((indexLeastCommonAge + 1) * 5);
}

void PersonStatisticsAnalyzer::analyzeGender(const PersonStatistics* statistics, PersonStatisticsData* data) {
    int indexMostCommonGender = 0;

    int quantityMostCommonGender = 0;

    for (int i = 0; i < 2; ++i) {
        if (statistics->genderStatistics[i] > quantityMostCommonGender) {
            indexMostCommonGender = i;
            quantityMostCommonGender = statistics->genderStatistics[i];
        } 
    }

    if (indexMostCommonGender == 0) {
        data->mostCommonGender = "male";
        data->leastCommonGender = "female";
    } else {
        data->mostCommonGender = "female";
        data->leastCommonGender = "male";
    }
}

void PersonStatisticsAnalyzer::analyzeCountry(const PersonStatistics* statistics, PersonStatisticsData* data) {
    int indexMostCommonCountry = 0;
    int indexLeastCommonCountry = 0;

    int quantityMostCommonCountry = 0;
    int quantityLeastCommonCountry = 10000000;

    for (int i = 0; i < countryQuantity; ++i) {
        if (statistics->countryStatistics[i] > quantityMostCommonCountry) {
            indexMostCommonCountry = i;
            quantityMostCommonCountry = statistics->countryStatistics[i];
        }

        if (statistics->countryStatistics[i] < quantityLeastCommonCountry) {
            indexLeastCommonCountry = i;
            quantityLeastCommonCountry = statistics->countryStatistics[i];
        }
    }

    data->mostCommonCountry = countriesStorage[indexMostCommonCountry];
    data->leastCommonCountry = countriesStorage[indexLeastCommonCountry];
}

void PersonStatisticsAnalyzer::analyzeMaritalStatus(const PersonStatistics* statistics, PersonStatisticsData* data) {
    int indexMostCommonMaritalStatus = 0;
    int indexLeastCommonMaritalStatus = 0;

    int quantityMostCommonMaritalStatus = 0;
    int quantityLeastCommonMaritalStatus = 100000000;

    for (int i = 0; i < 5; ++i) {
        if (statistics->maritalStatusStatistics[i] > quantityMostCommonMaritalStatus) {
            indexMostCommonMaritalStatus = i;
            quantityMostCommonMaritalStatus = statistics->maritalStatusStatistics[i];
        }

        if (statistics->maritalStatusStatistics[i] < quantityLeastCommonMaritalStatus) {
            indexLeastCommonMaritalStatus = i;
            quantityLeastCommonMaritalStatus = statistics->maritalStatusStatistics[i];
        }        
    }

    data->mostCommonMaritalStatus = maritalStatusesStorage[indexMostCommonMaritalStatus];
    data->leastCommonMaritalStatus = maritalStatusesStorage[indexLeastCommonMaritalStatus];
}

void PersonStatisticsAnalyzer::analyzeQuantityOfChildren(const PersonStatistics* statistics, PersonStatisticsData* data) {
    int indexMostCommonQuantityOfChildren = 0;
    int indexLeastCommonQuantityOfChildren = 0;

    int quantityMostCommonQuantityOfChildren = 0;
    int quantityLeastCommonQuantityOfChildren = 100000000;

    for (int i = 0; i < 7; ++i) {
        if (statistics->quantityOfChildrenStatistics[i] > quantityMostCommonQuantityOfChildren) {
            indexMostCommonQuantityOfChildren = i;
            quantityMostCommonQuantityOfChildren = statistics->quantityOfChildrenStatistics[i];
        }

        if (statistics->quantityOfChildrenStatistics[i] < quantityLeastCommonQuantityOfChildren) {
            indexLeastCommonQuantityOfChildren = i;
            quantityLeastCommonQuantityOfChildren = statistics->quantityOfChildrenStatistics[i];
        } 
    }

    data->mostCommonQuantityOfChildren = std::to_string(indexMostCommonQuantityOfChildren);
    data->leastCommonQuantityOfChildren = std::to_string(indexLeastCommonQuantityOfChildren);
}

void PersonStatisticsAnalyzer::analyzeJob(const PersonStatistics* statistics, PersonStatisticsData* data) {
    int indexMostCommonJob = 0;
    int indexLeastCommonJob = 0;

    int quantityMostCommonJob = 0;
    int quantityLeastCommonJob = 100000000;

    for (int i = 0; i < jobQuantity; ++i) {
        if (statistics->jobStatistics[i] > quantityMostCommonJob) {
            indexMostCommonJob = i;
            quantityMostCommonJob = statistics->jobStatistics[i];
        } 
        
        if (statistics->jobStatistics[i] < quantityLeastCommonJob) {
            indexLeastCommonJob = i;
            quantityLeastCommonJob = statistics->jobStatistics[i];
        }
    }

    data->mostCommonJob = jobsStorage[indexMostCommonJob];
    data->leastCommonJob = jobsStorage[indexLeastCommonJob];
}

void PersonStatisticsAnalyzer::analyzeSalary(const PersonStatistics* statistics, PersonStatisticsData* data) {
    int indexMostCommonSalary = 0;
    int indexLeastCommonSalary = 0;

    int quantityMostCommonSalary = 0;
    int quantityLeastCommonSalary = 100000000;

    for (int i = 0; i < 5; ++i) {
        if (statistics->salaryStatistics[i] > quantityMostCommonSalary) {
            indexMostCommonSalary = i;
            quantityMostCommonSalary = statistics->salaryStatistics[i];
        }

        if (statistics->salaryStatistics[i] < quantityLeastCommonSalary) {
            indexLeastCommonSalary = i;
            quantityLeastCommonSalary = statistics->salaryStatistics[i];
        }
    }

    if (indexMostCommonSalary == 0) {
        data->mostCommonSalary = "0 - unemployed";
    } else {
        data->mostCommonSalary = "from " + std::to_string(indexMostCommonSalary * 1000 + 1) + 
        + " to " + std::to_string((indexMostCommonSalary + 1) * 1000);
    }

    if (indexLeastCommonSalary == 0) {
        data->leastCommonSalary = "0 - unemployed";
    } else {
        data->leastCommonSalary = "from " + std::to_string(indexLeastCommonSalary * 1000 + 1) + 
        + " to " + std::to_string((indexLeastCommonSalary + 1) * 1000);
    }
}

void printPersonStatisticsData(PersonStatisticsData* data) {
    std::cout << "mostCommonMaleName = " << data->mostCommonMaleName << "\n";
    std::cout << "leastCommonMaleName = " << data->leastCommonMaleName << "\n";

    std::cout << "mostCommonFemaleName = " << data->mostCommonFemaleName << "\n";
    std::cout << "leasstCommonFealeName = " << data->leastCommonFemaleName << "\n";

    std::cout << "mostCommonAge = " << data->mostCommonAge << "\n";
    std::cout << "leastCommonAge = " << data->leastCommonAge << "\n";

    std::cout << "mostCommonGender = " << data->mostCommonGender << "\n";
    std::cout << "leastCommonGender = " << data->leastCommonGender << "\n";

    std::cout << "mostCommonCountry = " << data->mostCommonCountry << "\n";
    std::cout << "leastCommonCountry = " << data->leastCommonCountry << "\n";
    
    std::cout << "mostCommonMaritalStatus = " << data->mostCommonMaritalStatus << "\n";
    std::cout << "leastCommonMaritalStatus = " << data->leastCommonMaritalStatus << "\n";

    std::cout << "mostCommonQuantityOfChildren = " << data->mostCommonQuantityOfChildren << "\n";
    std::cout << "leastCommonQuantityOfChildren = " << data->leastCommonQuantityOfChildren << "\n";

    std::cout << "mostCommonJob = " << data->mostCommonJob << "\n";
    std::cout << "leastCommonJob = " << data->leastCommonJob << "\n";

    std::cout << "mostCommonSalary = " << data->mostCommonSalary << "\n";
    std::cout << "leastCommonSalary = " << data->leastCommonSalary << "\n";
}