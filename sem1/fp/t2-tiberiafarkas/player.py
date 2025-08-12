class Player:
    def __init__(self, id, name, team_id):
        self.__id = id
        self.__name = name
        self.__team_id = team_id

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @property
    def team_id(self):
        return self.__team_id

    def __str__(self):
        return f'{self.__id},{self.__name},{self.__team_id}'

class PlayerValidator:
    @staticmethod
    def validate_player(player):
        errors = []
        if not isinstance(player, Player):
            errors.append('The player must be a Player instance')

        try:
            int(player.id)
            if int(player.id) < 0:
                errors.append('The player id must be a positive integer')
        except TypeError:
            errors.append('The player id must be an integer')

        if player.name == '':
            errors.append('The player name must not be empty')

        try:
            int(player.team_id)
            if int(player.team_id) < 0:
                errors.append('The team id must be a positive integer')
        except TypeError:
            errors.append('The team id must be an integer')

        if len(errors) > 0:
            raise ValueError(errors)
