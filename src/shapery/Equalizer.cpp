#include "Equalizer.h"

namespace analogorium {

Equalizer::Equalizer(

) :
        gain{GAIN} {

}

void Equalizer::shape(Essentia &essentia) {
    auto &inputSignal = *essentia.getSignal(SEEDLING);
    auto equalizedSignal = std::make_unique<Signal>(inputSignal.size());
    for (auto sample: inputSignal) {
        auto equalizedSample = sample * gain;
        equalizedSignal->addSample(equalizedSample);
    }
    essentia.setSignal(EQUALIZED, move(equalizedSignal));
}

}
