from Crypto.Cipher import AES

HEX_ALPHABET = "0123456789abcdef"

def caesar_hex_decrypt(hex_key, shift):
    res = ''
    for ch in hex_key:
        val = int(ch, 16)
        res += format((val - shift) % 16, 'x')
    return res

def decrypt_aes_256_ecb_hex(ciphertext_hex, key_hex):
    key = bytes.fromhex(key_hex)
    if len(key) != 32:
        raise ValueError("Bad key length")
    data = bytes.fromhex(ciphertext_hex)
    cipher = AES.new(key, AES.MODE_ECB)
    out = cipher.decrypt(data)
    pad = out[-1]
    if 1 <= pad <= AES.block_size and out.endswith(bytes([pad]) * pad):
        out = out[:-pad]
    return out.decode('utf-8', errors='replace')

encrypted_key = "fb61269a71aa01ff649588b23dcc3cbd2fdf2371520b7b42abd26279bdba8e06"
ROLL_NO = "564c6c01b88abad82cb584dc0d99aaab"
NAME = "d50ebee9e7630ed5f0d54aa3fc44f7e7"

# try all Caesar shifts
for s in range(16):
    k = caesar_hex_decrypt(encrypted_key, s)
    if len(k) == 64:
        try:
            name = decrypt_aes_256_ecb_hex(NAME, k)
            roll = decrypt_aes_256_ecb_hex(ROLL_NO, k)
            print(f"\nShift {s} Key: {k}")
            print("Name:", name)
            print("Roll:", roll)
        except Exception:
            pass

# also decrypt using actual key
print("\n--- Using Actual Key ---")
print("Name:", decrypt_aes_256_ecb_hex(NAME, encrypted_key))
print("Roll:", decrypt_aes_256_ecb_hex(ROLL_NO, encrypted_key))
