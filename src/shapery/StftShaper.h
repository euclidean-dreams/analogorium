#ifndef ANALOGORIUM_STFTSHAPER_H
#define ANALOGORIUM_STFTSHAPER_H

#ifdef USE_MUFFT
#include <fft.h>
#include <fft_internal.h>
#else
#include <NE10.h>
#endif // USE_MUFFT

#include <complex>
#include "Shaper.h"

namespace analogorium {

enum class WindowFunction {
    hamming = 0,
    hann = 1
};

class StftShaper : public Shaper {
private:
    WindowFunction windowFunction;
    int hopSize;
    int windowSize;
    int fftSize;
    int stftSize;
#ifdef USE_MUFFT
    float *fftInput;
    cfloat *fftOutput;
    mufft_plan_1d *fftPlan;
#else
    ne10_float32_t *fftInput;
    ne10_fft_cpx_float32_t *fftOutput;
    ne10_fft_r2c_cfg_float32_t fftPlan;
#endif // USE_MUFFT
    std::list<std::shared_ptr<Signal>> inputSignals;

    float hammingWindow(int sampleNumber) const;

    float hannWindow(int sampleNumber) const;

public:
    StftShaper();

    ~StftShaper();

    void shape(Essentia &essentia) override;

};

}

#endif //ANALOGORIUM_STFTSHAPER_H
