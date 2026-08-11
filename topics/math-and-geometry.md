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

### Pattern F: Global Affine Transformation with Modular Inverse
To support sequence-wide additions, multiplications, and appends in $\mathcal{O}(1) / \mathcal{O}(\log M)$ per operation:
1. **Global Linear Function**: Maintain $f(x) = (a \cdot x + b) \pmod M$ representing the cumulative transformation applied to all existing values.
2. **Operations**:
   - `addAll(inc)`: $b = (b + inc) \pmod M$.
   - `multAll(m)`: $a = (a \cdot m) \pmod M, \quad b = (b \cdot m) \pmod M$.
3. **Inverse Insertion**: When appending $val$, store raw value $x = (val - b) \cdot a^{-1} \pmod M$, where $a^{-1} = a^{M-2} \pmod M$ via Fermat's Little Theorem.
4. **Point Query**: $getIndex(idx) = (a \cdot arr[idx] + b) \pmod M$.

### Pattern G: Factoradic Decomposition / Direct Permutation Rank Decoding
To compute the $k^{\text{th}}$ lexicographical permutation of $\{1, \dots, n\}$ directly in $\mathcal{O}(n^2)$ without generating permutations:
1. Precompute factorials $(n - 1)!, (n - 2)!, \dots, 1!$.
2. Convert $k$ to 0-based: $k \leftarrow k - 1$.
3. At each step $i \in [n - 1 \dots 1]$:
   - Index of chosen digit: `idx = k / fact`.
   - Extract `numbers[idx]` and remove it from the list.
   - Update $k \leftarrow k \bmod \text{fact}$ and $\text{fact} \leftarrow \text{fact} / i$.

### Pattern H: Deterministic Finite State Machine for Number Parsing
Maintain boolean flags `seenDigit`, `seenDot`, `seenExponent` to validate numerical formats in $\mathcal{O}(N)$ time and $\mathcal{O}(1)$ space:
1. `+`/`-`: Permitted only at index 0 or immediately after `e`/`E`.
### Pattern J: Irreducible Coprime Slope Representation & Collinear Sweeps
When finding the maximum number of collinear points on an integer 2D plane:
1. Fix an anchor point $(x_i, y_i)$.
2. For each other point $(x_j, y_j)$, compute differences $\Delta x = x_j - x_i, \Delta y = y_j - y_i$.
3. Reduce by $g = \gcd(|\Delta x|, |\Delta y|)$ and normalize direction (canonical sign and zero cases).
4. Pack coprime integer pair into a 64-bit key and accumulate in a hash map to avoid all floating-point precision loss.

### Pattern K: Place-Value Positional Counting (Number of Digit One)
When counting occurrences of a target digit across all integers in $[1, n]$:
1. Iterate over each place value $m \in \{1, 10, 100, \dots\}$ where $m \le n$.
2. Compute $\text{higher} = \lfloor n / (10m) \rfloor$, $\text{curr} = \lfloor n / m \rfloor \bmod 10$, and $\text{lower} = n \bmod m$.
3. If $\text{curr} == 0 \implies \text{count} += \text{higher} \times m$.
4. If $\text{curr} == 1 \implies \text{count} += \text{higher} \times m + (\text{lower} + 1)$.
5. If $\text{curr} > 1 \implies \text{count} += (\text{higher} + 1) \times m$.
Achieves optimal $\mathcal{O}(\log_{10} n)$ time with $\mathcal{O}(1)$ space.

### Pattern L: Orthogonal 2D Spiral Self-Crossing Classification
For a 2D path turning $90^\circ$ counter-clockwise at each step, self-intersection can only occur across 3 canonical geometric configurations:
1. **Line $i$ crosses Line $i-3$ ($i \ge 3$)**:
   $$\text{dist}[i] \ge \text{dist}[i-2] \land \text{dist}[i-1] \le \text{dist}[i-3]$$
2. **Line $i$ meets / overlaps Line $i-4$ ($i \ge 4$)**:
   $$\text{dist}[i-1] == \text{dist}[i-3] \land \text{dist}[i] + \text{dist}[i-4] \ge \text{dist}[i-2]$$
3. **Line $i$ crosses Line $i-5$ on Expanding-to-Contracting Transition ($i \ge 5$)**:
   $$\text{dist}[i-2] \ge \text{dist}[i-4] \land \text{dist}[i-1] \le \text{dist}[i-3] \land \text{dist}[i-1] + \text{dist}[i-5] \ge \text{dist}[i-3] \land \text{dist}[i] + \text{dist}[i-4] \ge \text{dist}[i-2]$$
Evaluating these 3 conditions in a single $\mathcal{O}(N)$ pass determines self-crossing in $\mathcal{O}(1)$ space without coordinate sets.

### Pattern M: Perfect Rectangle Cover via Corner Parity + Area Conservation
To verify whether $N$ axis-aligned rectangles tile a bounding rectangle exactly (no gaps, no overlaps):
1. **Area Conservation**: $\sum \text{area}(R_i) = \text{area}(\text{bounding box})$. This catches gaps and overlaps that change total area.
2. **Corner Parity Theorem**: Toggle each rectangle's 4 corners in a set (insert if absent, erase if present). After all rectangles, exactly the 4 corners of the bounding box must remain.
3. **Why This Is Sufficient**: Interior vertices of a valid tiling always have 2 or 4 rectangles meeting → even corner count → cancelled. Edge vertices (non-bounding-corner) also pair up. Only the 4 bounding corners appear exactly once.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **`INT_MIN` Negation**: Negating `INT_MIN` ($-2^{31}$) causes integer overflow because `INT_MAX` is $2^{31} - 1$. Always cast to `long long` before taking absolute values or negating.
2. **Division by Zero**: Guard against division or modulo operations with $0$.
3. **Floating Point Precision**: When checking floating point equality (geometry), use an epsilon comparison or exact integer coprime fractions.
4. **Factorial Overflow in Permutation Counts**: Compute combinations incrementally using $\binom{n}{m} = \prod \frac{n-j+1}{j}$ and cap intermediate products at $k+1$.
5. **Pair Count Overflow**: With $N \le 10^5$, total pairs can exceed $5 \times 10^9$; always store counts and prefix sums in `long long`.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 60 | [Permutation Sequence](../solutions/0060-permutation-sequence/README.md) | `Hard` | $\mathcal{O}(N^2)$ | $\mathcal{O}(N)$ | [C++](../solutions/0060-permutation-sequence/solution.cpp) |
| 65 | [Valid Number](../solutions/0065-valid-number/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0065-valid-number/solution.cpp) |
| 149 | [Max Points on a Line](../solutions/0149-max-points-on-a-line/README.md) | `Hard` | $\mathcal{O}(N^2 \log(\max(\text{coord})))$ | $\mathcal{O}(N)$ | [C++](../solutions/0149-max-points-on-a-line/solution.cpp) |
| 233 | [Number of Digit One](../solutions/0233-number-of-digit-one/README.md) | `Hard` | $\mathcal{O}(\log_{10} N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0233-number-of-digit-one/solution.cpp) |
| 273 | [Integer to English Words](../solutions/0273-integer-to-english-words/README.md) | `Hard` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | [C++](../solutions/0273-integer-to-english-words/solution.cpp) |
| 335 | [Self Crossing](../solutions/0335-self-crossing/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0335-self-crossing/solution.cpp) |
| 391 | [Perfect Rectangle](../solutions/0391-perfect-rectangle/README.md) | `Hard` | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0391-perfect-rectangle/solution.cpp) |
| 1622 | [Fancy Sequence](../solutions/1622-fancy-sequence/README.md) | `Hard` | $\mathcal{O}(\log M) \text{ append}, \mathcal{O}(1) \text{ rest}$ | $\mathcal{O}(N)$ | [C++](../solutions/1622-fancy-sequence/solution.cpp) |
| 1840 | [Maximum Building Height](../solutions/1840-maximum-building-height/README.md) | `Hard` | $\mathcal{O}(R \log R)$ | $\mathcal{O}(R)$ | [C++](../solutions/1840-maximum-building-height/solution.cpp) |
| 3312 | [Sorted GCD Pair Queries](../solutions/3312-sorted-gcd-pair-queries/README.md) | `Hard` | $\mathcal{O}(N + M \log M + Q \log M)$ | $\mathcal{O}(M)$ | [C++](../solutions/3312-sorted-gcd-pair-queries/solution.cpp) |
| 3336 | [Find the Number of Subsequences With Equal GCD](../solutions/3336-find-the-number-of-subsequences-with-equal-gcd/README.md) | `Hard` | $\mathcal{O}(N \cdot M^2)$ | $\mathcal{O}(M^2)$ | [C++](../solutions/3336-find-the-number-of-subsequences-with-equal-gcd/solution.cpp) |
| 3518 | [Smallest Palindromic Rearrangement II](../solutions/3518-smallest-palindromic-rearrangement-ii/README.md) | `Hard` | $\mathcal{O}(N \log k)$ | $\mathcal{O}(N)$ | [C++](../solutions/3518-smallest-palindromic-rearrangement-ii/solution.cpp) |
| 3559 | [Number of Ways to Assign Edge Weights II](../solutions/3559-number-of-ways-to-assign-edge-weights-ii/README.md) | `Hard` | $\mathcal{O}((N + Q) \log N)$ | $\mathcal{O}(N \log N)$ | [C++](../solutions/3559-number-of-ways-to-assign-edge-weights-ii/solution.cpp) |
| 3700 | [Number of ZigZag Arrays II](../solutions/3700-number-of-zigzag-arrays-ii/README.md) | `Hard` | $\mathcal{O}((2M)^3 \log N)$ | $\mathcal{O}((2M)^2)$ | [C++](../solutions/3700-number-of-zigzag-arrays-ii/solution.cpp) |
| 3753 | [Total Waviness of Numbers in Range II](../solutions/3753-total-waviness-of-numbers-in-range-ii/README.md) | `Hard` | $\mathcal{O}(D^3 \log_{10}(num_2))$ | $\mathcal{O}(D^2 \log_{10}(num_2))$ | [C++](../solutions/3753-total-waviness-of-numbers-in-range-ii/solution.cpp) |






