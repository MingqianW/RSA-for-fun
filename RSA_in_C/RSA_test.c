#include <stdio.h>
#include <stdlib.h>
#include "RSA.h"

// Function to test RSA encryption and decryption for numbers
void test_rsa_numbers() {
    printf("Running RSA Numeric Encryption/Decryption Test...\n");

    // Initialize RSA
    RSA *rsa = new_rsa();
    if (!rsa) {
        fprintf(stderr, "Error: Failed to initialize RSA keys.\n");
        exit(EXIT_FAILURE);
    }

    // Print RSA keys for debugging
    printf("RSA Keys:\n");
    printf("p: %llu, q: %llu\n", rsa->p, rsa->q);
    printf("n: %llu, phi: %llu\n", rsa->n, rsa->phi);
    printf("e: %llu, d: %llu\n", rsa->e, rsa->d);

    // Test encryption and decryption with a number
    unsigned long long plaintext = 12345; // Example number to encrypt
    unsigned long long ciphertext, decrypted;

    printf("Plaintext Number: %llu\n", plaintext);

    // Encrypt the number
    ciphertext = power_mod_helper(plaintext, rsa->e, rsa->n);
    printf("Ciphertext: %llu\n", ciphertext);

    // Decrypt the number
    decrypted = power_mod_helper(ciphertext, rsa->d, rsa->n);
    printf("Decrypted Number: %llu\n", decrypted);

    // Validate the result
    if (plaintext == decrypted) {
        printf("Test Passed: Decrypted number matches original plaintext.\n");
    } else {
        printf("Test Failed: Decrypted number does not match original plaintext.\n");
    }

    // Cleanup
    delete_rsa(rsa);
}

int main() {
    // Run numeric RSA test
    test_rsa_numbers();

    return 0;
}
