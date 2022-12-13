// PluginFeedback.hpp
// Lucas Samaruga (samarugalucas@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace fbugen {

class Feedback : public SCUnit {
public:
    Feedback();

    // Destructor
    // ~Feedback();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace fbugen
