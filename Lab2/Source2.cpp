#include <iostream>
#include <windows.h>
#include <time.h>
using namespace std;

class Matrix
{
public:
	// ������������
	Matrix();
	Matrix(int n);
	Matrix(int n, int min, int max);

	// ����������� �����������
	Matrix(const Matrix& matrix); 
	
	// �������
	int GetMin();
	int GetMax();
	int GetValue();
	int GetElement(int rows, int cols);
	int GetFirstNorm();
	int GetInfinitelyNorm();
	int GetEuclodsNorm();
	
	// ������ �������
	void ShowMatrix();
	void ShowTransMatrix();

	// �������
	void SetRows(int rows);
	void SetCols(int rows);
	void SetElement(int rows, int cols, int el);
	

	// ���������� ����������
	void operator = (const Matrix& new_matrix);
	Matrix operator + (const Matrix& new_matrix);
	Matrix operator - (const Matrix& new_matrix);
	Matrix operator * (const Matrix& new_matrix);
	Matrix operator *= (const Matrix& new_matrix);
	Matrix Stepen(const Matrix& new_matrix, int n);
	int* operator[](int index);


	// ����������
	~Matrix();

private:
	int n;
	int min, max;
	int** matrix;
};
// ������������
Matrix::Matrix() {
	this->n = 0;
}
Matrix::Matrix(int n)
{
	this->n = n;
	this->matrix = new int*[n];

	for (int i = 0; i < n; i++)
		matrix [i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0;
}
Matrix::Matrix(int n, int min, int max) : Matrix::Matrix(n)
{
	this->max = max;
	this->min = min;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = rand() % (max(max, min) - min(max, min) + 1) + min(max, min);
}

// CONSTRUCTOR COPY
Matrix::Matrix(const Matrix& new_matrix) : Matrix(new_matrix.n)  {
	for (int i = 0; i < this->n; i++)
		for (int j = 0; j < this->n; j++)
			this->matrix[i][j] = new_matrix.matrix[i][j];
}

// GETTERS
int Matrix::GetMin() { return this->min; }
int Matrix::GetMax() { return this->max; }
int Matrix::GetValue() { return this->n; }
int Matrix::GetElement(int rows, int cols) {
	if (rows > n || cols > n)
	{
		cout << "ERROR\n";
		return 0;
	}
	else
		return this->matrix[rows--][cols--];
}
int Matrix::GetFirstNorm() {
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		int temp = 0;
		for (int j = 0; j < n; j++)
			temp += this->matrix[j][i];
		sum = max(temp, sum);
	}
	return sum;
}
int Matrix::GetInfinitelyNorm() {
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		int temp = 0;
		for (int j = 0; j < n; j++)
			temp += this->matrix[i][j];
		sum = max(temp, sum);
	}
	return sum;
}
int Matrix::GetEuclodsNorm() {
	int sum = 0;
	for (int i = 0; i < this->n; i++)
		for (int j = 0; j < this->n; j++)
			sum += this->matrix[i][j];
	return sqrt(sum);
}

// SETTERS
void Matrix::SetRows(int rows) {
	if (rows > this->n)
		cout << "ERROR\n";
	else
		for (int i = 0; i < rows; i++)
		{
			cout << "����� ������� [" << rows << "][" << i + 1 << "]";
			cin >> this->matrix[rows - 1][i];
		}
}
void Matrix::SetCols(int cols) {
	if (cols > this->n)
		cout << "ERROR\n";
	else
		for (int i = 0; i < cols; i++)
		{
			cout << "����� ������� [" << i + 1 << "][" << cols << "]";
			cin >> this->matrix[i][cols - 1];
		}
}
void Matrix::SetElement(int rows, int cols, int el) {
	if (rows > n || cols > n)
		cout << "ERROR\n";
	else
		this->matrix[rows - 1][cols - 1] = el;
}

// SHOW MATRIX
void Matrix::ShowMatrix() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << this->matrix[i][j] << '\t';
		}
		cout << "\n\n";
	}
	cout << '\n';
}
void Matrix::ShowTransMatrix() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matrix[j][i] << '\t';
		}
		cout << '\n\n';
	}
	cout << '\n';
}

// OPERATOR OVERLOADS
void Matrix::operator=(const Matrix& new_matrix){
	if (this->GetValue() != new_matrix.n)
	{
		cout << "Is not equal matrix!\n\n";
		return;
	}
	else {
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->n; j++)
				this->matrix[i][j] = new_matrix.matrix[i][j];
	}
}
Matrix Matrix::operator+(const Matrix& new_matrix)  {
	if (this->n!=new_matrix.n)
	{
		cout << "ERROR";
		return 0;
	}
	else{
		Matrix temp(this->n);
		for (int i = 0; i < temp.n; i++)
			for (int j = 0; j < temp.n; j++)
				temp.matrix[i][j] = this->matrix[i][j] + new_matrix.matrix[i][j];
		return temp;
	}
}
Matrix Matrix::operator-(const Matrix& new_matrix) {
	if (this->n != new_matrix.n)
	{
		cout << "ERROR";
		return 0;
	}
	else {
		Matrix temp(this->n);
		for (int i = 0; i < temp.n; i++)
			for (int j = 0; j < temp.n; j++)
				temp.matrix[i][j] = this->matrix[i][j] - new_matrix.matrix[i][j];
		return temp;
	}
}
Matrix Matrix::operator*(const Matrix& new_matrix) {
	if (this->n != new_matrix.n)
	{
		cout << "ERROR";
		return 0;
	}
	else {
		Matrix temp(this->n);
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->n; j++)
				for (int k = 0; k < n; k++)
					temp.matrix[i][j] += this->matrix[i][k] * new_matrix.matrix[k][j];
		return temp;
	}	
}
Matrix Matrix::Stepen(const Matrix& new_matrix, int n) {
	Matrix temp(new_matrix);
	if (n <= 1)
		cout << "ERROR\n";
	else
		for (int i = 0; i < n - 1; i++)
			temp = temp * new_matrix;

	return temp;
}

int* Matrix::operator [] (int index) // �������� [] ���������� ������ �� int
{
	return matrix[index];
}

// DESTRUCTOR
Matrix::~Matrix()
{
	for (int i = 0; i < n; i++)
		delete[]this->matrix[i];
	delete[]this->matrix;
}

int main() {
	srand(time(NULL));
	cout << "Matrix A\n\n";
	Matrix A(2, 1, 10);
	A.ShowMatrix();

	cout << "Matrix B\n\n";
	Matrix B(2, 1, 10);
	B.ShowMatrix();

	cout << "Matrix C\n\n";
	Matrix C(2);

	cout << "Matrix C +++\n\n";
	C = A + B;
	C.ShowMatrix();

	cout << "Matrix C ---\n\n";
	C = A - B;
	C.ShowMatrix();

	cout << "Matrix C ***\n\n";
	C = A * B;
	C.ShowMatrix();

	cout << "Matrix C ^^^\n\n";
	A = A.Stepen(A, 2);
	A.ShowMatrix();

	return 0;
	system("pause");
}
