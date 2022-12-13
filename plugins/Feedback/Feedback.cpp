// PluginFeedback.cpp
// Lucas Samaruga (samarugalucas@gmail.com)

#include "SC_PlugIn.hpp"
#include "Feedback.hpp"

static InterfaceTable* ft;

namespace fbugen {

Feedback::Feedback() {
    mCalcFunc = make_calc_function<Feedback, &Feedback::next>();
    next(1);
}

void Feedback::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(0);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace fbugen

PluginLoad(FeedbackUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<fbugen::Feedback>(ft, "Feedback");
}
