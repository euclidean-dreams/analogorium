#ifndef ANALOGORIUM_ESSENTIA_H
#define ANALOGORIUM_ESSENTIA_H

#include <ImpresarioUtils.h>
#include "Config.h"
#include "signal/Signal.h"

namespace analogorium {

enum SignalFlavor {
    SEEDLING = 0,
    STFT_REAL = 1,
    STFT_IMAGINARY = 2,
    STFT_MAGNITUDE = 3,
    EQUALIZED = 4,
    AUTO_BALANCE = 5,

    // remember to update!
    SIGNAL_FLAVOR_COUNT = 6
};

class Essentia : public impresarioUtils::NonCopyable {
private:
    std::vector<std::shared_ptr<Signal>> signals;

public:
    Essentia();

    void setSignal(SignalFlavor signalFlavor, std::unique_ptr<Signal> signal);

    std::shared_ptr<Signal> getSignal(SignalFlavor signalFlavor);

    std::unique_ptr<flatbuffers::FlatBufferBuilder> serialize() const;
};

}

#endif //ANALOGORIUM_ESSENTIA_H
