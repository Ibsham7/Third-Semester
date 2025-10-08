# des_decrypt_helper.py
from task1_lab4 import desPlaintextBlock        # used only for tests if needed
from task2_lab4 import desInitialPermutation
from task1 import desExpansionPermutation
from task2 import getSubBoxes
from task3 import desRoundPermutation
from task4 import desFinalPermutation
from generateRoundkeys import generateRoundKeys
# If your generateRoundKeys function has a different name, adjust import accordingly.

# ------------------ Utilities ------------------
def normalize_encrypted_blocks(enc_output):
    """
    Accepts either:
      - list of lists of ints [[0,1,0,...], ...]
      - list of 64-bit strings ['010101...', ...]
      - a single concatenated bitstring '010101...'
    Returns: list of blocks where each block is a list of 64 ints.
    """
    if isinstance(enc_output, list):
        normalized = []
        for blk in enc_output:
            if isinstance(blk, str):
                if len(blk) != 64:
                    raise ValueError("Block string length not 64 bits")
                normalized.append([int(ch) for ch in blk])
            elif isinstance(blk, list):
                if len(blk) != 64:
                    raise ValueError("Block list length not 64 bits")
                normalized.append([int(x) for x in blk])
            else:
                raise TypeError("Unsupported block type in list")
        return normalized
    elif isinstance(enc_output, str):
        # single long bitstring -> split into 64-bit blocks
        if len(enc_output) % 64 != 0:
            raise ValueError("Bitstring length not multiple of 64")
        return [[int(ch) for ch in enc_output[i:i+64]] for i in range(0, len(enc_output), 64)]
    else:
        raise TypeError("Unsupported encrypted output type")

def bits_to_text(bit_input):
    """
    Accepts either a list of ints (bits) or a bitstring and converts to ASCII text.
    Strips trailing NULL bytes '\x00' which commonly come from block padding.
    """
    if isinstance(bit_input, list):
        bitstring = ''.join(str(b) for b in bit_input)
    else:
        bitstring = bit_input
    chars = []
    for i in range(0, len(bitstring), 8):
        byte = bitstring[i:i+8]
        chars.append(chr(int(byte, 2)))
    return ''.join(chars).rstrip('\x00')  # strip common padding nulls

# ------------------ DES Decryption (compatible with your encryption) ------------------
def desDecryption_from_blocks(encrypted_blocks, key64):
    """
    encrypted_blocks: list of blocks (each block is list of 64 ints OR 64-char string OR single concatenated string).
    key64: list of 64 ints (the same format used in your generateRoundKeys call)
    Returns: (decrypted_blocks_as_bitlists, decrypted_text)
    """
    # Normalize input
    blocks = normalize_encrypted_blocks(encrypted_blocks)

    # Generate and reverse round keys
    round_keys = generateRoundKeys(key64)        # list of 16 keys, each 48 either ints/strings
    round_keys_rev = list(reversed(round_keys))

    decrypted_blocks = []

    for block in blocks:
        # Step 1: Initial Permutation (make sure we get ints)
        permuted = [int(b) for b in desInitialPermutation(block)]  # returns 64 bits

        # Step 2: Split
        L = permuted[:32]
        R = permuted[32:]

        # Step 3: 16 rounds using reversed keys
        for i in range(16):
            # expansion (32 -> 48)
            expanded_R = [int(b) for b in desExpansionPermutation(R)]

            # XOR with round key (ensure key bits are ints)
            key_i = [int(x) for x in round_keys_rev[i]]
            xor_result = [expanded_R[j] ^ key_i[j] for j in range(48)]

            # S-box substitution (48 -> 32)
            sbox_out = [int(b) for b in getSubBoxes(xor_result)]

            # P-box / round permutation (32 -> 32)
            round_out = [int(b) for b in desRoundPermutation(sbox_out)]

            # Feistel XOR with left
            new_R = [L[j] ^ round_out[j] for j in range(32)]

            # swap for next round
            L = R
            R = new_R

        # After 16 rounds combine R and L (note the swap)
        combined = R + L

        # Final permutation
        plain_block = [int(b) for b in desFinalPermutation(combined)]
        decrypted_blocks.append(plain_block)

    # Flatten blocks to a single bitstring and convert to text
    full_bits = ''.join(''.join(str(b) for b in blk) for blk in decrypted_blocks)
    plaintext = bits_to_text(full_bits)
    return decrypted_blocks, plaintext

# ------------------ Debug helper to compare encrypt->decrypt ------------------
def debug_compare(desEncryption_func, plaintext, key64):
    """
    Calls your desEncryption function, then decrypts the result using the helper,
    and prints checks to help find mismatch points.
    desEncryption_func must return blocks as either list-of-lists or list-of-strings.
    """
    print("Encrypting...")
    encrypted_blocks = desEncryption_func(plaintext, key64)

    # Print first encrypted block (as bitstring)
    print("Encrypted blocks (first block):")
    print(''.join(str(b) for b in (encrypted_blocks[0] if isinstance(encrypted_blocks[0], list) else encrypted_blocks[0])))

    print("Now decrypting...")
    decrypted_blocks, decrypted_text = desDecryption_from_blocks(encrypted_blocks, key64)

    print("Decrypted text:", repr(decrypted_text))
    # Also show decrypted bits of first block
    print("Decrypted first block bits:", ''.join(str(b) for b in decrypted_blocks[0]))

    return encrypted_blocks, decrypted_blocks, decrypted_text

# ------------------ Example usage ------------------
if __name__ == "__main__":
    # Example key64 format (list of 64 ints) - replace with your key
    key64 = [0,0,1,1,0,1,0,1,  1,0,1,0,0,1,1,0,
             1,1,0,0,1,0,1,1,  0,1,0,1,1,1,0,1,
             1,0,1,1,0,0,1,0,  0,1,1,0,1,1,0,0,
             1,0,0,1,0,1,1,1,  1,1,0,1,0,0,1,0]

    # If you have a desEncryption() function in the same namespace, you can test:
    try:
        from part2A import desEncryption   # adjust if your encryption function lives elsewhere
        encrypted_blocks, decrypted_blocks, decrypted_text = debug_compare(desEncryption, "hello world", key64)
    except Exception as e:
        print("Skipping auto-debug run (couldn't import desEncryption). Error:", e)
        # You can manually call desDecryption_from_blocks(...) with your encrypted_blocks and key.
