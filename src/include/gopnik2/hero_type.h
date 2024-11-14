#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <fmt/core.h>

class HeroType {
public:
    enum Value : uint8_t {
        // Геймерские типы героев
        PODTSAN = 0,
        OTMOROZOK,
        GOPNIK,
        NEFOR,

        // Остальные типы героев
        BRATVA,
        BRATVA_S_OBSCHAGI,
        BESPREDELSCHIK,
        DOHLYAK,
        NARK,
        MENT,
        VETER,
        SKINHED,

        // Специальные типы, которые встречаются в сценах
        OHRANNIK,
        MANYAK,
        ULICHNYI_MAG,

        // Персонажи в центре города
        STUDENT,
        EMOKID,
        INTELLIGENT,

        // Боссы
        VAHTERSHA,
        KOMENDA,

        // Конец массива
        Count,
    };

    HeroType() = default;
    constexpr HeroType(Value type) : value(type) { }
    constexpr operator Value() const { return value; }
    explicit operator bool() const = delete;

    std::string ToString() const {
        return std::string(heroTypeStrings[value]);
    }

    static HeroType FromString(const std::string& str) {
        for (size_t i = 0; i < static_cast<size_t>(Value::Count); ++i) {
            if (std::string(heroTypeStrings[i]) == str) {
                return HeroType(static_cast<Value>(i + 1));
            }
        }
        throw std::invalid_argument("Неизвестный тип героя: " + str);
    }

private:
    Value value;

    static constexpr const std::string_view heroTypeStrings[static_cast<size_t>(Value::Count)] = {
        "Подтсан",
        "Отморозок",
        "Гопник",
        "Нефор",
        "Братва",
        "Братва с общаги",
        "Беспредельщик",
        "Дохляк",
        "Нарк",
        "Мент",
        "Ветер",
        "Скинхед",
        "Охранник",
        "Маньяк",
        "Студент",
        "Эмокид",
        "Интеллигент",
        "Вахтёрша",
        "Коменда",
        "Уличный маг"
    };
};

template <>
struct fmt::formatter<HeroType> : fmt::formatter<std::string> {
    template <typename FormatContext>
    auto format(HeroType h, FormatContext& ctx) const {
        return fmt::formatter<std::string>::format(h.ToString(), ctx);
    }
};