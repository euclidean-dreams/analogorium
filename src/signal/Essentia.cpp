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
    auto signalOffset = builder->CreateVector(signals[EQUALIZED]->getVectorReference());
    auto serializedPacket = ImpresarioSerialization::CreateEssentia(*builder, signalOffset);
    builder->Finish(serializedPacket);
    return builder;
}

}
