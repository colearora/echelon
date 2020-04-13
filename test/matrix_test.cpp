#include "inc/catch.h"
#include "inc/matrix.h"

// TEST_CASE("matrix: construction and access", "[matrix]") {
//     la::Matrix<double, 4, 3> A({
//         { 1,  2,  3},
//         { 4,  5,  6},
//         { 7,  8,  9},
//         {10, 11, 12}});
//     REQUIRE(A.rows() == 4);
//     REQUIRE(A.cols() == 3);
//     REQUIRE(A(0, 0) == 1);
//     REQUIRE(A(0, 1) == 2);
//     REQUIRE(A(1, 0) == 4);
//     REQUIRE(A[1] == la::Vector<double, 4>{2, 5, 8, 11});
// }