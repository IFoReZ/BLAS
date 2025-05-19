#include <gtest.h>
#include "TVectorCls.h"

// Тесты для конструкторов
TEST(TVectorTest, DefaultConstructor) {
	TVector<int> v;
	EXPECT_EQ(v.GetLen(), 0);
}

TEST(TVectorTest, ParamConstructor) {
	TVector<int> v(5);
	EXPECT_EQ(v.GetLen(), 5);
}

TEST(TVectorTest, CopyConstructor) {
	TVector<int> original(3);
	original[0] = 1; original[1] = 2; original[2] = 3;
	TVector<int> copy(original);

	ASSERT_EQ(copy.GetLen(), 3);
	EXPECT_EQ(copy[0], 1);
	EXPECT_EQ(copy[1], 2);
	EXPECT_EQ(copy[2], 3);
}

TEST(TVectorTest, MoveConstructor) {
	TVector<int> original(3);
	original[0] = 1; original[1] = 2; original[2] = 3;
	TVector<int> moved(std::move(original));

	EXPECT_EQ(moved.GetLen(), 3);
	EXPECT_EQ(moved[0], 1);
	EXPECT_EQ(moved[1], 2);
	EXPECT_EQ(moved[2], 3);
	EXPECT_EQ(original.GetLen(), 0); // После перемещения оригинал пуст
}

// Тесты для операторов
TEST(TVectorTest, AdditionOperator) {
	TVector<int> a(2);
	a[0] = 1; a[1] = 2;
	TVector<int> b(2);
	b[0] = 3; b[1] = 4;
	TVector<int> c = a + b;

	ASSERT_EQ(c.GetLen(), 2);
	EXPECT_EQ(c[0], 4);
	EXPECT_EQ(c[1], 6);
}

TEST(TVectorTest, SubtractionOperator) {
	TVector<int> a(2);
	a[0] = 5; a[1] = 7;
	TVector<int> b(2);
	b[0] = 3; b[1] = 2;
	TVector<int> c = a - b;

	ASSERT_EQ(c.GetLen(), 2);
	EXPECT_EQ(c[0], 2);
	EXPECT_EQ(c[1], 5);
}

TEST(TVectorTest, DotProductOperator) {
	TVector<int> a(3);
	a[0] = 1; a[1] = 2; a[2] = 3;
	TVector<int> b(3);
	b[0] = 4; b[1] = 5; b[2] = 6;
	int dot = a * b;

	EXPECT_EQ(dot, 32); // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
}

TEST(TVectorTest, ScalarMultiplication) {
	TVector<int> a(3);
	a[0] = 1; a[1] = 2; a[2] = 3;
	TVector<int> result = a * 2;

	ASSERT_EQ(result.GetLen(), 3);
	EXPECT_EQ(result[0], 2);
	EXPECT_EQ(result[1], 4);
	EXPECT_EQ(result[2], 6);
}

TEST(TVectorTest, AssignmentOperator) {
	TVector<int> a(2);
	a[0] = 1; a[1] = 2;
	TVector<int> b;
	b = a;

	ASSERT_EQ(b.GetLen(), 2);
	EXPECT_EQ(b[0], 1);
	EXPECT_EQ(b[1], 2);
}

TEST(TVectorTest, MoveAssignmentOperator) {
	TVector<int> a(2);
	a[0] = 1; a[1] = 2;
	TVector<int> b;
	b = std::move(a);

	EXPECT_EQ(b.GetLen(), 2);
	EXPECT_EQ(b[0], 1);
	EXPECT_EQ(b[1], 2);
	EXPECT_EQ(a.GetLen(), 0);
}

TEST(TVectorTest, EqualityOperator) {
	TVector<int> a(2);
	a[0] = 1; a[1] = 2;
	TVector<int> b(2);
	b[0] = 1; b[1] = 2;
	TVector<int> c(2);
	c[0] = 3; c[1] = 4;

	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a == c);
}

TEST(TVectorTest, IndexOperator) {
	TVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;

	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 3);

	v[1] = 5;
	EXPECT_EQ(v[1], 5);
}

TEST(TVectorTest, FirstNorm) {
	TVector<double> v(3);
	v[0] = 1.0; v[1] = -2.0; v[2] = 3.0;
	EXPECT_DOUBLE_EQ(v.FirstNorm(), 6.0);
}

TEST(TVectorTest, SecondNorm) {
	TVector<double> v(2);
	v[0] = 3.0; v[1] = 4.0;
	EXPECT_DOUBLE_EQ(v.SecondNorm(), 5.0);
}

TEST(TVectorTest, InfinityNorm) {
	TVector<double> v(4);
	v[0] = 1.0; v[1] = -5.0; v[2] = 3.0; v[3] = 4.0;
	EXPECT_DOUBLE_EQ(v.InfinityNorm(), 5.0);
}

TEST(TVectorTest, HolderNorm) {
	TVector<double> v(2);
	v[0] = 3.0; v[1] = 4.0;
	EXPECT_NEAR(v.HolderNorm(2.0), 5.0, 1e-6);
}
