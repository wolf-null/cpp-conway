#pragma once

#include <string>

#include "indices/property.hpp"

/**
 * Describes a state (semantics) of IJ coordinate.
 */
enum IJState {
    VALID,      /**< State corresponding to  existing/valid (i, j) which correspond to certain Node Index */

    INVALID,    /**< State corresponding to non-existing (i, j).
                * If IJ.state is IJState.INVALID the values of IJ.i and IJ.j can be any and has no meaning.
                * All IJ with IJState.INVALID are ALWAYS non-equal to any IJ (not depending on IJ.i and IJ.j values).
                * This also implies non-equity to other invalid coordinates.*/

    PADDING     /**<  State corresponding to padding Index. Meaning of IJ.i and IJ.j depends on the selected IndexModel
                * Usually all IJs with IJ.state PADDING is liklely to denote one and the same Node independent of
                * IJ.i and IJ.j values. This is why ALL IJs with state=PADDING are considered equal
                */
};


/**
 * IJ struct is a pair of coordinates (i, j) on the cell field.
 *
 * It may or may not correspond to a certain node Index.
 * E.g. IJ doesn't correspond to any node Index it has IJ.State = IJState::INVALID
 * IJ.state is usually set by methods returning IJ.
 * Methods receiving IJ must also implement behavior depending on all possible IJ.state values (see IJState)
 *
 * Note: Naming "IJ" instead of "Coordinate2D" is dur to convenience (less to type)
 */
struct IJ {
    [[no_unique_address]] Property <int> i; /**< IJ.i - first coordinate, usually for column number */
    [[no_unique_address]] Property <int> j; /**< IJ.j - second coordinate, usually for row number */
    [[no_unique_address]] Property <IJState> state; /**< Coordinate state. See IJState for documentation */

    explicit IJ() = default;
    explicit IJ(int i_value, int j_value, IJState valid=IJState::VALID) : i{i_value}, j{j_value}, state{valid} {};

    std::string to_string() const; /**< one-one transformation from IJ to std::string*/
    // TODO: static IJ::from_string(std::string) or IJ(std::string)

    /**
     * Compares IJ with @param other IJ.
     * Comparison depends on both IJ's IJ::state (of type IJState)
     *      - Two IJState::VALID coords are equal if i==i and j==j
     *      - Two IJState::PADDING are always equal
     *      - IJState::INVALID not equal to any coordinate (oneself included)
     * @return coordinate equality
     */
    bool operator == (const IJ& other) const;

    /**
     * @return state == IJState::VALID. NOT INCLUDING IJState::PADDING
     */
    const bool is_valid() const;
};

using Coordinate2D = IJ; /**< Reasonable but long IJ name*/

std::ostream& operator << (std::ostream& ostream, const IJ& index);

