#include <enumutil.h>


#define CustomEnum(DO) \
    DO(VAL1) \
    DO(VAL2) \
    DO(VAL3)

ENUM(CustomEnum)
