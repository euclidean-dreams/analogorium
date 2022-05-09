#include "Essentia.h"

namespace analogorium {

Essentia::Essentia()
        : signals{} {
    signals.resize(SIGNAL_FLAVOR_COUNT);
}

void Essentia::setSignal(SignalFlavor signalFlavor, std::unique_ptr<Signal> signal) {
    signals[signalFlavor] = move(signal);
}

std::shared_ptr<Signal> Essentia::getSignal(SignalFlavor signalFlavor) {
    return signals[signalFlavor];
}

std::unique_ptr<flatbuffers::FlatBufferBuilder> Essentia::serialize() const {
    auto builder = std::make_unique<flatbuffers::FlatBufferBuilder>();
    auto stft = builder->CreateVector(signals[STFT_MAGNITUDE]->getVectorReference());
    auto serializedPacket = ImpresarioSerialization::CreateEssentia(*builder, stft);
    builder->Finish(serializedPacket);
    return builder;
}

}
