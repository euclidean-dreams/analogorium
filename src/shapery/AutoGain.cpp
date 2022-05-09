#include "AutoGain.h"

namespace analogorium {

AutoGain::AutoGain() :
        balancer{0, SEEDLING_SIGNAL_SIZE, 0.002} {

}

void AutoGain::shape(Essentia &essentia) {
    auto &inputSignal = *essentia.getSignal(SEEDLING);
    auto outputSignal = std::make_unique<Signal>(inputSignal.size());
    for (auto sample: inputSignal) {
        outputSignal->addSample(sample);
    }
    balancer.balance(*outputSignal);
    essentia.setSignal(AUTO_GAIN, move(outputSignal));
}

}
