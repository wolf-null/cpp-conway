//
// Created by Mann on 12.03.2023.
//

#ifndef CPP__CONWAY_ASSETS_H
#define CPP__CONWAY_ASSETS_H

#include <map>
#include <string>

enum class IJState {
    UNDEFINED,
    INDEX,
    PADDING
};

struct IJ {
    int i{0};
    int j{0};

    IJState state{IJState::INDEX};

    friend auto operator <=> (const IJ& a, const IJ& b) {
        return std::tie(a.i, a.j) <=> std::tie(b.i, b.j);
    }

    std::string to_string() const {
        return "[" + std::to_string(i) + ", " + std::to_string(j) + "]";
    }
};

int sign(int val) {
    return val == 0 ? 0 : (val > 0 ? 1 : -1);
}

#endif //CPP__CONWAY_ASSETS_H
