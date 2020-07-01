def power(x, y, p):
    res = 1
    x = x % p
    while y > 0:
        if y & 1:
            res = (res * x) % p
        y = y >> 1
        x = (x * x) % p
    return res

def gcd_extend(a, b, x, y):
    if (a == 0):
        x[0] = 0
        y[0] = 1
        return b
    x_new = [0]
    y_new = [0]
    d = gcd_extend(b % a, a, x_new, y_new)
    x[0] = y_new[0] - (b // a) * x_new[0]
    y[0] = x_new[0]
    return d

def LDE(a, b, c):
    x = [-1]
    y = [-1]
    gcd = gcd_extend(a, b, x, y)
    if c % gcd != 0:
        return -1
    else:
        c //= gcd
        return - x[0] * c, - y[0] * c

def discrete_log(a, b, m):

    def create_s2():
        S2 = {}
        tmp = (b * a) % m
        for s in range(1, k + 1):
            S2[tmp] = s
            tmp = (tmp * a) % m
        return S2

    def find_x():
        mn = power(a, k, m)
        tmp = mn
        for r in range(1, k + 1):
            if tmp in S2:
                return (r * k - S2[tmp]) % m
            tmp = (tmp * mn) % m
        return -1

    k = int(m ** (1 / 2) + 1)
    S2 = create_s2()
    return find_x()

def get_generator(p):

    def get_prime_devisors(n):
        prime_devisors = []
        cur_div = 2
        while cur_div ** 2 <= n:
            if n % cur_div == 0:
                prime_devisors.append(cur_div)
                while n % cur_div == 0:
                    n //= cur_div
            cur_div += 1
        if n > 1:
            prime_devisors.append(n)
        return prime_devisors

    def check_gen(g, p):
        for i in prime_div_p_min_1:
            if power(g, (p - 1) // i, p) == 1:
                return False
        return True

    prime_div_p_min_1 = get_prime_devisors(p - 1)
    for g in range(2, p + 1):
        if check_gen(g, p):
            return g

def discr_sqrt(b, k, p):
    g = get_generator(p)
    s = discrete_log(g, b, p)
    if s == -1:
        return -1
    else:
        lde = LDE(k, p - 1, -s)
        if lde == -1:
            return -1
        else:
            return power(g, lde[0] % (p - 1), p)

t = int(input())
for _ in range(t):
    a, b, m = list(map(int, input().split()))
    print(discr_sqrt(a, b, m))
