#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up table headers
    ui->gameTable->setColumnCount(3);
    QStringList headers = {"Name", "Price", "Genre"};
    ui->gameTable->setHorizontalHeaderLabels(headers);
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addGameButton_clicked()
{
    qDebug() << "Add Game Button Clicked";
    // Retrieve and trim input values
    QString name = ui->nameInput->text().trimmed();
    QString priceStr = ui->priceInput->text().trimmed();
    QString genre = ui->genreInput->text().trimmed();

    // Print out the trimmed values for debugging
    qDebug() << "Name: " << name;
    qDebug() << "Price: " << priceStr;
    qDebug() << "Genre: " << genre;

    // Check if any of the fields are empty after trimming
    if (name.isEmpty() || priceStr.isEmpty() || genre.isEmpty()) {
        qDebug() << "Error: One or more fields are empty!";
        QMessageBox::warning(this, "Input Error", "All fields must be filled out!");
        return;
    }

    // Validate that price is a valid number
    bool isPriceValid;
    double price = priceStr.toDouble(&isPriceValid);

    // Debug the result of the price conversion
    qDebug() << "Is price valid: " << isPriceValid;
    qDebug() << "Parsed price value: " << price;

    // Check if the price is a valid number and greater than zero
    if (!isPriceValid || price <= 0) {
        qDebug() << "Error: Invalid price!";
        QMessageBox::warning(this, "Input Error", "Please enter a valid price!");
        return;
    }

    // If all inputs are valid, add the new game to the vector
    qDebug() << "Adding game: " << name << ", Price: " << price << ", Genre: " << genre;
    games.push_back(Game(name, price, genre));

    // Refresh the table to show the new game
    refreshTable();

    // Clear input fields after adding successfully
    ui->nameInput->clear();
    ui->priceInput->clear();
    ui->genreInput->clear();
}

void MainWindow::on_updateGameButton_clicked()
{
    if (selectedRow == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select a game to update!");
        return;
    }

    QString name = ui->nameInput->text().trimmed();
    QString price = ui->priceInput->text().trimmed();
    QString genre = ui->genreInput->text().trimmed();

    // Check if any of the fields are empty after trimming
    if (name.isEmpty() || price.isEmpty() || genre.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out!");
        return;
    }

    // Update the selected game in the vector
    games[selectedRow].name = name;
    games[selectedRow].price = price.toDouble();
    games[selectedRow].genre = genre;

    // Refresh the table to reflect the changes
    refreshTable();

    // Clear input fields and reset selectedRow
    ui->nameInput->clear();
    ui->priceInput->clear();
    ui->genreInput->clear();
    selectedRow = -1;
}


// Delete the selected game from the vector and table
void MainWindow::on_deleteGameButton_clicked()
{
    if (selectedRow == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select a game to delete!");
        return;
    }

    // Remove the selected game from the vector
    games.erase(games.begin() + selectedRow);

    // Refresh the table to reflect the removal
    refreshTable();

    // Clear input fields and reset selectedRow
    ui->nameInput->clear();
    ui->priceInput->clear();
    ui->genreInput->clear();
    selectedRow = -1;
}

// Handle item selection in the table
void MainWindow::on_gameTable_itemClicked(QTableWidgetItem *item)
{
    selectedRow = item->row();

    ui->nameInput->setText(games[selectedRow].name);
    ui->priceInput->setText(QString::number(games[selectedRow].price));
    ui->genreInput->setText(games[selectedRow].genre);
}

// Function to refresh the table after every CRUD operation
void MainWindow::refreshTable()
{
    // Clear the table first
    ui->gameTable->setRowCount(0);

    // Add all games from the vector to the table
    for (size_t i = 0; i < games.size(); ++i) {
        ui->gameTable->insertRow(static_cast<int>(i));
        ui->gameTable->setItem(static_cast<int>(i), 0, new QTableWidgetItem(games[i].name));
        ui->gameTable->setItem(static_cast<int>(i), 1, new QTableWidgetItem(QString::number(games[i].price)));
        ui->gameTable->setItem(static_cast<int>(i), 2, new QTableWidgetItem(games[i].genre));
    }
}


