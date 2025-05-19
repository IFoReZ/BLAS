#include <gtest.h>
#include "TVectorCls.h"
#include "TMatrixCls.h"

TEST(TMatrixTest, DefaultConstructor) {
  TMatrix<int> mat;
  EXPECT_EQ(mat.GetRows(), 0);
  EXPECT_EQ(mat.GetColumns(), 0);
}

TEST(TMatrixTest, SquareConstructor) {
  TMatrix<int> mat(3, 3);
  EXPECT_EQ(mat.GetRows(), 3);
  EXPECT_EQ(mat.GetColumns(), 3);
}

TEST(TMatrixTest, RowsColumnsConstructor) {
  TMatrix<int> mat(2, 5);
  EXPECT_EQ(mat.GetRows(), 2);
  EXPECT_EQ(mat.GetColumns(), 5);
}

TEST(TMatrixTest, CopyConstructor) {
  TMatrix<int> original(2, 2);
  original[0][0] = 1; original[0][1] = 2;
  original[1][0] = 3; original[1][1] = 4;
  TMatrix<int> copy(original);

  EXPECT_EQ(copy.GetRows(), 2);
  EXPECT_EQ(copy.GetColumns(), 2);
  EXPECT_EQ(copy[0][0], 1);
  EXPECT_EQ(copy[0][1], 2);
  EXPECT_EQ(copy[1][0], 3);
  EXPECT_EQ(copy[1][1], 4);
}

TEST(TMatrixTest, MoveConstructor) {
  TMatrix<int> original(2, 2);
  original[0][0] = 1; original[0][1] = 2;
  original[1][0] = 3; original[1][1] = 4;
  TMatrix<int> moved(std::move(original));

  EXPECT_EQ(moved.GetRows(), 2);
  EXPECT_EQ(moved.GetColumns(), 2);
  EXPECT_EQ(moved[0][0], 1);
  EXPECT_EQ(moved[0][1], 2);
  EXPECT_EQ(moved[1][0], 3);
  EXPECT_EQ(moved[1][1], 4);
  EXPECT_EQ(original.GetRows(), 0);
  EXPECT_EQ(original.GetColumns(), 0);
}

// Тестирование операций
TEST(TMatrixTest, Addition) {
  TMatrix<int> a(2, 2), b(2, 2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  b[0][0] = 5; b[0][1] = 6; b[1][0] = 7; b[1][1] = 8;
  TMatrix<int> result = a + b;

  EXPECT_EQ(result[0][0], 6);
  EXPECT_EQ(result[0][1], 8);
  EXPECT_EQ(result[1][0], 10);
  EXPECT_EQ(result[1][1], 12);
}

TEST(TMatrixTest, Subtraction) {
  TMatrix<int> a(2, 2), b(2, 2);
  a[0][0] = 5; a[0][1] = 6; a[1][0] = 7; a[1][1] = 8;
  b[0][0] = 1; b[0][1] = 2; b[1][0] = 3; b[1][1] = 4;
  TMatrix<int> result = a - b;

  EXPECT_EQ(result[0][0], 4);
  EXPECT_EQ(result[0][1], 4);
  EXPECT_EQ(result[1][0], 4);
  EXPECT_EQ(result[1][1], 4);
}

TEST(TMatrixTest, MatrixMultiplication) {
  TMatrix<int> a(2, 3), b(3, 2);
  a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
  a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;
  b[0][0] = 7; b[0][1] = 8;
  b[1][0] = 9; b[1][1] = 10;
  b[2][0] = 11; b[2][1] = 12;
  TMatrix<int> result = a * b;

  EXPECT_EQ(result[0][0], 58);
  EXPECT_EQ(result[0][1], 64);
  EXPECT_EQ(result[1][0], 139);
  EXPECT_EQ(result[1][1], 154);
}

TEST(TMatrixTest, ScalarMultiplication) {
  TMatrix<int> a(2, 2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  TMatrix<int> result = a * 3;

  EXPECT_EQ(result[0][0], 3);
  EXPECT_EQ(result[0][1], 6);
  EXPECT_EQ(result[1][0], 9);
  EXPECT_EQ(result[1][1], 12);
}

TEST(TMatrixTest, DivisionByScalar) {
  TMatrix<int> a(2, 2);
  a[0][0] = 6; a[0][1] = 12; a[1][0] = 18; a[1][1] = 24;
  TMatrix<int> result = a / 3;

  EXPECT_EQ(result[0][0], 2);
  EXPECT_EQ(result[0][1], 4);
  EXPECT_EQ(result[1][0], 6);
  EXPECT_EQ(result[1][1], 8);
}

// Тестирование операторов присваивания
TEST(TMatrixTest, CopyAssignment) {
  TMatrix<int> a(2, 2), b(2, 2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  b = a;

  EXPECT_EQ(b[0][0], 1);
  EXPECT_EQ(b[0][1], 2);
  EXPECT_EQ(b[1][0], 3);
  EXPECT_EQ(b[1][1], 4);
}

// Тестирование сравнения
TEST(TMatrixTest, EqualityOperator) {
  TMatrix<int> a(2, 2), b(2, 2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  b[0][0] = 1; b[0][1] = 2; b[1][0] = 3; b[1][1] = 4;

  EXPECT_TRUE(a == b);
  b[0][0] = 5;
  EXPECT_FALSE(a == b);
}

// Тест для SaveToFile и ReadFromFile
TEST(TMatrixFileIOTest, SaveAndReadFile) {
  // Создаем тестовую матрицу
  TMatrix<int> originalMatrix(2, 3);
  originalMatrix[0][0] = 1; originalMatrix[0][1] = 2; originalMatrix[0][2] = 3;
  originalMatrix[1][0] = 4; originalMatrix[1][1] = 5; originalMatrix[1][2] = 6;

  const char* testFileName = "test_matrix.txt";

  // Сохраняем матрицу в файл
  originalMatrix.SaveToFile(testFileName);

  // Проверяем, что файл создан
  std::ifstream testFile(testFileName);
  EXPECT_TRUE(testFile.is_open());
  testFile.close();

  // Создаем новую матрицу для чтения
  TMatrix<int> loadedMatrix(2, 3);
  loadedMatrix.ReadFromFile(testFileName);

  // Проверяем, что матрицы идентичны
  EXPECT_EQ(2, loadedMatrix.GetRows());
  EXPECT_EQ(3, loadedMatrix.GetColumns());

  for (int i = 0; i < originalMatrix.GetRows(); ++i) {
    for (int j = 0; j < originalMatrix.GetColumns(); ++j) {
      EXPECT_EQ(originalMatrix[i][j], loadedMatrix[i][j]);
    }
  }

  // Удаляем тестовый файл
  remove(testFileName);
}

// Тест для проверки исключения при несовпадении размеров
TEST(TMatrixFileIOTest, ReadWithWrongSize) {
  // Создаем тестовую матрицу
  TMatrix<int> originalMatrix(2, 2);
  originalMatrix[0][0] = 1; originalMatrix[0][1] = 2;
  originalMatrix[1][0] = 3; originalMatrix[1][1] = 4;

  const char* testFileName = "test_matrix.txt";

  // Сохраняем матрицу в файл
  originalMatrix.SaveToFile(testFileName);

  // Пытаемся прочитать в матрицу другого размера
  TMatrix<int> wrongSizeMatrix(3, 3);
  EXPECT_THROW(wrongSizeMatrix.ReadFromFile(testFileName), const char*);

  // Удаляем тестовый файл
  remove(testFileName);
}

// Тест для пустой матрицы
TEST(TMatrixFileIOTest, EmptyMatrix) {
  TMatrix<int> emptyMatrix;
  const char* testFileName = "empty_matrix.txt";

  // Сохраняем пустую матрицу
  emptyMatrix.SaveToFile(testFileName);

  std::ifstream testFile(testFileName);
  int rows, cols;
  testFile >> rows >> cols;
  EXPECT_EQ(0, rows);
  EXPECT_EQ(0, cols);
  testFile.close();

  TMatrix<int> loadedMatrix;
  loadedMatrix.ReadFromFile(testFileName);
  EXPECT_EQ(0, loadedMatrix.GetRows());
  EXPECT_EQ(0, loadedMatrix.GetColumns());

  remove(testFileName);
}

TEST(TMatrixFileIOTest, NonExistentFile) {
  TMatrix<int> matrix(2, 2);
  const char* nonExistentFile = "non_existent_file.txt";

  EXPECT_THROW(matrix.ReadFromFile(nonExistentFile), const char*);
}