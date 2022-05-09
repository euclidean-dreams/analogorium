#ifndef ANALOGORIUM_EQUALIZER_H
#define ANALOGORIUM_EQUALIZER_H

#include "shapery/Shaper.h"

namespace analogorium {

class Equalizer : public Shaper {
public:
    float gain;
    float sampleRate;
    std::map<int, float> scalingFactors;

    Equalizer();

    void shape(Essentia &essentia) override;
};

}

#endif //ANALOGORIUM_EQUALIZER_H
