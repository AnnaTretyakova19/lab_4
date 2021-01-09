#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>


using namespace std;

class mulmatrix;

class normal {



private:
	friend mulmatrix;
	typedef unsigned int data_t;

	static const int SIZE = 32;
	data_t* intlong;


	

	int highbit() const {
		int i = 0;
		for (i = SIZE * 32 - 1; i != 0 && this->getbit(i) == 0; i--);
		return i;
	}

	void setbit(int n, bool val) {
		if (val) {
			intlong[n / 32] |= (1 << (n % 32));
		}
		else {
			intlong[n / 32] &= ~(1 << (n % 32));
		}
	}

	void duplicate(bool toleft) {
		for (int i = 0; i < SIZE / 2; ++i) {
			intlong[i + (toleft * (SIZE / 2))] = intlong[i + (!toleft * (SIZE / 2))];
		}
	}

	void cut(bool left) {
		for (int i = 0; i < SIZE / 2; ++i) {
			intlong[left * (SIZE / 2) + i] = 0;
		}
	}



public:


	bool getbit(int n) const {
		return intlong[n / 32] & (1 << (n % 32));
	}
	normal() {
		intlong = new data_t[SIZE];
		for (int i = 0; i < SIZE; i++) {
			intlong[i] = 0;
		}
	}

	normal(string _str) : normal()
	{
		for (int i = 0; i < _str.size(); i++) {
			setbit(i, _str[_str.size() - i - 1] - '0');
		}
	}


	normal(const normal& _normal) {
		intlong = new data_t[SIZE];
		for (int i = 0; i < SIZE; ++i) {
			intlong[i] = _normal.intlong[i];
		}
	}

	~normal() {
		delete[] intlong;
	}

	void closeshift(int _shift, bool dir) {
		if (_shift == 0) {
			return;
		}
		duplicate(1);
		if (dir) {

			for (int i = SIZE / 2 - 1; i > 0; i--) {
				intlong[i] = ((intlong[i] << 21) + (intlong[i - 1] >> 11));
			}
			intlong[0] = intlong[0] << 21;
			int delta1 = _shift / 32;
			int delta2 = _shift % 32;
			for (int i = SIZE - 1; i > delta1; i--) {
				intlong[i] = (intlong[i - delta1] << delta2) +
					((32 - delta2) < 32 ? intlong[i - delta1 - 1] >> (32 - delta2) : 0);
			}
			intlong[delta1] = intlong[0] << delta2;
			duplicate(0);
			cut(1);
		}

		else {
			for (int i = SIZE / 2 - 1; i > 0; i--) {
				intlong[i] = ((intlong[i] << 21) + (intlong[i - 1] >> 11));
			}
			intlong[0] = intlong[0] << 21;
			_shift += 21;
			int delta1 = _shift / 32;
			int delta2 = _shift % 32;
			for (int i = 0; i < SIZE - 1 - delta1; i++) {
				intlong[i] = (intlong[i + delta1] >> delta2) +
					((32 - delta2) < 32 ? intlong[i + delta1 + 1] << (32 - delta2) : 0);
			}
			intlong[SIZE - 1 - delta1] = intlong[SIZE - 1] >> delta2;
			for (int i = SIZE - delta1; i <= SIZE - 1; i++) {
				intlong[i] = 0;
			}
			cut(1);
		}
		intlong[SIZE / 2 - 1] &= (1 << 11) - 1;
	}
	normal& operator = (const normal& _normal) {
		for (int i = 0; i < SIZE; ++i) {
			intlong[i] = _normal.intlong[i];
		}
		return *this;
	}

	normal operator + (const normal& b) const {
		normal res;
		for (int i = 0; i < SIZE; i++) {
			res.intlong[i] = intlong[i] ^ b.intlong[i];
		}
		return res;
	}

	normal operator * (const normal& b) const {
		normal res;
		for (int i = 0; i < SIZE; i++) {
			res.intlong[i] = intlong[i] & b.intlong[i];
		}
		return res;
	}

	operator string() const {
		string snum;
		for (int i = SIZE / 2 - 1; i >= 0; --i) {
			for (int j = 31; j >= 0; --j) {
				snum += "01"[(intlong[i] >> j) & 1];
			}
		}
		return snum;
	}

	bool tr() const {
		bool tr = 0;
		for (int i = 0; i < SIZE * 32; i++) {
			tr ^= getbit(i);
		}
		return tr;
	}

	/*normal operator * (const normal& b) const {
		normal res;
		for(int k = 0, k < m, )
		res.setbit[k] = +intlong[i] * mulmatrix[i][j] * b.intlong[j];


	}*/


	void print() const
	{
		cout << string(*this) << "\n\n";
	}

};

class mulmatrix {

private:

	normal mulm[491];

	mulmatrix() {
		normal one("1");
		long long s1 = 1;
		long long s2 = 1;
		int k = 0;
		for (int i = 0; i < 491; i++) {
			s2 = 1;
			for (int j = 0; j < 491; j++) {
				int x = 491 - i - 1, y = 491 - j - 1;
				if (((s1 + s2 + 983) % 983 == 1) | ((s1 - s2 + 983) % 983 == 1) | ((s2 - s1 + 983) % 983 == 1) | (((-s2 - s1 + 983) % 983) == 1)) {
					mulm[i].setbit(y, 1);
					++k;
				}
				s2 *= 2;
				s2 %= 983;
			}
			s1 *= 2;
			s1 %= 983;
		}
		cout << mulm[490].getbit(0) << "\n";
		cout << mulm[490].getbit(490) << "\n";
		cout << mulm[0].getbit(490) << "\n";
		cout << mulm[0].getbit(0) << "\n";
	}


public:

	static mulmatrix muler;

	normal MULPTIPLY_MOTHERFUCKERS(const normal a, const normal b) {
		normal m1(a);
		normal m2(b);
		normal res;
		normal t;
		bool flag = 0;
		for (int i = 0; i < 491; i++) {
			normal tmp;
			for (int j = 0; j < 491; ++j) {
				tmp.setbit(491 - j - 1, (mulm[j] * m1).tr());
			}
			res.setbit(491 - i - 1, (tmp * m2).tr());
			m1.closeshift(1, 1);
			m2.closeshift(1, 1);
		}
		return res;
	}

};

mulmatrix mulmatrix::muler = mulmatrix();
