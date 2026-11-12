"""Dyck words checked against explicit stamp sums; OpenAI Codex, 2026-11-13."""
from math import comb

def words(n, up=0, down=0, positions=()):
    if up == down == n:
        yield positions
        return
    if up < n:
        yield from words(n, up+1, down, positions+(up+down+1,))
    if down < up:
        yield from words(n, up, down+1, positions)

for n in range(1, 11):
    images=set()
    for basis in words(n):
        assert basis not in images
        images.add(basis)
        sums=set(basis)
        for x in basis:
            for y in basis:
                sums.add(x+y)
        assert all(x in sums for x in range(1, basis[-1]+1))
    assert len(images) == comb(2*n,n)//(n+1)
    print(f'n={n}: {len(images)} distinct admissible images')
print('PASS')
