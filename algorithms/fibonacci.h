//
//  Created by longjianjiang on 2019/08/16.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef fibonacci_h
#define fibonacci_h

#include <iostream>

namespace jiang {

	// helper class & method
	class two_dimension_matrix {
	public:
		long arr[2][2];
		two_dimension_matrix(long a, long b, long c, long d) {
			this->arr[0][0] = a;
			this->arr[0][1] = b;
			this->arr[1][0] = c;
			this->arr[1][1] = d;
		}

		friend two_dimension_matrix operator*(const two_dimension_matrix& lhs, const two_dimension_matrix& rhs) {
			two_dimension_matrix res(0, 0, 0, 0);

			res.arr[0][0] = lhs.arr[0][0]*rhs.arr[0][0] + lhs.arr[0][1]*rhs.arr[1][0];
			res.arr[0][1] = lhs.arr[0][0]*rhs.arr[0][1] + lhs.arr[0][1]*rhs.arr[1][1];
			res.arr[1][0] = lhs.arr[1][0]*rhs.arr[0][0] + lhs.arr[1][1]*rhs.arr[1][0];
			res.arr[1][1] = lhs.arr[1][0]*rhs.arr[0][1] + lhs.arr[1][1]*rhs.arr[1][1];

			return res;
		}
	};

	two_dimension_matrix matrix_power(const two_dimension_matrix& matrix, int n) {
		assert(n >= 1);
		if (n == 1) { return matrix; }

		if (n % 2 == 0) {
			return matrix_power(matrix*matrix, n/2);
		} else {
			return matrix_power(matrix*matrix, n/2) * matrix;
		}
	}
	

	// method
	long fibonacci(int n) {
		if (n < 0) { return -1; }
		if (n <= 2) { return n; }
		return fibonacci(n-1) + fibonacci(n-2);
	}

	long fibonacci_dp(int n) {
		if (n < 0) { return -1; }
		int dp[n+1];
		for (int i = 0; i <= 2; ++i) {
			dp[i] = i;
		}
		for (int i = 3; i <= n; ++i) {
			dp[i] = dp[i-1] + dp[i-2];
		}
		return dp[n];
	}

	long fibonacci_dp_space_o1(int n) {
		if (n < 0) { return -1; }
		long prev = 0, curr = 1, next = 2;
		
		for (int i = 3; i <= n; ++i) {
			prev = curr;
			curr = next;
			next = prev + curr;
		}
		return next;
	}

	/*
	 * f(n)      | 1  1 |   | f(n-1)  |
	 *        =  |      | * |         |
	 * f(n-1)    | 1  0 |   | f(n-2)  |
	 *
	 * ----------------------------------
	 *  
	 * f(n)      | 1  1 |(n-2)   | f(2)  |
	 *        =  |      |      * |       |
	 * f(n-1)    | 1  0 |        | f(1)  |
	 *
	 */
	long fibonacci_logn(int n) {
		if (n < 0) { return -1; }
		if (n <= 2) { return n; }

		two_dimension_matrix m1(1, 1, 1, 0), m2(2, 0, 1, 0);
		m1 = matrix_power(m1, n-2);

		two_dimension_matrix res = m1 * m2;

		return res.arr[0][0];
	}
}
#endif /* fibonacci_h */

