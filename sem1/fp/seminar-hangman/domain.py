class Sequence():
    """
    class to work with sentences
    it should check every word in the sentence and to get the letters from the word
    """
    def __init__(self, sentence, guessed=None):
        self.__sentence = sentence
        self.__guessed = [-1] * len(self.__sentence) if None else guessed
        # self.__words = sentence.split(" ")

    def get_sentence(self):
        return self.__sentence

    def get_words(self):
        return self.__words

    def add_sentence(self, sentence):
        self.__sentence = sentence
        self.__words = sentence.split(" ")

    def get_guessed(self):
        return self.__guessed

    def __str__(self):
        """
        the print should look like this:
        "a _ _ a has a _ _ _ _ s"
        :return:
        """
        sentence = str()
        sentence += (self.__sentence[0])
        for i in range(1, len(self.__sentence) - 1):
            if self.__guessed[i] == 1 and self.__sentence != " ":
                # print(self.__sentence[i], end=" ")
                sentence += self.__sentence[i]
            elif self.__sentence[i] == " ":
                # print(" ", end=" ")
                sentence += " "
            else:
                # print("_", end=" ")
                sentence += "_"
        # print(self.__sentence[-1])
        sentence += self.__sentence[-1]
        self.__sentence = sentence
        return sentence