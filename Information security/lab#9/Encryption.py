from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import serialization, hashes

# all the file names are declared over here
PUBLIC_KEY_FILE = 'public.pem'
INPUT_FILE = 'original.txt'  # Your .txt or .docx file
ENCRYPTED_FILE = 'encrypted.bin'


try:
    # opening files and reading content
    with open(INPUT_FILE, 'rb') as f:
        file_content = f.read()
    print(f"Read {len(file_content)} bytes from {INPUT_FILE}.")

except FileNotFoundError:
    print(f"Error: Input file '{INPUT_FILE}' not found.")
    print("Please create this file with some text in it.")
    exit()

# loading public key saved in public.pem
with open(PUBLIC_KEY_FILE, 'rb') as f:
    public_key = serialization.load_pem_public_key(
        f.read()
    )

#encrypting using public key
try:
    encrypted_content = public_key.encrypt(
        file_content,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
except ValueError as e:
    print("\n--- ENCRYPTION FAILED ---")
    print(f"Error: {e}")
    print("This usually means your file is too large to be encrypted with RSA.")
    print("See the 'Important Note' below.\n")
    exit()

with open(ENCRYPTED_FILE, 'wb') as f:
    f.write(encrypted_content)

print(f"Encrypted content saved to {ENCRYPTED_FILE}.")
