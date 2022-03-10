#include "RingBuffer.h"

namespace analogorium {

RingBuffer::RingBuffer()
        : mutex{},
          signalAddedExpectant{},
          signalSize{SEEDLING_SIGNAL_SIZE},
          bufferSize{signalSize * RING_BUFFER_SIZE_MULTIPLIER},
          internalBuffer(bufferSize),
          readIterator{internalBuffer.cbegin()},
          writeIterator{internalBuffer.begin()} {

}

void RingBuffer::addSamples(const float *samples, unsigned long count) {
    for (int i = 0; i < count; i++) {
        if (writeIterator >= internalBuffer.end()) {
            writeIterator = internalBuffer.begin();
        }
        *writeIterator = samples[i];
        writeIterator++;
    }
    if (nextSignalIsReady()) {
        signalAddedExpectant.notify_all();
    }
}

bool RingBuffer::nextSignalIsReady() const {
    if (readIterator + signalSize <= writeIterator
        || (writeIterator < readIterator && writeIterator >= internalBuffer.begin() + signalSize)) {
        return true;
    } else {
        return false;
    }
}

std::unique_ptr<Signal> RingBuffer::getNextSignal() {
    auto signal = std::make_unique<Signal>(signalSize);
    for (int i = 0; i < signalSize; i++) {
        signal->addSample(*readIterator);
        readIterator++;
    }
    if (readIterator >= internalBuffer.end()) {
        readIterator = internalBuffer.cbegin();
    }
    return signal;
}

void RingBuffer::waitUntilNextSignalIsReady() {
    std::unique_lock<std::mutex> lock{mutex};
    while (!nextSignalIsReady()) {
        signalAddedExpectant.wait(lock);
    }
}

}
