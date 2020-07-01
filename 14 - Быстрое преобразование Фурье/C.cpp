#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>
#include <set>

using namespace std;

typedef long long ll;
typedef complex<double> cd;

const double PI = 3.1415926535897932384626433832795;
const int MAXN = 1 << 19;
int n;
string s, t;
vector<cd> a;
vector<cd> b;
int sum[MAXN];

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
	vector<cd> a_ans(MAXN), b_ans(MAXN), c(MAXN), c_ans(MAXN);
	fft(a, a_ans);
	fft(b, b_ans);

	for (int i = 0; i < MAXN; i++) {
		c[i] = a_ans[i] * b_ans[i];
	}

	inv_fft(c, c_ans);

	for (int i = 0; i < MAXN; i++) {
		sum[i] += (int) (c_ans[i].real() + 0.5);
	}
}

int main() {
	cin >> n >> s >> t;
	set<char> dct = {'A', 'C', 'G', 'T'};

	for (char c : dct) {
		a.clear();
		b.clear();
		a.resize(MAXN);
		b.resize(MAXN);

		for (int i = 0; i < s.size(); i++) {
			if (s[i] == c) {
				a[i] = cd(1);
				a[i + s.size()] = cd(1);
			}
		}

		for (int i = 0; i < t.size(); i++) {
			if (t[i] == c) {
				b[s.size() - 1 - i] = cd(1);
			}
		}

		solve();
	}

	int ans = 0;
	int pos = 0;

	for (int i = s.size() - 1; i + 1 < 2 * s.size(); i++) {
		if (sum[i] > ans) {
			ans = sum[i];
			pos = i - s.size() + 1;
		}
	}

	cout << ans << ' ' << pos;
	return 0;
}
