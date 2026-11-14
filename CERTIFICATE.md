# Verification certificate

## Claim

For every n>=1, the number of admissible two-stamp n-denomination bases is at least the n-th Catalan number.

## Evidence

| What | Program | Author and date | Coverage | Result |
|---|---|---|---|---|
| Human-checkable proof | `proof.md` | Adapted by OpenAI Codex from ChatGPT, 2026-11-12 | All n>=1 | Not machine-checked |
| Producer | `programs/producer.py` | ChatGPT, 2026-11-12 | Bases and Catalan subfamily through n=10 | Passed |
| Independent check | `verification/check.py` | OpenAI Codex, 2026-11-13 | Dyck images and admissibility through n=10 | Passed |
| Independent referee and check | `verification/agent-2026-11-15/` (REPORT.md, independent.cpp) | ChatGPT agent, 2026-11-15; own C++, no repository code | Exhaustive admissible-basis counts n = 1..15; image of the Dyck map checked n = 1..18; proof read line by line | Passed; one orientation slip in the reflection step (fixed in proof.md on 2026-11-15; the count is unchanged) |

The checker independently generates Dyck words and tests their sums; it shares no producer code or tables. Guide review is recorded in `athanor-oeis/tasks/README.md`.

## Replayed for this repository

2026-11-13, Darwin arm64, Python 3.14.6: `python3 programs/producer.py` reports 305226 bases and 16796 Catalan-family bases for n=10; `python3 verification/check.py` reports 16796 distinct admissible images for n=10. Both report `PASS`. Full logs are in `verification/logs/`.

2026-11-15, Darwin arm64 (Apple clang `-O3`), by the guide: `./independent` in `verification/agent-2026-11-15/`
finished in 181 s with `PASS`, the same counts as the agent's log.

## Not covered

No formal verification of the all-n proof. The independent program checks the injection through n=10, not the total count of all bases; the source's checks through n=12 and the separate lemma enumeration were not replayed.

## Guide's independent check

15 November 2026: the guide read `proof.md` line by line. Lemma: a set of k distinct numbers below x with x <= 2k meets
some complementary pair {t, x-t} or contains x/2, since otherwise its size is at most floor((x-1)/2) <= k-1. An
increasing basis with b_1 = 1 and b_i <= 2i-1 is admissible (take the least j with x <= b_j; the j-1 smaller elements
satisfy the lemma because x <= 2(j-1)). The up-step positions of a Dyck word satisfy b_i <= 2i-1 and determine the word,
so the map is injective, and Dyck words are counted by the Catalan numbers. The referee's orientation slip in the
reflection step was corrected on 15 November 2026 (the bad words go to words with n+1 up-steps; binomial(2n,n+1) =
binomial(2n,n-1), so the count is unchanged). Verdict: correct.

## Verdict

complete — the bound is proved (read independently by the guide and by a separate referee) and the computations are
reproduced by programs that share no code. Not covered: no formal proof. Priority: the referee reports that the bound
follows from Torelli (2006) by an elementary transformation; the guide has not read that paper (see PRIOR-ART.md).
