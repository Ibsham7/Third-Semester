#1.	Write a method called desPlaintextBlock that takes the plaintext as input and splits it up into 64 bit blocks. 
# If the last block is less than 64 bits, pad it with 0s.
def desPlaintextBlock(plaintext):
    binary_string = ""
    
    for char in plaintext:
        ascii_value = ord(char)
        binary_char = format(ascii_value, '08b')  
        binary_string += binary_char

    block_size = 64  
    blocks = []

    for i in range(0, len(binary_string), block_size):
        block = binary_string[i:i + block_size]
        if len(block) < block_size:
            padding_needed = block_size - len(block)
            block += '0' * padding_needed

        blocks.append(block)
    return blocks


if __name__ == "__main__":
    test_text = "Hello World"
    result_blocks = desPlaintextBlock(test_text)

    print(f"Original text: '{test_text}'")
    print(f"Number of 64-bit blocks: {len(result_blocks)}")
    print("\nBlocks:")
    for i, block in enumerate(result_blocks, 1):
        print(f"Block {i}: {block} (length: {len(block)} bits)")