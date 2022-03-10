#ifndef ANALOGORIUM_ESSENTIA_H
#define ANALOGORIUM_ESSENTIA_H

#include <ImpresarioUtils.h>
#include "Config.h"
#include "signal/Signal.h"

namespace analogorium {

enum SignalFLavor {
    SEEDLING = 0,
    EQUALIZED = 1,
    STFT_REAL = 2,
    STFT_IMAGINARY = 3,

    // remember to update!
    SIGNAL_FLAVOR_COUNT = 4
};

class Essentia : public impresarioUtils::NonCopyable {
private:
    std::vector<std::shared_ptr<Signal>> signals;

public:
    Essentia();

    void setSignal(SignalFLavor signalFlavor, std::unique_ptr<Signal> signal);

    std::shared_ptr<Signal> getSignal(SignalFLavor signalFlavor);

    std::unique_ptr<flatbuffers::FlatBufferBuilder> serialize() const;
};

}

#endif //ANALOGORIUM_ESSENTIA_H
