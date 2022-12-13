// PluginFeedback.hpp
// Lucas Samaruga (samarugalucas@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace fbugen {

class Feedback : public SCUnit {
public:
    Feedback();
    ~Feedback();

private:
    // Calc function
    void next(int nSamples);

    // Max feedback delay in seconds.
    float maxdelay;
    // Size of the internal buffer in samples, always a power of 2 and at least twice of maxdelay in samples.
    int bufsize;
    // bufsize - 1, so the modulo function can be replaced with a faster bitwise.
    int bufmask;
    // Internal buffer.
    float* buf;
    // Control block size.
    int blocksize;
    // Number of control blocks pero buffer.
    int numblocks;
    // Current block number within the buffer.
    int currblock;
};

} // namespace fbugen
