#ifndef ANALOGORIUM_AUTOBALANCE_H
#define ANALOGORIUM_AUTOBALANCE_H

#include <list>
#include "signal/Signal.h"

namespace analogorium {

class AutoBalance {
public:
    int signalStartIndex;
    int signalEndIndex;
    float ceilingTarget;
    float gain;
    std::list<float> history;
    int historySize;

    AutoBalance(
            int signalStartIndex,
            int signalEndIndex,
            float target
    );

    void balance(Signal &signal);
};

}

#endif //ANALOGORIUM_AUTOBALANCE_H
