//
// Created by 龚喜 on 2024/8/22.
//
#ifndef ASSIMPDEMO_ENUM_H
#define ASSIMPDEMO_ENUM_H

#include <string>
#include <cassert>
#include <optional>

namespace roamgl {

template <typename T>
class Enum {
public:
    using Type = T;
    static const char * toString(T);
    static std::optional<T> toEnum(const std::string&);
};

#define MBGL_DEFINE_ENUM(T, values...)                                          \
                                                                                \
static const constexpr std::pair<const T, const char *> T##_names[] = values;   \
                                                                                \
template <>                                                                     \
const char * Enum<T>::toString(T t) {                                           \
    auto it = std::find_if(std::begin(T##_names), std::end(T##_names),          \
        [&] (const auto& v) { return t == v.first; });                          \
    assert(it != std::end(T##_names)); return it->second;                       \
}                                                                               \
                                                                                \
template <>                                                                     \
std::optional<T> Enum<T>::toEnum(const std::string& s) {                             \
    auto it = std::find_if(std::begin(T##_names), std::end(T##_names),          \
        [&] (const auto& v) { return s == v.second; });                         \
    return it == std::end(T##_names) ? std::optional<T>() : it->first;               \
}

} // namespace mbgl



#endif //ASSIMPDEMO_ENUM_H
