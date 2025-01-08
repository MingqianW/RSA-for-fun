#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct RSA {
    long long p; // p and q are two large primes with large difference, we let them be 32 bit here
    long long q; 
    long long n; // Modulus and n = pq
    long long e;
    long long d;
    long long phi;
    long long (*encrypt)(struct RSA *self, char* plaintext);
    long long (*decrypt)(struct RSA *self, long long ciphertext, char* plaintext_out);

} RSA;

long long encrypt_impl(struct RSA *self, char* plaintext);
long long decrypt_impl(struct RSA *self, long long ciphertext, char* plaintext_out);

RSA *new_rsa();
void delete_rsa(RSA *rsa);

//For large prime(p and q) generation, refer to https://www.geeksforgeeks.org/how-to-generate-large-prime-numbers-for-rsa-algorithm/

unsigned long long generate_large_odd_number(); //32 bits for now. If want to use larger prime, maybe consider use GMP lib.
bool low_level_primality_test(unsigned long long n);
unsigned long long power_mod_helper(unsigned long long base, unsigned long long exp, unsigned long long mod); //calculate base^exp mod mod
bool miller_rabin(unsigned long long n, int k); // refer to https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test and k is iteration
unsigned long long find_large_prime(int k);

