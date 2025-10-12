import math

def encryption(key , plainText):
    keyNum = []
    for alpha in key:
        if 'A' <= alpha <= 'Z':
            keyNum.append(ord(alpha) - ord('A') + 1)
    sortedkey = sorted(keyNum)


    rows = len(key)
    columns = math.ceil(len(plainText) / rows)

    # creating rows x columns matrix 
    transpositionMatrix = [['_'] * columns for _ in range(rows)]

    # filling the matrix rows down the coloumn as done in slides
    for i, ch in enumerate(plainText):
        row = i % rows
        col = i // rows
        transpositionMatrix[row][col] = ch

    cipherText = ''

    # this logic makes sure that cipher text is according to the sorted key
    for i in range(rows):
        index = keyNum.index(sortedkey[i])
        for j in range(columns):
            cipherText += transpositionMatrix[index][j]
    return cipherText

def decryption(key, cipherText):
    keyNum = []
    for alpha in key:
        if 'A' <= alpha <= 'Z':
            keyNum.append(ord(alpha) - ord('A') + 1)
    sortedkey = sorted(keyNum)

    rows = len(key)
    columns = math.ceil(len(cipherText) / rows)

    transpositionMatrix = [['_'] * columns for _ in range(rows)]

    # in order for decrytion to work we have to fill it coloumn wise
    k = 0
    for i in range(rows):
        index = keyNum.index(sortedkey[i])
        for j in range(columns):
            if k < len(cipherText):
                transpositionMatrix[index][j] = cipherText[k]
                k += 1
    print(transpositionMatrix)
    # iterate the matrix to get plaintext
    plainText = ''
    for j in range(columns):
        for i in range(rows):
            plainText += transpositionMatrix[i][j]
    
    return plainText



if __name__ == "__main__":
    key = "GREAT"
    #i have hardcoded the key as per required in assigment but if 
    # input then make sure key is captalize before for next logic to work
    key = key.upper()
    plainText = input("Enter plain text :")   
    cipherText = encryption(key , plainText)
    print("cipher Text :" + cipherText)
    decryptedPlainText = decryption(key , cipherText)
    print("decrypted text :" + decryptedPlainText)