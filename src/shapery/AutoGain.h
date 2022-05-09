#ifndef ANALOGORIUM_AUTOGAIN_H
#define ANALOGORIUM_AUTOGAIN_H

#include "Shaper.h"
#include "AutoBalance.h"

namespace analogorium {

class AutoGain : public Shaper {
public:
    AutoBalance balancer;

    AutoGain();

    void shape(Essentia &essentia) override;
};

}

#endif //ANALOGORIUM_AUTOGAIN_H
