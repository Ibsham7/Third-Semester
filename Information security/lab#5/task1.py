def desExpansionPermutation(block32):

    EP_TABLE = [
        32,  1,  2,  3,  4,  5,
         4,  5,  6,  7,  8,  9,
         8,  9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32,  1
    ]
    block48 = [0] * 48
    i = 0
    for val in EP_TABLE:
        block48[i] = block32[val - 1]
        i += 1 
    
    return block48


if __name__ == "__main__":
    block32 = [1,0,1,1,1,1,0,0,1,0,1,0,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,1]
    block48 = desExpansionPermutation(block32)
    #took help form internet for formating the output of code
    print("Original 32-bit block:")
    print("Idx: " + " ".join(f"{i+1:02}" for i in range(32)))
    print("Val: " + " ".join(f"{bit:02}" for bit in block32))

    print("\nExpanded 48-bit block:")
    print("Idx: " + " ".join(f"{i+1:02}" for i in range(48)))
    print("Val: " + " ".join(f"{bit:02}" for bit in block48))


