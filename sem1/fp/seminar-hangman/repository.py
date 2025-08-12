class TextFileRepo:
    def __init__(self, file_name):
        self.__file_name = file_name
        self._data = []
        self.load_from_file()

    def load_from_file(self):
        try:
            with open(self.__file_name, "r") as file:
                lines = file.readlines()
                for line in lines:
                    line = line.strip()
                    if line != "":
                        self.add(line)
        except FileNotFoundError:
            self._data = []

    def write_to_file(self, sentence):
        fout = open(self.__file_name, "wt", newline='')
        for elem in self._data:
            fout.write(f"{elem}\n")
        fout.write(f"{sentence}\n")
        fout.close()

    def add(self, elem):
        if elem in self._data:
            raise ValueError("Duplicate object ID")
        self._data.append(elem)




