#ifndef MATRIX_MULTIPLICATION_H_
#define MATRIX_MULTIPLICATION_H_

#include <exception>
#include <stdexcept>

#include "concepts.h"
#include "vector.h"

namespace stl {

/**
 * @brief Perform matrix multiplication
 * @param A an (m x n) matrix
 * @param B an (n x p) matrix
 * @return the resulting (m x p) matrix of the multiplication
 */
template<Numeric T>
vector<vector<T>> matrix_multiplication(const vector<vector<T>>& A,
                                        const vector<vector<T>>& B) {

  const size_t m = A.size();
  const size_t n = A.front().size();
  const size_t p = B.front().size();
  if (n != B.size()) {
    throw std::invalid_argument(
        "Attempt to multiply two incompatible matrices");
  }

  vector<vector<T>> C(m, vector<T>(p));
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < p; j++) {
      T c = 0;
      for (size_t k = 0; k < n; k++) {
        c += A[i][k] * B[k][j];
      }
      C[i][j] = c;
    }
  }

  return C;
}

}  // namespace stl

#endif  // MATRIX_MULTIPLICATION_H_