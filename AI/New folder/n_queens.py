import random

class Queens():

    def __init__(self, size):
        self.board = []
        self.queens_position = [0] * size
        for i in range(size):
            self.board.append(self.queens_position[:])
        self.node_generated = 0
        self.node_expanded = 0

    def print_board(self):
        """Prints the current Queens position on board"""
        for i in range(len(self.board)):
            for j in range(len(self.board)):
                print(self.board[i][j], end=" ")
            print()
        #print("*" * 50)
        #print(f"For Queens position in rows: {self.queens_position}")

    def initialize(self):
        """Initial State of Board"""
        for col in range(len(self.board)):
            row = random.randint(0, len(self.board) - 1)
            self.board[row][col] = 1
            self.queens_position[col] = row
        #generated first node
        self.node_generated += 1

    def create_board(self, positions):
        """Modifies the current board for given list of positions"""
        #make all board tiles to 0
        for row in range(len(self.board)):
            for col in range(len(self.board)):
                self.board[row][col] = 0

        #updating the tiles
        self.queens_position = positions[:]
        for col in range(len(self.board)):
            self.board[positions[col]][col] = 1
            #if row in positions:
            #    self.board[row][positions.index(row)] = 1


    def is_goal(self):
        """Returns 1 if the current state is a goal state, else 0"""
        #check two queens not in same row, ie - sum of all rows should be 1
        for i in range(len(self.board)):
            if (sum(self.board[i]) != 1):
                return 0

        #no need to check for column as problem is formulates such that it wont happen

        #check for diagonal
        diag_diff = []
        diag_sum = []
        for i in range(len(self.board)):
            diag_diff.append(self.queens_position[i] - i)
            diag_sum.append(self.queens_position[i] + i)

        for row in range(len(self.board)):
            for col in range(len(self.board)):
                if ((row - col) in diag_diff and self.board[row][col] == 1):
                    return 0
                if ((row + col) in diag_sum and self.board[row][col] == 1):
                    return 0

        #means has no attacking queens
        return 1

    def objective(self):
        """Returns the number of the queens are attacking each other as objective value"""
        attack_count = 0

        #for row
        for row in range(len(self.board)):
            queen_no = sum(self.board[row])
            attack_count += ((queen_no - 1) * queen_no)
        #print(f"Attack count after row check: {attack_count}")

        #for column no need as only one queen each column

        #for diagonal
        diag_diff = []
        queen_no_diag = []
        diag_sum = []
        queen_no_diag_inv = []
        for i in range(len(self.board)):
            diag_diff.append(self.queens_position[i] - i)
            diag_sum.append(self.queens_position[i] + i)
            queen_no_diag.append(0)
            queen_no_diag_inv.append(0)

        #print(diag_sum, diag_diff, queen_no_diag, queen_no_diag_inv)

        for row in range(len(self.board)):
            for col in range(len(self.board)):
                if ((row - col) in diag_diff and self.board[row][col] == 1):
                    #print(f"found for {row} - {col}")
                    queen_no_diag[diag_diff.index(row - col)] = queen_no_diag[diag_diff.index(row - col)] + 1

                if ((row + col) in diag_sum and self.board[row][col] == 1):
                    #print(f"Found for {row} + {col}")
                    queen_no_diag_inv[diag_sum.index(row + col)] = queen_no_diag_inv[diag_sum.index(row + col)] + 1

        #print(queen_no_diag, queen_no_diag_inv)

        for i in range(len(self.board)):
            attack_count += ((queen_no_diag[i] - 1) * queen_no_diag[i])
            attack_count += ((queen_no_diag_inv[i] - 1) * queen_no_diag_inv[i])

        return attack_count

    def successor(self):
        """Finds the successor for the current node by generating all better nodes and selecting one"""
        #can create the successor by just changing the value of queen_position list
        #creating successors
        copy_queens_pos = self.queens_position[:]
        neighbours = []
        #increasing number of expanded nodes
        self.node_expanded += 1

        for col in self.queens_position:
            for row in range(len(self.board)):
                copy_queens_pos[col] = row
                new_board = Queens(len(self.board))
                new_board.create_board(copy_queens_pos)
                if (new_board.objective() < self.objective()):
                    neighbours.append(copy_queens_pos[:])
                    self.node_generated += 1
            copy_queens_pos[col] = self.queens_position[col]

        print(f"Current number of neighbours: {len(neighbours)}")
        #select any random neighbour and return it
        if (len(neighbours) > 0):
            position = random.randint(0, len(neighbours) - 1)
        else:
            position = -1

        return neighbours[position] if position != -1 else None

    def stochastic_hill_climbing(self):
        """Perform the stochastic_hill_climbing until we get where there is no successor"""
        next_state = self.successor()
        while not self.is_goal() and next_state is not None:
            #print("Next State: ", next_state)
            self.create_board(next_state)
            self.print_board()
            print(f"Attack count: {self.objective()}")
            print("=" * 50)
            next_state = self.successor()

        print("DONE!!!")

    def sn_count(self):
        print(f"Total Nodes Expanded: {self.node_expanded}")
        print(f"Total Nodes Generated: {self.node_generated}")

    def run(self):
        self.initialize()
        print("The chess board is initialized with this position")
        self.print_board()
        print("=" * 50)
        self.stochastic_hill_climbing()
        self.sn_count()





#main funtion
if __name__ == "__main__":

    chess_board = Queens(8)
    # queen_8.initialize()
    # queen_8.print_board()
    # queen_8.stochastic_hill_climbing()
    # queen_8.sn_count()
    chess_board.run()

