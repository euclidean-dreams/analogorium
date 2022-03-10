#ifndef ANALOGORIUM_SHAPERY_H
#define ANALOGORIUM_SHAPERY_H

#include <ImpresarioUtils.h>
#include "primordium/SignalConduit.h"
#include "StftShaper.h"

namespace analogorium {

class Shapery : public impresarioUtils::Circulable {
private:
    std::shared_ptr<SignalConduit> input;
    std::unique_ptr<impresarioUtils::NetworkSocket> output;
    std::vector<std::unique_ptr<Shaper>> shapers;

public:
    Shapery(std::shared_ptr<SignalConduit> input, std::unique_ptr<impresarioUtils::NetworkSocket> output);

    void activate() override;
};

}

#endif //ANALOGORIUM_SHAPERY_H
