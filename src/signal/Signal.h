#ifndef ANALOGORIUM_SIGNAL_H
#define ANALOGORIUM_SIGNAL_H

#include <ImpresarioUtils.h>

namespace analogorium {

class Signal : public impresarioUtils::NonCopyable {
private:
    int maxSize;
    std::vector<float> samples;

public:
    Signal(int size);

    int size() const;

    const std::vector<float> &getVectorReference() const;

    void addSample(float sample);

    float getSample(int index);

    void populate(float value);

    std::vector<float>::iterator begin();

    std::vector<float>::iterator end();
};

}

#endif //ANALOGORIUM_SIGNAL_H
