#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h> 
#include <time.h>
#include <unistd.h> // For getpid()

typedef struct RSA {
    mpz_t p; // p and q are two large primes with large difference, we let them be 32 bit here
    mpz_t q; 
    mpz_t n; // Modulus and n = pq
    mpz_t e;
    mpz_t d;
    mpz_t phi;
    void (*encrypt)(struct RSA *self, const char* plaintext, mpz_t ciphertext);
    void (*decrypt)(struct RSA *self, const mpz_t ciphertext, char* plaintext_out);
    void (*encrypt_num)(struct RSA *self, const mpz_t plaintext, mpz_t ciphertext);
    void (*decrypt_num)(struct RSA *self, const mpz_t ciphertext, mpz_t plaintext);
} RSA;

    void encrypt_impl(struct RSA *self, const char* plaintext, mpz_t ciphertext);
    void decrypt_impl(struct RSA *self, const mpz_t ciphertext, char* plaintext_out);
    void encrypt_num_impl(struct RSA *self, const mpz_t plaintext, mpz_t ciphertext);
    void decrypt_num_impl(struct RSA *self, const mpz_t ciphertext, mpz_t plaintext);

RSA *new_rsa();
void delete_rsa(RSA *rsa);

//For large prime(p and q) generation, refer to https://www.geeksforgeeks.org/how-to-generate-large-prime-numbers-for-rsa-algorithm/

void generate_random_n_bit_odd_number(mpz_t result, unsigned int n);  //n bits
bool low_level_primality_test(unsigned long long n);
void find_large_prime(mpz_t prime, unsigned int bits);

