#include <stdexcept>

#include "gopnik2/hero_type.h"

std::string HeroType::ToString() const {
    return std::string(heroTypeStrings[value]);
}

HeroType HeroType::FromString(const std::string& str) {
    for (size_t i = 0; i < static_cast<size_t>(Value::Count); ++i) {
        if (std::string(heroTypeStrings[i]) == str) {
            return HeroType(static_cast<Value>(i));
        }
    }
    throw std::invalid_argument("Неизвестный тип героя: " + str);
}

