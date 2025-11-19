import matplotlib.pyplot as plt
import matplotlib.patches as patches

def N_Queens_fc(n):
    board = [-1] * n
    solutionArray = []

    available_cols_per_row = [set(range(n)) for _ in range(n)]

    def backTracking(row):
        if row == n:
            solutionArray.append(board.copy())
            return

        for col in list(available_cols_per_row[row]):
            board[row] = col
            
            removed_info = [] 
            is_valid_placement = True
            
            for next_row in range(row + 1, n):
                cols_to_remove = set()
                
                #Column Conflict
                cols_to_remove.add(col) 

                #Diagonal Conflicts
                diff = next_row - row
                down_left = col - diff
                down_right = col + diff
                
                if 0 <= down_left < n:
                    cols_to_remove.add(down_left)
                if 0 <= down_right < n:
                    cols_to_remove.add(down_right)
                
                # Pruning
                removed = available_cols_per_row[next_row].intersection(cols_to_remove)
                
                if removed:
                    available_cols_per_row[next_row] -= removed
                    removed_info.append((next_row, removed))
                    
                if not available_cols_per_row[next_row]:
                    is_valid_placement = False
                    break 

            if is_valid_placement:
                backTracking(row + 1)

            board[row] = -1

            # 2. Restore the available columns in the future rows
            for next_row, restored_cols in removed_info:
                available_cols_per_row[next_row].update(restored_cols)

    backTracking(0)
    return solutionArray


def printBoard(board , N):
    twoDimensionBoard = [["_" for _ in range(N)] for _ in range(N)]
    for row in range(N):
        twoDimensionBoard[row][board[row]] = "Q"

    for row in twoDimensionBoard:
        print(" ".join(row))

def plotBoard(board, N, solution_num):
    fig, ax = plt.subplots(figsize=(8, 8))
    
    # Draw the chessboard
    for row in range(N):
        for col in range(N):
            color = 'white' if (row + col) % 2 == 0 else 'lightgray'
            square = patches.Rectangle((col, N - 1 - row), 1, 1, 
                                         linewidth=1, edgecolor='black', 
                                         facecolor=color)
            ax.add_patch(square)
    
    for row in range(N):
        col = board[row]
        circle = patches.Circle((col + 0.5, N - 1 - row + 0.5), 0.35, 
                                 color='red', zorder=10)
        ax.add_patch(circle)
        ax.text(col + 0.5, N - 1 - row + 0.5, 'Q', 
                fontsize=20, fontweight='bold', color='white',
                ha='center', va='center', zorder=11)
    
    ax.set_xlim(0, N)
    ax.set_ylim(0, N)
    ax.set_aspect('equal')
    ax.axis('off')
    ax.set_title(f'N-Queens Solution #{solution_num} (N={N})', 
                 fontsize=16, fontweight='bold', pad=20)
    
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":

    N = int(input("Enter N for N-Queens problem:"))
    solutions = N_Queens_fc(N) 

    print(f"\nTotal solutions found: {len(solutions)}\n")
    print("Solution array for forward checking problem:")
    
    for sol, number in zip(solutions, range(1, len(solutions)+1)):
        print(f"\nSolution {number}:")
        printBoard(sol, N)
        print()
        # Display matplotlib visualization
        plotBoard(sol, N, number)