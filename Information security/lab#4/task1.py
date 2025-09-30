def desPlaintextBlock(plaintext):
    binary_string = ""
    
    for char in plaintext:
        # Get the ASCII value of the character and convert to 8-bit binary
        ascii_value = ord(char)
        binary_char = format(ascii_value, '08b')  # '08b' means 8-digit binary with leading zeros
        binary_string += binary_char

    

    # Step 2: Split the binary string into 64-bit blocks
    block_size = 64  # DES uses 64-bit blocks
    blocks = []

    # Process the binary string in chunks of 64 bits
    for i in range(0, len(binary_string), block_size):
        # Get the next 64-bit chunk
        block = binary_string[i:i + block_size]

        # Step 3: If this is the last block and it's shorter than 64 bits, pad with zeros
        if len(block) < block_size:
            # Calculate how many zeros we need to add
            padding_needed = block_size - len(block)
            # Add the required number of zeros at the end
            block += '0' * padding_needed

        # Add this completed block to our list
        blocks.append(block)

    # Step 4: Return the list of 64-bit blocks
    return blocks


# Example usage (you can test this when you run the program)
if __name__ == "__main__":
    # Test the function with some sample text
    test_text = "Hello World!"
    result_blocks = desPlaintextBlock(test_text)

    print(f"Original text: '{test_text}'")
    print(f"Number of 64-bit blocks: {len(result_blocks)}")
    print("\nBlocks:")
    for i, block in enumerate(result_blocks, 1):
        print(f"Block {i}: {block} (length: {len(block)} bits)")