# PC-1 permutation table (64 -> 56 bits)
PC1 = [
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
]

# PC-2 permutation table (56 -> 48 bits)
PC2 = [
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
]

# Number of left shifts for each round
SHIFTS = [1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1]

def permute(block, table):
    """General permutation helper: takes a list of bits and a table"""
    return [block[i - 1] for i in table]

def left_shift(bits, n):
    """Left rotate the list 'bits' by 'n' positions"""
    return bits[n:] + bits[:n]

def generateRoundKeys(key64):
    """
    Generate 16 round keys from a 64-bit key (as a list of bits).
    Returns a list of 16 keys, each 48 bits.
    """
    # Step 1: Apply PC-1 to get 56-bit key
    key56 = permute(key64, PC1)

    # Step 2: Split into C and D halves (28 bits each)
    C = key56[:28]
    D = key56[28:]

    round_keys = []

    # Step 3: 16 rounds
    for i in range(16):
        # Left shift C and D
        C = left_shift(C, SHIFTS[i])
        D = left_shift(D, SHIFTS[i])

        # Combine halves
        combined = C + D

        # Step 4: Apply PC-2 to get 48-bit round key
        round_key = permute(combined, PC2)
        round_keys.append(round_key)

    return round_keys
