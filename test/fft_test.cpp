#include <gtest/gtest.h>
#include <cmath>
#include <complex>

#include "concepts.h"
#include "vector.h"

using namespace stl;

/**
 * @brief Round an unsigned integer to its next power of 2
 * @param n the unsigned integer to round up
 * @return its next power of 2
 */
inline uint32_t next_power_of_2(uint32_t n) {
  if (n == 0) {
    return 1;
  }

  n--;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  n++;

  return n;
}

/**
 * @brief If `inverse` is false, calculate the discrete Fourier transform (DFT)
 * of the coefficient vector `a`. Otherwise, interpolate from the point-value
 * representation to the coefficient representation
 * @param a the coefficient vector or the point-value vector
 * @param inverse whether to perform inverse DFT
 */
void fft(vector<std::complex<double>>& a, bool inverse) {
  size_t n = a.size();
  if (n == 1) {
    return;
  }

  vector<std::complex<double>> a0(n / 2), a1(n / 2);
  for (size_t i = 0; 2 * i < n; i++) {
    a0[i] = a[2 * i];
    a1[i] = a[2 * i + 1];
  }

  fft(a0, inverse);
  fft(a1, inverse);

  double angle = 2 * M_PI / n * (inverse ? -1 : 1);
  std::complex<double> w(1), wn(cos(angle), sin(angle));

  for (size_t i = 0; 2 * i < n; i++) {
    a[i] = a0[i] + w * a1[i];
    a[i + n / 2] = a0[i] - w * a1[i];
    if (inverse) {
      a[i] /= 2;
      a[i + n / 2] /= 2;
    }
    w *= wn;
  }
}

/**
 * @brief Multiply two polynomials A(x) and B(x) using coefficient representations
 * @param a the coefficient representation of polynomial A(x)
 * @param b the coefficient representation of polynomial B(x)
 * @return the coefficient representation of the resulting polynomial C(x)
 */
template<Numeric T>
vector<T> multiply_polynomials(const vector<T>& a, const vector<T>& b) {
  vector<std::complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());

  uint32_t degree_bound = a.size() + b.size();
  degree_bound = next_power_of_2(degree_bound);
  fa.resize(degree_bound);
  fb.resize(degree_bound);

  // Compute point-value representations of two polynomials
  fft(fa, false);
  fft(fb, false);

  // Multiply the two polynomials using the point-value representations
  for (uint32_t i = 0; i < degree_bound; i++) {
    fa[i] *= fb[i];
  }

  // Interpolate from point-value representation to coefficient representation
  fft(fa, true);

  vector<T> c(degree_bound);
  for (uint32_t i = 0; i < degree_bound; i++) {
    c[i] = round(fa[i].real());
  }

  return c;
}

TEST(FFTTest, BasicTest) {
  vector<int> A{4, 7, 1, 5, 2, 3};
  vector<int> B{1, 2, 3, 1, 6};
  vector<int> expected{4, 15, 27, 32, 46, 65, 23, 41, 15, 18};

  auto C = multiply_polynomials(A, B);
  for (size_t i = 0; i < expected.size(); i++) {
    EXPECT_EQ(C[i], expected[i]);
  }
}
