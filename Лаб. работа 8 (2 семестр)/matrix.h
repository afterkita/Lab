#pragma once
#include <iostream>

namespace mt
{
	// MY_DEBUG определена
	//#define MY_DEBUG 

	template<typename T, int N, int M>
	struct MasWrapper
	{
		T mas[N][M];
	};

	template<typename T, int N, int M>
	class Matrix
	{
	public:
		// Конструктор
		Matrix()
		{
#ifdef MY_DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = 0;
		}

		// Конструктор
		Matrix(const T mas[N][M])
		{
#ifdef MY_DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas[i][j];
		}

		// Конструктор
		Matrix(const MasWrapper<T, N, M>& mas)
		{
#ifdef MY_DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas.mas[i][j];
		}

		// Конструктор копирования
		Matrix(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			std::cout << "Copy constructor" << std::endl;
#endif

			m_n = mat.m_n;
			m_m = mat.m_m;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.m_mat[i][j];
		}

		int getN() const { return m_n; }
		int getM() const { return m_m; }
		int get(int i, int j) const { return m_mat[i][j]; }
		void set(int i, int j, T data) { m_mat[i][j] = data; }

		// Присваивание
		template<typename T, int N, int M>
		Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			std::cout << "Operator =" << std::endl;
#endif

			m_n = mat.getN();
			m_m = mat.getM();

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.get(i, j);

			return *this;
		}

		// Оператор сложения
		template<typename T, int N, int M>
		Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			std::cout << "operator+" << std::endl;
#endif
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
			return tmp;
		}

		// Оператор умножения
		template<typename T, int N, int M>
		Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			std::cout << "operator*" << std::endl;
#endif
			Matrix<T, N, M> tmp;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < mat.getM(); j++)
				{
					int sum = 0;
					for (int k = 0; k < m_m; k++)
						sum += m_mat[i][k] * mat.get(k, j);
					tmp.set(i, j, sum);
				}

			return tmp;
		}

		// Деструктор
		~Matrix()
		{
#ifdef MY_DEBUG
			std::cout << "Destructor" << std::endl;
#endif
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
		
		Matrix<double,N,M> Tmatrix()
		{
			Matrix<T, N, M> tmp;
			if (m_n != m_m)
			{
				std::cout << "Ошибка!" << std::endl;
				return tmp;
			}
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
				{
						tmp.set(j, i, m_mat[i][j]);

				}

			return tmp;
		}
		// Нахождение минора
		Matrix<double, N-1, M-1> Minor(int a1, int a2)
		{
			Matrix<T, N-1, M-1> E;
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
								E.set(i1,j1, m_mat[i][j]);
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
		Matrix<double, N, M> RMatrix()
		{
			Matrix<T, N, M> R;
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

			Matrix<T, N, M> C;
			for (int i = 0;i < m_n;i++)
			{
				for (int j = 0;j < m_m;j++)
				{
					C.set(i, j, m_mat[i][j]);
				}
			}
			float d = C.Det();
			std::cout << d << std::endl;
			int cof = 1;
			if (d != 0)
			{
				for (int i = 0;i < m_n;i++)
				{
					for (int j = 0;j < m_m;j++)
					{
						if ((i + j) % 2 != 0)
						{
							cof = (-1);
						}
						R.set(j, i, C.Minor(i, j).Det() * cof);

						cof = 1;
					}
				}
				for (int i = 0;i < m_n;i++)
				{
					for (int j = 0;j < m_m;j++)
					{
						R.set(j, i, R.m_mat[i][j] / d) ;
					}
				}
			}
			else
			{
				std::cout << "Нет обратной матрицы\n";
				for (int i = 0;i < m_n;i++)
				{
					for (int j = 0;j < m_m;j++)
					{
						R.m_mat[i][j] = m_mat[i][j];
					}
				}
			}
			return R;
		}
		// friend - позволяет функции иметь доступ к private полям/методам класса
		template<typename T, int N, int M>
		friend std::istream& operator>>(std::istream& os, Matrix<T, N, M>& mat);


		template<typename T, int N, int M>
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& mat);

	private:
		int m_n, m_m;
		T m_mat[N][M];
	};

	// Перегрузка оператора ввода
	template<typename T, int N, int M>
	std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat)
	{
		for (int i = 0; i < mat.m_n; i++)
			for (int j = 0; j < mat.m_m; j++)
				in >> mat.m_mat[i][j];
		return in;
	}

	// Перегрузка оператора вывода
	template<typename T, int N, int M>
	std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat)
	{
		out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
		for (int i = 0; i < mat.m_n; i++) {
			for (int j = 0; j < mat.m_m; j++)
				out << mat.m_mat[i][j] << " ";
			out << std::endl;
		}
		return out;
	}

	using Vec2i = Matrix<int, 2, 1>;	// Сокращенное удобное название
	using Vec2d = Matrix<double, 2, 1>;
	using Mat22i = Matrix<int, 2, 2>;
	using Mat22d = Matrix<double, 2, 2>;
	using Mat33d = Matrix<double, 3, 3>;
}
