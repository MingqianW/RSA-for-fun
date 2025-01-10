#include <stdio.h>
#include <string.h>
#include "RSA.h"

int main() {
    // Initialize RSA
    RSA* rsa = new_rsa();
    gmp_printf("RSA Key Details: p=%Zd, q=%Zd, n=%Zd, phi=%Zd, e=%Zd, d=%Zd\n",
               rsa->p, rsa->q, rsa->n, rsa->phi, rsa->e, rsa->d);

    // Original plaintext message
    const char* plaintext = "We hold these truths to be self-evident, that all men are created equal, that they are endowed by their Creator with certain unalienable Rights, that among these are Life, Liberty and the pursuit of Happiness.";

    // Print original plaintext
    printf("Original plaintext: %s\n", plaintext);

    // Initialize ciphertext
    mpz_t ciphertext;
    mpz_init(ciphertext);

    // Encrypt the plaintext
    rsa->encrypt(rsa, plaintext, ciphertext);

    // Print the encrypted ciphertext
    gmp_printf("Encrypted ciphertext: %Zd\n", ciphertext);

    // Decrypt the ciphertext
    char decrypted_plaintext[102400];
    rsa->decrypt(rsa, ciphertext, decrypted_plaintext);

    // Print the decrypted plaintext
    printf("Decrypted plaintext: %s\n", decrypted_plaintext);

    // Verify if decryption matches the original plaintext
    if (strcmp(plaintext, decrypted_plaintext) == 0) {
        printf("Success: Decrypted text matches original plaintext.\n");
    } else {
        printf("Error: Decrypted text does not match original plaintext.\n");
    }

    // Clean up
    mpz_clear(ciphertext);
    delete_rsa(rsa);

    return 0;
}
