from task1 import desPlaintextBlock
def desInitialPermutation(block):
    #  IP table as given in lab manual
    IP = [
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17,  9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    ]
    permuted_block = ""
    for position in IP:
        permuted_block += block[position - 1]

    return permuted_block


if __name__ == "__main__":
    UserInput = input("Enter the plaintext: ")
    blocks = desPlaintextBlock(UserInput)

    for i, block in enumerate(blocks, 1):
        print(f"Block {i}: {block}")
        permuted_block = desInitialPermutation(block)
        print(f"Permuted Block {i}: {permuted_block}")
