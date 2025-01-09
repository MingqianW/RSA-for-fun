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
    unsigned long long plaintnumber = 123; // Example number to encrypt
    unsigned long long ciphernumber, decryptednumber;

    printf("Plaintext Number: %llu\n", plaintnumber);

    // Encrypt the number
    ciphernumber = rsa->encrypt_num(rsa, plaintnumber);
    printf("Ciphertext: %llu\n", ciphernumber);

    // Decrypt the number
    decryptednumber = rsa->decrypt_num(rsa, ciphernumber);
    printf("Decrypted Number: %llu\n", decryptednumber);

    // Validate the result
    if (plaintnumber == decryptednumber) {
        printf("Test Passed: Decrypted number matches original plaintext.\n");
    } else {
        printf("Test Failed: Decrypted number does not match original plaintext.\n");
    }
    char plaintext[] = "Hel"; // Example string to encrypt
    char decrypted[128]; // Ensure sufficient space for decryption output
    unsigned long long ciphertext;

    printf("Plaintext String: %s\n", plaintext);

    // Encrypt the string
    ciphertext = rsa->encrypt(rsa, plaintext);
    printf("Ciphertext: %llu\n", ciphertext);

    // Decrypt the string
    if (rsa->decrypt(rsa, ciphertext, decrypted) == 0) {
        printf("Decrypted String: %s\n", decrypted);

        // Validate the result
        if (strcmp(plaintext, decrypted) == 0) {
            printf("Test Passed: Decrypted string matches original plaintext.\n");
        } else {
            printf("Test Failed: Decrypted string does not match original plaintext.\n");
        }
    } else {
        fprintf(stderr, "Error: Decryption failed.\n");
    }
    // Cleanup
    delete_rsa(rsa);
}

int main() {
    // Run numeric RSA test
    test_rsa_numbers();

    return 0;
}
