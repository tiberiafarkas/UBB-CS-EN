from src.domain import FlightValidator
from src.repository import TextFileRepo
from src.services import Service
from src.tests import Test
from src.ui import UI

file_name = "flights.txt"
text_repo = TextFileRepo(file_name)
flight_validator = FlightValidator()
service = Service(text_repo, flight_validator)
ui = UI(service)
# test = Test()

if __name__ == "__main__":
    ui.run()
    # test.run_tests()