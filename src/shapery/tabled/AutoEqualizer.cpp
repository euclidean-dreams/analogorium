#include "AutoEqualizer.h"

namespace analogorium {

AutoEqualizer::AutoEqualizer() :
        balancers{} {
}

void AutoEqualizer::shape(Essentia &essentia) {
    auto &inputSignal = *essentia.getSignal(STFT_MAGNITUDE);
    auto outputSignal = std::make_unique<Signal>(inputSignal.size());

    // initialize balancers
    if(balancers.empty()) {
        auto frequencyIncrement = SAMPLE_RATE / inputSignal.size();
        balancers.push_back(std::make_unique<AutoBalance>(0, 60 / frequencyIncrement - 1, 1));
        balancers.push_back(std::make_unique<AutoBalance>(60 / frequencyIncrement, 250 / frequencyIncrement - 1, 0.));
        balancers.push_back(std::make_unique<AutoBalance>(250 / frequencyIncrement, 500 / frequencyIncrement - 1, 1));
        balancers.push_back(std::make_unique<AutoBalance>(500 / frequencyIncrement, 2000 / frequencyIncrement - 1, 1));
        balancers.push_back(std::make_unique<AutoBalance>(2000 / frequencyIncrement, 4000 / frequencyIncrement - 1, 1));
        balancers.push_back(std::make_unique<AutoBalance>(4000 / frequencyIncrement, 6000 / frequencyIncrement - 1, 1));
        balancers.push_back(std::make_unique<AutoBalance>(6000 / frequencyIncrement, 20000 / frequencyIncrement - 1, 1));
    }

    for (auto sample: inputSignal) {
        outputSignal->addSample(sample);
    }
    for (auto &balancer: balancers) {
        balancer->balance(*outputSignal);
    }
    essentia.setSignal(STFT_MAGNITUDE, move(outputSignal));
}

}
