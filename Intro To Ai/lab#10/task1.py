import matplotlib.pyplot as plt
import matplotlib.patches as patches

def N_Queens_bt(n):
    board = [-1] *n
    solutionArray = []

    def isSafe( row , column, board):
        for x in range(row):
            if board [x] == column or abs(board[x] - column ) == abs(x - row):
                return False
        return True

    def backTracking(row):
        if row == n:
            solutionArray.append(board.copy())
        else:
            for col in range(n):
                if isSafe(row , col , board):
                    board[row] = col
                    backTracking(row+1)
                    board[row] = -1
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
            # Alternate colors for chessboard pattern
            color = 'white' if (row + col) % 2 == 0 else 'lightgray'
            square = patches.Rectangle((col, N - 1 - row), 1, 1, 
                                       linewidth=1, edgecolor='black', 
                                       facecolor=color)
            ax.add_patch(square)
    
    # Place the queens
    for row in range(N):
        col = board[row]
        # Draw queen as a circle with "Q" text
        circle = patches.Circle((col + 0.5, N - 1 - row + 0.5), 0.35, 
                               color='red', zorder=10)
        ax.add_patch(circle)
        ax.text(col + 0.5, N - 1 - row + 0.5, 'Q', 
               fontsize=20, fontweight='bold', color='white',
               ha='center', va='center', zorder=11)
    
    # Set axis properties
    ax.set_xlim(0, N)
    ax.set_ylim(0, N)
    ax.set_aspect('equal')
    ax.axis('off')
    ax.set_title(f'N-Queens Solution #{solution_num} (N={N})', 
                fontsize=16, fontweight='bold', pad=20)
    
    plt.tight_layout()
    plt.show()


if  __name__ == "__main__":

    N = int(input("Enter N for N-Queens problem:"))
    solutions = N_Queens_bt(N)

    print(f"\nTotal solutions found: {len(solutions)}\n")
    print("Solution array for backtracking problem:")
    
    for sol, number in zip(solutions, range(1, len(solutions)+1)):
        print(f"\nSolution {number}:")
        printBoard(sol, N)
        print()
        # Display matplotlib visualization
        plotBoard(sol, N, number)        

