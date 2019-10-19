#ifndef ENUMUTIL_H
#define ENUMUTIL_H

#include <unordered_map>


#define DECLARE_ENUM(VAL) VAL,
#define DECLARE_ENUM_WITH_VAL(NAME, VAL) NAME = VAL,
#define DECLARE_ENUM_WITH_NAMES(VAL, STR) DECLARE_ENUM(VAL)
#define DECLARE_ENUM_WITH_NAMES_VAL(NAME, STR, VAL) DECLARE_ENUM_WITH_VAL(NAME, VAL)
#define DECLARE_ENUM_WITH_VAL_NAMES(NAME, VAL, STR) DECLARE_ENUM_WITH_VAL(NAME, VAL)


#define ENUM(NAME) \
    enum NAME##_enum \
    { \
        NAME(DECLARE_ENUM) \
    };

#define ENUM_C(NAME) \
    enum class NAME##_enum \
    { \
        NAME(DECLARE_ENUM) \
    };

#define ENUM_WITH_VAL(NAME) \
    enum NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_VAL) \
    };

#define ENUM_C_WITH_VAL(NAME) \
    enum class NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_VAL) \
    };

#define ENUM_WITH_NAMES(NAME) \
    enum NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_NAMES) \
    };

#define ENUM_C_WITH_NAMES(NAME) \
    enum class NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_NAMES) \
    };

#define ENUM_WITH_NAMES_VAL(NAME) \
    enum NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_NAMES_VAL) \
    };

#define ENUM_C_WITH_NAMES_VAL(NAME) \
    enum class NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_NAMES_VAL) \
    };

#define ENUM_WITH_VAL_NAMES(NAME) \
    enum NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_VAL_NAMES) \
    };

#define ENUM_C_WITH_VAL_NAMES(NAME) \
    enum class NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_VAL_NAMES) \
    };


#define DECLARE_STR_TO_ENUM(VAL) { #VAL, VAL },
#define DECLARE_STR_TO_ENUM_WITH_NAMES(VAL, STR) { STR, VAL },
#define DECLARE_STR_TO_ENUM_WITH_VAL(NAME, VAL) { #NAME, NAME },
#define DECLARE_STR_TO_ENUM_WITH_VAL_NAMES(NAME, VAL, STR) { STR, NAME },
#define DECLARE_STR_TO_ENUM_WITH_NAMES_VAL(NAME, STR, VAL) { STR, NAME },


#define STR_TO_ENUM_DELC(NAME) extern std::unordered_map<std::string, int> NAME##_from_str;

#define STR_TO_ENUM(NAME) \
    std::unordered_map<std::string, int> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM) \
    };

#define STR_TO_ENUM_WTIH_VAL(NAME) \
    std::unordered_map<std::string, int> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_WITH_VAL) \
    };

#define STR_TO_ENUM_WITH_NAMES(NAME) \
    std::unordered_map<std::string, int> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_WITH_NAMES) \
    };

#define STR_TO_ENUM_WITH_VAL_NAMES(NAME) \
    std::unordered_map<std::string, int> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_WITH_VAL_NAMES) \
    };


#endif // ENUMUTIL_H
