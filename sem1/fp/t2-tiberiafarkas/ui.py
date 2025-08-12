import time

from src.repository import TeamMemoRepo, TeamTextRepo
from src.services import Service


class UI:
    def __init__(self, service):
        self.__service = service
        self.__commands = {
            "1": self.add_team,
            "2": self.display_teams,
            "3": self.add_player,
            "4": self.display_players,
            "5": self.draft_team,
            "6": self.set_lineup,
            "7": self.simulate_game
        }

    def add_team(self):
        id = int(input('Enter the team id: '))
        name = input('Enter the team name: ')
        self.__service.add_team(id, name)

    def display_teams(self):
        teams = self.__service.get_all()
        for team in teams:
            print(team)

    def add_player(self):
        id = int(input('Enter the player id: '))
        name = input('Enter the player name: ')
        team_id = int(input('Enter the team id: '))
        self.__service.add_player(id, name, team_id)

    def display_players(self):
        players = self.__service.get_players()
        for player in players:
            print(player)

    def draft_team(self):
        team_id = int(input('Enter the team id: '))
        self.__service.draft_team(team_id)
        print(f'Team drafted {team_id}')
        for player in self.__service.get_players():
            print(player)

    def set_lineup(self):
        team_id = int(input('Enter the team id: '))
        players = self.__service.set_lineup(team_id)
        print('The lineup is:')
        print(players)

    def simulate_game(self):
        team1 = int(input('Enter the first team id: '))
        team2 = int(input('Enter the second team id: '))
        players_team1, players_team2, all_players = self.__service.simulate_game(team1, team2)

        goals_team1 = 0
        goals_team2 = 0

        print(f"Team {team1} vs Team {team2}")
        print("-------------------the game starts--------------------")
        for player in all_players:
            if player in players_team1:
                goals_team1 += 1
            else:
                goals_team2 += 1

            print(f"{player} is scoring!")
            print(f"Team {team1} - {goals_team1} goals vs Team {team2} - {goals_team2} goals")

            time.sleep(1)

        print("--------------------the game ends---------------------")
        print("-----------------the final score is-------------------")
        print(f"Team {team1} - {goals_team1} goals vs Team {team2} - {goals_team2} goals")

        if goals_team1 > goals_team2:
            print(f"Team {team1} wins!")
        elif goals_team1 < goals_team2:
            print(f"Team {team2} wins!")
        else:
            print("It's a draw!")


    def print_menu(self):
        print('1. Add team')
        print('2. Display teams')
        print('3. Add player')
        print('4. Display players')
        print('5. Draft team')
        print('6. Set lineup')
        print('7. Simulate game')
        print('0. Exit')

    def run(self):
        while True:
            self.print_menu()
            option = input('Enter a command: ')
            if option == '0':
                break
            if option in self.__commands:
                try:
                    self.__commands[option]()
                except ValueError as ve:
                    print(ve)
            else:
                print('Invalid command')
