#include "observation.h"

namespace WarSpider {

bool Observation::isValid() const {
    return mac.length() > 0;
}

}