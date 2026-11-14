# Independent verification — 2026-11-15

Source audited: supplied archive of `iwasborninbali/oeis-A167809-unsubmitted` at `4447c85`. I read `README.md`, `CERTIFICATE.md`, `PRIOR-ART.md`, `proof.md`, `programs/producer.py`, `verification/check.py`, and both existing verification logs. No existing files were changed.

## Claim

**Exact CERTIFICATE.md claim:** For every integer `n >= 1`, the number `a(n)` of admissible two-stamp `n`-denomination bases is at least the Catalan number `C_n = binom(2n,n)/(n+1)`.

An admissible basis has `1=b_1<...<b_n` and every `1 <= x <= b_n` is representable by one or two denominations, permitting repetition. The certificate explicitly does *not* claim formal machine verification of the universal proof; its independent checker previously covered the injection only through `n=10`, not the total basis counts.

## Proof check

Referee audit of **every substantive line** of `proof.md`:

| Line | Referee finding | Status / remedy |
| --- | --- | --- |
| 1–2 | Heading only. | No issue. |
| 3 | Agrees with the OEIS definition and correctly permits repeated denominations. | Correct. |
| 5 | The complement-pair pigeonhole lemma is correct. Assuming no pair sums to `x`, `S` contains at most one element from each complementary pair; for even `x`, the midpoint cannot be selected because doubling is allowed. Thus `|S| <= floor((x-1)/2) < k` when `x <= 2k`. | Correct. The proof's tacit contradiction assumption is clear from “Otherwise”, not a mathematical gap. |
| 7 | For the first `j` with `x<=b_j`, strict increase gives `x>b_{j-1}` if `j>1`; hence all `j-1` previous denominations are below `x`, and `x<=b_j-1<=2(j-1)`. The lemma applies; `j=1` is explicitly handled. | Correct; no missing hypothesis. |
| 9 | Prior to up-step `i`, the Dyck prefix has `i-1` up-steps and `b_i-i` down-steps, whence `b_i<=2i-1`. The step positions uniquely determine the word, so the map is injective. | Correct; no conjecture. |
| 11 | **Wrong direction in reflection argument.** Flipping the prefix up to and including the first step below zero transforms a bad balanced word into one with **`n+1` UP-steps and `n-1` DOWN-steps**, not the stated `n+1` down-steps and `n-1` up-steps. Example `DU -> UU` at `n=1`. | **Fixable, nonfatal:** interchange “down” and “up” in the target description. Both target orientation classes have cardinality `binom(2n,n-1)`, so the numeric result and bound remain valid. |

**Proof verdict: correct with fixable gaps** (one nonfatal reflection-orientation error; no fatal gaps, unproved conjectures, or necessary unstated assumptions). The result is mathematically valid for every `n>=1` regardless of finite computation.

## Independent computation

New, original `independent.cpp` in this directory, not imported from or copied from the repository's programs. Compiled with `g++ -O3 -std=c++17` (uses GCC/Clang `unsigned __int128`). Its first algorithm exhaustively enumerates admissible bases by maintaining a denomination bit mask and an *incrementally shifted 128-bit single/double-sum mask*; it counts all admissible bases, not merely the injective family. Completeness follows because a new last denomination must lie between the old last denomination plus one and the first still-uncovered positive integer. The implementation also counts the subfamily satisfying `b_i<=2i-1`.

A **separate** second algorithm generates strictly increasing rising-step positions subject to `b_i<=2i-1`, recomputes their sums directly by nested arithmetic loops at each node, explicitly tests coverage through the maximum, and compares the count against an independently evaluated Catalan recurrence. Each strictly increasing position sequence is generated exactly once.

Coverage: **complete enumeration `n=1..15`**, versus repository producer `n=1..10`; **independent exhaustive image checks `n=1..18`**, versus repository independent checker `n=1..10`. Every comparison passed. Representative results (complete tables, including maximum denominators, are in `independent.log`):

| n | All admissible `a(n)` | Catalan subfamily `C_n` | Independently tested images |
| ---: | ---: | ---: | ---: |
| 10 | 305,226 | 16,796 | 16,796 |
| 11 | 2,122,983 | 58,786 | 58,786 |
| 12 | 15,752,080 | 208,012 | 208,012 |
| 13 | 124,015,310 | 742,900 | 742,900 |
| 14 | 1,031,857,395 | 2,674,440 | 2,674,440 |
| 15 | 9,041,908,204 | 9,694,845 | 9,694,845 |
| 16 | — | — | 35,357,670 |
| 17 | — | — | 129,644,790 |
| 18 | — | — | 477,638,700 |

Actual run: **62.715 s CPU** for full enumeration, **109.940 s CPU** for the explicit-image test, **172.656 s CPU total** (172.721 s wall), `PASS`. These timings are machine-dependent; the output log records this actual run.

SHA-256 of `independent.cpp`:
`a51a1213439ec319056f6b848ece8b1a8ecae54a0a3881d5ddb0597a8565dac8`

SHA-256 of `independent.log`:
`c24668f7a050475c3a719c60eb89981c2f13760f541b16ca92ceb29f03acf362`

Reproduce: `g++ -O3 -std=c++17 independent.cpp -o independent && ./independent > independent.log`. Re-running yields the same mathematical counts and `PASS`; elapsed-time fields, and therefore the output-file hash, vary by run.

## Prior art

**Decisive positive finding: Mauro Torelli (2006).** [*Increasing integer sequences and Goldbach's conjecture*, RAIRO/Theoretical Informatics and Applications **40** (2006), 107–121](https://archive.numdam.org/articles/10.1051/ita%3A2006017/), [full text PDF](https://www.numdam.org/item/ITA_2006__40_2_107_0.pdf), DOI [10.1051/ita:2006017](https://doi.org/10.1051/ita:2006017). Page 108 defines his Goldbach sequences by two-summand coverage using preceding elements. Page 113, Definition 10 and the preceding argument, show that his *binomial sequences* `a_0=1<a_1<...<a_r`, `a_i<=2i` for `i>=1`, are Goldbach sequences. Page 116 says their number for each length `r` is the Catalan number `C_r`; page 118, Table 3, lists matching counts. **This is an explicit 2006 antecedent from which the exact claimed bound follows immediately**, not just literature about a tangential postage-stamp problem.

**Indexing/translation (important).** Torelli's sequence has `r+1` elements; the repository has `n` elements. Set `r=n` and map each Torelli binomial sequence to `B=(a_1-1,...,a_n-1)`. Then `b_1=1` and `b_i<=2i-1`, exactly the repository's Catalan family, and the map is injective. For any `1<=x<b_n`, put `y=x+2<=a_n`; Torelli's Goldbach property represents `y=a_j+a_k` with `j,k<n`. If neither index is 0, then `x=b_j+b_k`; if one index is 0, then `x=b_k` (one stamp). Finally `x=b_n` is a denomination. Thus every image is admissible under A167809's definition. Torelli did not phrase the statement as `A167809(n)>=C_n`, but the claimed mathematical result is an elementary corollary of his published results. Attribution/novelty must reflect this.

**OEIS:** [A167809](https://oeis.org/A167809) still labels `a(n)>=A000108(n)` as Michael Chu's conjecture dated 2022-05-16, gives the same definition, and lists the exact enumeration through `n=19`. The related [A008932](https://oeis.org/A008932) has the same values for `n>=1` (and an additional convention `a(0)=1`); it links to Torelli's 1996 preprint and 2006 journal paper. [A000108](https://oeis.org/A000108) is Catalan; [A167810](https://oeis.org/A167810) through [A167814](https://oeis.org/A167814) change the stamp count parameter `h`, while [A123509](https://oeis.org/A123509) concerns largest allowable elements. The [OEIS change-history endpoint](https://oeis.org/history?seq=A167809) could not be retrieved by the research interface (`DisabledError`), so historical edit-by-edit review is **not established**. The accessible OEIS entry and indexed internal-format snapshots retain the 2022 conjecture; that does not show the history contains a proof.

**arXiv and journals:** Checked abstracts/available descriptions for Jukka Kohonen, [arXiv:1403.5945](https://arxiv.org/abs/1403.5945), *Journal of Integer Sequences* 17 (2014), 14.6.8, and [arXiv:1503.03416](https://arxiv.org/abs/1503.03416), which concern algorithms for extremal restricted additive 2-bases. The [2026 paper arXiv:2610.19470](https://arxiv.org/abs/2610.19470) treats positive versus negative `h`-bases, a different problem. A167809 also cites Lunnon (1969), Alter–Barnett (1980), Mossige (1981), and Challis (1993); no matching explicit Catalan injection was identified in the accessible metadata/entry references. **Do not mistake failure to find one there for proof of its absence.** The strong prior-art result is Torelli (2006).

**MathOverflow, Math StackExchange, zbMATH:** Searched indexed pages using `A167809`, `A008932`, `Catalan postage stamp admissible bases`, `Goldbach binomial sequences`, and Torelli's title; no directly matching independent proof/refutation surfaced in MathOverflow or Math StackExchange. An [MSE 2025 thread](https://math.stackexchange.com/questions/5086773/counting-the-number-of-sets-of-natural-numbers-generated-from-two-coprime-number) mentions Catalan numbers for a different numerical-semigroup/ideal counting problem, not A167809. Targeted web searches of `zbmath.org` did not return a usable bibliographic record for this exact result; zbMATH coverage is therefore **unverified**, not certified absent.

## Verdict

**COMPLETE mathematical verification; NOT NEW as a mathematical result.** The all-`n` claim is proved with one fixable wording error; independent enumerations and explicit coverage tests passed over substantially larger ranges than the repository's check. **Novelty is refuted by Torelli (2006)**: the exact Catalan lower bound is a short, explicit corollary of that paper's Goldbach/binomial-sequence theorem and enumeration, although not stated there with OEIS A167809's notation. This warrants correcting the novelty/priority narrative before submission. No formal proof-assistant certification was performed or claimed. The OEIS history and a comprehensive zbMATH search remain inaccessible/unverified, but neither limitation affects the earlier published corollary.
