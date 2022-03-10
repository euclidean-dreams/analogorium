#include "Signal.h"

namespace analogorium {

Signal::Signal(int size)
        : maxSize{size},
          samples{} {
    samples.reserve(size);
}

int Signal::size() const {
    return maxSize;
}

const std::vector<float> &Signal::getVectorReference() const {
    return samples;
}

void Signal::addSample(float sample) {
    if (samples.size() >= maxSize) {
        throw std::runtime_error("attempted to add a sample to a finalized signal");
    }
    samples.push_back(sample);
}

float Signal::getSample(int index) {
    if (samples.size() < maxSize) {
        throw std::runtime_error("attempted to use a signal that wasn't finalized");
    }
    if (index < 0 || index >= maxSize) {
        throw std::out_of_range("attempted to access an out of range sample on a signal");
    }
    return samples[index];
}

void Signal::populate(float value) {
    samples.clear();
    samples.resize(size(), value);
}

std::vector<float>::iterator Signal::begin() {
    return samples.begin();
}

std::vector<float>::iterator Signal::end() {
    return samples.end();
}

}
