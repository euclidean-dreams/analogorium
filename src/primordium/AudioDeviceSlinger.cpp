#include "AudioDeviceSlinger.h"

namespace analogorium {

AudioDeviceSlinger::AudioDeviceSlinger()
        : inputStream{},
        outputStream{std::make_shared<RingBuffer>()},
        inputParameters{} {
    throwOnPortaudioError(Pa_Initialize());
    LOGGER->info("enumerating audio devices");
    auto desiredDeviceName = AUDIO_DEVICE;
    int inputDevice = -1;
    for (int deviceIndex = 0; deviceIndex < Pa_GetDeviceCount(); deviceIndex++) {
        auto deviceInfo = Pa_GetDeviceInfo(deviceIndex);
        auto deviceName = std::string{deviceInfo->name};
        LOGGER->info("device {}: {}", deviceIndex, deviceName);
        if (deviceName.compare(0, desiredDeviceName.size(), desiredDeviceName) == 0) {
            inputDevice = deviceIndex;
        }
    }

    LOG_BREAK;
    if (inputDevice == -1) {
        LOGGER->error("could not find audio device {}", desiredDeviceName);
        throw std::runtime_error("could not find input audio device");
    } else {
        LOGGER->info("using audio device: {}", Pa_GetDeviceInfo(inputDevice)->name);
    }
    inputParameters.device = inputDevice;
    inputParameters.channelCount = 1;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputDevice)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = nullptr;
    throwOnPortaudioError(Pa_OpenStream(
            &inputStream,
            &inputParameters,
            nullptr,
            SAMPLE_RATE,
            paFramesPerBufferUnspecified,
            paNoFlag,
            streamCallback,
            &(*outputStream)
    ));
    PaAlsa_EnableRealtimeScheduling(inputStream, true);
    throwOnPortaudioError(Pa_StartStream(inputStream));
}

AudioDeviceSlinger::~AudioDeviceSlinger() {
    throwOnPortaudioError(Pa_Terminate());
}

std::shared_ptr<SignalConduit> AudioDeviceSlinger::getSignalConduit() {
    return outputStream;
}

int AudioDeviceSlinger::streamCallback(
        const void *input, void *output, unsigned long frameCount,
        const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
        void *userData
) {
    auto samples = static_cast<const float *>(input);
    auto ringBuffer = static_cast<RingBuffer *>(userData);
    ringBuffer->addSamples(samples, frameCount);
    return paContinue;
}

void AudioDeviceSlinger::throwOnPortaudioError(PaError portaudioReturnCode) {
    if (portaudioReturnCode != paNoError) {
        LOGGER->error(Pa_GetErrorText(portaudioReturnCode));
        throw std::runtime_error(Pa_GetErrorText(portaudioReturnCode));
    }
}

}
