from Crypto.Cipher import AES # requires pip install pycryptodome

HEX_ALPHABET = "0123456789abcdef"


def generate_caesar_shift_keys(base_key_hex: str):  # task 2

    base = base_key_hex.lower() # shifting to lower
    table = {c: i for i, c in enumerate(HEX_ALPHABET)} # dictionary for index and corresponding hex digit
    out = [] # array that holds the 15 shifted keys

    for shift in range(1, 16):
        shifted_chars = []
        for ch in base:
            if ch in table: # validation
                shifted_chars.append(HEX_ALPHABET[(table[ch] + shift) % 16]) # mod 16 to ensure that range stays in hex range
            else:
                shifted_chars.append(ch)   # keep non-hex chars as-is 
        out.append(''.join(shifted_chars))  # appending tehe new shifted key
    return out




def decrypt_aes_256_ecb_hex(ciphertext_hex: str, key_hex: str):  # Task 4
    # convert into raw bytes —> AES requires binary key input.
    key = bytes.fromhex(key_hex)
    
    # validation
    if len(key) != 32:
        raise ValueError("Key must be 32 bytes (64 hex characters) for AES-256.")  # validation

    cipher_bytes = bytes.fromhex(ciphertext_hex)

    # new AES cipher object in ECB mode using the key.
    cipher = AES.new(key, AES.MODE_ECB)

    # decrypting the ciphertext bytes to get the padded plaintext bytes.
    plaintext_padded = cipher.decrypt(cipher_bytes)

    # remove padding if it exists 
    if plaintext_padded:  # if not empty
        # the value of the last byte represents how many padding bytes were added.
        pad = plaintext_padded[-1]
        # validate padding: if it's within block size and all last bytes match the pad value.
        if 1 <= pad <= AES.block_size and plaintext_padded.endswith(bytes([pad]) * pad):
            # remove the padding bytes from the end of plaintext.
            plaintext = plaintext_padded[:-pad]
        else:
            # ff padding is invalid, keep the data as-is (fallback).
            plaintext = plaintext_padded
    else:
        # if decryption returned nothing (edge case), keep as empty.
        plaintext = plaintext_padded

    # decode the plaintext bytes into a readable string (UTF-8).
    # 'errors="replace"' ensures invalid bytes don't crash the program.
    return plaintext.decode('utf-8', errors='replace')




MY_KEY = "0a9a0115a34a0699a9f25757754b675c327b6eecab5eb37332a1211fc77201c5"
ROLL_NO = "73b8d149125219a11b70a3f01408fa99"
NAME = "5f82fa58e6dc740efeddde319cbc834b"
shifted_keys = generate_caesar_shift_keys(MY_KEY)

print()
print(f"ENCRYPTED NAME: {NAME}")
print(f"ENCRYPTED ROLL NO: {ROLL_NO}")
print()

for key in shifted_keys:

    print(f"Using KEY: {key}")
    print(decrypt_aes_256_ecb_hex(NAME, key))
    print(decrypt_aes_256_ecb_hex(ROLL_NO, key))
    print()