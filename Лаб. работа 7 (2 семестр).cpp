/* ЛабВозьмите за основу репозиторий mathutils (https://gitlab.com/mishklgpmi/mathutils) и 
дополните в нем перегрузку для оператора умножения.    +
Выполните перегрузку оператора вычитания.  +
Дополните класс методами для нахождения определителя матрицы размерами 2х2 и 3х3. +
Для других размеров предусмотрите сообщение «Операция не поддерживается». +
Дополните класс методом для нахождения обратной матрицы размером 2х2 и 3х3.Для остальных размеров -
предусмотрите сообщение «Операция не поддерживается».
Дополните класс методами для нахождения транспонированной матрицы произвольного размера. +
Выполните проверку. */
#include <iostream>

class Matrix
{
	// Абстракция
	// Инкапсуляция
	// Использование вне класса
public:
	// Конструктор
	Matrix(int n, int m)
	{
		//std::cout << "Constructor" << std::endl;
		m_n = n;
		m_m = m;
		m_mat = new float* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new float[m_m];
	}
	// Конструктор копирования
	Matrix(const Matrix& mat)
	{
		//std::cout << "Copy constructor" << std::endl;

		m_n = mat.m_n;
		m_m = mat.m_m;

		m_mat = new float* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new float[m_m];

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];
	}
	// Присваивание
	Matrix& operator=(const Matrix& mat)
	{
		//std::cout << "Operator =" << std::endl;

		m_n = mat.m_n;
		m_m = mat.m_m;

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];

		return *this;
	}
	// Оператор сложения
	Matrix operator+(const Matrix& mat) {
		std::cout << "operator+" << std::endl;
		int t = 1, r=1;
		if (mat.m_m == m_m && mat.m_n == m_n)
		{
			t = mat.m_m;
			r = mat.m_n;
		}
		else
		{
			std::cout << "Eror 1" << std::endl;
			Matrix tmp1(0, 0);
			return tmp1;
		}
		Matrix tmp(r, t);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}
	// Оператор сложения  C += A <=> C = C + A
	Matrix operator+=(const Matrix& mat) {
		std::cout << "operator+=" << std::endl;
		int t = 1, r = 1;
		if (mat.m_m == m_m && mat.m_n == m_n)
		{
			t = mat.m_m;
			r = mat.m_n;
		}
		else
		{
			std::cout << "Eror 1" << std::endl;
			Matrix tmp1(0, 0);
			return tmp1;
		}
		Matrix tmp(r, t);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}
	// Оператор вычитания
	Matrix operator-(const Matrix& mat) {
		std::cout << "operator-" << std::endl;
		int t = 1, r = 1;
		if (mat.m_m == m_m && mat.m_n == m_n)
		{
			t = mat.m_m;
			r = mat.m_n;
		}
		else
		{
			std::cout << "Eror 1" << std::endl;
			Matrix tmp1(0, 0);
			return tmp1;
		}
		Matrix tmp(r, t);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
		return tmp;
	}
	// Оператор вычитания  C -= A <=> C = C - A
	Matrix operator-=(const Matrix& mat) {
		std::cout << "operator-=" << std::endl;
		int t = 1, r = 1;
		if (mat.m_m == m_m && mat.m_n == m_n)
		{
			t = mat.m_m;
			r = mat.m_n;
		}
		else
		{
			std::cout << "Eror 1" << std::endl;
			Matrix tmp1(0, 0);
			return tmp1;
		}
		Matrix tmp(r, t);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
		return tmp;
	}
	// Оператор умножения
	Matrix operator*(const Matrix& mat) {
		std::cout << "operator*" << std::endl;
		int t = 1, r = 1;
		if (mat.m_n == m_m)
		{
			t = m_m;
			r = mat.m_n;
		}
		else
		{
			std::cout << "Eror 1" << std::endl;
			Matrix tmp1(0, 0);
			return tmp1;
		}
		Matrix tmp(r, t);
		for (int i = 0; i < m_m;i++)
		{
			for (int j = 0; j < mat.m_n; j++)
			{
				tmp.m_mat[i][j] = 0;
				for (int k = 0; k < m_n; k++)
				{
					tmp.m_mat[i][j] += m_mat[i][k] * mat.m_mat[k][j];
				}
			}
		}
			
		return tmp;
	}
	// Определитель 2х2 и 3х3
	float Det()
	{
		float d = 0;
		if (m_n == 2 && m_m == 2)
		{
			d += m_mat[0][0] * m_mat[1][1];
			d -= m_mat[0][1] * m_mat[1][0];
			return d;
		}
		else if (m_n == 3 && m_m == 3)
		{
			d = m_mat[0][0] * m_mat[1][1] * m_mat[2][2] - m_mat[0][0] * m_mat[1][2] * m_mat[2][1]
				- m_mat[0][1] * m_mat[1][0] * m_mat[2][2] + m_mat[0][1] * m_mat[1][2] * m_mat[2][0]
				+ m_mat[0][2] * m_mat[1][0] * m_mat[2][1] - m_mat[0][2] * m_mat[1][1] * m_mat[2][0];
			return d;
		}
		else if (m_n == 1 && m_m == 1)
		{
			d = m_mat[0][0];
			return d;
		}
		else
		{
			std::cout << "Операция не поддерживается" << std::endl;
			return 0;
		}
	}
	// Транспонированная матрица
	Matrix Tmatrix()
	{
		Matrix tmp(m_m, m_n);
		for (int i = 0;i < m_n;i++)
		{
			for (int j = 0;j < m_m;j++)
			{
				tmp.m_mat[j][i] = m_mat[i][j];
			}
		}
		return tmp;
	}

	// Деструктор
	~Matrix()
	{
		//std::cout << "Destructor" << std::endl;
		for (int i = 0; i < m_n; i++)
			delete[] m_mat[i];
		delete m_mat;
	}

	// friend - позволяет функции иметь доступ к private полям/методам класса
	friend std::istream& operator>>(std::istream& os, Matrix& mat);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
	int Getn()
	{
		return m_n;
	}
	int Getm()
	{
		return m_m;
	}
	// Не помню что конкретно делает но пусть будет
	void inversion()
	{
		int N = m_n;
		double temp;

		Matrix E(m_n, m_m);
		
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				E.m_mat[i][j] = 0.0;

				if (i == j)
					E.m_mat[i][j] = 1.0;
			}

		for (int k = 0; k < N; k++)
		{
			temp = m_mat[k][k];

			for (int j = 0; j < N; j++)
			{
				m_mat[k][j] /= temp;
				E.m_mat[k][j] /= temp;
			}

			for (int i = k + 1; i < N; i++)
			{
				temp = m_mat[i][k];

				for (int j = 0; j < N; j++)
				{
					m_mat[i][j] -= m_mat[k][j] * temp;
					E.m_mat[i][j] -= E.m_mat[k][j] * temp;
				}
			}
		}

		for (int k = N - 1; k > 0; k--)
		{
			for (int i = k - 1; i >= 0; i--)
			{
				temp = m_mat[i][k];

				for (int j = 0; j < N; j++)
				{
					m_mat[i][j] -= m_mat[k][j] * temp;
					E.m_mat[i][j] -= E.m_mat[k][j] * temp;
				}
			}
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				m_mat[i][j] = E.m_mat[i][j];

		
	}
	Matrix Minor( int a1, int a2)
	{
		Matrix E(m_n - 1, m_m - 1);
		if (m_m != m_n)
		{
			std::cout << "Я ещё не умею выводить не квадратные миноры" << std::endl;
			return E;
		}
		else
		{
			int i1 = 0, j1 = 0;
			for (int i = 0;i < m_n;i++)
			{
				for (int j = 0;j < m_m;j++)
				{
					if (i != a1)
					{
						if (j != a2)
						{
							E.m_mat[i1][j1] = m_mat[i][j];
							j1++;
							if (j1 % (m_m - 1) == 0)
							{
								i1++;
								j1 = 0;
								if (i1 >= m_m - 1)
								{
									i1 = m_m - 2;
								}
							}
							
						}
						
					}
				}
			}
			return E;
		}
	}
	// Обратная матрица
	Matrix RMatrix()
	{
		Matrix R(m_n, m_m);
		if (m_m != m_n)
		{
				std::cout << "«Операция не поддерживается»" << std::endl;
				return R;
		}
		else if (m_m > 3)
		{
			std::cout << "«Операция не поддерживается»" << std::endl;
			return R;
		}

		Matrix M(m_n - 1, m_m - 1);
		Matrix C(m_n, m_m);
		for (int i = 0;i < m_n;i++)
		{
			for (int j = 0;j < m_m;j++)
			{
				C.m_mat[i][j] = m_mat[i][j];
			}
		}
		float d = C.Det();
		R = R.Tmatrix();
		std::cout << d << std::endl;
		int cof = 1;
		if (d != 0)
		{
			for (int i = 0;i < m_n;i++)
			{
				for (int j = 0;j < m_m;j++)
				{
					if (i + j % 2 != 0)
					{
						cof = (-1);
					}
					R.m_mat[i][j] = C.Minor(i, j).Det()*cof;
					//cof = cof * (-1);
					cof = 1;
				}
			}
			
			std::cout << R;
			for (int i = 0;i < m_n;i++)
			{
				for (int j = 0;j < m_m;j++)
				{
					R.m_mat[i][j] = R.m_mat[i][j] / d;
				}
			}
		}
		R = R.Tmatrix();
		return R;
	}
	// Использование внутри класса
private:
	int m_n, m_m;		// Поле
	float n;
	float** m_mat;
};

// Перегрузка оператора ввода
// 
std::istream& operator>>(std::istream& in, Matrix& mat)
{
	for (int i = 0; i < mat.m_n; i++)
		for (int j = 0; j < mat.m_m; j++)
			in >> mat.m_mat[i][j];
	return in;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& out, const Matrix& mat)
{
	out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
	for (int i = 0; i < mat.m_n; i++) {
		for (int j = 0; j < mat.m_m; j++)
			out << mat.m_mat[i][j] << " ";
		out << std::endl;
	}
	return out;
}

int main()
{
	Matrix A(2, 2);

	std::cin >> A;
	//std::cout << A.Det() << std::endl; 
	//std::cout << A.Tmatrix() << std::endl;
	//std::cout << A.Minor(1, 2);
	//std::cout << A.Minor(1, 2).Det();
	std::cout << A.RMatrix();
	//A.inversion();
	//std::cout << A  << std::endl;
	//Matrix B(3, 3);
	//std::cin >> B;
	//std::cout << B << std::endl;

	//Matrix C(2, 4);
	//C = A + B;

	//std::cout << C << std::endl;

	//C = A * B;
	//std::cout << A * B << std::endl;

	return 0;
}