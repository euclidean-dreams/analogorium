#ifndef ANALOGORIUM_AUTOBALANCE_H
#define ANALOGORIUM_AUTOBALANCE_H

#include <list>
#include "signal/Signal.h"
#include "Shaper.h"

namespace analogorium {

class AutoBalance : public Shaper {
public:
    int signalStartIndex;
    int signalEndIndex;
    float ceilingTarget;
    float sampleMultiplier;
    std::list<float> history;
    int historySize;

    AutoBalance(
            int signalStartIndex,
            int signalEndIndex,
            float target
    );

    void balance(Signal &signal);

    void shape(Essentia &essentia);
};

}

#endif //ANALOGORIUM_AUTOBALANCE_H
