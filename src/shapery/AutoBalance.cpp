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
        sampleMultiplier{impresarioUtils::Config::getInstance().getFloat("sample_multiplier")},
        history{},
        historySize{impresarioUtils::Config::getInstance().getInt("autobalance_history_size")} {

}

//void AutoBalance::balance(Signal &signal) {
//    float highestSample = 0;
//    for (int index = signalStartIndex; index < signalEndIndex; index++) {
//        // balance sample in signal
//        auto rawSample = signal.getSample(index);
//        auto sample = rawSample * sampleMultiplier;
//        signal.setSample(index, sample);
//
//        // update highest sample
//        auto absSample = std::abs(sample);
//        if (absSample > highestSample) {
//            highestSample = absSample;
//        }
//    }
//
//    // update history
//    history.push_back(highestSample);
//    if (history.size() > historySize) {
//        history.pop_front();
//    }
//
//    // adjust gain
//    float sum = 0;
//    for (auto value: history) {
//        sum += value;
//    }
//    auto ceilingAverage = sum / static_cast<float>(history.size());
//
//    if (ceilingAverage < ceilingTarget) {
//        sampleMultiplier += 0.001 * std::abs(ceilingTarget - ceilingAverage);
//    } else if (ceilingAverage > ceilingTarget && sampleMultiplier > 0) {
//        sampleMultiplier -= 0.001 * std::abs(ceilingTarget - ceilingAverage);
//    }
//
//}

void AutoBalance::shape(Essentia &essentia) {
    auto &inputSignal = *essentia.getSignal(SEEDLING);
    auto outputSignal = std::make_unique<Signal>(inputSignal.size());
    for (auto sample: inputSignal) {
        outputSignal->addSample(sample * sampleMultiplier);
    }
//    balance(*outputSignal);
    essentia.setSignal(AUTO_BALANCE, move(outputSignal));
}

}
