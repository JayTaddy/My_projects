#include <iostream>
#include <vector>
#include <cmath>

//advanced euclidean algorithm
int gcd (int a, int b, int & x, int & y) {
  if (a == 0) {
    x = 0; y = 1;
    return b;
  }
  int x1, y1;
  int d = gcd (b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

//returns inversed by mod
int inverseMod(int a, int m) {
  int x, y;
  int g = gcd(a, m, x, y);
  if (g != 1) {
    return -1;
  }
  x = (x % m + m) % m;
  return x;
}

//power by module.
unsigned long powerByMod(unsigned long a, unsigned long x, unsigned long p)
{
    if (x == 0) return 1;
    unsigned long res = powerByMod(a, x >> 1, p);
    res *= res;
    res %= p;
    return (x & 1)? (a * res) % p : res;
}


//.first - open key
//. second - closed key
//.first.first - e || .first.second - n
//.second.first - d || .second.second - n
std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> keysGeneration(int p, int q) {
    int phi = (p - 1) * (q - 1);
    int n = p * q;
    const int e = 33721;
    int d = inverseMod(e, phi);
    return {{e, n}, {d, n}};
}

int main() {

  size_t encryptedMessage[42] = {484531375, 336760179, 509690251, 505258072, 355612286, 676188508, 123505334, 490569067,
                            539618080, 505258072, 130404878, 676188508, 409409484, 355612286, 505258072, 13390192,
                            539618080, 123505334, 355612286, 505258072, 508868492, 336760179, 509690251, 505258072,
                            482789597, 336760179, 409409484, 355612286, 505258072, 534296388, 676188508, 676188508,
                            576324693, 505258072, 355612286, 336760179, 505258072, 423266821, 676188508, 123505334,
                            644743513, 534296388};
  int  p = 21787, q = 31511;
  auto result = keysGeneration(p, q);
  size_t dencryptedMessage[42];
  for (int index = 0; index < 42 ; ++index) {
    dencryptedMessage[index] = powerByMod(encryptedMessage[index], result.second.first, result.first.second);
    std::cout << static_cast<char>(dencryptedMessage[index]);
  }
  std::cout << std::endl;
}
