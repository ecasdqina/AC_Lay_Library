#include <stdlib.h>
#include <complex>
#include <math.h>
#include "../polynomial.hpp"

namespace fast_fourier_transform {
	using Real = double;
	using Complex = std::complex<Real>;
	using poly = polynomial<Complex>;
	
	const Real PI = M_PI;

	const poly DFT(poly f) {
		const int N = f.size();
		if(N == 1) return f;
		
		poly f0(N / 2);
		poly f1(N / 2);
		for(int i = 0; i < f0.size(); i++) f0[i] = f[i << 1];
		for(int i = 0; i < f1.size(); i++) f1[i] = f[i << 1 ^ 1];

		poly inv_f0 = DFT(f0);
		poly inv_f1 = DFT(f1);

		poly inv_f(N);
		for(int i = 0; i < f.size(); i++) {
			Complex zeta_n_i = Complex(cos(2. * PI * i / N), sin(2. * PI * i / N));

			inv_f[i] = inv_f0[i % f0.size()] + zeta_n_i * inv_f1[i % f1.size()];
		}
		return inv_f;
	}

	const poly IDFT(poly inv_f) {
		const int N = inv_f.size();

		poly arranged = DFT(inv_f);

		poly f(N);
		for(int i = 0; i < N; i++) f[i] = arranged[(N - i) % N] / Complex(N, 0);
		return f;
	}

	const poly convolution(poly a, poly b) {
		const int sz = a.size() + b.size() - 1;

		int N = 1;
		while(N < sz) N <<= 1;
		a.resize(N);
		b.resize(N);

		poly inv_a = DFT(a);
		poly inv_b = DFT(b);
		poly inv_c(N);
		for(int i = 0; i < N; i++) inv_c[i] = inv_a[i] * inv_b[i];
		return IDFT(inv_c);
	}
};

// verify
// + https://atcoder.jp/contests/atc001/submissions/7423586
