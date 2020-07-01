#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <complex>

using namespace std;

typedef long long ll;

int n;
string s, t;

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

int neg = 0;

void prepare(string &a) {
	if (a[0] == '-') {
		neg ^= 1;
		a.erase(a.begin());
	}

	reverse(a.begin(), a.end());

	while (a.size() < MAXN) {
		a.push_back('0');
	}
}

void solve() {
	prepare(s);
	prepare(t);
	vector<complex<double>> a(MAXN), b(MAXN), a_ans(MAXN), b_ans(MAXN);

	for (int i = 0; i < MAXN; i++) {
		a[i] = complex<double>(s[i] - '0');
	}

	for (int i = 0; i < MAXN; i++) {
		b[i] = complex<double>(t[i] - '0');
	}

	fft(a, a_ans);
	fft(b, b_ans);
	vector<complex<double>> c(MAXN);

	for (int i = 0; i < MAXN; i++) {
		c[i] = a_ans[i] * b_ans[i];
		a[i] = 0;
	}

	inv_fft(c, a);
	int carry = 0;
	string ans;

	for (int i = 0; i < MAXN; i++) {
		int cur = (int) (a[i].real() + 0.5) + carry;
		ans.push_back('0' + cur % 10);
		carry = cur / 10;
	}

	while (ans.size() > 1 && ans.back() == '0') {
		ans.pop_back();
	}

	reverse(ans.begin(), ans.end());

	if (neg && ans != "0") {
		cout << '-';
	}

	cout << ans << '\n';
}

int main() {
	cin >> s >> t;
	solve();
	return 0;
}
