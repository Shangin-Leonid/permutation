#pragma once


#include <initializer_list>
#include <vector>
#include <limits>


namespace mu { /* 'mu' = math utils */



class permutation;



permutation make_id_permutation(size_t length = 1);



class permutation final
{

  public:

            /* Types and checking */

    using num_t = uint;

    static_assert(std::numeric_limits<num_t>::is_integer,
                  "permutation::num_t must be a numeric integer type");

    enum class sign_t : int
    {
        EVEN = 1,
        ODD = -1
    };



  private:

            /* Data members */

    std::vector<num_t> _oln; // oln == One-Line Notation
    sign_t _sign; // the sign of permutation (even/odd amount of inversions)



  public:

    static permutation make_id(size_t length);

            /* Constructors */

    permutation(void);
    permutation(size_t length);
    permutation(std::initializer_list<num_t> ilist);
    permutation(const permutation & origin);
    permutation(permutation && rval_ref) noexcept(std::is_nothrow_move_constructible<std::vector<num_t>>::value);

            /* Destructor */

    ~permutation() noexcept(std::is_nothrow_destructible<std::vector<num_t>>::value);

            /* Assigning */

    permutation & operator=(const permutation & origin);
    permutation & operator=(permutation && rval_ref) noexcept(std::is_nothrow_move_assignable<std::vector<num_t>>::value);

    void assign(size_t length);
    void assign(std::initializer_list<num_t> ilist);
    void assign(const permutation & origin);
    void assign(permutation && rval_ref) noexcept(std::is_nothrow_move_assignable<permutation>::value);
    template <typename Input_iter_t>
    void assign(Input_iter_t begin, Input_iter_t end);

            /* Accessing */

    const num_t & operator[](size_t index) const; // counts numbers from 0
    const num_t & at(size_t index) const; // same as 'operator[]', but check if index is out of range
    num_t image_of(num_t num) const; // same as 'at()' but counts numbers from 1

            /*  Lexicographically next or previous */ // FIXME TODO this section

    permutation operator+(int steps) const;
    permutation & operator+=(int steps);
    permutation & operator++(void);
    permutation operator++(int _);

    permutation operator-(int steps) const;
    permutation & operator-=(int steps);
    permutation & operator--(void);
    permutation operator--(int _);

            /* Arithmetic operators */

    permutation operator*(const permutation & another) const;
    permutation & operator*=(const permutation & another);
    permutation operator^(int exponent) const;
    permutation & operator^=(int exponent);
    permutation reciprocal(void) const;

            /* Shifting */

    permutation operator<<(size_t n_shifts) const;
    permutation & operator<<=(size_t n_shifts);
    permutation operator>>(size_t n_shifts) const;
    permutation & operator>>=(size_t n_shifts);

            /* Comparing */

    bool operator==(const permutation & another) const;
    bool operator!=(const permutation & another) const;
    bool operator<( const permutation & another) const;
    bool operator>( const permutation & another) const;
    bool operator<=(const permutation & another) const;
    bool operator>=(const permutation & another) const;

            /* Others */

    size_t count_inversions(const std::vector<num_t> & oln) const noexcept;
    sign_t sign(void) const noexcept;
    size_t size(void) const noexcept;
    bool is_id(void) const;



  private:

            /* Check correctness */

    bool _is_oln_bijection(const std::vector<num_t> & oln) const noexcept;

            /* Others */

    sign_t _find_sign(const std::vector<num_t> & oln) const noexcept;

};



} /* namespace 'mu' */
