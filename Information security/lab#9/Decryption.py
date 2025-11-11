from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import serialization, hashes

PRIVATE_KEY_FILE = 'private.pem'
ENCRYPTED_FILE = 'encrypted.bin'
DECRYPTED_FILE = 'decrypted.txt'

#here we will fetch private key for decryption as encryption was done using public key
with open(PRIVATE_KEY_FILE, 'rb') as f:
    private_key = serialization.load_pem_private_key(
        f.read(),
        password=None  # We didn't set a password on the key
    )


try:
    with open(ENCRYPTED_FILE, 'rb') as f:
        encrypted_content = f.read()
except FileNotFoundError:
    print(f"Error: Encrypted file '{ENCRYPTED_FILE}' not found.")
    exit()

# decrypting using private key
try:
    decrypted_content = private_key.decrypt(
        encrypted_content,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
except ValueError:
    print("Decryption failed. This could be due to a corrupt key or file.")
    exit()

with open(DECRYPTED_FILE, 'wb') as f:
    f.write(decrypted_content)

print(f"Decrypted content saved to {DECRYPTED_FILE}.")