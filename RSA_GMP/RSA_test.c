#include "RSA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Initialize RSA structure
    RSA *rsa = new_rsa();

    // Test 1: String Encryption and Decryption
    printf("\n--- String Encryption and Decryption ---\n");
    const char *original_message = "Hello, RSA!";
    char decrypted_message[1024];

    mpz_t ciphertext;
    mpz_init(ciphertext);
    // Encrypt the string
    rsa->encrypt(rsa, original_message, ciphertext);

    // Decrypt the ciphertext
    rsa->decrypt(rsa, ciphertext, decrypted_message);

    // Print the decrypted message
    printf("Decrypted message: %s\n", decrypted_message);

    // Verify correctness
    if (strcmp(original_message, decrypted_message) == 0) {
        printf("String encryption/decryption test passed!\n");
    } else {
        printf("String encryption/decryption test failed!\n");
    }

    mpz_clear(ciphertext);

    // Test 2: Number Encryption and Decryption
    printf("\n--- Number Encryption and Decryption ---\n");
    mpz_t original_number, encrypted_number, decrypted_number;

    mpz_init_set_ui(original_number, 123456789); // Original number
    mpz_init(encrypted_number);
    mpz_init(decrypted_number);

    // Encrypt the number
    rsa->encrypt_num(rsa, original_number, encrypted_number);

    // Print the encrypted number
    gmp_printf("Encrypted number: %Zd\n", encrypted_number);

    // Decrypt the number
    rsa->decrypt_num(rsa, encrypted_number, decrypted_number);

    // Print the decrypted number
    gmp_printf("Decrypted number: %Zd\n", decrypted_number);

    // Verify correctness
    if (mpz_cmp(original_number, decrypted_number) == 0) {
        printf("Number encryption/decryption test passed!\n");
    } else {
        printf("Number encryption/decryption test failed!\n");
    }

    // Clean up
    mpz_clear(original_number);
    mpz_clear(encrypted_number);
    mpz_clear(decrypted_number);

    delete_rsa(rsa);

    return 0;
}
