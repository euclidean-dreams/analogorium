#include "StftShaper.h"

namespace analogorium {

StftShaper::StftShaper()
        : windowFunction{WINDOW_FUNCTION},
          hopSize{HOP_SIZE},
          windowSize{WINDOW_SIZE},
          fftSize{windowSize * SEEDLING_SIGNAL_SIZE},
          stftSize{fftSize / 2 + 1},
#ifdef USE_MUFFT
          fftInput{static_cast<float *>(mufft_alloc(fftSize * sizeof(float)))},
          fftOutput{static_cast<cfloat *>(mufft_alloc(fftSize * sizeof(cfloat)))},
          fftPlan{mufft_create_plan_1d_r2c(fftSize, 0)},
#else
        fftInput{static_cast<ne10_float32_t *>(malloc(fftSize * sizeof(ne10_float32_t)))},
        fftOutput{static_cast<ne10_fft_cpx_float32_t *>(malloc(fftSize * sizeof(ne10_fft_cpx_float32_t)))},
        fftPlan{ne10_fft_alloc_r2c_float32(fftSize)},
#endif // USE_MUFFT
          inputSignals{} {
    for (int i = 0; i < fftSize; i++) {
        fftInput[i] = 0;
    }
}

StftShaper::~StftShaper() {
#ifdef USE_MUFFT
    mufft_free(fftInput);
    mufft_free(fftOutput);
    mufft_free(fftPlan);
#else
    NE10_FREE(fftInput);
    NE10_FREE(fftOutput);
    ne10_fft_destroy_r2c_float32(fftPlan);
#endif // USE_MUFFT
}

void StftShaper::shape(Essentia &essentia) {
    if (inputSignals.size() < windowSize / hopSize) {
        // waiting to have enough seedlings to operate on
        // generate some null signals to allow future shapers to work
        inputSignals.push_back(essentia.getSignal(AUTO_BALANCE));

        auto realSignal = std::make_unique<Signal>(stftSize);
        realSignal->populate(0);
        essentia.setSignal(STFT_REAL, move(realSignal));

        auto imaginarySignal = std::make_unique<Signal>(stftSize);
        imaginarySignal->populate(0);
        essentia.setSignal(STFT_IMAGINARY, move(imaginarySignal));

        auto magnitudeSignal = std::make_unique<Signal>(stftSize);
        magnitudeSignal->populate(0);
        essentia.setSignal(STFT_MAGNITUDE, move(magnitudeSignal));
        return;
    } else {
        inputSignals.pop_front();
        inputSignals.push_back(essentia.getSignal(AUTO_BALANCE));
    }

    // perform windowing
    auto fftInputIndex = 0;
    for (auto &seedling: inputSignals) {
        for (auto sample: *seedling) {
            if (windowFunction == WindowFunction::hann) {
                fftInput[fftInputIndex] = sample * hannWindow(fftInputIndex);
            } else if (windowFunction == WindowFunction::hamming) {
                fftInput[fftInputIndex] = sample * hammingWindow(fftInputIndex);
            } else {
                throw std::logic_error{"invalid window function selected"};
            }
            fftInputIndex++;
        }
    }

    // perform the actual fft
#ifdef USE_MUFFT
    mufft_execute_plan_1d(fftPlan, fftOutput, fftInput);
#else
    ne10_fft_r2c_1d_float32_neon(fftOutput, fftInput, fftPlan);
#endif // USE_MUFFT

    auto realSignal = std::make_unique<Signal>(stftSize);
    auto imaginarySignal = std::make_unique<Signal>(stftSize);
    auto magnitudeSignal = std::make_unique<Signal>(stftSize);
    for (int i = 0; i < stftSize; i++) {
#ifdef USE_MUFFT
        realSignal->addSample(fftOutput[i].real);
        imaginarySignal->addSample(fftOutput[i].imag);
        magnitudeSignal->addSample(static_cast<float>(std::sqrt(
                std::pow(fftOutput[i].real, 2) + std::pow(fftOutput[i].imag, 2))));
#else
        realSignal->addSample(fftOutput[i].r);
        imaginarySignal->addSample(fftOutput[i].i);
        magnitudeSignal->addSample(static_cast<float>(std::sqrt(
                std::pow(fftOutput[i].r, 2) + std::pow(fftOutput[i].i, 2))));
#endif // USE_MUFFT
    }
    essentia.setSignal(STFT_REAL, move(realSignal));
    essentia.setSignal(STFT_IMAGINARY, move(imaginarySignal));
    essentia.setSignal(STFT_MAGNITUDE, move(magnitudeSignal));
}

float StftShaper::hammingWindow(int sampleNumber) const {
    return static_cast<float>(0.53836 - 0.46164 * std::cos((2 * M_PI * sampleNumber) / (fftSize - 1)));
}

float StftShaper::hannWindow(int sampleNumber) const {
    return static_cast<float>(0.5 * (1 - std::cos((2 * M_PI * sampleNumber) / (fftSize - 1))));
}

}
