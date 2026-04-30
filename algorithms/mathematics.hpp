#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

typedef long long ll;

namespace algo {

static ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }


static ll lcm(ll a, ll b) { return a * b / gcd(a, b); }


static bool prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}


static ll phi(ll n) {
    if (n < 1) return -1;
    ll ans = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0){
            ans -= ans / i;
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) ans -= ans / n;
    return ans;
}


static void factorization(ll n, std::map<ll, int> primes) {
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            primes[i]++;
            n /= i;
        }
    }
    if (n > 1) primes[n]++;
}


static void sieve(std::vector<bool> &prime) {
    std::fill(prime.begin(), prime.end(), true);
    for (int i = 2; i * i < prime.size(); i++) {
        if(!prime[i]) continue;
        for(int j = i * i; j < prime.size(); j += i){
            prime[j] = false;
        }
    }
}


static void euler_totient_sieve(std::vector<int> &phi) {
    std::iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i < phi.size(); i++) {
        if(phi[i] != i) continue;
        for(int j = i; j < phi.size(); j += i){
            phi[j] -= phi[j] / i;
        }
    }
}


// with memoization you can precompute the inverses in O(n)
static ll inverse(ll a, ll MOD) {
    if (a == 1LL) return 1LL;
    a = a % MOD;
    return -MOD / a * inverse(MOD % a, MOD);
}


// using fermat's little theorem if MOD is prime you can compute a^-1 mod m by calling fast_exp(a, m - 2, m)
static ll fast_exp(ll a, ll b, ll MOD) {
    if (b == 0LL) return 1LL;
    if (b & 1LL) return a * fast_exp(a, b - 1, MOD) % MOD;
    ll k = fast_exp(a, b / 2, MOD);
    return k * k % MOD;
}


static void compute_factorials_and_inverses(std::vector<ll> &fact, std::vector<ll> &inv, ll MOD) {
    int n = fact.size();
    fact[0] = 1LL;
    for (int i = 1; i < n; i++) fact[i] = fact[i - 1] * i % MOD;
    inv[n - 1] = fast_exp(fact[n - 1], MOD - 2, MOD);
    for (int i = n - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
}

} // namespace algo