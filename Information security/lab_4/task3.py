from task1 import desPlaintextBlock
from task2 import desInitialPermutation

def desFinalPermutation(block):
    IP = [40, 8, 48, 16, 56, 24, 64, 32,
          39, 7, 47, 15, 55, 23, 63, 31,
          38, 6, 46, 14, 54, 22, 62, 30,
          37, 5, 45, 13, 53, 21, 61, 29,
          36, 4, 44, 12, 52, 20, 60, 28,
          35, 3, 43, 11, 51, 19, 59, 27,
          34, 2, 42, 10, 50, 18, 58, 26,
          33, 1, 41, 9, 49, 17, 57, 25
          ]

    permuted_block = ""
    for position in IP:
        permuted_block += block[position - 1]
    return permuted_block

if __name__ == "__main__":
    UserInput = input("Enter the plaintext: ")
    blocks = desPlaintextBlock(UserInput)

    for i, block in enumerate(blocks, 1):
        print(f"Initial Block {i}: {block}")
        permuted_block = desInitialPermutation(block)
        print(f"Permuted Block {i}: {permuted_block}")
        final_permuted_block = desFinalPermutation(permuted_block)
        print(f"Final Permuted Block {i}: {final_permuted_block}")