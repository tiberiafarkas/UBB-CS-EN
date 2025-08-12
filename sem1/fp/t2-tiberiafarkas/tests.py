from unittest import TestCase

class Test(TestCase):
    def __init__(self, service):
        self.__service = service
        self.run_tests()

    def test_add_team(self):
        self.__service.add_team(100, 'team1')
        assert len(self.__service.get_all()) == 1
        try:
            self.__service.add_team(100, 'team2')
            assert False
        except Exception as e:
            assert True
        assert len(self.__service.get_all()) == 1

    def test_get_all(self):
        self.__service.add_team(200, 'team2')
        self.__service.add_team(300, 'team3')
        assert len(self.__service.get_all()) == 3
        assert self.__service.get_all()[0].name == 'team1'
        assert self.__service.get_all()[1].name == 'team2'
        assert self.__service.get_all()[2].name == 'team3'

    def test_add_player(self):
        self.__service.add_team(400, 'team1')
        self.__service.add_player(1, 'player1', 400)
        assert len(self.__service.get_players()) == 1
        try:
            self.__service.add_player(1, 'player2', 2)
            assert False
        except Exception as e:
            assert True
        assert len(self.__service.get_players()) == 1

    def test_draft_team(self):
        self.__service.add_player(2, 'player2', 400)
        self.__service.add_player(3, 'player3', 400)
        assert len(self.__service.get_players()) == 3
        self.__service.draft_team(400)
        assert len(self.__service.get_players()) == 11

    def test_set_lineup(self):
        self.__service.set_lineup(400)
        assert len(self.__service.set_lineup(400)) == 11

    def run_tests(self):
        self.test_add_team()
        self.test_get_all()
        self.test_add_player()
        self.test_draft_team()
