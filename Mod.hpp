#ifndef INCLUDE_MOD_HPP
#define INCLUDE_MOD_HPP

#include<iostream>

using namespace std;

using mod_t = long long;

mod_t extend_gcd(mod_t a, mod_t b, mod_t &x, mod_t &y ) {
    if ( b == 0 ) {
        x = 1;
        y = 0;
        return a;
    }

    mod_t d = extend_gcd(b, a%b, x, y);
    mod_t xd = y; mod_t yd = x-a/b*y;
    x = xd; y = yd;
    return d;
}

mod_t rev_mod( mod_t a, mod_t p ) {
    mod_t x, y;
    extend_gcd(a,p, x, y);
    return ( ( x < 0 ) ? x+p : x );
}

class Mod {
    static const mod_t init_P = 2;
    static mod_t P;
    mod_t value;
    mod_t p;

    Mod ( mod_t v, mod_t p ) : value(calmod(v, p)), p(p) {}

    bool isDiffMod (const Mod& x ) const { return !(this->p == x.p); }

    static mod_t extend_gcd (mod_t a, mod_t b, mod_t &x, mod_t &y );
    static mod_t rev_mod( mod_t a, mod_t p );
    static mod_t calmod( mod_t a, mod_t p ) {
        mod_t v = a%p;
        if ( v < 0 ) v += p;
        return v;
    }

    public:
     Mod ( mod_t v) : p(P), value(calmod(v, P))  {}

    static void set( const mod_t p ) { P = p; }
    Mod operator+(const Mod& x);
    Mod operator-(const Mod& x);
    Mod operator*(const Mod& x);
    Mod operator/(const Mod& x);
    Mod& operator=(const Mod& x);
    friend ostream& operator<<(ostream& os, const Mod& m );
};

mod_t Mod::extend_gcd(mod_t a, mod_t b, mod_t &x, mod_t &y ) {
    if ( b == 0 ) {
        x = 1;
        y = 0;
        return a;
    }

    mod_t d = extend_gcd(b, a%b, x, y);
    mod_t xd = y; mod_t yd = x-a/b*y;
    x = xd; y = yd;
    return d;
}


mod_t Mod::rev_mod( mod_t a, mod_t p ) {
    mod_t x, y;
    extend_gcd(a,p, x, y);
    return ( ( x < 0 ) ? x+p : x );
}

Mod Mod::operator+(const Mod& x ) {
    if ( isDiffMod(x) ) throw exception();

    mod_t v = calmod(value+x.value, p);
    return Mod(v, p);
}

Mod Mod::operator-(const Mod& x ) {
    if ( isDiffMod(x) ) throw exception();

    Mod rev = Mod(-x.value, p);
    return (*this)+rev;
}

Mod Mod::operator*(const Mod& x) {
    if ( isDiffMod(x) ) throw exception();

    mod_t v = calmod(value*x.value, p);
    return Mod(v);
}

Mod Mod::operator/(const Mod& x) {
    if ( isDiffMod(x) ) throw exception();

    Mod rev (rev_mod(x.value, x.p), p);
    return (*this)*rev;
}

Mod& Mod::operator=(const Mod& x) {
    this->p = x.p;
    this->value = x.value;
    return (*this);
}

ostream& operator<<(ostream& os, const Mod& m ) {
    os << m.value; return os;
}



mod_t Mod::P = Mod::init_P;

#endif