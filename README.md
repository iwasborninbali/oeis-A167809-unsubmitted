# OEIS A167809: Catalan lower bound (not yet submitted)

<!-- oeis-status:begin -->
**OEIS status: not submitted.** (replaced by the registry tool)
<!-- oeis-status:end -->

## Definition

For n>=1, a(n) counts increasing integer bases 1=b₁<...<bₙ such that each integer from 1 to bₙ is a sum of at most two elements of the basis, with repetition allowed. The offset is 1. The Catalan number is Cₙ=binomial(2n,n)/(n+1).

The task snapshot `context/A167809.seq` and the live [entry](https://oeis.org/A167809), read 2026-11-13, record Michael Chu's May 16, 2022 conjecture: “Conjecture: a(n) >= A000108(n).” The live entry does not record the proof.

## Terms / result

The inequality a(n)>=Cₙ holds for all n>=1.

| n | a(n) | Cₙ |
|---:|---:|---:|
| 1 | 1 | 1 |
| 2 | 2 | 2 |
| 3 | 5 | 5 |
| 4 | 17 | 14 |
| 5 | 65 | 42 |
| 6 | 292 | 132 |

## How it was obtained

Up-step positions of a Dyck word form an admissible basis. A complementary-pair argument proves admissibility and the positions uniquely determine the word. The full proof is in [proof.md](proof.md).

## Verification

The producer enumerates admissible bases through n=10. An independently written program generates Dyck words and directly tests all images through n=10. The proof is human-checkable, not formally machine-checked; finite checks do not establish the bound for all n. See [CERTIFICATE.md](CERTIFICATE.md).

## Prior art and credit

Chu stated the conjecture. ChatGPT supplied the injection and Claude Code reviewed it. Earlier priority has not been settled; see [PRIOR-ART.md](PRIOR-ART.md).

## Reproduce

Run `python3 programs/producer.py` and `python3 verification/check.py`; each ends `PASS` and both together take about three seconds on the recorded machine. The producer reports 305226 bases and 16796 Catalan-family bases for n=10; the checker reports 16796 distinct admissible images. Complete logs are in `verification/logs/`.

## Provenance

Source `projects/science/athanor-oeis`, commit `7662d9a678c6d414685a899a631c63ac320f6840`, paths `tasks/2026-11-12-A167809-postage-catalan/answers/2026-11-12-chatgpt.md`, `context/A167809.seq`, and `TASK.md`. Guide review is recorded in `tasks/README.md`.

## Author, licence

Aleksei Kudriashov (ORCID 0009-0006-8885-5338), Athanor lab, with AI assistance (OpenAI Codex cores; Claude Code as the lab's guide). Code: MIT; data and text: CC BY 4.0 (see LICENSE.md).
