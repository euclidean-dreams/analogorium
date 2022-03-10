#ifndef ANALOGORIUM_RINGBUFFER_H
#define ANALOGORIUM_RINGBUFFER_H

#include <condition_variable>
#include "SignalConduit.h"
#include "Config.h"

namespace analogorium {

class RingBuffer : public SignalConduit {
private:
    std::mutex mutex;
    std::condition_variable signalAddedExpectant;
    int signalSize;
    int bufferSize;
    std::vector<float> internalBuffer;
    std::vector<float>::const_iterator readIterator;
    std::vector<float>::iterator writeIterator;

    bool nextSignalIsReady() const override;

public:
    explicit RingBuffer();

    void addSamples(const float *samples, unsigned long count);

    void waitUntilNextSignalIsReady() override;

    std::unique_ptr<Signal> getNextSignal() override;
};

}

#endif //ANALOGORIUM_RINGBUFFER_H
