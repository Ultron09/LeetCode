# 📐 Math & Geometry

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Mathematics, Number Theory, and Computational Geometry.

---

## 📖 1. Core Theory & Fundamentals

Mathematical problems frequently test properties of integers, prime factorization, modular arithmetic, and geometric rotations.

### Key Mathematical Foundations
- **GCD & LCM**: Euclidean Algorithm $\mathcal{O}(\log(\min(a, b)))$.
- **Prime Sieve (Sieve of Eratosthenes)**: Finds all primes up to $N$ in $\mathcal{O}(N \log \log N)$.
- **Fast Modular Exponentiation**: Computes $(x^n) \pmod M$ in $\mathcal{O}(\log n)$.
- **Matrix Rotation / Reflection**: Rotating $N \times N$ matrix by $90^\circ$ clockwise = Transpose + Reverse each row.

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Fast Modular Exponentiation ($\text{Pow}(x, n)$)
```cpp
double myPow(double x, int n) {
    long long N = n;
    if (N < 0) {
        x = 1.0 / x;
        N = -N;
    }
    double result = 1.0;
    double currentProduct = x;

    while (N > 0) {
        if (N % 2 == 1) {
            result *= currentProduct;
        }
        currentProduct *= currentProduct;
        N /= 2;
    }
    return result;
}
```

### Pattern B: Sieve of Eratosthenes (Count Primes)
```cpp
int countPrimes(int n) {
    if (n <= 2) return 0;
    vector<bool> isPrime(n, true);
    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p < n; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i < n; i += p) {
                isPrime[i] = false;
            }
        }
    }
    return count(isPrime.begin(), isPrime.end(), true);
}
```

### Pattern C: Rotate $N \times N$ Matrix by $90^\circ$ Clockwise
```cpp
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    // 1. Transpose: Swap matrix[i][j] with matrix[j][i]
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    // 2. Reverse each row
    for (int i = 0; i < n; ++i) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}
```

### Pattern D: Multiset $k$-th Permutation / Inverse Cantor Expansion
Used to find the $k$-th lexicographical permutation of a multiset (e.g. LeetCode 3518).
1. Count character frequencies.
2. At each position, greedily try each candidate character $c$.
3. Compute combinations/multinomial count $P = \prod \binom{\text{rem}}{\text{cnt}_i}$ with cap at $k+1$.
4. If $P \ge k$, fix character $c$; else subtract $P$ from $k$ and continue.

### Pattern E: Harmonic Sieve & GCD Pair Counting with Inclusion-Exclusion
To count pairs $(a, b)$ with exact $\text{GCD}(a, b) = g$ across an array with values up to $M$:
1. Count element frequencies: `freq[x]` for all $x$.
2. For each $g$ from $M$ down to $1$:
   - Count elements divisible by $g$: $C = \sum_{k=1}^{\lfloor M/g \rfloor} \text{freq}[k \cdot g]$.
   - Total pairs with GCD as a multiple of $g$: $\text{pairs} = \frac{C(C-1)}{2}$.
   - Subtract counts of pairs whose GCD is a larger multiple of $g$: $\text{gcdCounts}[g] = \text{pairs} - \sum_{k=2}^{\lfloor M/g \rfloor} \text{gcdCounts}[k \cdot g]$.
3. Harmonic series complexity: $\sum_{g=1}^M \frac{M}{g} = \mathcal{O}(M \log M)$. Prefix sums over `gcdCounts` enable binary search queries in $\mathcal{O}(\log M)$.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **`INT_MIN` Negation**: Negating `INT_MIN` ($-2^{31}$) causes integer overflow because `INT_MAX` is $2^{31} - 1$. Always cast to `long long` before taking absolute values or negating.
2. **Division by Zero**: Guard against division or modulo operations with $0$.
3. **Floating Point Precision**: When checking floating point equality (geometry), use an epsilon comparison: `fabs(a - b) < 1e-9`.
4. **Factorial Overflow in Permutation Counts**: Compute combinations incrementally using $\binom{n}{m} = \prod \frac{n-j+1}{j}$ and cap intermediate products at $k+1$.
5. **Pair Count Overflow**: With $N \le 10^5$, total pairs can exceed $5 \times 10^9$; always store counts and prefix sums in `long long`.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 3312 | [Sorted GCD Pair Queries](../solutions/3312-sorted-gcd-pair-queries/README.md) | `Hard` | $\mathcal{O}(N + M \log M + Q \log M)$ | $\mathcal{O}(M)$ | [C++](../solutions/3312-sorted-gcd-pair-queries/solution.cpp) |
| 3336 | [Find the Number of Subsequences With Equal GCD](../solutions/3336-find-the-number-of-subsequences-with-equal-gcd/README.md) | `Hard` | $\mathcal{O}(N \cdot M^2)$ | $\mathcal{O}(M^2)$ | [C++](../solutions/3336-find-the-number-of-subsequences-with-equal-gcd/solution.cpp) |
| 3518 | [Smallest Palindromic Rearrangement II](../solutions/3518-smallest-palindromic-rearrangement-ii/README.md) | `Hard` | $\mathcal{O}(N \log k)$ | $\mathcal{O}(N)$ | [C++](../solutions/3518-smallest-palindromic-rearrangement-ii/solution.cpp) |


