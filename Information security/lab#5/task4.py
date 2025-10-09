def desFinalPermutation(block64):
    FP_TABLE = [
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
    ]

    permuted_block = [0] * 64
    for i, val in enumerate(FP_TABLE):
        permuted_block[i] = block64[val - 1]  

    return permuted_block

if __name__ == "__main__":
    block64 = [
        1,0,1,0,1,0,1,0,   0,1,0,1,0,1,0,1,
        1,1,0,0,1,1,0,0,   0,0,1,1,0,0,1,1,
        1,0,0,1,1,0,0,1,   0,1,1,0,1,0,1,0,
        1,1,1,0,0,0,1,0,   0,0,0,1,1,1,0,1
    ]
    
    print("Original 64-bit block:")
    print(''.join(map(str, block64)))

    permuted_block = desFinalPermutation(block64)
    print("\nAfter Final Permutation (64 bits):")
    print(''.join(map(str, permuted_block)))
