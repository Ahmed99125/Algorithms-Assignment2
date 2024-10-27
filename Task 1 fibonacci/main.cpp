#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#define ll long long
using namespace std;
using namespace std::chrono;
//The regular fibonacci
ll fib(ll n){
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    return fib(n-1) + fib(n-2);
}

map <ll, ll> dp;
//fibonacci optimized with dp
ll fibDP(ll n){
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    if (dp.find(n) != dp.end())
        return dp[n];

    return dp[n] = fibDP(n-1) + fibDP(n-2);
}

vector<vector<ll>> matrix_mult(vector<vector<ll>>& A, vector<vector<ll>>& B){
    vector<vector<long long>> result = {
            {A[0][0] * B[0][0] + A[0][1] * B[1][0], A[0][0] * B[0][1] + A[0][1] * B[1][1]},
            {A[1][0] * B[0][0] + A[1][1] * B[1][0], A[1][0] * B[0][1] + A[1][1] * B[1][1]}
    };
    return result;
}

vector<vector<ll>> fastPower(vector<vector<ll>>& base, ll power){
    if (power == 1)
        return base;
    if (power % 2 == 0){    //even
        vector<vector<ll>> result = fastPower(base, power/2);
        return matrix_mult(result, result);
    }
    else{
        vector<vector<ll>> evenPart = fastPower(base, (power-1)/2);
        vector<vector<ll>> result = matrix_mult(evenPart, evenPart);
        return matrix_mult(result, base);
    }

}

//fibonacci optimized with matrix exponentiation
ll fibMatrix(ll n){
    if (n == 1)
        return 1;
    if (n == 0)
        return 0;

    vector<vector<ll>> T = {{1, 1}, {1, 0}};
    vector<vector<ll>> T_n_minus_1 = fastPower(T, n-1);
    return T_n_minus_1[0][0];
}



int main() {
//    auto start = high_resolution_clock::now();
//    cout << "regular fib: " << fib(40) << endl;
//    auto end = high_resolution_clock::now();
//    auto duration = duration_cast<microseconds>(end-start);
//    cout << "time taken is: " << duration.count() << "\n\n";

    auto start = high_resolution_clock::now();
    cout << "optimized fib: " << fibDP(1000) << '\n';
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time taken is: " << duration.count() << "\n\n";

    start = high_resolution_clock::now();
    cout << "More optimized fib: " << fibMatrix(1000) << '\n';
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end-start);
    cout << "time taken is: " << duration.count() << endl;
}
