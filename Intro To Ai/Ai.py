def calculate_distance(first_string, second_string):
    length_first = len(first_string)
    length_second = len(second_string)
    distance_matrix = [[0] * (length_second + 1) for _ in range(length_first + 1)]

    for i in range(length_first + 1):
        distance_matrix[i][0] = i
    for j in range(length_second + 1):
        distance_matrix[0][j] = j

    for i in range(1, length_first + 1):
        for j in range(1, length_second + 1):
            if first_string[i - 1] == second_string[j - 1]:
                distance_matrix[i][j] = distance_matrix[i - 1][j - 1]
            else:
                distance_matrix[i][j] = 1 + min(
                    distance_matrix[i - 1][j],
                    distance_matrix[i][j - 1],
                    distance_matrix[i - 1][j - 1]
                )

    row, col = length_first, length_second
    deletion_count = insertion_count = substitution_count = 0

    while row > 0 and col > 0:
        if first_string[row - 1] == second_string[col - 1]:
            row -= 1
            col -= 1
        elif distance_matrix[row][col] == distance_matrix[row - 1][col - 1] + 1:
            substitution_count += 1
            row -= 1
            col -= 1
        elif distance_matrix[row][col] == distance_matrix[row - 1][col] + 1:
            deletion_count += 1
            row -= 1
        elif distance_matrix[row][col] == distance_matrix[row][col - 1] + 1:
            insertion_count += 1
            col -= 1

    while row > 0:
        deletion_count += 1
        row -= 1
    while col > 0:
        insertion_count += 1
        col -= 1

    return distance_matrix[length_first][length_second], deletion_count, insertion_count, substitution_count, distance_matrix


string_one = "kitten"
string_two = "sitting"

edit_distance, deletions, insertions, substitutions, final_matrix = calculate_distance(string_one, string_two)

print("string 1 is :", string_one)
print("string 2 is :", string_two)
print()
for row in final_matrix:
    print(row)

print("\nTotal Number of Deletions are :", deletions)
print("Total Number of Substitutions are :", substitutions)
print("Total Number of Insertions are :", insertions)
print("\nLevenshtein distance is :", edit_distance)
