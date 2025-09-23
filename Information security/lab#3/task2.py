from task1_B import rail_fence_decrypt   

def rail_fence_brute_force(ciphertext):
    print(f"\n[*] Brute force results for: {ciphertext}\n")

    for key in range(2, len(ciphertext) + 1):
        n = len(ciphertext)
        # fill in the zig zag positions in matrix
        matrix = [[' ' for _ in range(n)] for _ in range(key)]
        row, direction = 0, 1
        for col in range(n):
            matrix[row][col] = '*'
            if row == 0:
                direction = 1
            elif row == key - 1:
                direction = -1
            row += direction

        # fillinng the matrix with ciphertext
        idx = 0
        for r in range(key):
            for c in range(n):
                if matrix[r][c] == '*' and idx < n:
                    matrix[r][c] = ciphertext[idx]
                    idx += 1

        # using decryption funciton in task1_B.py to decrypt
        try:
            possible_plain = rail_fence_decrypt(ciphertext, key)
            print(f"Key {key:2d} -> {possible_plain}")
            print("Matrix:")
            for r in matrix:
                print(" ".join(r))
            print()
        except Exception as e:
            print(f"Key {key:2d} -> Error: {e}\n")


if __name__ == "__main__":
    # Test Case 1
    rail_fence_brute_force("HOLELWRDLOX")

    # Test Case 2
    rail_fence_brute_force("AAXTKTNXTCDWXAAX")

    # Test Case 3
    rail_fence_brute_force("CYTGAHRPORPY")