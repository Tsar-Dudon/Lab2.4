#include <iostream>
#include <string>

const short N_max = 1000;

class BigInt
{
	char m_value[N_max];
	short m_size = 0;
	bool m_negative = false;

	public:
		BigInt() = default;

		BigInt(const std::string& value)
		{
			short len = value.length();
			if(value[0] == '-')
			{
				m_negative = true;
				for(short i = 1; i < len; i++)
					m_value[i-1] = value[len - i] - '0';
				m_size = len - 1;
			}
			else
			{
				for(short i = 0; i < len; i++)
					m_value[i] = value[len - i - 1] - '0';
				m_size = len;
			}
			for(short i = m_size; i < N_max; i++)
				m_value[i] = 0;
		}

		void aboba(const BigInt& other)
		{
			if(*this < abs(other))
			{
				BigInt tmp = *this;
				for(short i = 0; i < other.m_size; i++)
					m_value[i] = other.m_value[i];
				for(short i = other.m_size; i < N_max; i++)
					m_value[i] = 0;
				m_size = other.m_size;
				for(short i = 0; i < m_size; i++)
				{
					//std::cerr<< static_cast<short>(m_value[i]) << '*'<< static_cast<short>(other.m_value[i]) << std::endl;
					m_value[i] -= tmp.m_value[i];
					//std::cerr<< static_cast<short>(m_value[i]) << std::endl;
					if(m_value[i] < 0)
					{
						m_value[i] += 10;
						m_value[i+1] -= 1;
					}
				}
				for(short i = m_size-1; i >= 0; i--)
				{	
					if(m_value[i] == 0)
						m_size--;
					else
						break;
				}
				m_negative = true;


			}	
			else if(*this == abs(other))
			{
				*this = BigInt("0");
			}
			else
			{
				for(short i = 0; i < m_size; i++)
				{
					//std::cerr<< static_cast<short>(m_value[i]) << '*'<< static_cast<short>(other.m_value[i]) << std::endl;
					m_value[i] -= other.m_value[i];
					//std::cerr<< static_cast<short>(m_value[i]) << std::endl;
					if(m_value[i] < 0)
					{
						m_value[i] += 10;
						m_value[i+1] -= 1;
					}
				}
				for(short i = m_size-1; i >= 0; i--)
				{	
					if(m_value[i] == 0)
						m_size--;
					else
						break;
				}
			}
		}

		BigInt& operator+=(const BigInt& other)
		{
			if(!m_negative && other.m_negative)
			{
				aboba(other);
				return *this;
			}
			else if(m_negative && !other.m_negative)
			{
				m_negative = false;
				BigInt tmp1("0");
				for(short i = 0; i < other.m_size; i++)
					tmp1.m_value[i] = other.m_value[i];
				tmp1.m_size = other.m_size;
				tmp1.m_negative = true;
				aboba(tmp1);
				if(abs(*this) > other)
					m_negative = true;
				else if(abs(*this) < other)
					m_negative = false;
				return *this;
			}
			else
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
			if(m_negative ^ other.m_negative)
				sum.m_negative = true;
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
			if(!m_negative && !other.m_negative)
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
			else if(m_negative && !other.m_negative)
				return true;
			else if(!m_negative && other.m_negative)
				return false;
			else
			{
				if(m_size < other.m_size)
					return false;
				else if (m_size > other.m_size)
					return true;
				else
				{
					for(int i = m_size - 1; i >= 0; i--)
					{
						if(m_value[i] > other.m_value[i])
						{
							return true;
						}
						if(m_value[i] < other.m_value[i])
						{
							return false;
						}
					}
				}
				return false;
			}
		}

		bool operator>(const BigInt& other)
		{
			if(!m_negative && !other.m_negative)
			{
				if(m_size < other.m_size)
					return false;
				else if (m_size > other.m_size)
					return true;
				else
				{
					for(int i = m_size - 1; i >= 0; i--)
					{
						if(m_value[i] > other.m_value[i])
						{
							return true;
						}
						if(m_value[i] < other.m_value[i])
						{
							return false;
						}
					}
				}
				return false;
			}
			else if(m_negative && !other.m_negative)
				return false;
			else if(!m_negative && other.m_negative)
				return true;
			else
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
		}

		bool operator==(const BigInt& other)
		{
			if(!(*this > other) && !(*this < other))
				return true;
			return false;
		}

		bool operator!=(const BigInt& other)
		{
			if((*this > other) || (*this < other))
				return true;
			return false;
		}

		friend std::ostream& operator<<(std::ostream& out, const BigInt& other);
		friend BigInt abs(const BigInt& other);
};

BigInt abs(const BigInt& other)
{
	BigInt result;
	result = other;
	result.m_negative = false;
	return result;
}

std::istream& operator>>(std::istream& in, BigInt& other)
{
	std::string a;
	in >> a;
	other = BigInt(a);
	return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& other)
{
	if(other.m_negative)
		out << '-';
	for(int i = other.m_size-1; i >= 0; i--)
	{
		out << static_cast<short>(other.m_value[i]);
	}
	return out;
}

int main()
{	
	BigInt x("-2");
	BigInt y("87709");
	x *= y;
	std::cout << x << std::endl;
	return 0;
}