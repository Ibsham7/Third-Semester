def calculate_word_level_distance(reference_words, hypothesis_words):
    len_ref = len(reference_words)
    len_hyp = len(hypothesis_words)
    distance_matrix = [[0] * (len_hyp + 1) for _ in range(len_ref + 1)]

    for i in range(len_ref + 1):
        distance_matrix[i][0] = i
    for j in range(len_hyp + 1):
        distance_matrix[0][j] = j

    for i in range(1, len_ref + 1):
        for j in range(1, len_hyp + 1):
            if reference_words[i - 1] == hypothesis_words[j - 1]:
                distance_matrix[i][j] = distance_matrix[i - 1][j - 1]
            else:
                distance_matrix[i][j] = 1 + min(
                    distance_matrix[i - 1][j],      
                    distance_matrix[i][j - 1],      
                    distance_matrix[i - 1][j - 1]   
                )

    row, col = len_ref, len_hyp
    deletions = insertions = substitutions = 0

    while row > 0 and col > 0:
        if reference_words[row - 1] == hypothesis_words[col - 1]:
            row -= 1
            col -= 1
        elif distance_matrix[row][col] == distance_matrix[row - 1][col - 1] + 1:
            substitutions += 1
            row -= 1
            col -= 1
        elif distance_matrix[row][col] == distance_matrix[row - 1][col] + 1:
            deletions += 1
            row -= 1
        elif distance_matrix[row][col] == distance_matrix[row][col - 1] + 1:
            insertions += 1
            col -= 1

    while row > 0:
        deletions += 1
        row -= 1
    while col > 0:
        insertions += 1
        col -= 1

    return distance_matrix[len_ref][len_hyp], insertions, deletions, substitutions


with open("reference.txt", "r", encoding="utf-8") as f:
    reference_line = f.readline().strip()

with open("hypothesis.txt", "r", encoding="utf-8") as f:
    hypothesis_line = f.readline().strip()

reference_words = reference_line.split()
hypothesis_words = hypothesis_line.split()

distance, insertions, deletions, substitutions = calculate_word_level_distance(reference_words, hypothesis_words)

with open("result.txt", "w", encoding="utf-8") as f:
    f.write(f"Levenshtein distance is {distance}\n")
    f.write(f"Insertions {insertions}\n\n")
    f.write(f"Deletions {deletions}\n\n")
    f.write(f"Substitutions {substitutions}\n\n")
