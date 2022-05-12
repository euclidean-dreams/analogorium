#include <ImpresarioUtils.h>
#include "Config.h"
#include "shapery/Shapery.h"
#include "primordium/AudioDeviceSlinger.h"

namespace analogorium {

int bootstrap() {
    std::string configFilePath = "./analogorium-config.yml";
    impresarioUtils::Bootstrapper bootstrapper(configFilePath, 1);

    // volitia percipient
    auto axiomologyArbiter = std::make_shared<impresarioUtils::Arbiter<const impresarioUtils::Parcel>>();
    auto phenomenology = std::make_shared<impresarioUtils::BufferArbiter<const impresarioUtils::Parcel>>();
    auto volitiaPercipientThread = impresarioUtils::VolitiaPercipient::create(
            bootstrapper.getZmqContext(), VOLITIA_ENDPOINT, axiomologyArbiter, phenomenology);


    // primordium
    AudioDeviceSlinger audioDeviceSlinger{};

    // shapery
    auto shaperyOutputSocket = std::make_unique<impresarioUtils::NetworkSocket>(
            bootstrapper.getZmqContext(), OUTPUT_ENDPOINT, zmq::socket_type::pub, true);
    auto shapery = std::make_unique<Shapery>(audioDeviceSlinger.getSignalConduit(), move(shaperyOutputSocket));
    auto shaperyThread = impresarioUtils::Circlet::begin(move(shapery));

    shaperyThread->join();
    volitiaPercipientThread->join();

    return 0;
}

}

int main() {
    return analogorium::bootstrap();
}
