#include <iostream>

static const long double PI = static_cast<long double>(3.14159265359);

//............................................ factorial ............................................//
template <int N> struct factorial {
  static const long long value = N * factorial<N-1>::value;
};

template <> struct factorial<1> {
  static const long long value = 1L;
};

//........................................... power .................................................//
template <class X, int N> struct power {
  static const long double value;
};

template <class X, int N> const long double power<X, N>::value = X::value * power<X, N-1>::value;

template <class X> struct power<X, 0> {
  static const long double value;
};

template <class X> const long double power<X, 0>::value = static_cast<long double>(1);

//................................................ Simplify Rad....................................................................................//
template <class X> struct SimplifyRad {
  static const long double value;
};

template <class X> const long double SimplifyRad<X>::value = X::value - (2 * PI * static_cast<long double>(static_cast<int>(X::value/(2*PI))));
//.................................................. Cos ................................................................................//
template <class X, int N> struct cos {
  static const long double value;
};

template <class X, int N> const long double cos<X, N>::value = (((N % 2 == 0 ? 1 : -1) * power<SimplifyRad<X>, 2*N>::value)/
                                                                (static_cast<long double>(factorial<2*N>::value))) + cos<X, N-1>::value;

template <class X> struct cos<X, 0> {
  static const long double value;
};

template <class X> const long double cos<X, 0>::value = static_cast<long double>(1);

//.................................................... Sin ............................................................................//
template <class X, int N> struct sin {
  static const long double value;
};

template <class X, int N> const long double sin<X, N>::value =(((N % 2 == 0 ? -1 : 1) * power<SimplifyRad<X>, 2*N-1>::value) /
                                                               (static_cast<long double>(factorial<2*N-1>::value))) + sin<X, N-1>::value;

template <class X> struct sin<X, 0> {
  static const long double value;
};

template <class X> const long double sin<X, 0>::value = static_cast<long double>(0);

//......................................... EXP ........................................................//
template <class X, int N> struct exp {
  static const long double value;
};

template <class X, int N> const long double exp<X, N>::value = (power<X, N>::value) / factorial<N>::value + exp <X, N - 1>::value;

template <class X> struct exp <X, 1> {
  static const long double value;
};

template <class X> const long double exp<X, 1>::value = X::value + static_cast<long double>(1.0);

//............................................ Logarithm ...........................................//
template<class X, int N> struct log {
  static const long double value;
};

template <class X, int N> const long double log<X, N>::value = log<X, N - 1>::value + ((N % 2 == 0 ? -1 : 1) * (power<X, N>::value) / static_cast<long double>(N + 1));

template<class X> struct log<X, 1> {
  static const long double value;
};

template <class X> const long double log<X, 1>::value = X::value - static_cast<long double>(1.0);

//............................................. sin(sin(x)) ...........................................//
template<class X, int N> struct sinSin {
  static const long double value;
};

template<class X, int N> const long double sinSin<X, N>::value = sin<sin<X, N - 1>, N >::value;

template<class X> struct sinSin<X, 1> {
  static const long double value;
};

template<class X> const long double sinSin<X, 1>::value = sin<X, 1>::value;
//............................................. cos(cos(x)) ...........................................//
template<class X, int N> struct cosCos {
  static const long double value;
};

template<class X, int N> const long double cosCos<X, N>::value = cos<cos<X, N - 1>, N >::value;

template<class X> struct cosCos<X, 1> {
  static const long double value;
};

template<class X> const long double cosCos<X, 1>::value = cos<X, 1>::value;
//............................................. exp(exp(x)) ...........................................//
template<class X, int N> struct expExp{
  static const long double value;
};

template<class X, int N> const long double expExp<X, N>::value = exp<exp<X, N - 1>, N>::value;

template<class X> struct expExp<X, 1> {
  static const long double value;
};

template<class X> const long double expExp<X, 1>::value = exp<X, 1>::value;
//............................................. ln(ln(x)) .............................................//
template<class X, int N> struct logLog{
  static const long double value;
};

template<class X, int N> const long double logLog<X, N>::value = log<log<X, N - 1>, N>::value;

template<class X> struct logLog<X, 1> {
  static const long double value;
};

template<class X> const long double logLog<X, 1>::value = logLog<X, 1>::value;
//........................................ Variable ........................................//
struct var
{
    static const long double value;
};

const long double var::value = static_cast<long double>(0.5);

int main () {
  std::cout << sinSin<cosCos<logLog<expExp<var, 2>, 2>, 3>, 4>::value  << std::endl;
}

