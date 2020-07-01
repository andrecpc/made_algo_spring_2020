#include <iostream>

using namespace std;

int n;
long long t[128][128][128];

long long get_sum(long long x, long long y, long long z) {

    if (x >= 0 && y >= 0 && z >= 0) {

        long long result = 0;
        for (long long i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for (long long j = y; j >= 0; j = (j & (j + 1)) - 1) {
                for(long long k = z; k >= 0; k = (k & (k + 1)) - 1)
                    result += t[i][j][k];
            }
        }
        return result;

    } else
        return 0;
}

void update(int x, int y, int z, int d) {

    for (int i = x; i < n; i = i | (i + 1)) {
        for (int j = y; j < n; j = j | (j + 1)) {
            for (int k = z; k < n; k = k | (k + 1)) {
                t[i][j][k] += d;
            }
        }
    }
}

int main() {

    cin >> n;
    int m = -1;

    while (m != 3) {

        cin >> m;

        if (m == 2) {

            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << get_sum(x2, y2, z2) - get_sum(x2, y1 - 1, z2)
                    - get_sum(x1 - 1, y2, z2) - get_sum(x2, y2, z1 - 1)
                    + get_sum(x2, y1 - 1, z1 - 1) + get_sum(x1 - 1, y2, z1 - 1)
                    + get_sum(x1 - 1, y1 - 1, z2) - get_sum(x1 - 1, y1 - 1, z1 - 1) << endl;
            continue;
        }

        if (m == 1) {

            int x, y, z, d;
            cin >> x >> y >> z >> d;
            update(x, y, z, d);
            continue;
        }

    }

    return 0;
}
