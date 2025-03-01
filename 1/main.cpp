#include <iostream>
#include <string>

const short N_max = 1000;

class BigInt
{
	char m_value[N_max];
	short m_size = 0;

	public:
		BigInt() = default;

		BigInt(const std::string& value)
		{
			short len = value.length();
			for(short i = 0; i < len; i++)
				m_value[i] = value[len - i - 1] - '0';
			for(short i = len; i < N_max; i++)
				m_value[i] = 0;
			m_size = len;
		}

		BigInt& operator+=(const BigInt& other)
		{
			if(other.m_size > m_size)
				m_size = other.m_size;

			for(short i = 0; i < m_size; i++)
			{
				m_value[i] += other.m_value[i];
				if(m_value[i] >= 10)
				{
					m_value[i] -= 10;
					m_value[i+1] += 1;
					if(i+1 == m_size)
						m_size++;
				} 
			}
			return *this;
		}

		BigInt& operator+=(int other)
		{
			*this += BigInt(std::to_string(other));
			return *this;
		}

		BigInt operator+(const BigInt& other)
		{
			BigInt result(*this);
			result += other;
			return result;
		}

		BigInt operator+(int other)
		{
			BigInt result(*this);
			result += other;
			return result;
		}

		BigInt& operator*=(const BigInt& other)
		{
			BigInt sum("0");
			if((*this == sum) || (sum == other))
			{
				sum.m_size = 1;
				*this = sum;
				return *this;
			}
			for(short i = 0; i < other.m_size; i++)
			{
				for(short j = 0; j < m_size; j++)
				{
					sum.m_value[i+j] += m_value[j] * other.m_value[i];
					if((i+j) >= sum.m_size)
						sum.m_size = i+j+1;
					if(sum.m_value[i+j] >= 10)
					{
						sum.m_value[i+j+1] += (sum.m_value[i+j] / 10);
						sum.m_value[i+j] %= 10;
						if(i+j+1 >= sum.m_size)
							sum.m_size = (i+j+2);
					}
				}
			}
			*this = sum;
			return *this;
		}

		BigInt& operator*=(int other)
		{
			*this *= BigInt(std::to_string(other));
			return *this;
		}

		BigInt operator*(const BigInt& other)
		{
			BigInt result(*this);
			result *= other;
			return result;
		}

		BigInt operator*(int other)
		{
			BigInt result(*this);
			result *= other;
			return result;
		}

		bool operator<(const BigInt& other)
		{
			if(m_size < other.m_size)
				return true;
			else if (m_size > other.m_size)
				return false;
			else
			{
				for(int i = m_size - 1; i >= 0; i--)
				{
					if(m_value[i] > other.m_value[i])
					{
						return false;
					}
					if(m_value[i] < other.m_value[i])
					{
						return true;
					}
				}
			}
			return false;
		}

		bool operator>(const BigInt& other)
		{
			if(m_size > other.m_size)
				return true;
			else if (m_size < other.m_size)
				return false;
			else
			{
				for(int i = m_size - 1; i >= 0; i--)
				{
					if(m_value[i] < other.m_value[i])
					{
						return false;
					}
					if(m_value[i] > other.m_value[i])
					{
						return true;
					}
				}
			}
			return false;
		}

		bool operator==(const BigInt& other)
		{
			if(!(*this > other) && !(*this < other))
				return true;
			return false;
		}

		bool operator!=(const BigInt& other)
		{
			if((*this > other) && (*this < other))
				return true;
			return false;
		}

		friend std::ostream& operator<<(std::ostream& out, const BigInt& other);
};

std::istream& operator>>(std::istream& in, BigInt& other)
{
	std::string a;
	in >> a;
	other = BigInt(a);
	return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& other)
{
	for(int i = other.m_size - 1; i >= 0; i--)
	{
		out << static_cast<short>(other.m_value[i]);
	}
	return out;
}

int main()
{	
	BigInt x("277");
	BigInt y("999");
	BigInt z;
	z = x * y;
	std::cout << z;
	return 0;
}