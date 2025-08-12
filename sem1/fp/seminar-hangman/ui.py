from random import choice

from src.domain import Sequence
from src.repository import TextFileRepo
from src.services import Service


class UI:
    def __init__(self):
        self.__commands = {
            "1": self.write_sentence,
            "2": self.play_game
        }
        self.__repo = TextFileRepo("sentence.txt")
        self.guess = []

    def write_sentence(self):
        sentence = input("Enter a sentence: ")
        if len(sentence) < 3:
            raise ValueError("Sentence must have at least 3 characters")
        if sentence not in self.__repo._data:
            sentence = Sequence(sentence)
            self.__repo.write_to_file(sentence.get_sentence())
        else:
            print("Sentence already in the list")

    def play_game(self):
        """
        You have to implement a console-based variation of the classical Hangman game.
        The computer will select a Sentence that the user can attempt to guess, letter by letter.
        Each time the user guesses a correct letter, the computer will fill it in the sentence at the correct positions.
        In case the letter does not appear, the computer will fill in a new letter in the word "hangman", starting from the empty string.
        The game ends when the user has guessed the sentence (user wins) or when the computer fills in the "hangman" word (user loses).
        :return:
        """
        print(self.__repo._data)
        sentence = choice(self.__repo._data)
        guessed = [-1] * len(sentence)
        sentence = Sequence(sentence, guessed)
        super_sentence = sentence.get_sentence()
        print(f"output: {sentence}")
        self.__sentence = Service(super_sentence, guessed)
        while True:
            letter = input("Enter a letter to guess: ")
            if len(letter) != 1:
                print("Invalid letter")
                continue
            self.__sentence.guess_leter(letter)
            hangman = self.__sentence.get_hangman()
            guessed = self.__sentence.get_guess()
            sentence = Sequence(self.__sentence.get_sentence(), guessed)
            # sentence = sentence.get_sentence()
            print(f"User guess: {letter}, output changes to: {sentence} - {hangman}")

            if self.__sentence.is_winner():
                print("You won!")
                return

            if self.__sentence.is_loser():
                print("You lost!")
                return


    def run(self):
        while True:
            print("1. Write sentence")
            print("2. Play game")
            print("0. Exit")
            command = input("Enter command: ")
            if command == "0":
                return
            if command in self.__commands:
                self.__commands[command]()
            else:
                print("Invalid command")


UI().run()



