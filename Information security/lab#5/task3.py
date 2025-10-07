
def desRoundPermutation(block32):
    RP = [16,7,20,21,29,12,28,17, 
            1,15,23,26,5,18,31,10, 
            2,8,24,14,32,27,3,9, 
            19,13,30,6,22,11,4,25]
    block32New = [0] * 32
    i = 0
    for val in RP:
        block32New[i] = block32[val - 1]
        i += 1 
    return block32New

if __name__ == "__main__":
    block32 = [
        1,0,1,0,  1,1,0,1,  0,1,0,0,  1,0,1,1,
        0,1,1,0,  1,0,0,1,  1,1,0,0,  0,1,0,1
    ]
    print("Original 32-bit block:")
    print(''.join(map(str, block32)))

    permuted_block = desRoundPermutation(block32)
    print("\nPermuted 32-bit block:")
    print(''.join(map(str, permuted_block)))