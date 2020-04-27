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

TEST_CASE("matrix: augmentation", "[matrix]") {
    la::Matrix A(2, 2, 1.0F);
    la::Vector b(2, 1.0F);
    la::Matrix aug1 = la::Matrix::fromParts(A, b);
    REQUIRE(aug1.rows() == 2);
    REQUIRE(aug1.cols() == 3);
    for (int j = 0; j < aug1.cols(); ++j) {
        for (int i = 0; i < aug1.rows(); ++i) {
            REQUIRE(aug1[j][i] == 1.0F);
        }
    }
    la::Matrix B(2, 2, 1.0F);
    la::Matrix aug2 = la::Matrix::fromParts(A, B);
    REQUIRE(aug2.rows() == 2);
    REQUIRE(aug2.cols() == 4);
    for (int j = 0; j < aug2.cols(); ++j) {
        for (int i = 0; i < aug2.rows(); ++i) {
            REQUIRE(aug2[j][i] == 1.0F);
        }
    }
}

TEST_CASE("matrix: identity", "[matrix]") {
    int n = 4;
    la::Matrix I = la::Matrix::identity(n);
    for (int j = 0; j < I.cols(); ++j) {
        for (int i = 0; i < I.rows(); ++i) {
            if (i == j) {
                // On main diagonal.
                REQUIRE(I[j][i] == 1.0F);
            } else {
                // Off main diagonal.
                REQUIRE(I[j][i] == 0.0F);
            }
        }
    }
}

TEST_CASE("matrix: random", "[matrix]") {
    int n = 25;
    REQUIRE(la::Matrix::random(n, n) != la::Matrix::random(n, n));
}

TEST_CASE("matrix: random in [lo, hi]", "[matrix]") {
    int n = 4;
    float lo = 6.0;
    float hi = 8.0;
    la::Matrix R = la::Matrix::random(n, n, lo, hi);
    for (const la::Vector& c : R) {
        for (float entry : c) {
            REQUIRE(entry >= lo);
            REQUIRE(entry <= hi);
        }
    }
}

TEST_CASE("matrix: whitelist", "[matrix]") {
    la::Matrix A = la::Matrix::fromRows({
        { 1,  2,  3,  4,  5},
        { 6,  7,  8,  9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}});
    REQUIRE(la::Matrix::whitelist(A, {1, 2}, {2, 3}) == la::Matrix::fromRows({
        { 8,  9},
        {13, 14}}));
}

TEST_CASE("matrix: blacklist", "[matrix]") {
    la::Matrix A = la::Matrix::fromRows({
        { 1,  2,  3,  4,  5},
        { 6,  7,  8,  9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}});
    REQUIRE(la::Matrix::blacklist(A, {0, 1, 2, 3}, {0, 1, 2, 3}) ==
        la::Matrix::fromRows({{25}}));
    REQUIRE(la::Matrix::blacklist(A, {1}, {2, 3}) ==
        la::Matrix::fromRows({
            { 1,  2,  5},
            {11, 12, 15},
            {16, 17, 20},
            {21, 22, 25}}));
}

TEST_CASE("matrix: sum and scalar multiple", "[matrix]") {
    la::Matrix A = la::Matrix::fromRows({
        { 4, 0, 5},
        {-1, 3, 2}});
    la::Matrix B = la::Matrix::fromRows({
        {1, 1, 1},
        {3, 5, 7}});
    REQUIRE(2 * B == la::Matrix::fromRows({
        {2,  2,  2},
        {6, 10, 14}}));
    REQUIRE(A - (2 * B) == la::Matrix::fromRows({
        { 2, -2,   3},
        {-7, -7, -12}}));
}

TEST_CASE("matrix: matrix-vector multiplication", "[matrix]") {
    la::Matrix M = la::Matrix::fromRows({
        {0.98033F, 0.00179F},
        {0.01967F, 0.99821F}});
    la::Vector x{3.8041430e7F, 2.75872610e8F};
    for (int i = 0; i < 10; ++i) {
        x = M * x;
    }
    REQUIRE(approxEqual(x, la::Vector{3.5729e7F, 2.7818e8F}, 1e-3));
}

TEST_CASE("matrix: matrix-matrix multiplication", "[matrix]") {
    la::Matrix A = la::Matrix::fromRows({
        {2,  3},
        {1, -5}});
    la::Matrix B = la::Matrix::fromRows({
        {4,  3, 6},
        {1, -2, 3}});
    REQUIRE(A * B == la::Matrix::fromRows({
        {11,  0, 21},
        {-1, 13, -9}}));
}

TEST_CASE("matrix: small power", "[matrix]") {
    la::Matrix A = la::Matrix::fromRows({
        {  1,   2,   2,    1,   4},
        {3.4,   1,   1,    0,   0},
        {0.5, 0.6, 1.9, -2.5, 1.6},
        {  4,   3,   2,    2,   1},
        {  8, 3.3,   2,    2,   7}});
    la::Matrix AAAAA = la::Matrix::fromRows({
        { 65028.3214F,	36701.4724F, 32087.1142F,  11718.985F,  65669.4188F},
        { 21771.0891F,	12142.9406F, 10561.7943F,  3892.1805F,  21793.3282F},
        {15385.95003F,	8688.77318F, 7465.56279F, 3000.89125F, 15359.35306F},
        { 50610.1654F,	28386.6304F, 24807.9022F,   8995.465F,  51117.7708F},
        {147033.9025F,	82781.2226F, 72387.6773F, 26271.6875F, 147941.2582F}});
    REQUIRE(la::approxEqual(la::pow(A, 5), AAAAA, 1e-3));
}

TEST_CASE("matrix: large power", "[matrix]") {
    la::pow(la::Matrix::random(25, 25), 100);
}

TEST_CASE("matrix: transpose", "[matrix]") {
    la::Matrix A = la::Matrix::fromRows({
        {-5,  2},
        { 1, -3},
        { 0,  4}});
    la::Matrix B = la::Matrix::fromRows({
        {6,  6},
        {2, -8},
        {3,  9}});
    la::Matrix C = la::Matrix::fromRows({
        { 1, 2},
        {-3, 4}});
    REQUIRE(la::transpose(A) == la::Matrix::fromRows({
        {-5, 1, 0},
        {2, -3, 4}}));
    REQUIRE(la::transpose(la::transpose(A)) == A);
    REQUIRE(la::transpose(A + B) == la::transpose(A) + la::transpose(B));
    REQUIRE(la::transpose(3.14F * A) == 3.14F * la::transpose(A));
    REQUIRE(la::transpose(A * C) == la::transpose(C) * la::transpose(A));
}

TEST_CASE("matrix: determinant", "[matrix]") {
    la::Matrix A = la::Matrix::fromRows({
        {1, 2},
        {3, 4}});
    la::Matrix B = la::Matrix::fromRows({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}});
    la::Matrix C = la::Matrix::fromRows({
        {1, 3, 5, 9},
        {1, 3, 1, 7},
        {4, 3, 9, 7},
        {5, 2, 0, 9}});
    la::Matrix D = la::Matrix::fromRows({
        {3, 1, 4, 1, 5, 9, 2, 6},
        {5, 3, 5, 8, 9, 7, 9, 3},
        {2, 3, 8, 4, 6, 2, 6, 4},
        {3, 3, 8, 3, 2, 7, 9, 5},
        {0, 2, 8, 8, 4, 1, 9, 7},
        {1, 6, 9, 3, 9, 9, 3, 7},
        {5, 1, 0, 5, 8, 2, 0, 9},
        {7, 4, 9, 4, 4, 5, 9, 2}});
    la::Matrix E = la::Matrix::fromRows({
        {3, 1, 4, 1, 5, 9, 2, 6},
        {5, 3, 5, 8, 9, 7, 9, 3},
        {2, 3, 8, 4, 6, 2, 6, 4},
        {3, 3, 8, 3, 2, 7, 9, 5},
        {0, 2, 8, 8, 4, 1, 9, 7},
        {1, 6, 9, 3, 9, 9, 3, 7},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {7, 4, 9, 4, 4, 5, 9, 2}});

    REQUIRE(la::det(A) == -2.0F);
    REQUIRE(la::det(B) == 0.0F);
    REQUIRE(la::det(C) == -376.0F);
    REQUIRE(la::det(D) == 1378143.0F);
    REQUIRE(la::det(E) == 0.0F);
}