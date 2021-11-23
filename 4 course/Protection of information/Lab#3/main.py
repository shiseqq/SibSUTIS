import math
import random
import sys
import typing
from hashlib import md5


def genP(a: int, b: int) -> int:
    while True:
        p = random.randint(a, b)
        if is_prime(p):
            return p


def genPQ(a: int, b: int) -> int:
    while True:
        q = genP(a // 2, (b - 1) // 2)
        if is_prime(q * 2 + 1):
            return q * 2 + 1


def is_prime(n, trials=8):
    if n != int(n):
        return False
    n = int(n)
    if n == 0 or n == 1 or n == 4 or n == 6 or n == 8 or n == 9:
        return False
    if n == 2 or n == 3 or n == 5 or n == 7:
        return True
    s = 0
    d = n - 1
    while d % 2 == 0:
        d >>= 1
        s += 1
    assert (2 ** s * d == n - 1)

    def trial_composite(a):
        if pow(a, d, n) == 1:
            return False
        for i in range(s):
            if pow(a, 2 ** i * d, n) == n - 1:
                return False
        return True

    for i in range(trials):
        a = random.randrange(2, n)
        if trial_composite(a):
            return False

    return True


def evklid(a: int, b: int) -> typing.Tuple[int, int, int]:
    u1, u2, u3 = a, 1, 0
    v1, v2, v3 = b, 0, 1
    while v1:
        q = u1 // v1
        t1, t2, t3 = u1 % v1, u2 - q * v2, u3 - q * v3
        u1, u2, u3 = v1, v2, v3
        v1, v2, v3 = t1, t2, t3
    return u1, u2, u3


def EG(filename):
    h = md5(open(filename, 'rb').read())
    h_int = int.from_bytes(h.digest(), byteorder=sys.byteorder)

    p = genPQ(1 << h.digest_size * 8 + 1, 1 << h.digest_size * 8 + 2)
    while True:
        g = random.randrange(2, p)
        if pow(g, (p - 1) // 2, p) != 1:
            break
    x = random.randrange(2, p - 1)
    y = pow(g, x, p)
    while True:
        k = random.randrange(2, p - 1)
        gcd, kk, _ = evklid(k, p - 1)
        if gcd == 1:
            break
    r = pow(g, k, p)
    u = (h_int - x * r) % (p - 1)
    s = kk * u % (p - 1)

    open('EG.txt', 'w').write(str(s))
    yr = pow(y, r, p) * pow(r, s, p) % p
    gh = pow(g, h_int, p)
    assert yr == gh


def RSA(filename):
    h = md5(open(filename, 'rb').read())
    h_int = int.from_bytes(h.digest(), byteorder=sys.byteorder)  # Хеш файла
    while True:
        p = genP(1 << h.digest_size * 8 // 2 + 1, 1 << h.digest_size * 8 // 2 + 2)
        q = genP(1 << h.digest_size * 8 // 2 + 1, 1 << h.digest_size * 8 // 2 + 2)
        if p != q:
            break
    n = p * q
    phi = (p - 1) * (q - 1)

    while True:
        c = random.randrange(2, phi)
        gcd, d, _ = evklid(c, phi)
        if gcd == 1:
            d = (d + phi) % phi
            break

    s = pow(h_int, c, n)
    open('RSA.txt', 'w').write(str(s))
    e = pow(s, d, n)
    assert e == h_int


def GOST(filename):
    q = genP(1 << 255, (1 << 256) - 1)

    while True:
        b = random.randint(math.ceil((1 << 1023) / q), ((1 << 1024) - 1) // q)
        if is_prime(p := b * q + 1):
            break

    while True:
        g = random.randrange(2, p - 1)
        if (a := pow(g, b, p)) > 1:
            break

    x = random.randrange(1, q)  # Закрытый ключ
    y = pow(a, x, p)  # Открытый ключ

    h = int.from_bytes(md5(open(filename, 'rb').read()).digest(), byteorder=sys.byteorder)
    assert 0 < h < q
    while True:
        k = random.randrange(1, q)
        if (r := pow(a, k, p) % q) == 0:
            continue
        if (s := (k * h % q + x * r % q) % q) != 0:
            break

    open('GOST.txt', 'w').write(f'{r = }\n{s = }')
    assert 0 < r < q
    assert 0 < s < q
    gcd, hh, _ = evklid(h, q)
    u1 = s * hh % q
    u2 = -r * hh % q
    v = pow(a, u1, p) * pow(y, u2, p) % p % q
    assert v == r


EG('1.png')
RSA('test.jpg')
GOST('test.jpg')
