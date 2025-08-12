from src.board import Board
from src.chaosplayer import ChaosPlayer
from src.orderplayer import OrderPlayer


class UI:
    def __init__(self, n, pieces):
        self.__board = Board(n, pieces)
        self.__commands = {
            "1": self.load_existing_game,
            "2": self.start_new_game
        }
        self.__order_player = OrderPlayer(self.__board, pieces, n)
        self.__chaos_player = ChaosPlayer(self.__board, pieces, n)

    def load_existing_game(self):
        game_mode = "load_existing_game"
        self.play_game(game_mode)

    def start_new_game(self):
        game_mode = "start_new_game"
        self.play_game(game_mode)

    def check_winner(self):
        if self.__order_player.check_winner():
            print(self.__board)
            print("Human wins!")
            return True

        if self.__chaos_player.check_winner():
            print(self.__board)
            print("AI wins!")
            return True

        return False

    def play_order(self):
        """
        The human player makes a move
        get the coordinates and the symbol from the user
        raise an exception if the symbol is invalid
        :return:
        """
        symbol = input("Enter symbol X or O or QUIT if you want to quit the game: ")
        symbol = symbol.upper()

        if symbol == "QUIT":
            exit(0)

        if symbol != "X" and symbol != "O":
            raise ValueError("Invalid symbol")
        else:
            try:
                x1 = int(input("Enter x: "))
                y1 = int(input("Enter y: "))

                self.__order_player.make_move(x1 - 1, y1 - 1, symbol)
                return symbol, x1, y1
            except ValueError:
                raise ValueError("Input must be an integer")

    def play_chaos(self):
        return self.__chaos_player.make_move()

    def play_game(self, game_mode):
        """
        The main game loop
        It is set the game mode
        :param game_mode:
        :return:
        """
        if game_mode == "load_existing_game":
            self.__board.open_file()
        else:
            self.__board.clear_board()
        print(self.__board)
        while True:
            try:
                symbol, x1, y1 = self.play_order()

                if self.check_winner():
                    break

                x2, y2, symbol_ai = self.play_chaos()
                x2 += 1
                y2 += 1

                if self.check_winner():
                    break

                self.__board.save_file()
                print(self.__board)
                print(f"Human: {x1, y1, symbol}, AI: {x2, y2, symbol_ai}")

            except ValueError as ve:
                print(ve)

    def print_menu(self):
        print("1. Load existing game")
        print("2. Start new game")
        print("0. Exit")


    def run(self):
        while True:
            self.print_menu()
            command = input("Enter command: ")
            if command == "0":
                return
            try:
                if command in self.__commands:
                    self.__commands[command]()
                else:
                    print("Invalid command")
            except Exception as e:
                print(e)