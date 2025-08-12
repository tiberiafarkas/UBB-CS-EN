from texttable import Texttable

class Board:
    def __init__(self, board_size, pieces):
        self.__board_size = board_size
        self.__pieces = pieces
        self.__board = [[" " for _ in range(board_size)] for _ in range(board_size)]
        self.open_file()

    def open_file(self):
        with open("board.txt", "r") as file:
            line = file.readline()
            line = line.strip()
            line = line.split(" ")
            if line[0] != str(self.__board_size) or line[1] != str(self.__pieces):
                self.clear_board()
                self.save_file()
            else:
                for line in file:
                    line = line.strip()
                    line = line.split(" ")
                    x = int(line[0])
                    y = int(line[1])
                    if len(line) == 3:
                        self.__board[x][y] = line[2]
                    else:
                        self.__board[x][y] = " "
        file.close()

    def save_file(self):
        with open("board.txt", "w") as file:
            file.write(str(self.__board_size) + " " + str(self.__pieces) + "\n")
            for i in range(self.__board_size):
                for j in range(self.__board_size):
                    file.write(str(i) + " " + str(j) + " " + self.__board[i][j] + "\n")
        file.close()

    @property
    def board(self):
        return self.__board

    def get_square(self, x, y):
        return self.__board[x][y]

    def set_square(self, x, y, value):
        if x < 0 or x >= self.__board_size or y < 0 or y >= self.__board_size or self.__board[x][y] != " ":
            raise ValueError("Invalid coordinates")
        self.__board[x][y] = value

    def clear_square(self, x, y):
        self.__board[x][y] = " "

    def clear_board(self):
        for i in range(self.__board_size):
            for j in range(self.__board_size):
                self.__board[i][j] = " "
        self.save_file()

    def __str__(self):
        board = Texttable()
        for i in range(self.__board_size):
            row = []
            for j in range(self.__board_size):
                row.append(self.__board[i][j])

            board.add_row(row)

        return board.draw()

