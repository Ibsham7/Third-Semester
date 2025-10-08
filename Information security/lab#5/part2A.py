from task1_lab4 import desPlaintextBlock
from task2_lab4 import desInitialPermutation
from task1 import desExpansionPermutation
from task2 import getSubBoxes
from task3 import desRoundPermutation
from task4 import desFinalPermutation
from generateRoundkeys import generateRoundKeys


def desEncryption(plaintext, key64):
    # this function is used to generate Round keys for encryption
    round_keys = generateRoundKeys(key64)

    blocks = desPlaintextBlock(plaintext)
    encrypted_blocks = []
    #all the functions made previously are being used here
    for block in blocks:
        permuted_block = [int(b) for b in desInitialPermutation(block)]
        L = permuted_block[:32]
        R = permuted_block[32:]
        for i in range(16):
            expanded_R = [int(b) for b in desExpansionPermutation(R)]
            xor_result = [expanded_R[j] ^ int(round_keys[i][j]) for j in range(48)]
            sbox_output = [int(b) for b in getSubBoxes(xor_result)]
            round_output = [int(b) for b in desRoundPermutation(sbox_output)]
            new_R = [int(L[j]) ^ round_output[j] for j in range(32)]
            L = R
            R = new_R
        combined_block = R + L

        cipher_block = [int(b) for b in desFinalPermutation(combined_block)]
        encrypted_blocks.append(cipher_block)

    return encrypted_blocks



if __name__ == "__main__":
    plaintext = input("Enter the plaintext: ")

    # an example key is being used here and it can be change to any 64 bit key as desired
    key64 = [0,0,1,1,0,1,0,1,  1,0,1,0,0,1,1,0,
             1,1,0,0,1,0,1,1,  0,1,0,1,1,1,0,1,
             1,0,1,1,0,0,1,0,  0,1,1,0,1,1,0,0,
             1,0,0,1,0,1,1,1,  1,1,0,1,0,0,1,0]

    encrypted_blocks = desEncryption(plaintext, key64)

    print("\nEncrypted Blocks:")
    for i, block in enumerate(encrypted_blocks, 1):
        print(f"Block {i}: {''.join(str(bit) for bit in block)}")
