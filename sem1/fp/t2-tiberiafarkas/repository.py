from src.domain import Team
from src.exceptions import DuplicateIDError


class TeamMemoRepo:
    def __init__(self):
        self._data = []

    def add_team(self, team):
        if any(existing_team.id == team.id for existing_team in self._data):
            raise DuplicateIDError('The team id already exists')
        else:
            self._data.append(team)

    def get_all(self):
        return self._data

    def remove_team(self, team):
        self._data.remove(team)


class TeamTextRepo(TeamMemoRepo):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.__load_from_file()

    def __load_from_file(self):
        with open(self.__file_name, 'r') as file:
            lines = file.readlines()
            for line in lines:
                parts = line.strip().split(',')
                team = Team(int(parts[0]), parts[1])
                self._data.append(team)

    def __save_to_file(self):
        with open(self.__file_name, 'w') as file:
            for team in self._data:
                file.write(str(team) + '\n')

    def add_team(self, team):
        super().add_team(team)
        self.__save_to_file()

    def find(self, team_id):
        for team in self._data:
            if team.id == team_id:
                return team
        raise ValueError('The team id does not exist')


class PlayerMemoRepo:
    def __init__(self):
        self._data = []

    def add_player(self, player):
        self._data.append(player)

    def remove_player(self, player):
        self._data.remove(player)

    def get_all(self):
        return self._data

