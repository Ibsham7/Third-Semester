def remove_duplicates(keyword):
    result = ""
    for ch in keyword:
        if ch not in result:
            result += ch
    return result

def find_position(matrix, letter):
    for r in range(5):
        for c in range(5):
            if matrix[r][c] == letter:
                return r, c
    return None

def create_digraph(plainText):
    digraphs = []
    for char in plainText:
        if char.isalpha() == False:
            continue

        if len(digraphs) == 0 or len(digraphs[-1]) == 2:
            digraphs.append(char)
        else:
            if digraphs[-1][0] == char:
                digraphs[-1] +='X'
                digraphs.append(char)
            else:
                digraphs[-1] += char

    if len(digraphs[-1]) == 1:
        digraphs[-1] += 'X'

    print("digraphs: ", digraphs)

    return digraphs



keyword = input("Enter a keyword: ")
keyword = keyword.upper()

# replacing J with I in keyword
keyword = keyword.replace('J', 'I')

keyword = keyword + 'ABCDEFGHIKLMNOPQRSTUVWXYZ'

keyword = remove_duplicates(keyword)




matrix = [list(keyword[i:i+5]) for i in range(0, 25, 5)]
print("Matrix: ")
for row in matrix:
    print(row)


plainText = input("Enter plain text: ")
plainText = plainText.upper()
plainText = plainText.replace('J', 'I')
plainText = plainText.replace(" ", "") 

digraphs = create_digraph(plainText)
cipherText = ""

for digraph in digraphs:
    row1 , col1 =  find_position(matrix, digraph[0])
    row2 , col2 =  find_position(matrix, digraph[1])
    if row1 == row2:
        cipherText += matrix[row1][(col1 + 1) % 5]
        cipherText += matrix[row2][(col2 + 1) % 5]
    elif col1 == col2:
        cipherText += matrix[(row1 + 1) % 5][col1]
        cipherText += matrix[(row2 + 1) % 5][col2]
    else:
        cipherText += matrix[row1][col2]
        cipherText += matrix[row2][col1]

print("Cipher Text: ", cipherText)

decipher_digraph = create_digraph(cipherText)
decipherText = ""
for digraph in decipher_digraph:
    row1 , col1 =  find_position(matrix, digraph[0])
    row2 , col2 =  find_position(matrix, digraph[1])
    if row1 == row2:
        decipherText += matrix[row1][(col1 - 1) % 5]
        decipherText += matrix[row2][(col2 - 1) % 5]
    elif col1 == col2:
        decipherText += matrix[(row1 - 1) % 5][col1]
        decipherText += matrix[(row2 - 1) % 5][col2]
    else:
        decipherText += matrix[row1][col2]
        decipherText += matrix[row2][col1]

print("Decipher Text: ", decipherText)

