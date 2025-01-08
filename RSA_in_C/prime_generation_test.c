#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RSA.h"

// Use chatgpt to generate a simple test for the large prime generation part.

int main() {
    // Seed random number generator
    srand((unsigned int)time(NULL));  // C-style cast used here

    // Test: Miller-Rabin primality test
    unsigned long long test_prime = 997; // Known prime
    unsigned long long test_composite = 1000; // Known composite
    int iterations = 20; // Number of iterations for Miller-Rabin

    bool miller_rabin_prime = miller_rabin(test_prime, iterations);
    bool miller_rabin_composite = miller_rabin(test_composite, iterations);


    printf("Miller-Rabin test on %llu: %s\n", test_prime, miller_rabin_prime ? "PASS" : "FAIL");
    printf("Miller-Rabin test on %llu: %s\n", test_composite, miller_rabin_composite ? "PASS" : "FAIL");

    // Test: Find a large prime number
    unsigned long long large_prime1 = find_large_prime(iterations);
    printf("Generated large prime: %llu\n", large_prime1);
    unsigned long long large_prime2 = find_large_prime(iterations);
    printf("Generated large prime: %llu\n", large_prime2);
    unsigned long long large_prime3 = find_large_prime(iterations);
    printf("Generated large prime: %llu\n", large_prime3);
    unsigned long long large_prime4 = find_large_prime(iterations);
    printf("Generated large prime: %llu\n", large_prime4);
    unsigned long long large_prime5 = find_large_prime(iterations);
    printf("Generated large prime: %llu\n", large_prime5);
    return 0;
}
