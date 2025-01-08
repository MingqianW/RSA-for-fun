import random
import sympy

class RSA:
    def __init__(self):
        self.p = self.generate_large_prime()
        self.q = self.generate_large_prime()
        self.n = self.p * self.q #public
        self.phi = (self.p - 1) * (self.q - 1)
        self.e = self.generate_coprime(self.phi) #public
        self.d = sympy.mod_inverse(self.e, self.phi) #private
        
    
    def generate_large_prime(self): 
        start = 10**100 #Because of the limit of runtime, we dont select larger prime here.
        end = 10**101 
        prime = sympy.randprime(start, end)
        return prime
    
    def gcd(self, a, b):
        while b != 0:
            a, b = b, a % b
        return a

    def generate_coprime(self, phi):
        e = random.randint(2, self.phi - 1)
        while self.gcd(e, phi) != 1:
            e = random.randint(2, self.phi - 1)
        return e

    def encrypt(self, plaintext):
        plaintext_int = [ord(char) for char in plaintext]
        ciphertext = [pow(char, self.e, self.n) for char in plaintext_int]
        return ciphertext

    def decrypt(self, ciphertext):
        plaintext_int = [pow(char, self.d, self.n) for char in ciphertext]
        plaintext = ''.join([chr(char) for char in plaintext_int])
        return plaintext

rsa = RSA()

message = "Hello, RSA!"

# Encrypt the message
encrypted_msg = rsa.encrypt(message)
print(f"Encrypted message: {encrypted_msg}")

# Decrypt the message
decrypted_msg = rsa.decrypt(encrypted_msg)
print(f"Decrypted message: {decrypted_msg}")