def desFinalPermutation(block64):
    FP_TABLE = [
        58,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7
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
