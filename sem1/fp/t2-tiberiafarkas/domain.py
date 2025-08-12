class Team:
    def __init__(self, id: int, name: str):
        self.__id = id
        self.__name = name

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    def __str__(self):
        return f'{self.__id},{self.__name}'

class TeamValidator:
    @staticmethod
    def validate(team):
        if not isinstance(team, Team):
            raise ValueError('The team must be a Team instance')

        try:
            int(team.id)
            if int(team.id) < 0:
                raise ValueError('The team id must be a positive integer')
        except TypeError:
            raise ValueError('The team id must be an integer')

        if team.name == '':
            raise ValueError('The team name must not be empty')
