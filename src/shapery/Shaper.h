#ifndef ANALOGORIUM_SHAPER_H
#define ANALOGORIUM_SHAPER_H

#include <ImpresarioUtils.h>
#include "signal/Essentia.h"

namespace analogorium {

class Shaper : public impresarioUtils::NonCopyable {
public:
    virtual void shape(Essentia &essentia) = 0;
};

}

#endif //ANALOGORIUM_SHAPER_H
