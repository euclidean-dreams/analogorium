#include "Essentia.h"

namespace analogorium {

Essentia::Essentia()
        : signals{} {
    signals.resize(SIGNAL_FLAVOR_COUNT);
}

void Essentia::setSignal(SignalFLavor signalFlavor, std::unique_ptr<Signal> signal) {
    signals[signalFlavor] = move(signal);
}

std::shared_ptr<Signal> Essentia::getSignal(SignalFLavor signalFlavor) {
    return signals[signalFlavor];
}

std::unique_ptr<flatbuffers::FlatBufferBuilder> Essentia::serialize() const {
    auto builder = std::make_unique<flatbuffers::FlatBufferBuilder>();
    auto stftRealPart = signals[STFT_REAL];
    auto stftImaginaryPart = signals[STFT_IMAGINARY];
    std::vector<float> stftMagnitude;
    stftMagnitude.reserve(stftRealPart->size());
    for (int index = 0; index < stftRealPart->size(); index++) {
        stftMagnitude.push_back(static_cast<float>(std::sqrt(
                std::pow(stftRealPart->getSample(index), 2) + std::pow(stftImaginaryPart->getSample(index), 2))));
    }
    auto signalOffset = builder->CreateVector(stftMagnitude);
    auto serializedPacket = ImpresarioSerialization::CreateEssentia(*builder, signalOffset);
    builder->Finish(serializedPacket);
    return builder;
}

}
