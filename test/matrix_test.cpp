#include "inc/catch.h"
#include "inc/matrix.h"

TEST_CASE("matrix: construction and equality", "[matrix]") {
    la::Matrix A(3, 3);
    for (int j = 0; j < A.cols(); ++j) {
        for (float& entry : A[j]) {
            entry = j + 1;
        }
    }

    la::Matrix B(3, 3, 1.0F);
    B[1] += B[0];
    B[2] += B[1];

    la::Vector c0{1.0F, 1.0F, 1.0F};
    la::Matrix C = la::Matrix::fromCols({c0, 2 * c0, 3 * c0});

    la::Matrix D = la::Matrix::fromRows({
        {1.0F, 2.0F, 3.0F},
        {1.0F, 2.0F, 3.0F},
        {1.0F, 2.0F, 3.0F}});

    REQUIRE(A == B);
    REQUIRE(B == C);
    REQUIRE(C == D);
}

TEST_CASE("matrix: iteration", "[matrix]") {
    la::Matrix A(2, 2, 1.0F);
    la::Vector c0{1.0F, 1.0F};
    for (la::Vector c : A) {
        REQUIRE(c == c0);
    }
    for (la::Vector& c : A) {
        REQUIRE(c == c0);
    }
    for (const la::Vector& c : A) {
        REQUIRE(c == c0);
    }
    for (int j = 0; j < A.cols(); ++j) {
        REQUIRE(A[j] == c0);
    }
}

TEST_CASE("matrix: identity", "[matrix]") {
    int n = 4;
    la::Matrix I = la::Matrix::identity(n);
    for (int j = 0; j < I.cols(); ++j) {
        for (int i = 0; i < I.rows(); ++i) {
            if (i == j) {
                // On main diagonal.
                REQUIRE(I[i][j] == 1.0F);
            } else {
                // Off main diagonal.
                REQUIRE(I[i][j] == 0.0F);
            }
        }
    }
}
