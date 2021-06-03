#ifndef ENUMUTIL_H
#define ENUMUTIL_H

#include <unordered_map>


#define DECLARE_ENUM(VAL) VAL,
#define DECLARE_ENUM_WITH_VAL(NAME, VAL) NAME = VAL,
#define DECLARE_ENUM_WITH_NAMES(VAL, STR) DECLARE_ENUM(VAL)
#define DECLARE_ENUM_WITH_NAMES_VAL(NAME, STR, VAL) DECLARE_ENUM_WITH_VAL(NAME, VAL)
#define DECLARE_ENUM_WITH_VAL_NAMES(NAME, VAL, STR) DECLARE_ENUM_WITH_VAL(NAME, VAL)

#define DECLARE_ENUM_C(TYPE, VAL) VAL,
#define DECLARE_ENUM_C_WITH_VAL(TYPE, NAME, VAL) NAME = VAL,
#define DECLARE_ENUM_C_WITH_NAMES(TYPE, VAL, STR) DECLARE_ENUM(VAL)
#define DECLARE_ENUM_C_WITH_NAMES_VAL(TYPE, NAME, STR, VAL) DECLARE_ENUM_WITH_VAL(NAME, VAL)
#define DECLARE_ENUM_C_WITH_VAL_NAMES(TYPE, NAME, VAL, STR) DECLARE_ENUM_WITH_VAL(NAME, VAL)


#define ENUM(NAME) \
    enum NAME##_enum \
    { \
        NAME(DECLARE_ENUM) \
    };

#define ENUM_C(NAME) \
    enum class NAME##_enum \
    { \
        NAME(DECLARE_ENUM_C) \
    };

#define ENUM_WITH_VAL(NAME) \
    enum NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_VAL) \
    };

#define ENUM_C_WITH_VAL(NAME) \
    enum class NAME##_enum \
    { \
        NAME(DECLARE_ENUM_C_WITH_VAL) \
    };

#define ENUM_WITH_NAMES(NAME) \
    enum NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_NAMES) \
    };

#define ENUM_C_WITH_NAMES(NAME) \
    enum class NAME##_enum \
    { \
        NAME(DECLARE_ENUM_C_WITH_NAMES) \
    };

#define ENUM_WITH_NAMES_VAL(NAME) \
    enum NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_NAMES_VAL) \
    };

#define ENUM_C_WITH_NAMES_VAL(NAME) \
    enum class NAME##_enum \
    { \
        NAME(DECLARE_ENUM_C_WITH_NAMES_VAL) \
    };

#define ENUM_WITH_VAL_NAMES(NAME) \
    enum NAME##_enum \
    { \
        NAME(DECLARE_ENUM_WITH_VAL_NAMES) \
    };

#define ENUM_C_WITH_VAL_NAMES(NAME) \
    enum class NAME##_enum \
    { \
        NAME(DECLARE_ENUM_C_WITH_VAL_NAMES) \
    };


#define DECLARE_STR_TO_ENUM(VAL) { #VAL, VAL },
#define DECLARE_STR_TO_ENUM_WITH_NAMES(VAL, STR) { STR, VAL },
#define DECLARE_STR_TO_ENUM_WITH_VAL(NAME, VAL) { #NAME, NAME },
#define DECLARE_STR_TO_ENUM_WITH_VAL_NAMES(NAME, VAL, STR) { STR, NAME },
#define DECLARE_STR_TO_ENUM_WITH_NAMES_VAL(NAME, STR, VAL) { STR, NAME },


#define DECLARE_STR_TO_ENUM_C(TYPE, VAL) { #VAL, TYPE##_enum::##VAL },
#define DECLARE_STR_TO_ENUM_C_WITH_NAMES(TYPE, VAL, STR) { STR, TYPE##_enum::##VAL },
#define DECLARE_STR_TO_ENUM_C_WITH_VAL(TYPE, NAME, VAL) { #NAME, TYPE##_enum::##NAME },
#define DECLARE_STR_TO_ENUM_C_WITH_VAL_NAMES(TYPE, NAME, VAL, STR) { STR, TYPE##_enum::##NAME },
#define DECLARE_STR_TO_ENUM_C_WITH_NAMES_VAL(TYPE, NAME, STR, VAL) { STR, TYPE##_enum::##NAME },


#define STR_TO_ENUM_DECL(NAME) extern std::unordered_map<std::string, NAME##_enum> NAME##_from_str;

#define STR_TO_ENUM(NAME) \
    std::unordered_map<std::string, NAME##_enum> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM) \
    };

#define STR_TO_ENUM_WTIH_VAL(NAME) \
    std::unordered_map<std::string, NAME##_enum> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_WITH_VAL) \
    };

#define STR_TO_ENUM_WITH_NAMES(NAME) \
    std::unordered_map<std::string, NAME##_enum> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_WITH_NAMES) \
    };

#define STR_TO_ENUM_WITH_VAL_NAMES(NAME) \
    std::unordered_map<std::string, NAME##_enum> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_WITH_VAL_NAMES) \
    };

#define STR_TO_ENUM_WITH_NAMES_VAL(NAME) \
    std::unordered_map<std::string, NAME##_enum> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_WITH_NAMES_VAL) \
    };


#define STR_TO_ENUM_C(NAME) \
    std::unordered_map<std::string, NAME##_enum> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_C) \
    };

#define STR_TO_ENUM_C_WTIH_VAL(NAME) \
    std::unordered_map<std::string, NAME##_enum> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_C_WITH_VAL) \
    };

#define STR_TO_ENUM_C_WITH_NAMES(NAME) \
    std::unordered_map<std::string, NAME##_enum> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_C_WITH_NAMES) \
    };

#define STR_TO_ENUM_C_WITH_VAL_NAMES(NAME) \
    std::unordered_map<std::string, NAME##_enum> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_C_WITH_VAL_NAMES) \
    };

#define STR_TO_ENUM_C_WITH_NAMES_VAL(NAME) \
    std::unordered_map<std::string, NAME##_enum> NAME##_from_str = { \
        NAME(DECLARE_STR_TO_ENUM_C_WITH_NAMES_VAL) \
    };



#define DECLARE_ENUM_TO_STR(VAL) { VAL, #VAL },
#define DECLARE_ENUM_TO_STR_WITH_NAMES(VAL, STR) { VAL, STR },
#define DECLARE_ENUM_TO_STR_WITH_VAL(NAME, VAL) { NAME, #NAME },
#define DECLARE_ENUM_TO_STR_WITH_VAL_NAMES(NAME, VAL, STR) { NAME, STR },
#define DECLARE_ENUM_TO_STR_WITH_NAMES_VAL(NAME, STR, VAL) { NAME, STR },


#define ENUM_TO_STR_DECL(NAME) extern std::unordered_map<NAME##_enum, std::string> NAME##_to_str;

#define ENUM_TO_STR(NAME) \
    std::unordered_map<NAME##_enum, std::string> NAME##_to_str = { \
        NAME(DECLARE_ENUM_TO_STR) \
    };

#define ENUM_TO_STR_WTIH_VAL(NAME) \
    std::unordered_map<NAME##_enum, std::string> NAME##_to_str = { \
        NAME(DECLARE_ENUM_TO_STR_WITH_VAL) \
    };

#define ENUM_TO_STR_WITH_NAMES(NAME) \
    std::unordered_map<NAME##_enum, std::string> NAME##_to_str = { \
        NAME(DECLARE_ENUM_TO_STR_WITH_NAMES) \
    };

#define ENUM_TO_STR_WITH_VAL_NAMES(NAME) \
    std::unordered_map<NAME##_enum, std::string> NAME##_to_str = { \
        NAME(DECLARE_ENUM_TO_STR_WITH_VAL_NAMES) \
    };

#define ENUM_TO_STR_WITH_NAMES_VAL(NAME) \
    std::unordered_map<NAME##_enum, std::string> NAME##_to_str = { \
        NAME(DECLARE_ENUM_TO_STR_WITH_NAMES_VAL) \
    };


#define DECLARE_ENUM_C_TO_STR(TYPE, VAL) { TYPE##_enum::##VAL, #VAL },
#define DECLARE_ENUM_C_TO_STR_WITH_NAMES(TYPE, VAL, STR) { TYPE##_enum::##VAL, STR },
#define DECLARE_ENUM_C_TO_STR_WITH_VAL(TYPE, NAME, VAL) { TYPE##_enum::##NAME, #NAME },
#define DECLARE_ENUM_C_TO_STR_WITH_VAL_NAMES(TYPE, NAME, VAL, STR) { TYPE##_enum::##NAME, STR },
#define DECLARE_ENUM_C_TO_STR_WITH_NAMES_VAL(TYPE, NAME, STR, VAL) { TYPE##_enum::##NAME, STR },


#define ENUM_C_TO_STR(NAME) \
    std::unordered_map<NAME##_enum, std::string> NAME##_to_str = { \
        NAME(DECLARE_ENUM_C_TO_STR) \
    };

#define ENUM_C_TO_STR_WTIH_VAL(NAME) \
    std::unordered_map<NAME##_enum, std::string> NAME##_to_str = { \
        NAME(DECLARE_ENUM_C_TO_STR_WITH_VAL) \
    };

#define ENUM_C_TO_STR_WITH_NAMES(NAME) \
    std::unordered_map<NAME##_enum, std::string> NAME##_to_str = { \
        NAME(DECLARE_ENUM_C_TO_STR_WITH_NAMES) \
    };

#define ENUM_C_TO_STR_WITH_VAL_NAMES(NAME) \
    std::unordered_map<NAME##_enum, std::string> NAME##_to_str = { \
        NAME(DECLARE_ENUM_C_TO_STR_WITH_VAL_NAMES) \
    };

#define ENUM_C_TO_STR_WITH_NAMES_VAL(NAME) \
    std::unordered_map<NAME##_enum, std::string> NAME##_to_str = { \
        NAME(DECLARE_ENUM_C_TO_STR_WITH_NAMES_VAL) \
    };


#endif // ENUMUTIL_H
