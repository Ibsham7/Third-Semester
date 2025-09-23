def rail_fence_encrypt(text, key):
    # foramt the plaintext
    plainText = text.replace(" ", "").upper()

    # add padding if necessary
    length = 2 * key - 2 if key > 1 else 1
    rem = len(plainText) % length
    if rem != 0:
        plainText += "X" * (length - rem)

    # Step 3: create matirx
    matrix = ["" for _ in range(key)]

    # Step 4: zigzag writing
    row, direction = 0, 1
    for ch in plainText:
        matrix[row] += ch

        if row == 0:
            direction = 1
        elif row == key - 1:
            direction = -1

        row += direction

    return "".join(matrix)



if __name__ == "__main__":
    plaintext = input("Enter the plaintext: ")
    key = int(input("Enter the key (number): "))

    ciphertext = rail_fence_encrypt(plaintext, key)
    print("\nCiphertext:", ciphertext)