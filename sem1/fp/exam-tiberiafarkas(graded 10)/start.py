from src.ui import UI

file_name = "file.txt"

n = 0
pieces = 0
with open(file_name, "r") as file:
    for line in file:
        line = line.strip()
        line = line.split(" ")
        if n == 0:
            n = int(line[2])
        else:
            pieces = int(line[2])
    file.close()

if __name__ == "__main__":
    ui = UI(n, pieces)
    ui.run()

