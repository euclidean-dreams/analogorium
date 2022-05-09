#ifndef ANALOGORIUM_AUTOEQUALIZER_H
#define ANALOGORIUM_AUTOEQUALIZER_H

#include "shapery/Shaper.h"
#include "shapery/AutoBalance.h"

namespace analogorium {

class AutoEqualizer: public Shaper {
public:
    std::vector<std::unique_ptr<AutoBalance>> balancers;

    AutoEqualizer();

    void shape(Essentia &essentia) override;

};

}

#endif //ANALOGORIUM_AUTOEQUALIZER_H
