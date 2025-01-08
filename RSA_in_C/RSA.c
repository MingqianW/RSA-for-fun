#include "RSA.h"

long long encrypt_impl(struct RSA *self, char* plaintext);
long long decrypt_impl(struct RSA *self, long long ciphertext, char* plaintext_out);

static const unsigned int prime_list[] = { // prime less than 1000
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
    53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109,
    113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
    181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241,
    251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313,
    317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
    397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
    463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547,
    557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617,
    619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691,
    701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773,
    787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859,
    863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947,
    953, 967, 971, 977, 983, 991, 997
};
static const unsigned int prime_list_length =sizeof(prime_list) / sizeof(prime_list[0]);

unsigned long long generate_large_odd_number() {
    unsigned long long num = ((unsigned int)rand() << 16) | (unsigned int)rand();
    return num | 1;
    }


bool low_level_primality_test(unsigned long long n) {
    for (int i = 0; i < prime_list_length; i++) {
        if (n % prime_list[i] == 0) {
            return false;
        }
    }
    return true;
}

unsigned long long power_mod_helper(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

bool miller_rabin(unsigned long long n, int k) {
    unsigned long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = 0; i < k; i++) {
        unsigned long long a = 2 + rand() % (n - 4);
        unsigned long long x = power_mod_helper(a, d, n);
        if (x == 1 || x == n - 1) 
            continue;
        bool is_composite = true;
        for (int r = 1; r < s; r++) {
            x = (x * x) % n;
            if (x == n - 1 || x == 1) {
                is_composite = false;
                break;
            }
        }
        if (is_composite) return false;
    }
    return true; 
}

unsigned long long find_large_prime(int k) {
    unsigned long long num = generate_large_odd_number();
    while (!low_level_primality_test(num) || !miller_rabin(num, k)) {
        num += 2;
        if (num > 0xFFFFFFFF) {
            num = generate_large_odd_number();
        }
    }
    return num;
}

// Compute modular multiplicative inverse with Extended Euclidean Algorithm, refer to https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Computing_multiplicative_inverses_in_modular_structures
unsigned long long mod_inverse(unsigned long long a, unsigned long long n) {
    long long t = 0, new_t = 1;
    long long r = n, new_r = a;
    while (new_r != 0) {
        long long quotient = r / new_r;
        long long temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;
        long long temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }
    if (r > 1) {
        fprintf(stderr, "a is not invertible\n");
        return 0;
    }
    if (t < 0) {
        t += n;
    }
    return t;
}

RSA *new_rsa() {
    RSA* rsa = (RSA*)malloc(sizeof(RSA));
    rsa->p = find_large_prime(20);
    rsa->q = find_large_prime(20);;
    rsa->n = rsa->p * rsa->q;
    rsa->phi = (rsa->p - 1) * (rsa->q - 1);
    rsa->e = 65537;
    rsa->d = mod_inverse(rsa->e, rsa->phi); 
    rsa->encrypt = encrypt_impl;
    rsa->decrypt = decrypt_impl;
    return rsa;
}

void delete_rsa(RSA *rsa) {
    if (rsa) {
        free(rsa);
    }
}

long long encrypt_impl(struct RSA *self, char* plaintext) {
    long long message_ASCII = 0;
    for (int i = 0; plaintext[i] != '\0'; i++) {
        message_ASCII = (message_ASCII << 8) | (unsigned char)plaintext[i]; 
    }

    // Encrypt the integer using RSA: C = M^e mod n
    return power_mod_helper(message_ASCII, self->e, self->n);
}


long long decrypt_impl(struct RSA *self, long long ciphertext, char* plaintext_out) {
    long long message_ASCII = power_mod_helper(ciphertext, self->d, self->n);
    int i = 0;
    while (message_ASCII > 0) {
        plaintext_out[i] = (char)(message_ASCII & 0xFF);  // Extract one character
        i++;
        message_ASCII = message_ASCII >> 8;  // Remove the extracted character
    }
    plaintext_out[i] = '\0';

    // Reverse the string to get the original order
    int len = strlen(plaintext_out);
    for (int j = 0; j < len / 2; j++) {
        char temp = plaintext_out[j];
        plaintext_out[j] = plaintext_out[len - 1 - j];
        plaintext_out[len - 1 - j] = temp;
    }
   return 0;
}