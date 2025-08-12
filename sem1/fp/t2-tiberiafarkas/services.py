import random

from numpy.random import choice

from src.domain import TeamValidator, Team
from src.player import Player, PlayerValidator
from src.tests import Test

from faker.proxy import Faker

class Service:
    def __init__(self, team_repo, player_repo):
        self.__team_repo = team_repo
        self.__player_repo = player_repo

    def add_team(self, id, name):
        team = Team(id, name)
        TeamValidator.validate(team)
        try:
            self.__team_repo.add_team(team)
        except Exception as e:
            raise(e)

    def add_player(self, id, name, team_id):
        player = Player(id, name, team_id)
        PlayerValidator.validate_player(player)
        ok = False
        if self.__team_repo.find(team_id) is not None:
            self.__player_repo.add_player(player)
            ok = True
        if not ok:
            raise ValueError('The team id does not exist')

    def draft_team(self, team_id):
        team = self.__team_repo.find(team_id)

        if team is None:
            raise ValueError('The team id does not exist')

        players = self.__player_repo.get_all()
        players_to_remove = [player for player in players if player.team_id == team_id]

        for player in players_to_remove:
            self.__player_repo.remove_player(player)

        fake = Faker()
        for i in range(1,23):
            player = Player(i, fake.name(), team_id)
            self.__player_repo.add_player(player)

    def set_lineup(self, team_id):
        self.draft_team(team_id)

        players = self.__player_repo.get_all()
        players_lineup = []

        while len(players_lineup) < 11:
            player = choice(players)
            if player.team_id == team_id and player.id not in players_lineup:
                players_lineup.append(player.id)

        return players_lineup

    def simulate_game(self, team1, team2):
        players_team1 = self.set_lineup(team1)
        players_team2 = self.set_lineup(team2)

        all_players = []
        all_players.extend(players_team1)
        all_players.extend(players_team2)

        goals = random.randint(0, 10)

        good_players = []

        for i in range(goals):
            player = choice(all_players)
            good_players.append(player)

        return players_team1, players_team2, good_players

    def get_players(self):
        return self.__player_repo.get_all()

    def get_all(self):
        return self.__team_repo.get_all()

