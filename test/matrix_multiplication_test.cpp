#include "matrix_multiplication.h"

#include <gtest/gtest.h>
#include <chrono>

#include "vector.h"

using namespace stl;

TEST(MatrixMultiplicationTest, BasicTest) {
  vector<vector<int>> A = {{1, 2, 3}, {4, 5, 6}};
  vector<vector<int>> B = {{7, 8}, {9, 10}, {11, 12}};
  vector<vector<int>> expected_result = {{58, 64}, {139, 154}};

  auto C = matrix_multiplication(A, B);

  EXPECT_EQ(C.size(), expected_result.size());
  EXPECT_EQ(C.front().size(), expected_result.front().size());
  const size_t m = C.size();
  const size_t n = C.front().size();

  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      EXPECT_EQ(C[i][j], expected_result[i][j]);
    }
  }
}

TEST(MatrixMultiplicationTest, PerformanceTest) {
  const size_t n = 100;
  vector<vector<int>> A(n, vector<int>(n)), B(n, vector<int>(n));

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      A[i][j] = rand() % 100;
      B[i][j] = rand() % 100;
    }
  }

  const auto start = std::chrono::steady_clock::now();
  auto C = matrix_multiplication(A, B);
  const auto end = std::chrono::steady_clock::now();
  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << "PerformanceTest: Multiplying two " << n << "x" << n
            << " matrices took " << elapsed.count() << "ms\n";
}
