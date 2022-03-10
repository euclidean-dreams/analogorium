#ifndef ANALOGORIUM_AUDIODEVICESLINGER_H
#define ANALOGORIUM_AUDIODEVICESLINGER_H

#include <ImpresarioUtils.h>
#include <portaudio.h>
#include <pa_linux_alsa.h>
#include "RingBuffer.h"

namespace analogorium {

class AudioDeviceSlinger : public impresarioUtils::NonCopyable {
private:
    PaStream *inputStream;
    std::shared_ptr<RingBuffer> outputStream;
    PaStreamParameters inputParameters;

    void throwOnPortaudioError(PaError portaudioReturnCode);

public:
    AudioDeviceSlinger();

    ~AudioDeviceSlinger();

    std::shared_ptr<SignalConduit> getSignalConduit();

    static int streamCallback(const void *input, void *output, unsigned long frameCount,
                              const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
                              void *userData);
};

}

#endif //ANALOGORIUM_AUDIODEVICESLINGER_H
