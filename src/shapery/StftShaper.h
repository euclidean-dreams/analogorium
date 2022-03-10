#ifndef ANALOGORIUM_STFTSHAPER_H
#define ANALOGORIUM_STFTSHAPER_H

#include <fft.h>
#include <fft_internal.h>
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
    float *fftInput;
    cfloat *fftOutput;
    mufft_plan_1d *fftPlan;
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
