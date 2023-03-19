#ifndef CPP__CONWAY_PADDING_POLICIES_H
#define CPP__CONWAY_PADDING_POLICIES_H

#include "assets.h"
#include "index.h"

class PaddingPolicy {


private:
    int w_ = 0;
    int h_ = 0;

public:
    PaddingPolicy() = default;
    explicit PaddingPolicy(int h, int w) : PaddingPolicy() { set_boundaries(h, w);};

    virtual IJ remap_ij(IJ ij) = 0;
    virtual void set_boundaries(int h, int w) {
        w_ = w;
        h_ = h;
    };

    int w(){return w_;}
    int h(){return h_;}

    bool is_ij_in_boundaries(IJ ij){
        return (ij.i < 0 || h() < ij.i) && (ij.j < 0 || w() < ij.j);
    }

    void check_ij_in_boundaries(IJ ij){
        if (ij.i < 0 || h() < ij.i){
            throw std::range_error("i index " + std::to_string(ij.i) + " out of bounds [0 ... "  + std::to_string(h()) + "]");
        }

        if (ij.j < 0 || w() < ij.j){
            throw std::range_error("j index " + std::to_string(ij.j) + " out of bounds [0 ... "  + std::to_string(w()) + "]");
        }
    }

    IJ remap_ij(int i, int j){return remap_ij(IJ{i, j});}
};

class PaddingPolicyEye : public PaddingPolicy{
public:
    IJ remap_ij(IJ ij) override {
        check_ij_in_boundaries(ij);
        ij.state = IJState::INDEX;
        return ij;
    }
};

class PaddingPolicyTor : public PaddingPolicy{
public:
    IJ remap_ij(IJ ij) override {
        return IJ{
                .i = ij.i % h() + (ij.i<0) * h(),
                .j = ij.j % w() + (ij.j<0) * w(),
                .state= IJState::INDEX
        };
    }
};

class PaddingPolicyConst : public PaddingPolicy{
public:
    PaddingPolicyConst(int h, int w) : PaddingPolicy(h, w) {};

    IJ remap_ij(IJ ij) override {
        if (is_ij_in_boundaries(ij)){
            ij.state = IJState::INDEX;
            return ij;
        }
        ij.state = IJState::PADDING;
        return ij;
    }
};


#endif //CPP__CONWAY_PADDING_POLICIES_H
