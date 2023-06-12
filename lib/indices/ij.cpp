#include "ij.h"


std::ostream& operator << (std::ostream& ostream, const IJ& index) {
    ostream << index.to_string();
    return ostream;
}


std::string IJ::to_string() const {
    return "[" + std::to_string(i.get()) + ", " + std::to_string(j.get()) + ", " +  std::to_string(state.get()) + "]";
}

bool IJ::operator == (const IJ& other) const {
    if (state.get() == IJState::INVALID || other.state.get() == IJState::INVALID)
        return false;

    if (state.get() == IJState::PADDING && other.state.get() == IJState::PADDING)
        return true;

    return other.i.get() == i.get() && other.j.get() == j.get() && state.get() == other.state.get();
}

const bool IJ::is_valid() const {
    return state.get() == IJState::VALID;
}


