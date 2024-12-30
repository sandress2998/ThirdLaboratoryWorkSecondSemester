#include "Person.h"
#include "PersonHandler.h"
#include "Dictionary.h"
#include "ParameterSelection.h"
#include "PersonParser.h"

#include <string>
#include <iostream>
#include <cassert>

#include <fstream>


void printPersonStatisticsData(PersonStatisticsData* data);
void writeTheResultToAFile(IDictionary<std::string, PersonStatisticsData*>* dictionary);

int main() {
    std::string str = "Olivia 74 w Russia Married 4 Salesman 3025";
    Person p = parsePerson(str);
    std::cout << p.getName() << " " << p.getAge() << " " << p.getGender() << " " << p.getCountry() << " "
        << p.getMaritalStatus() << " " << p.getQuantityOfChildren() << " " << p.getJob() << " " << p.getSalary() << "\n";
    /*
    MutableSegmentedDeque<Person>* persons = new MutableSegmentedDeque<Person>();
    for (int i = 0; i < 100; ++i) {
        persons->append(generatePerson());
        Person p = persons->getLast();
        std::cout << p.getName() << " " << p.getAge() << " " << p.getGender() << " " << p.getCountry() << " "
        << p.getMaritalStatus() << " " << p.getQuantityOfChildren() << " " << p.getJob() << " " << p.getSalary() << "\n";
    }

    ParameterSelection parameterSelection(persons);
    IDictionary<std::string, PersonStatisticsData*>* dictionary = parameterSelection.sort("salary");

    writeTheResultToAFile(dictionary);
    MutableSegmentedDeque<std::string>* keys = dictionary->getKeys();
    for (int i = 0; i < dictionary->getSize(); ++i) {
        delete dictionary->getValue(keys->get(i));
    }
    delete keys;
    */
}

void writeTheResultToAFile(IDictionary<std::string, PersonStatisticsData*>* dictionary) { 
    std::ofstream out;
    out.open("results.txt");
    if (out.is_open()) {
        MutableSegmentedDeque<std::string>* keys = dictionary->getKeys();
        std::string category;
        for (int i = 0; i < dictionary->getSize(); ++i) {
            category = keys->get(i);
            out << "quantityOfPeople = " << dictionary->getValue(category)->quantityOfSubmittedPersons << "\n";

            out << "mostCommonMaleName = " << dictionary->getValue(category)->mostCommonMaleName << "\n";
            out << "leastCommonMaleName = " << dictionary->getValue(category)->leastCommonMaleName << "\n";

            out << "mostCommonFemaleName = " << dictionary->getValue(category)->mostCommonFemaleName << "\n";
            out << "leastCommonFemaleName = " << dictionary->getValue(category)->leastCommonFemaleName << "\n";

            out << "mostCommonAge = " << dictionary->getValue(category)->mostCommonAge << "\n";
            out << "leastCommonAge = " << dictionary->getValue(category)->leastCommonAge << "\n";

            out << "mostCommonGender = " << dictionary->getValue(category)->mostCommonGender << "\n";
            out << "leastCommonGender = " << dictionary->getValue(category)->leastCommonGender << "\n";

            out << "mostCommonCountry = " << dictionary->getValue(category)->mostCommonCountry << "\n";
            out << "leastCommonCountry = " << dictionary->getValue(category)->leastCommonCountry << "\n";
            
            out << "mostCommonMaritalStatus = " << dictionary->getValue(category)->mostCommonMaritalStatus << "\n";
            out << "leastCommonMaritalStatus = " << dictionary->getValue(category)->leastCommonMaritalStatus << "\n";

            out << "mostCommonQuantityOfChildren = " << dictionary->getValue(category)->mostCommonQuantityOfChildren << "\n";
            out << "leastCommonQuantityOfChildren = " << dictionary->getValue(category)->leastCommonQuantityOfChildren << "\n";

            out << "mostCommonJob = " << dictionary->getValue(category)->mostCommonJob << "\n";
            out << "leastCommonJob = " << dictionary->getValue(category)->leastCommonJob << "\n";

            out << "mostCommonSalary = " << dictionary->getValue(category)->mostCommonSalary << "\n";
            out << "leastCommonSalary = " << dictionary->getValue(category)->leastCommonSalary << "\n";
            out << "\n\n";
        }
        out.close(); 
        std::cout << "File has been written" << std::endl;
        delete keys;
    }
}