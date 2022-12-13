// PluginFeedback.cpp
// Lucas Samaruga (samarugalucas@gmail.com)

#include "SC_PlugIn.hpp"
#include "Feedback.hpp"

static InterfaceTable* ft;

namespace fbugen {

Feedback::Feedback() {
    maxdelay = in0(1);
    bufsize = NEXTPOWEROFTWO((float)mRate->mSampleRate * maxdelay) * 2;
    bufmask = bufsize - 1;
    blocksize = mBufLength; // *** I DON'T KNOW IF THIS IS BLOCKSIZE, IT SEEMS...
    Print("blocksize (si es): %i", blocksize);
    numblocks = bufsize / blocksize;
    currblock = 0;
    buf = (float*)RTAlloc(mWorld, bufsize * sizeof(float));

    // Make sure that RTAlloc succeeded.
    if (buf == NULL) {
        mCalcFunc = (UnitCalcFunc)&ft->fClearUnitOutputs; // *** RAW, THERE SOULD BE A FUNCTION.
        mCalcFunc(this, 1);  // *** REVIEW HOW IT IS IN C++, HERE IS REDUNDANT, MAYBE THERE IS FUNCTION.
        if(mWorld->mVerbosity > -2) {
            Print("Failed to allocate memory for Feedback ugen.\n");
        }
        return;
    }

    // Fill the buffer with zeros.
    memset(buf, 0, bufsize * sizeof(float));

    mCalcFunc = make_calc_function<Feedback, &Feedback::next>();
    // next(1);  // *** can't be called because it count the blocks, mem is with zeros already.
}

Feedback::~Feedback() {
    RTFree(mWorld, buf);
}

void Feedback::next(int nSamples) {
    const float* input = in(0);
    float delay = in0(2);  // *** this should be abs to avoid negative delays and crashes.
    float k = in0(3);
    float* outbuf = out(0);

    const float maxdelay = this->maxdelay;
    if (delay > maxdelay) {
        delay = maxdelay;
    }

    // Delay in samples
    int d = (int)((float)mRate->mSampleRate * delay);

    // Count the current block offset.
    int offset = blocksize * currblock;
    if (offset < bufsize) {
        currblock++;
    } else {
        currblock = offset = 0;
    }

    for (int i = 0; i < nSamples; ++i) {
        int bufpos = offset + i;
        int bufpos2 = (bufpos - d + bufsize) & bufmask;
        buf[bufpos] = outbuf[i] = zapgremlins(input[i] + buf[bufpos2] * k);  // *** zapgremlins may degrade.
    }
}

} // namespace fbugen

PluginLoad(FeedbackUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<fbugen::Feedback>(ft, "Feedback");
}
