#ifndef ANALOGORIUM_SIGNALCONDUIT_H
#define ANALOGORIUM_SIGNALCONDUIT_H

#include <ImpresarioUtils.h>
#include "signal/Signal.h"

namespace analogorium {

class SignalConduit : public impresarioUtils::NonCopyable {
public:
    virtual bool nextSignalIsReady() const = 0;

    virtual void waitUntilNextSignalIsReady() = 0;

    virtual std::unique_ptr<Signal> getNextSignal() = 0;
};

}

#endif //ANALOGORIUM_SIGNALCONDUIT_H
