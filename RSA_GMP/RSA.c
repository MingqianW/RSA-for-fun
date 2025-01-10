#include "RSA.h"

void encrypt_impl(struct RSA *self, const char* plaintext, mpz_t ciphertext);
void decrypt_impl(struct RSA *self, const mpz_t ciphertext, char* plaintext_out);
void encrypt_num_impl(struct RSA *self, const mpz_t plaintext, mpz_t ciphertext);
void decrypt_num_impl(struct RSA *self, const mpz_t ciphertext, mpz_t plaintext);

// generate_random_n_bit_odd_numbe is done by gpt
unsigned long int generate_unique_seed() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // Get current time with nanoseconds

    // Combine nanoseconds, process ID, and rand() for a robust seed
    unsigned long int seed = ts.tv_nsec ^ (unsigned long int)getpid() ^ rand();
    return seed;
}

void generate_random_n_bit_odd_number(mpz_t result, unsigned int n) {
    // Initialize GMP random state
    gmp_randstate_t state;
    gmp_randinit_default(state);

    // Generate a unique seed
    unsigned long int seed = generate_unique_seed();
    gmp_randseed_ui(state, seed);

    // Generate the random number
    mpz_urandomb(result, state, n);

    // Ensure the number is odd
    mpz_setbit(result, 0);

    // Print the result
    gmp_printf("Generated random %u-bit odd number: %Zd\n", n, result);

    // Clear the random state
    gmp_randclear(state);
}



void find_large_prime(mpz_t prime, unsigned int bits) {
    gmp_randstate_t state;
    gmp_randinit_mt(state);

    // Seed with a unique value, such as current time plus memory address
    gmp_randseed_ui(state, time(NULL) + (uintptr_t)&prime);

    do {
        mpz_urandomb(prime, state, bits); // Generate a random number with the specified number of bits
        mpz_nextprime(prime, prime); // Find the next prime greater than the generated number
    } while (mpz_probab_prime_p(prime, 25) == 0); // Ensure the number is prime

    gmp_randclear(state);
}


RSA *new_rsa() {
    RSA* rsa = (RSA*)malloc(sizeof(RSA));
    // rsa->p = find_large_prime(20);
    // rsa->q = find_large_prime(20);;
    mpz_init(rsa->p);
    mpz_init(rsa->q);
    mpz_init(rsa->n);
    mpz_init(rsa->phi);
    mpz_init(rsa->e);
    mpz_init(rsa->d);
    find_large_prime(rsa->p, 1024);
    mpz_t p_double;
    mpz_init(p_double);
    mpz_t num;
    mpz_init(num);
    mpz_set_ui(num, 2);
    mpz_mul(p_double, rsa->p, num);
    mpz_nextprime(rsa->q, p_double);
    mpz_clear(p_double);
    mpz_mul(rsa->n, rsa->p, rsa->q);
    mpz_t q_minus1;
    mpz_init(q_minus1);
    mpz_t p_minus1;
    mpz_init(p_minus1);
    mpz_sub_ui(p_minus1, rsa->p, 1);
    mpz_sub_ui(q_minus1, rsa->q, 1);
    mpz_mul(rsa->phi, q_minus1, p_minus1);
    mpz_clear(q_minus1);
    mpz_clear(p_minus1);
    mpz_set_ui(rsa->e, 65537);
    mpz_invert(rsa->d, rsa->e, rsa->phi);
    rsa->encrypt = encrypt_impl;
    rsa->decrypt = decrypt_impl;
    rsa->encrypt_num = encrypt_num_impl;
    rsa->decrypt_num = decrypt_num_impl;
    gmp_printf("RSA Key Details: p=%Zd, q=%Zd, n=%Zd, phi=%Zd, e=%Zd, d=%Zd\n",
               rsa->p, rsa->q, rsa->n, rsa->phi, rsa->e, rsa->d);

    return rsa;
}

void delete_rsa(RSA *rsa) {
    if (rsa) {
        mpz_clear(rsa->p);
        mpz_clear(rsa->q);
        mpz_clear(rsa->n);
        mpz_clear(rsa->phi);
        mpz_clear(rsa->e);
        mpz_clear(rsa->d);
        free(rsa);
    }
}

void encrypt_impl(struct RSA *self, const char* plaintext, mpz_t ciphertext) {
    mpz_t message_ASCII;
    mpz_init(message_ASCII);
    mpz_set_ui(message_ASCII, 0);

    for (int i = 0; plaintext[i] != '\0'; i++) {
        mpz_mul_ui(message_ASCII, message_ASCII, 256);
        mpz_add_ui(message_ASCII, message_ASCII, (unsigned char)plaintext[i]);
        mpz_mod(message_ASCII, message_ASCII, self->n);
    }
    mpz_powm(ciphertext, message_ASCII, self->e, self->n);
    mpz_clear(message_ASCII);
}


void decrypt_impl(struct RSA *self, const mpz_t ciphertext, char* plaintext_out) {
    mpz_t message_ASCII;
    mpz_init(message_ASCII);
    mpz_powm(message_ASCII, ciphertext, self->d, self->n);
    int i = 0;
    while (mpz_cmp_ui(message_ASCII, 0) > 0) {
        plaintext_out[i++] = (char)(mpz_get_ui(message_ASCII) & 0xFF);
        mpz_div_ui(message_ASCII, message_ASCII, 256);
    }
    plaintext_out[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = plaintext_out[j];
        plaintext_out[j] = plaintext_out[i - j - 1];
        plaintext_out[i - j - 1] = temp;
    }
    mpz_clear(message_ASCII);
}

void encrypt_num_impl(struct RSA *self, const mpz_t plaintext, mpz_t ciphertext) {
    mpz_powm(ciphertext, plaintext, self->e, self->n);
}

void decrypt_num_impl(struct RSA *self, const mpz_t ciphertext, mpz_t plaintext) {
    mpz_powm(plaintext, ciphertext, self->d, self->n);
}
