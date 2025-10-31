/*
 * Sin-Yaw Wang <swang24@scu.edu>
 */
#include <bitset>
#include <stdexcept>
#include "rng.h"
#include "dna.h"

namespace csen79 {

// Student to implement all of these member functions
DNA::DNA(unsigned int v) {
    codes = static_cast<Gene>(v & mask);  // Mask to ensure only nCode bits are used
}

bool DNA::getCode(const int i) const {
    if (i < 0 || i >= nCode)
        throw std::out_of_range("DNA::getCode: index out of range");
    return (codes >> i) & 1;  // Get the i-th bit
}

void DNA::setCode(const int i, bool v) {
    if (i < 0 || i >= nCode)
        throw std::out_of_range("DNA::setCode: index out of range");
    if (v)
        codes |= (1 << i);   // Set the i-th bit to 1
    else
        codes &= ~(1 << i);  // Set the i-th bit to 0
}

size_t DNA::size() const {
    return nCode;
}

size_t DNA::count() const {
    // Count number of 1 bits using bitset
    std::bitset<nCode> bits(codes);
    return bits.count();
}

unsigned int DNA::matchDNA(const DNA& other) const {
    // XOR to find differences, then count matching bits
    // Matching bits are 0 after XOR, so count 0s = total - count(1s)
    Gene diff = codes ^ other.codes;
    std::bitset<nCode> bits(diff);
    return nCode - bits.count();  // Number of matching bits
}

}   // namespace csen79