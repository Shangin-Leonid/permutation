#include <iostream>

#include "permutation.hpp"

using namespace mu;

void print_oln_permutation(const permutation & p);

int main(void)
{
    size_t sz = 7;

    // Create default (identity is not guaranteed) permutation
    permutation p0(sz);

    // Create identity (guaranteed) permutation
    permutation p1;
    p1 = permutation::make_id(sz);

    // Create certain permutation
    permutation p2 = {3, 0, 2, 1, 6, 5, 4};
    // ...         = {1, 2, 3, 4, 5, 6, 7};
    // ...         = {0, 1, 2, 2};
    // ERRORS: is not bijection [0 ; length) <-> [0 ; length)

    // Simple function for printing permutation in one-line notation
    print_oln_permutation(p2);
    std::cout << "\n\n";

    // Using loop for permutation enumeration
    sz = 4;
    // Process here id permutation, and then process others in the folllowing loop:
    print_oln_permutation(permutation::make_id(sz));
    for(auto p = permutation::make_id(sz) + 1; !p.is_id(); ++p)
        print_oln_permutation(p);

    return 0;
}


void print_oln_permutation(const permutation & p)
{
    std::cout << "(  ";
    for(size_t i = 0; i < p.size(); ++i)
        std::cout << p[i] << "  ";
    /*
    For counting from 1 (not from 0) use:
    for(size_t i = 1; i <= p.size(); ++i)
        std::cout << p.image_of(i) << "  ";
    */
    std::cout << ')' << std::endl;
}
