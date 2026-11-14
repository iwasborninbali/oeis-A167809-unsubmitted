// Independent verification of A167809, 2026-11-15.
// Original implementation: incremental 128-bit sum masks for all admissible
// bases, plus a separate lexicographic ballot-position enumerator that
// recomputes every represented integer from its chosen denominations.
// No code or tables from the audited repository are used as inputs.
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>

using u128 = unsigned __int128;
constexpr int ALL_LIMIT = 15;
constexpr int BALLOT_LIMIT = 18;
std::array<std::uint64_t, ALL_LIMIT + 1> all_counts{};
std::array<std::uint64_t, ALL_LIMIT + 1> subfamily_counts{};
std::array<int, ALL_LIMIT + 1> maximum_denominations{};
std::array<std::uint64_t, BALLOT_LIMIT + 1> ballot_counts{};
std::array<int, BALLOT_LIMIT + 1> positions{};

static inline u128 bit(int p) {
    if (p < 0 || p >= 128) throw std::runtime_error("128-bit mask limit exceeded");
    return u128{1} << p;
}

// A state stores all *single and double sums* already achievable. Adding
// denomination v requires only a shift of the OLD denomination bitmask.
void count_all(int depth, int last, u128 denom, u128 reachable, bool within_ballot) {
    ++all_counts[depth];
    if (within_ballot) ++subfamily_counts[depth];
    maximum_denominations[depth] = std::max(maximum_denominations[depth], last);
    if (depth == ALL_LIMIT) return;

    int first_hole = last + 1;
    while ((reachable & bit(first_hole)) != 0) ++first_hole;
    for (int v = last + 1; v <= first_hole; ++v) {
        u128 after = reachable | bit(v) | (denom << v);
        if (2 * v < 128) after |= bit(2 * v);
        count_all(depth + 1, v, denom | bit(v), after,
                  within_ballot && (v <= 2 * (depth + 1) - 1));
    }
}

// Exact Catalan recurrence, evaluated independently of the enumerations.
std::uint64_t cat(int n) {
    std::uint64_t c = 1;
    for (int k = 0; k < n; ++k) {
        c = c * (4ULL * k + 2) / (k + 2);
    }
    return c;
}

// Explicitly test each member of the candidate Catalan family from scratch.
// The generator chooses the rising positions, not balanced up/down words;
// the test independently forms the sumset by arithmetic, not mask shifts.
void check_ballot(int depth, int previous) {
    ++ballot_counts[depth];
    u128 represented = 0;
    for (int i = 1; i <= depth; ++i) {
        int a = positions[i];
        represented |= bit(a);
        for (int j = 1; j <= i; ++j) {
            represented |= bit(a + positions[j]);
        }
    }
    u128 required = bit(previous + 1) - 2;
    if ((represented & required) != required) {
        std::cerr << "FAILED coverage at n=" << depth << "\n";
        std::exit(1);
    }
    if (depth == BALLOT_LIMIT) return;
    const int next_i = depth + 1;
    for (int p = previous + 1; p <= 2 * next_i - 1; ++p) {
        positions[next_i] = p;
        check_ballot(next_i, p);
    }
}

int main() {
    const auto t0 = std::chrono::steady_clock::now();
    const std::clock_t cpu0 = std::clock();
    count_all(1, 1, bit(1), bit(1) | bit(2), true);
    const auto t1 = std::chrono::steady_clock::now();
    const std::clock_t cpu1 = std::clock();
    std::cout << "INDEPENDENT A167809 CHECK, 2026-11-15\n";
    std::cout << "Full admissible-basis enumeration: incremental 128-bit masks\n";
    std::cout << "n all a(n) subfamily C(n) largest_denominator\n";
    for (int n = 1; n <= ALL_LIMIT; ++n) {
        auto c = cat(n);
        std::cout << n << ' ' << all_counts[n] << ' ' << subfamily_counts[n]
                  << ' ' << c << ' ' << maximum_denominations[n] << '\n';
        if (subfamily_counts[n] != c || all_counts[n] < subfamily_counts[n]) return 2;
    }
    std::cout << "Full-enumeration wall_seconds=" << std::fixed << std::setprecision(3)
              << std::chrono::duration<double>(t1 - t0).count()
              << " cpu_seconds=" << double(cpu1 - cpu0) / CLOCKS_PER_SEC << '\n';

    const auto t2 = std::chrono::steady_clock::now();
    const std::clock_t cpu2 = std::clock();
    positions[1] = 1;
    check_ballot(1, 1);
    const auto t3 = std::chrono::steady_clock::now();
    const std::clock_t cpu3 = std::clock();
    std::cout << "Independent exhaustive ballot-position coverage tests\n";
    std::cout << "n distinct_tested_images C(n)\n";
    for (int n = 1; n <= BALLOT_LIMIT; ++n) {
        auto c = cat(n);
        std::cout << n << ' ' << ballot_counts[n] << ' ' << c << '\n';
        if (ballot_counts[n] != c) return 3;
    }
    std::cout << "Ballot-enumeration wall_seconds="
              << std::chrono::duration<double>(t3 - t2).count()
              << " cpu_seconds=" << double(cpu3 - cpu2) / CLOCKS_PER_SEC << '\n';
    std::cout << "TOTAL wall_seconds="
              << std::chrono::duration<double>(t3 - t0).count()
              << " cpu_seconds=" << double(cpu3 - cpu0) / CLOCKS_PER_SEC << '\n';
    std::cout << "PASS\n";
}
