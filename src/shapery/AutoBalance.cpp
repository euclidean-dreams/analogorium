#include "AutoBalance.h"

namespace analogorium {

AutoBalance::AutoBalance(
        int signalStartIndex,
        int signalEndIndex,
        float target
) :
        signalStartIndex{signalStartIndex},
        signalEndIndex{signalEndIndex},
        ceilingTarget{target},
        gain{1},
        history{},
        historySize{impresarioUtils::Config::getInstance().getInt("autogain_history_size")} {

}

void AutoBalance::balance(Signal &signal) {
    float highestSample = 0;
    for (int index = signalStartIndex; index < signalEndIndex; index++) {
        // balance sample in signal
        auto rawSample = signal.getSample(index);
        auto sample = rawSample * gain;
        signal.setSample(index, sample);

        // update highest sample
        auto absSample = std::abs(sample);
        if (absSample > highestSample) {
            highestSample = absSample;
        }
    }

    // update history
    history.push_back(highestSample);
    if (history.size() > historySize) {
        history.pop_front();
    }

    // adjust gain
    float sum = 0;
    for (auto value: history) {
        sum += value;
    }
    auto ceilingAverage = sum / history.size();

    if (ceilingAverage < ceilingTarget) {
        gain += 0.0001;
    } else if (ceilingAverage > ceilingTarget) {
        gain -= 0.0001;
    }

}

}
