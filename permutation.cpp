#include <utility>
#include <algorithm>
#include <iterator>
#include <initializer_list>
#include <vector>

#include "permutation.hpp"



namespace /* nameless */{

inline size_t max(size_t a, size_t b)
{ return (a > b ? a : b); }

inline size_t min(size_t a, size_t b)
{ return (a < b ? a : b); }

} /* nameless namespace */


using namespace mu;



        /* Constructors */


// Must construct id permutation of length 1
permutation::permutation(void) : _sign(permutation::sign_t::EVEN)
{
    try{
        this->_oln = {0};
    }
    catch(...){
        throw "exc";
    }
}

// Must construct id permutation of certain length
permutation::permutation(size_t length) : _sign(permutation::sign_t::EVEN)
{
    if(length == 0)
        throw "exc";

    try{
        this->_oln = std::vector<num_t>(length);
    }
    catch(...){
        throw "exc";
    }
    for(size_t i = 0; i < length; ++i)
        this->_oln[i] = i;
}

permutation::permutation(std::initializer_list<permutation::num_t> ilist) : permutation()
{
    std::vector<num_t> tmp_oln;
    try{
        tmp_oln = ilist;
    }
    catch(...){
        throw "exc";
    }

    if(!_is_oln_bijection(tmp_oln))
        throw "exc";

    this->_oln = std::move(tmp_oln);
    this->_sign = this->_find_sign(this->_oln);
}

permutation::permutation(const permutation & origin) : _sign(origin._sign)
{
    try{
        this->_oln = origin._oln;
    }
    catch(...){
        throw "exc";
    }
}

permutation::permutation(permutation && rval_ref)
    noexcept(std::is_nothrow_move_constructible<std::vector<num_t>>::value)
{
    this->_oln = std::move(rval_ref._oln);
    this->_sign = rval_ref._sign;
}



        /* Destructor */


permutation::~permutation()
    noexcept(std::is_nothrow_destructible<std::vector<num_t>>::value)
{ /* empty */ }



        /* Assigning */


permutation & permutation::operator=(const permutation & origin)
{
    try{
        this->_oln = origin._oln;
        this->_sign = origin._sign;
    }
    catch(...){
        throw "exc";
    }

    return *this;
}

permutation & permutation::operator=(permutation && rval_ref)
    noexcept(std::is_nothrow_move_assignable<std::vector<num_t>>::value)
{
    this->_oln = std::move(rval_ref._oln);
    this->_sign = rval_ref._sign;

    return *this;
}

void permutation::assign(size_t length)
{
    try{
        this->_oln.resize(length);
        for(size_t i = 0; i < length; ++i)
            this->_oln[i] = i;
    }
    catch(...){
        throw "exc";
    }

    this->_sign = permutation::sign_t::EVEN;
}

void permutation::assign(std::initializer_list<permutation::num_t> ilist)
{
    try{
        this->_oln = ilist;
    }
    catch(...){
        throw "exc";
    }

    this->_sign = this->_find_sign(this->_oln);
}

void permutation::assign(const permutation & origin)
{ (*this) = origin; }

void permutation::assign(permutation && rval_ref)
    noexcept(std::is_nothrow_move_assignable<permutation>::value)
{ (*this) = std::move(rval_ref); }

template <typename Input_iter_t>
void permutation::assign(Input_iter_t begin, Input_iter_t end)
{
    try{
        this->_oln.assign(begin, end);
    }
    catch(...){
        throw "exc";
    }

    this->_sign = this->_find_sign(this->_oln);
}



        /* Accessing */


const permutation::num_t & permutation::operator[](size_t index) const
{ return this->_oln[index]; }

const permutation::num_t & permutation::at(size_t index) const
{
    if(index >= this->_oln.size())
        throw "exc";

    return this->_oln.at(index);
}

typename permutation::num_t permutation::image_of(permutation::num_t num) const
{
    if(num == 0 || num > this->_oln.size())
        throw "exc";

    return this->_oln.at(num-1)+1;
}



        /*  Lexicographically next or previous */ // FIXME TODO this section

permutation permutation::operator+(int steps) const
{
    permutation summed = (*this);

    if(steps > 0)
    {
        while(steps--)
            std::next_permutation(summed._oln.begin(), summed._oln.end());
    }
    else if(steps < 0)
    {
        steps = -steps;
        while(steps--)
            std::prev_permutation(summed._oln.begin(), summed._oln.end());
    }

    return summed;
}

permutation & permutation::operator+=(int steps)
{
    if(steps > 0)
    {
        while(steps--)
            std::next_permutation(this->_oln.begin(), this->_oln.end());
    }
    else if(steps < 0)
    {
        steps = -steps;
        while(steps--)
            std::prev_permutation(this->_oln.begin(), this->_oln.end());
    }

    return (*this);
}

permutation & permutation::operator++(void)
{
    std::next_permutation(this->_oln.begin(), this->_oln.end());

    return (*this);
}

permutation permutation::operator++(int _)
{
    permutation tmp = (*this);

    std::next_permutation(this->_oln.begin(), this->_oln.end());

    return tmp;
}

permutation permutation::operator-(int steps) const
{ return (*this) + (-steps); }

permutation & permutation::operator-=(int steps)
{
    (*this) += (-steps);

    return (*this);
}

permutation & permutation::operator--(void)
{
    std::prev_permutation(this->_oln.begin(), this->_oln.end());

    return (*this);
}

permutation permutation::operator--(int _)
{
    permutation tmp = (*this);

    std::prev_permutation(this->_oln.begin(), this->_oln.end());

    return tmp;
}



        /* Arithmetic operators */


permutation permutation::operator*(const permutation & another) const
{
    permutation product = (this->size() > another.size() ? (*this) : another);

    for(size_t i = 0; i < another.size(); ++i)
    {
        if(another[i] < this->size())
            product._oln[i] = this->_oln[another._oln[i]];
        else
            product._oln[i] = another._oln[i];
    }

    return product;
}

permutation & permutation::operator*=(const permutation & another)
{
    (*this) = (*this) * another;

    return (*this);
}

permutation permutation::operator^(int exponent) const
{
    if(exponent == 0)
        return permutation(this->size());

    size_t sz = this->size();
    permutation power(sz);
    int abs_exp = (exponent > 0 ? exponent : -exponent);

    for(size_t ind = 0; ind < sz; ++ind)
    {
        num_t image = (*this)[ind];
        for(int _ = 1; _ < abs_exp; ++_)
            image = (*this)[image];
        power._oln[ind] = image;
    }

    if(exponent < 0)
        power = power.reciprocal();

    return power;
}

permutation & permutation::operator^=(int exponent)
{
    (*this) = (*this) ^ exponent;

    return (*this);
}

permutation permutation::reciprocal(void) const
{
    permutation rec;
    try{
        permutation rec = permutation(this->size());
        for(size_t i = 0; i < this->size(); ++i)
            rec._oln[this->_oln[i]] = i;
    }
    catch(...){
        throw "exc";
    }
    rec._sign = this->_sign;

    return rec;
}



        /* Shifting */


permutation permutation::operator<<(size_t n_shifts) const
{
    n_shifts %= this->size();

    permutation shifted = (*this);

    std::rotate(shifted._oln.begin(), std::next(shifted._oln.begin(), n_shifts), shifted._oln.end());
    shifted._sign = shifted._find_sign(shifted._oln);

    return shifted;
}

permutation & permutation::operator<<=(size_t n_shifts)
{
    n_shifts %= this->size();

    std::rotate(this->_oln.begin(), std::next(this->_oln.begin(), n_shifts), this->_oln.end());
    this->_sign = this->_find_sign(this->_oln);

    return (*this);
}

permutation permutation::operator>>(size_t n_shifts) const
{
    n_shifts %= this->size();

    permutation shifted = (*this);

    std::rotate(shifted._oln.rbegin(), std::next(shifted._oln.rbegin(), n_shifts), shifted._oln.rend());
    shifted._sign = shifted._find_sign(shifted._oln);

    return shifted;
}

permutation & permutation::operator>>=(size_t n_shifts)
{
    n_shifts %= this->size();

    std::rotate(this->_oln.rbegin(), std::next(this->_oln.rbegin(), n_shifts), this->_oln.rend());
    this->_sign = this->_find_sign(this->_oln);

    return (*this);
}



        /* Comparing */


bool permutation::operator==(const permutation & another) const
{ return (this->_oln == another._oln); }

bool permutation::operator!=(const permutation & another) const
{ return (this->_oln != another._oln); }

bool permutation::operator<(const permutation & another) const
{ return (this->_oln < another._oln); }

bool permutation::operator>(const permutation & another) const
{ return (this->_oln > another._oln); }

bool permutation::operator<=(const permutation & another) const
{ return (this->_oln <= another._oln); }

bool permutation::operator>=(const permutation & another) const
{ return (this->_oln >= another._oln); }



        /* Others */


size_t permutation::count_inversions(const std::vector<permutation::num_t> & oln) const
    noexcept
{
    size_t n_inv = 0;

    for(size_t i = 0; i < oln.size()-1; ++i)
        for(size_t j = i+1; j < oln.size(); ++j)
            if(oln[i] > oln[j])
                ++n_inv;

    return n_inv;
}

typename permutation::sign_t permutation::sign(void) const
    noexcept
{ return this->_sign; }

size_t permutation::size(void) const
    noexcept
{ return  this->_oln.size(); }

bool permutation::is_id(void) const
{
    size_t sz = this->_oln.size();
    for(size_t i = 0; i < sz/2; ++i)
        if(this->_oln[i] != i || this->_oln[sz-1-i] != sz-1-i)
            return false;
    return true;
}



        /* Check correctness */


bool permutation::_is_oln_bijection(const std::vector<permutation::num_t> & oln) const
    noexcept
{
    size_t min_num = oln[0],
           max_num = oln[0];

    for(size_t i = 0; i < oln.size(); ++i)
    {
        min_num = min(min_num, oln[i]);
        max_num = max(max_num, oln[i]);
        for(size_t j = i+1; j < oln.size(); ++j)
            if(oln[i] == oln[j])
                return false;
    }

    return (min_num == 0) && (max_num == oln.size() - 1);
}



        /* Others */


typename permutation::sign_t permutation::_find_sign(const std::vector<permutation::num_t> & oln) const
    noexcept
{
    return (this->count_inversions(oln) % 2 == 0 ?
            permutation::sign_t::EVEN :
            permutation::sign_t::ODD  );
}


permutation permutation::make_id(size_t length)
{ return permutation(length); }
