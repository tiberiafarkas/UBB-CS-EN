from src.repository import TeamMemoRepo, TeamTextRepo, PlayerMemoRepo
from src.services import Service
from src.tests import Test
from src.ui import UI

team_memo_repo = TeamMemoRepo()
team_text_repo = TeamTextRepo('teams.txt')
player_memo_repo = PlayerMemoRepo()
service = Service(team_text_repo, player_memo_repo)

# Test(service)

ui = UI(service)
ui.run()

