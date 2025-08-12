class Service:
    def __init__(self, sentence, guessed):
        self.__sentence = sentence
        self.__guessed = guessed if guessed else [-1] * len(self.__sentence)
        self.__words = []
        self.__hangman = ""
        self.__tries = 0
        self.__tried_letters = set()

    def get_sentence(self):
        return self.__sentence

    def get_guess(self):
        return self.__guessed

    def get_hangman(self):
        return self.__hangman

    def get_tries(self):
        return self.__tries

    def guess_leter(self, letter):
        if letter in self.__sentence and letter not in self.__tried_letters:
            for i in range(len(self.__sentence)):
                if ( self.__sentence[i] == letter or self.__sentence[i] == " " or i == 0 or i == len(self.__sentence) - 1 ):
                    self.__guessed[i] = 1
                    self.__tried_letters.add(letter)
        else:
            self.__tries += 1
            self.__hangman += "HANGMAN"[self.__tries - 1]

    def is_winner(self):
        return -1 not in self.__guessed

    def is_loser(self):
        return len(self.__hangman) == 7

    def __str__(self):
        return "".join(self.__sentence)
