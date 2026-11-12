from math import comb

N = 10
counts = [0] * (N + 1)
dyck = [0] * (N + 1)

def cover(B):
    return {0, *B} | {x+y for x in B for y in B}

def search(B):
    n = len(B)
    counts[n] += 1
    dyck[n] += all(b <= 2*i-1 for i,b in enumerate(B,1))

    S = cover(B)
    assert all(x in S for x in range(1, 2*n+1)), B

    if n == N:
        return

    gap = next(x for x in range(1, max(S)+2) if x not in S)

    for b in range(B[-1]+1, gap+1):
        search(B+(b,))

search((1,))

print('n: a(n) / Catalan subfamily / C_n')
for n in range(1, N+1):
    C = comb(2*n,n)//(n+1)
    print(f'{n}: {counts[n]} / {dyck[n]} / {C}')
    assert counts[n] >= dyck[n] == C

assert counts[1:] == [
    1,2,5,17,65,292,1434,7875,47098,305226
]
print('PASS')
