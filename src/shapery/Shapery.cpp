#include "Shapery.h"
#include "AutoBalance.h"

namespace analogorium {

Shapery::Shapery(std::shared_ptr<SignalConduit> input, std::unique_ptr<impresarioUtils::NetworkSocket> output)
        : input{move(input)},
        output{move(output)},
        shapers{} {
//    shapers.push_back(std::make_unique<AutoBalance>(0, SEEDLING_SIGNAL_SIZE, 1));
    shapers.push_back(std::make_unique<StftShaper>());
}

void Shapery::activate() {
    // input
    input->waitUntilNextSignalIsReady();
    auto essentia = std::make_unique<Essentia>();
    auto seedling = input->getNextSignal();
    essentia->setSignal(SEEDLING, move(seedling));

    // shaping
    for (auto &shaper: shapers) {
        shaper->shape(*essentia);
    }

    // output
    output->sendParcel(ImpresarioSerialization::Identifier::essentia, *essentia->serialize());
}

}
