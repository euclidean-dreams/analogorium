#ifndef ANALOGORIUM_EQUALIZER_H
#define ANALOGORIUM_EQUALIZER_H

#include "Shaper.h"

namespace analogorium {

class Equalizer : public Shaper {
public:
    float gain;

    Equalizer();

    void shape(Essentia &essentia) override;
};

}

#endif //ANALOGORIUM_EQUALIZER_H
