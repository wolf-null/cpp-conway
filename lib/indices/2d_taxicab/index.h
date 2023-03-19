/*
 *
 * 2. **Index**. Organizes indexing, random access and traverse (iteration) over Domain's nodes. Destructor of the Index doesn't affect the Domain or Nodes. Target:
   1. We need two types of access:
      1. Model access. *Use case*: generating of cell grids. Class: ```Taxicab2DIndex```
         * ```operator[i, j]``` for model access (for instance, padding or toroidal topology support)
           * Access to (i, j) if not itinialized causes initialization
         * ```.data[][]``` for direct access
         * ```neighborhood(i,j,r)``` for iterating neighbors of (i, j)
         * (i, j) traverse iterator

      2. Direct access. Use case: fast traverse for node visiting. Class ```LinearIndex```
 */
#ifndef CPP__CONWAY_INDEX_H
#define CPP__CONWAY_INDEX_H

#include <map>
#include <stdexcept>
#include <tuple>
#include <iostream>
#include <string>
#include <functional>

#include "topology/domain.h"
#include "topology/abstract_node.h"

#include "assets.h"
#include "padding_policies.h"
#include "index_policies.h"

class Index2DTaxicab {

    // Index receives node domain and arranges it's values in 2 dimensionam MxN grid
    static constexpr bool DEBUG = true;
    static inline void log(std::string msg) {
        if constexpr (DEBUG)
            std::cout << msg << "\n";
    }


private:
    int w_ = 0;
    int h_ = 0;
    int length_ = 0;

    PaddingPolicy * padding_policy_ = nullptr;
    IndexPolicy * index_policy_ = nullptr;

    topology::NodeDomain * domain_;
    std::map <IJ, topology::AbstractNode*> mapping_;

public:
    Index2DTaxicab() = delete;

    Index2DTaxicab(topology::NodeDomain *domain, int h, int w) : domain_{domain}, w_{w}, h_{h} {
        set_length(h, w);
    };

    topology::AbstractNode* operator[](const IJ& ij) {
        IJ reindexed_ij = padding_policy_->remap_ij(ij);
        if (mapping_.contains(reindexed_ij)){
            return mapping_[reindexed_ij];
        }
        throw std::range_error("Index " + ij.to_string() + " is out of range " + IJ{h_, w_}.to_string());
    }

    void set_padding_policy(PaddingPolicy* policy, bool setup_boundaries = true) {
        padding_policy_ = policy;
        if (setup_boundaries)
            padding_policy_->set_boundaries(h_, w_);
    }

    void set_index_policy(IndexPolicy* policy, bool setup_boundaries = true) {
        index_policy_ = policy;
        index_policy_->set_boundaries(h_, w_, length_);
        if (setup_boundaries)
            padding_policy_->set_boundaries(h_, w_);
    }

    int h() const{return h_;}
    int w() const{return w_;}
    int length() const {return length_;}
    void set_length(int h, int w) {
        length_ = w * h;
    }

    void rebuild_index(int h, int w) {
        mapping_.clear();

        index_policy_->set_boundaries(h, w, length_);
        padding_policy_->set_boundaries(h, w);

        if (length_ != domain_->length())
            throw std::length_error("Number of nodes in domain = " + std::to_string(domain_->length()) + " doesn't match expected length " + std::to_string(length_));

        int idx = 0;
        for (auto i = domain_->begin(); i != domain_->end(); i ++, idx ++) {
            IJ unflattened = index_policy_->flat_index_to_index(idx);
            mapping_[unflattened] = *i;

            log("index: " + std::to_string(idx) + " <--> " + unflattened.to_string());
        }
    }

    template <typename ValueType>
    void map_value(std::function<ValueType(IJ)> func){
        for (const auto & index_node : mapping_) {
            IJ index = index_node.first;
            topology::AbstractNode* node = index_node.second;
            if (!node->get_role()->has_value)
                continue;
            auto role = node->role();
            constexpr int i = role->max_neighbours();
            auto* v_node = static_cast <topology::ValueNode<i, ValueType>*> (node);
            ValueType old_value = v_node->value();
            ValueType new_value = func(index);
            log(index.to_string() + " map : " + std::to_string(old_value) + " -> " + std::to_string( v_node->value()));
        }
    }

protected:



};

template <  typename T = Index2DTaxicab,
            typename TPaddingPolicy = PaddingPolicyEye,
            typename TIndexPolicy = IndexPolicyLinear>
T* make_index_2d_taxicab (topology::NodeDomain *domain, int h, int w, bool rebuild_index_now=true) {
    Index2DTaxicab * taxicab = new T{domain, h, w};

    PaddingPolicy * padding_policy = new TPaddingPolicy{};
    taxicab->set_padding_policy(padding_policy, !rebuild_index_now);

    IndexPolicy * index_policy = new TIndexPolicy{};
    taxicab->set_index_policy(index_policy, !rebuild_index_now);

    if (rebuild_index_now)
        taxicab->rebuild_index(h, w);

    return taxicab;
}

#endif //CPP__CONWAY_INDEX_H
