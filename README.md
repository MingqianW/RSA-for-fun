# RSA-for-fun

This project contains three implementations of the RSA encryption algorithm:
1. **Pure C Implementation**: Operates on 32-bit integers for simplicity and portability.
2. **C with GMP (GNU Multiple Precision)**: Uses the GMP library for handling large integers (1024-bit or more).
3. **Python impelmention**: Use sympy to implement RSA (about 333 bits).



---

## Features
### Common Features
- RSA Key Generation:
  - Generates two large primes (\( p \) and \( q \)) and computes \( n = p \times q \).
  - Derives the public key \( (e, n) \) and private key \( (d, n) \).
- Encryption/Decryption:
  - Text encryption and decryption.
  - Direct numerical encryption and decryption.

### Differences Between Versions
| Feature               | Pure C Version                    | C with GMP Version                     |
|-----------------------|------------------------------------|----------------------------------------|
| **Prime Size**        | Fixed at 32 bits (small primes).  | Configurable (default: 1024-bit or larger).      |
| **Precision**         | Limited by `unsigned long long`.  | Should be unlimited via GMP.           |
| **Performance**       | Faster for small primes and short text.| Scalable for large primes and longer texts.|

---

### Todo
- Make RSA CPA secure.
- Add make file for easier compilation.
- Apply RSA for text files.
 
