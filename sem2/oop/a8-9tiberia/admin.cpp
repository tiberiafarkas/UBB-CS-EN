#include "admin.h"

AdminWidget::AdminWidget(Service& service, QWidget* parent)
	: QWidget(parent), service(service)
{
	this->setWindowTitle("Admin Mode");
	this->setMinimumSize(1000, 600);
	this->setStyleSheet("background-color: #985fc2;"); // Set a light background color

	QVBoxLayout* layout = new QVBoxLayout(this);
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	//movie table
	this->movieTableWidget = new QTableWidget(this);
	this->movieTableWidget->setColumnCount(constant::TABLE_WIDTH);
	this->movieTableWidget->setHorizontalHeaderLabels({ "Title", "Genre", "Year", "Likes", "Trailer" });
	this->movieTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	this->movieTableWidget->verticalHeader()->setVisible(false);
	this->movieTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->movieTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->movieTableWidget->setStyleSheet("QTableWidget { background-color: #f0f0f0; }");
	layout->addWidget(this->movieTableWidget);

	this->setLayout(layout);

	this->populateTable();

	//buttons layout
	QHBoxLayout* buttonsLayout = new QHBoxLayout();
	QVBoxLayout* completionLayout = new QVBoxLayout();
	buttonsLayout->setSpacing(5); // Set spacing between buttons

	titleInput = new QLineEdit(this);
	titleInput->setPlaceholderText("Title");
	titleInput->setStyleSheet("background-color: #f0f0f0; padding: 5px; font-size: 15px;");
	completionLayout->addWidget(titleInput);

	genreInput = new QLineEdit(this);
	genreInput->setPlaceholderText("Genre");
	genreInput->setStyleSheet("background-color: #f0f0f0; padding: 5px; font-size: 15px;");
	completionLayout->addWidget(genreInput);

	yearInput = new QLineEdit(this);
	yearInput->setPlaceholderText("Year");
	yearInput->setStyleSheet("background-color: #f0f0f0; padding: 5px; font-size: 15px;");
	completionLayout->addWidget(yearInput);
	
	likesInput = new QLineEdit(this);
	likesInput->setPlaceholderText("Likes");
	likesInput->setStyleSheet("background-color: #f0f0f0; padding: 5px; font-size: 15px;");
	completionLayout->addWidget(likesInput);

	trailerInput = new QLineEdit(this);
	trailerInput->setPlaceholderText("Trailer");
	trailerInput->setStyleSheet("background-color: #f0f0f0; padding: 5px; font-size: 15px;");
	completionLayout->addWidget(trailerInput);

	QPushButton* addButton = new QPushButton("Add Movie", this);
	// Set the button style
	addButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");

	QPushButton* updateButton = new QPushButton("Update Movie", this);
	// Set the button style
	updateButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");

	QPushButton* deleteButton = new QPushButton("Delete Movie", this);
	// Set the button style
	deleteButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");

	QPushButton* back = new QPushButton("Back", this);
	// Set the button style
	back->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");

	buttonsLayout->addWidget(addButton);
	buttonsLayout->addWidget(updateButton);
	buttonsLayout->addWidget(deleteButton);
	buttonsLayout->addWidget(back);

	layout->addLayout(completionLayout);
	layout->addLayout(buttonsLayout);
	this->setLayout(layout);

	//connect the back button to the main window
	connect(back, &QPushButton::clicked, this, &AdminWidget::goBackToMain);
	connect(addButton, &QPushButton::clicked, this, &AdminWidget::addMovie);
	connect(updateButton, &QPushButton::clicked, this, &AdminWidget::updateMovie);
	connect(deleteButton, &QPushButton::clicked, this, &AdminWidget::deleteMovie);

}

AdminWidget::~AdminWidget()
{
	this->movieTableWidget->clearContents();
	this->movieTableWidget->setRowCount(0);
	this->movieTableWidget = nullptr; // Set the pointer to nullptr to avoid dangling pointer
}

void AdminWidget::populateTable()
{
	//this->movieListWidget->clear();
	this->movieTableWidget->clearContents(); // Clear the table contents before populating it
	this->movieTableWidget->setRowCount(0); // Clear the table before populating it
	std::vector<Movie> movies = this->service.getMovies();
	int row = 0;

	for (const auto& movie : movies)
	{
		this->movieTableWidget->insertRow(row);
		QTableWidgetItem* titleItem = new QTableWidgetItem(QString::fromStdString(movie.getTitle()));
		QTableWidgetItem* genreItem = new QTableWidgetItem(QString::fromStdString(movie.getGenre()));
		QTableWidgetItem* yearItem = new QTableWidgetItem(QString::number(movie.getYearOfRelease()));
		QTableWidgetItem* likesItem = new QTableWidgetItem(QString::number(movie.getNumberOfLikes()));
		QTableWidgetItem* trailerItem = new QTableWidgetItem(QString::fromStdString(movie.getTrailer()));

		this->movieTableWidget->setItem(row, constant::TITLE_COLUMN, titleItem);
		this->movieTableWidget->setItem(row, constant::GENRE_COLUMN, genreItem);
		this->movieTableWidget->setItem(row, constant::YEAR_COLUMN, yearItem);
		this->movieTableWidget->setItem(row, constant::LIKES_COLUMN, likesItem);
		this->movieTableWidget->setItem(row, constant::TRAILER_COLUMN, trailerItem);
		
		row++;

	}
}

void AdminWidget::showAdminWindow()
{
	this->show();
}

void AdminWidget::goBackToMain()
{
	this->hide();
	emit backButtonClicked();
}

void AdminWidget::addMovie()
{
	QString title = titleInput->text();
	QString genre = genreInput->text();
	int year = yearInput->text().toInt();
	int likes = likesInput->text().toInt();
	QString trailer = trailerInput->text();

	// Validate inputs
	if (title.isEmpty() || genre.isEmpty() || trailer.isEmpty()) {
		QMessageBox::warning(this, "Error", "All fields except must be filled.");
		return;
	}

	if (year <= 0 || likes < 0) {
		QMessageBox::warning(this, "Error", "Year and likes must be positive numbers.");
		return;
	}

	Movie newMovie(title.toStdString(), genre.toStdString(), year, likes, trailer.toStdString());

	try {
		service.addMovie(newMovie);
	}
	catch (const DuplicateMovieException& e) {
		QMessageBox::warning(this, "Error", "Movie already exists.");
		return;
	}

	populateTable();
}

void AdminWidget::updateMovie()
{
	QString title = titleInput->text();
	QString genre = genreInput->text();
	int year = yearInput->text().toInt();
	int likes = likesInput->text().toInt();
	QString trailer = trailerInput->text();

	if (title.isEmpty() || genre.isEmpty() || trailer.isEmpty()) {
		QMessageBox::warning(this, "Error", "All fields must be filled.");
		return;
	}

	if (year <= 0 || likes < 0) {
		QMessageBox::warning(this, "Error", "Year and likes must be positive numbers.");
		return;
	}

	Movie updatedMovie(title.toStdString(), genre.toStdString(), year, likes, trailer.toStdString());

	try
	{
		service.updateMovie(updatedMovie);
	}
	catch (const RepositoryException& e) {
		QMessageBox::warning(this, "Error", "Movie not found.");
		return;
	}

	service.updateMovie(updatedMovie);
	populateTable();
}

void AdminWidget::deleteMovie()
{
	QString title = titleInput->text();
	if (title.isEmpty()) {
		QMessageBox::warning(this, "Error", "Title must be filled.");
		return;
	}

	try
	{
		service.deleteMovie(title.toStdString());
	}
	catch (const RepositoryException& e) {
		QMessageBox::warning(this, "Error", "Movie not found.");
		return;
	}
	populateTable();
}