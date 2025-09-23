def rail_fence_decrypt(ciphertext, key):
    # generating matrix for cypher
    n = len(ciphertext)
    matrix = [['\n' for _ in range(n)] for _ in range(key)]
    row, direction = 0, 1
    for col in range(n):
        matrix[row][col] = '*'
        if row == 0:
            direction = 1
        elif row == key - 1:
            direction = -1
        row += direction
    index = 0
    # filling matrix
    for r in range(key):
        for c in range(n):
            if matrix[r][c] == '*' and index < n:
                matrix[r][c] = ciphertext[index]
                index += 1

    result = []
    # reading the matrix in zig zag format
    row, direction = 0, 1
    for col in range(n):
        result.append(matrix[row][col])
        if row == 0:
            direction = 1
        elif row == key - 1:
            direction = -1
        row += direction

    return "".join(result).replace("X", "")   


if __name__ == "__main__":
    ciphertext = input("Enter the ciphertext: ").replace(" ", "").upper()
    key = int(input("Enter the key (number of rails): "))

    plaintext = rail_fence_decrypt(ciphertext, key)
    print("\nDecrypted text:", plaintext)