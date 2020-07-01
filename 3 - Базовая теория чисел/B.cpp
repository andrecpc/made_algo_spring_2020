#include <iostream>
#include <vector>

using namespace std;

int pow (int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1) {
            res *= a;
        }
        a *= a;
        n >>= 1;
    }
    return res;
}

const int N = 100000000;
int d[N];
vector<int> primes;

int main() {

    for (int i = 2; i < N; i++) {
        if (!d[i]) {
            d[i] = i;
            primes.push_back(i);
        }

        for (auto p : primes) {
            if (p > d[i] || i * p >= N) {
                break;
            }
            d[i * p] = p;
        }
    }

    d[1] = 1;
    int n = 0;

    cin >> n;

    long long sum_d = 0;
    long long sum_phi = 1;
    long long sum_s0 = 1;
    long long sum_s1 = 1;

    for (int i = 2; i <= n; i++) {
        int k = i;
        int prev = d[k];
        int prev_count = 0;
        long long euler = 1;
        long long s0 = 1;
        long long s1 = 1;
        while (true) {
            if (d[k] == prev) {
                prev_count += 1;
            }

            if (d[k] != prev) {
                euler *= (pow(prev, prev_count) - pow(prev, prev_count - 1));
                s0 *= prev_count + 1;
                long long sigma = 0;
                long long tmp = 1;
                for (int j = 0; j <= prev_count; j++) {
                    sigma += tmp;
                    tmp *= prev;
                }
                s1 *= sigma;
                prev_count = 1;
                prev = d[k];
            }

            if (k == 1) {
                break;
            }

            k /= d[k];
        }

        sum_phi += euler;
        sum_s0 += s0;
        sum_s1 += s1;
        sum_d += d[i];
    }

    cout << sum_d << " " << sum_s0 << " " << sum_s1 << " " << sum_phi;

    return 0;
}
