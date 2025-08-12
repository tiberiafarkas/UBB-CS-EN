import random


class ChaosPlayer:
    def __init__(self, board, pieces, n):
        self.__board = board
        self.__pieces = pieces
        self.__size = n

    def make_random_move(self):
        """
        The computer makes a random move
        :return:
        """
        x = random.randint(0, self.__size - 1)
        y = random.randint(0, self.__size - 1)
        symbols = ["X", "O"]
        symbol = random.choice(symbols)

        while self.__board.get_square(x, y) != " ":
            x = random.randint(0, self.__size - 1)
            y = random.randint(0, self.__size - 1)

        return x, y, symbol


    def verify_stop_move(self, i, j):
        """
        Here we verify if the computer can stop the player from winning
        We check if there on rows, column or diagonals there are "pieces" - 1 of the player
        :return: where the player has "pieces" - 1 in a row, column or diagonal
        """
        #check for row
        count = 0
        y = 0
        while self.__board.get_square(i, y) != self.__board.get_square(i, j) and y < self.__size:
            y += 1

        if y < self.__size:
            for ycopy in range(y, self.__size):
                if self.__board.get_square(i, ycopy) == self.__board.get_square(i, j):
                    count += 1
                else:
                    break

        if count == self.__pieces - 1:
            return "R"

        #check for column
        count = 0
        x = 0
        while self.__board.get_square(x, j) != self.__board.get_square(i, j) and x < self.__size:
            x += 1

        if x < self.__size:
            for xcopy in range(x, self.__size):
                if self.__board.get_square(xcopy, j) == self.__board.get_square(i, j):
                    count += 1
                else:
                    break

        if count == self.__pieces - 1:
            return "C"

        #check for diagonal
        count = 0
        x = i
        y = j
        while x >= 0 and y >= 0 and self.__board.get_square(x, y) == self.__board.get_square(i, j):
            x -= 1
            y -= 1
            count += 1

        x = i + 1
        y = j + 1
        while x < self.__size and y < self.__size and self.__board.get_square(x, y) == self.__board.get_square(i, j):
            x += 1
            y += 1
            count += 1

        if count == self.__pieces - 1:
            return "D"

        return False

    def make_stop_move(self):
        """
        The computer makes a move to stop the player from winning
        :return: the stop move
        """
        for i in range(self.__size):
            for j in range(self.__size):
                if self.__board.get_square(i, j) != " ":
                    stop_move = self.verify_stop_move(i, j)

                    if self.__board.get_square(i, j) == "X":
                        chaos_symbol = "O"
                    else:
                        chaos_symbol = "X"

                    print(stop_move)

                    if stop_move != False:
                        if stop_move == "D":
                            print("on diag", i, j)
                            if i - 1 >= 0 and j - 1 >= 0:
                                print(i - 1, j - 1)
                                if self.__board.get_square(i - 1, j - 1) == " ":
                                    print("on diag > 0", i - 1, j - 1)
                                    return i - 1, j - 1, chaos_symbol
                            if i + self.__pieces - 1 < self.__size and j + self.__pieces - 1 < self.__size:
                                print(i + self.__pieces - 1, j + self.__pieces - 1)
                                if self.__board.get_square(i + self.__pieces - 1, j + self.__pieces - 1) == " ":
                                    print("on diag < n", i + self.__pieces - 1, j + self.__pieces - 1)
                                    return i + self.__pieces - 1, j + self.__pieces - 1, chaos_symbol
                            if self.__board.get_square(i, j) == " ":
                                    print("on diag < n", i, j)
                                    return i, j, chaos_symbol
                        if stop_move == "C":
                            # print("on row", i, j)
                            if i - 1 > 0:
                                if self.__board.get_square(i - 1, j) == " ":
                                    # print("on row", i - 1, j)
                                    return i - 1, j, chaos_symbol
                            if i + self.__pieces - 1 < self.__size:
                                if self.__board.get_square(i + self.__pieces - 1, j) == " ":
                                    # print("on row", i + self.__pieces - 1 , j)
                                    return i + self.__pieces - 1, j, chaos_symbol
                        if stop_move == "R":
                            # print("on col", i, j)
                            if j - 1 > 0:
                                if self.__board.get_square(i, j - 1) == " ":
                                    # print("on col", i, j - 1)
                                    return i, j - 1, chaos_symbol
                            if j + self.__pieces - 1 < self.__size:
                                if self.__board.get_square(i, j + self.__pieces - 1) == " ":
                                    # print("on col", i, j + self.__pieces - 1)
                                    return i, j + self.__pieces - 1, chaos_symbol

        return False

    def make_move(self):
        """
        The computer makes a move
        It checks if it can stop the player from winning
        If not, it makes a random move
        :return:
        """
        stop_move = self.make_stop_move()

        if stop_move != False:
            x, y, symbol = stop_move
            print("stop move", x, y, symbol)
            self.__board.set_square(x, y, symbol)
            return x, y, symbol

        else:
            x, y, symbol = self.make_random_move()
            self.__board.set_square(x, y, symbol)
            return x, y, symbol

    def check_winner(self):
        win = True

        for i in range(self.__size):
            for j in range(self.__size):
                if self.__board.get_square(i, j) == " ":
                    win = False

        return win