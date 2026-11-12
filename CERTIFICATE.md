# Verification certificate

## Claim

For every n>=1, the number of admissible two-stamp n-denomination bases is at least the n-th Catalan number.

## Evidence

| What | Program | Author and date | Coverage | Result |
|---|---|---|---|---|
| Human-checkable proof | `proof.md` | Adapted by OpenAI Codex from ChatGPT, 2026-11-12 | All n>=1 | Not machine-checked |
| Producer | `programs/producer.py` | ChatGPT, 2026-11-12 | Bases and Catalan subfamily through n=10 | Passed |
| Independent check | `verification/check.py` | OpenAI Codex, 2026-11-13 | Dyck images and admissibility through n=10 | Passed |

The checker independently generates Dyck words and tests their sums; it shares no producer code or tables. Guide review is recorded in `athanor-oeis/tasks/README.md`.

## Replayed for this repository

2026-11-13, Darwin arm64, Python 3.14.6: `python3 programs/producer.py` reports 305226 bases and 16796 Catalan-family bases for n=10; `python3 verification/check.py` reports 16796 distinct admissible images for n=10. Both report `PASS`. Full logs are in `verification/logs/`.

## Not covered

No formal verification of the all-n proof. The independent program checks the injection through n=10, not the total count of all bases; the source's checks through n=12 and the separate lemma enumeration were not replayed.

## Guide's independent check

pending

## Verdict

complete — the independent injection check was replayed in full through its stated range; the universal proof remains human-checkable, not machine-checked.
