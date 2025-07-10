#include "user.h"
#include <windows.h>
#include <QtWebEngineCore/QWebEngineSettings>
#include <QCoreApplication>

UserWidget::UserWidget(Service& service, QWidget* parent)
	: QWidget(parent), service(service)
{
	this->setWindowTitle("User Mode");
	this->setMinimumSize(1200, 600);
	this->setStyleSheet("background-color: #985fc2;"); // Set a light background color
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setSpacing(10); // Set spacing between widgets

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

	//input layout
	QVBoxLayout* completionLayout = new QVBoxLayout();
	completionLayout->setSpacing(5); // Set spacing between input fields

	titleInput = new QLineEdit(this);
	titleInput->setPlaceholderText("Title");
	titleInput->setStyleSheet("background-color: #f0f0f0; padding: 5px; font-size: 15px;");
	completionLayout->addWidget(titleInput);

	genreInput = new QLineEdit(this);
	genreInput->setPlaceholderText("Genre");
	genreInput->setStyleSheet("background-color: #f0f0f0; padding: 5px; font-size: 15px;");
	completionLayout->addWidget(genreInput);

	//buttons layout
	QHBoxLayout* buttonsLayout = new QHBoxLayout();

	addButton = new QPushButton("Add Movie", this);
	addButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");
	buttonsLayout->addWidget(addButton);

	deleteButton = new QPushButton("Delete Movie", this);
	deleteButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");
	buttonsLayout->addWidget(deleteButton);

	undo = new QPushButton("Undo", this);
	undo->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");
	buttonsLayout->addWidget(undo);

	redo = new QPushButton("Redo", this);
	redo->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");
	buttonsLayout->addWidget(redo);

	//genre filter
	QPushButton* filterButton = new QPushButton("Filter by Genre", this);
	filterButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");
	buttonsLayout->addWidget(filterButton);
	connect(filterButton, &QPushButton::clicked, this, &UserWidget::filterMoviesByGenre);

	QHBoxLayout* likeNextLayout = new QHBoxLayout();

	likeButton = new QPushButton("Like", this);
	likeButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");
	likeButton->setFixedWidth(150); // Set fixed width for the button

	nextButton = new QPushButton("Next", this);
	nextButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");
	nextButton->setFixedWidth(150); // Set fixed width for the button

	likeButton->setVisible(false);
	nextButton->setVisible(false);

	back = new QPushButton("Back", this);
	back->setStyleSheet("background-color: #fafa98; color: black; font-size: 15px; padding: 10px;");

	movieDetailsLabel = new QLabel(this);
	movieDetailsLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
	movieDetailsLabel->setVisible(false);
	layout->addWidget(movieDetailsLabel);

	likeNextLayout->addWidget(likeButton, 0, Qt::AlignLeft);
	likeNextLayout->addWidget(nextButton, 0, Qt::AlignRight);
	buttonsLayout->addWidget(back);

	layout->addLayout(likeNextLayout);
	layout->addLayout(completionLayout);
	layout->addLayout(buttonsLayout);

	//connect the back button to bring you back to main
	connect(back, &QPushButton::clicked, this, &UserWidget::goBackToMain);
	connect(addButton, &QPushButton::clicked, this, &UserWidget::addToWatchlist);
	connect(deleteButton, &QPushButton::clicked, this, &UserWidget::deleteFromWatchlist);
	connect(nextButton, &QPushButton::clicked, this, &UserWidget::showNextMovie);
	connect(likeButton, &QPushButton::clicked, this, &UserWidget::likeMovie);
	connect(undo, &QPushButton::clicked, this, &UserWidget::handleUndo);
	connect(redo, &QPushButton::clicked, this, &UserWidget::handleRedo);

}

UserWidget::~UserWidget()
{
	this->movieTableWidget->clearContents(); // Clear the table before populating it
	this->movieTableWidget->setRowCount(0); // Clear the table before populating it
	this->movieTableWidget = nullptr; // Set the pointer to nullptr to avoid dangling pointer
}

void UserWidget::populateTable()
{
	this->movieTableWidget->clearContents(); // Clear the table before populating it
	this->movieTableWidget->setRowCount(0); // Clear the table before populating it
	std::vector<Movie> movies = this->service.getWatchlist();
	
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

void UserWidget::showUserWindow()
{
	this->populateTable();
	this->show();
}

void UserWidget::goBackToMain()
{
	emit backButtonClicked();
	this->hide();
}

void UserWidget::addToWatchlist()
{
	std::string title = titleInput->text().toStdString();
	try
	{
		if (!title.empty()) {
			this->service.addMovieToWatchlist(title);
		}
		else if (this->currentMovieIndex != -1) {
			this->service.addMovieToWatchlist(this->moviesByGenre[this->currentMovieIndex].getTitle());
		}
		else {
			QMessageBox::warning(this, "Warning", "Please enter a title or display a trailer to add.");
			return;
		}
		this->populateTable();
	}
	catch (RepositoryException& e) 
	{
		QMessageBox::warning(this, "Warning", e.what());
	}
}

void UserWidget::deleteFromWatchlist()
{
	std::string title = titleInput->text().toStdString();
	if (title.empty())
	{
		QMessageBox::warning(this, "Warning", "Please fill in title field.");
		return;
	}
	try
	{
		this->service.deleteMovieFromWatchlist(title);
		this->populateTable();
	}
	catch (RepositoryException& e)
	{
		QMessageBox::warning(this, "Warning", e.what());
	}
}

void UserWidget::likeMovie()
{
	try
	{
		this->service.increaseLikes(this->moviesByGenre[this->currentMovieIndex].getTitle());
		this->populateTable();
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "Warning", e.what());
	}
}

void UserWidget::showMovieInfo() {
	Movie movie = this->moviesByGenre[this->currentMovieIndex];
	QString info = QString("Title: %1\nGenre: %2\nLikes: %3\nYear: %4")
		.arg(QString::fromStdString(movie.getTitle()))
		.arg(QString::fromStdString(movie.getGenre()))
		.arg(movie.getNumberOfLikes())
		.arg(movie.getYearOfRelease());
	movieDetailsLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
	movieDetailsLabel->setText(info);
	movieDetailsLabel->setVisible(true);
}

void UserWidget::showNextMovie()
{
	if (this->moviesByGenre.empty())
	{
		QMessageBox::warning(this, "Warning", "No movies available in the selected genre.");
		return;
	}
	this->currentMovieIndex = (this->currentMovieIndex + 1) % this->moviesByGenre.size();
	this->showMovieInfo();
	std::string url = moviesByGenre[this->currentMovieIndex].getTrailer();
	ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);

}

void UserWidget::filterMoviesByGenre()
{
	std::string genre = genreInput->text().toStdString();
	if (genre.empty())
	{
		QMessageBox::warning(this, "Warning", "Please fill in genre field.");
		return;
	}
	this->moviesByGenre = this->service.getMoviesByGenre(genre);
	if (this->moviesByGenre.empty())
	{
		QMessageBox::warning(this, "Warning", "No movies available in the selected genre.");
		return;
	}

	likeButton->setVisible(true);
	nextButton->setVisible(true);

	this->currentMovieIndex = 0;
	
	std::string url = moviesByGenre[this->currentMovieIndex].getTrailer();
	ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
	
	this->showMovieInfo();
	this->populateTable();
}

void UserWidget::handleUndo()
{
	try
	{
		this->service.executeUndo();
		this->populateTable();
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "Warning", e.what());
	}
}

void UserWidget::handleRedo()
{
	try
	{
		this->service.executeRedo();
		this->populateTable();
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "Warning", e.what());
	}
}
