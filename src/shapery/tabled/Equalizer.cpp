#include "Equalizer.h"

namespace analogorium {

Equalizer::Equalizer(

) :
        gain{GAIN},
        sampleRate{SAMPLE_RATE},
        scalingFactors() {
    // todo: make configurable
    scalingFactors.emplace(100, SCALING_FACTOR_100);
    scalingFactors.emplace(200, SCALING_FACTOR_200);
    scalingFactors.emplace(400, SCALING_FACTOR_400);
    scalingFactors.emplace(1000, SCALING_FACTOR_1000);
    scalingFactors.emplace(2000, SCALING_FACTOR_2000);
    scalingFactors.emplace(20000, SCALING_FACTOR_20000);
}

void Equalizer::shape(Essentia &essentia) {
    auto &inputSignal = *essentia.getSignal(STFT_MAGNITUDE);
    auto equalizedSignal = std::make_unique<Signal>(inputSignal.size());
    auto frequencyIncrement = sampleRate / inputSignal.size();
    auto currentScalingFactorIterator = begin(scalingFactors);
    for (int index = 0; index < inputSignal.size(); index++) {
        if (index * frequencyIncrement > currentScalingFactorIterator->first) {
            currentScalingFactorIterator++;
        }
        auto inputSample = inputSignal.getSample(index);
        auto outputSample = inputSample * currentScalingFactorIterator->second * gain;
        equalizedSignal->addSample(outputSample);
    }
    essentia.setSignal(EQUALIZED, move(equalizedSignal));
}

}
