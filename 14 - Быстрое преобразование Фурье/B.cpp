#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>

using namespace std;

typedef long long ll;
typedef complex<double> cd;

int n;
string s;
const double PI = 3.1415926535897932384626433832795;
const int MAXN = 1 << 19;

void fft(vector<complex<double>> &a, vector<complex<double>> &ans, int n,
        complex<double> z, int abg, int ast, int ansbg) {

	if (n == 1) {
		ans[ansbg] = a[abg];
		return;
	}

	fft(a, ans, n >> 1, z * z, abg, ast * 2, ansbg);
	fft(a, ans, n >> 1, z * z, abg + ast, ast * 2, ansbg + n / 2);
	complex<double> x = 1;

	for (int i = 0; i < (n >> 1); i++) {
		complex<double> ans1 = ans[ansbg + i];
		complex<double> ans2 = ans[ansbg + i + n / 2];
		ans[ansbg + i] = ans1 + x * ans2;
		ans[ansbg + i + n / 2] = ans1 - x * ans2;
		x *= z;
	}
}

void fft(vector<complex<double>> &a, vector<complex<double>> &ans) {
	fft(a, ans, MAXN, complex<double>(cos(2 * PI / MAXN), sin(2 * PI / MAXN)), 0, 1, 0);
}

void inv_fft(vector<complex<double>> &a, vector<complex<double>> &ans) {
	fft(a, ans, MAXN, complex<double>(cos(-2 * PI / MAXN), sin(-2 * PI / MAXN)), 0, 1, 0);
	for (int i = 0; i < MAXN; i++) {
		ans[i] /= MAXN;
	}
}

void solve() {
    n = s.size();
	vector<cd> q(MAXN);

	for (int i = 0; i < n; i++) {
		q[i] = cd(s[i] - '0');
	}

	vector<cd> a(MAXN);
	fft(q, a);
	vector<cd> b(MAXN);

	for (int i = 0; i < MAXN; i++) {
		b[i] = a[i] * a[i];
	}

	vector<cd> c(MAXN);
	inv_fft(b, c);
	ll ans = 0;

	for (int i = 0; i < MAXN; i += 2) {
		if (q[i / 2] == cd(0)) {
			continue;
		}

		ll cur = (int) (c[i].real() + 0.5);
		ans += (cur - 1) / 2;
	}

	cout << ans << '\n';
}

int main() {
	cin >> s;
	solve();
	return 0;
}
