#pragma once
#include <string>

// количества элементов в хранилищах
inline constexpr int maleNameQuantity = 26;
inline constexpr int femaleNameQuantity = 26;
inline constexpr int ageQuantity = 16;
inline constexpr int countryQuantity = 15;
inline constexpr int maritalStatusesQuantity = 5;
inline constexpr int quantityOfChildren = 7;
inline constexpr int jobQuantity = 17;


// хранилища всех возможных данных
extern std::string maleNamesStorage[maleNameQuantity];
extern std::string femaleNamesStorage[femaleNameQuantity];
extern std::string countriesStorage[countryQuantity];
extern std::string maritalStatusesStorage[maritalStatusesQuantity];
extern std::string jobsStorage[jobQuantity];