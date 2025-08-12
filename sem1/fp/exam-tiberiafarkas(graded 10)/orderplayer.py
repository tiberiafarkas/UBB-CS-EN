from multiprocessing.pool import job_counter


class OrderPlayer:
    def __init__(self, board, pieces, n):
        self.__board = board
        self.__pieces = pieces
        self.__size = n

    def make_move(self, x, y, symbol):
        if x < 0 or x > self.__pieces or y < 0 or y > self.__pieces:
            raise ValueError("Invalid coordinates")

        self.__board.set_square(x, y, symbol)

    def check_pieces(self, i, j, symbol):
        """
        Here we check if the player has "pieces" in a row, column or diagonal
        :return:
        """
        win = True
        y = 0
        count = 0

        #check for row
        while self.__board.get_square(i, y) != symbol and y < self.__size:
            y += 1

        if y < self.__size:
            for ycopy in range(y, self.__size):
                if self.__board.get_square(i, ycopy) != symbol:
                    win = False
                    break
                else:
                    count += 1
        else:
            win = False

        if win and count >= self.__pieces:
            # print(count)
            return True

        #chec for column
        x = 0
        count = 0
        win  = True
        while self.__board.get_square(x, j) != symbol and x < self.__size:
            x += 1

        if x < self.__size:
            for xcopy in range(x, self.__size):
                if self.__board.get_square(xcopy, j) != symbol:
                    win = False
                    break
                else:
                    count += 1
        else:
            win = False

        if win and count >= self.__pieces:
            # print(count)
            return True

        #check for diagonal
        x = i
        y = j
        count = 0
        win = True
        while ( x >= 0 and y >= 0 and self.__board.get_square(x, y) == symbol):
            x -= 1
            y -= 1
            count += 1

        x = i + 1
        y = j + 1
        while ( x < self.__size and y < self.__size and self.__board.get_square(x, y) == symbol):
            x += 1
            y += 1
            count += 1

        if count >= self.__pieces:
            # print(count)
            return True

    def check_winner(self):
        for i in range(self.__size):
            for j in range(self.__size):
                if self.__board.get_square(i, j) == " ":
                    continue

                if self.check_pieces(i, j, self.__board.get_square(i, j)):
                    return True

        return False

