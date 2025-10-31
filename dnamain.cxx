/*
 * Unit tests for DNA class
 */
#include <iostream>
#include <cassert>
#include <random>
#include "rng.h"
#include "dna.h"

// Global RNG implementation
namespace {
    std::mt19937& global_rng() {
        static std::mt19937 rng(std::random_device{}());
        return rng;
    }
}

int rand_int(int lo, int hi) {
    if (hi <= lo) return lo;
    std::uniform_int_distribution<int> d(lo, hi);
    return d(global_rng());
}

bool rand_bool() {
    std::bernoulli_distribution d(0.5);
    return d(global_rng());
}

using namespace csen79;

int main() {
    std::cout << "Testing DNA class..." << std::endl;
    
    // Test constructor and count
    DNA dna1(0x0000);
    DNA dna2(0xFFFF);
    DNA dna3(0x00FF);
    assert(dna1.count() == 0);
    assert(dna2.count() == 16);
    assert(dna3.count() == 8);
    std::cout << "  Constructor and count: OK" << std::endl;
    
    // Test size
    assert(dna1.size() == 16);
    std::cout << "  Size: OK" << std::endl;
    
    // Test get/set
    DNA dna4(0x0000);
    dna4.setCode(0, true);
    dna4.setCode(5, true);
    dna4.setCode(15, true);
    assert(dna4.getCode(0) == true);
    assert(dna4.getCode(1) == false);
    assert(dna4.getCode(5) == true);
    assert(dna4.getCode(15) == true);
    assert(dna4.count() == 3);
    std::cout << "  Get/Set: OK" << std::endl;
    
    // Test matchDNA
    DNA dna5(0xFFFF);
    DNA dna6(0xFFFF);
    DNA dna7(0x0000);
    DNA dna8(0xFF00);
    DNA dna9(0x00FF);
    assert(dna5.matchDNA(dna6) == 16);  // All match
    assert(dna5.matchDNA(dna7) == 0);   // None match
    assert(dna8.matchDNA(dna9) == 0);   // None match
    std::cout << "  MatchDNA: OK" << std::endl;
    
    // Test boundary conditions
    bool caught = false;
    try {
        dna1.getCode(-1);
    } catch (std::out_of_range&) {
        caught = true;
    }
    assert(caught);
    
    caught = false;
    try {
        dna1.getCode(16);
    } catch (std::out_of_range&) {
        caught = true;
    }
    assert(caught);
    std::cout << "  Boundary checking: OK" << std::endl;
    
    // Test random DNA
    DNA random1;
    DNA random2;
    assert(random1.size() == 16);
    assert(random2.size() == 16);
    assert(random1.count() <= 16);
    assert(random2.count() <= 16);
    std::cout << "  Random DNA: OK" << std::endl;
    
    std::cout << "\nAll DNA tests passed!" << std::endl;
    return 0;
}

