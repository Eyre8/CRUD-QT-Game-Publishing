#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <vector>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Game {
    QString name;
    double price;
    QString genre;

    Game(const QString& n, double p, const QString& g)
        : name(n), price(p), genre(g) {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addGameButton_clicked();
    void on_updateGameButton_clicked();
    void on_deleteGameButton_clicked();
    void on_gameTable_itemClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    std::vector<Game> games;  // Vector to store games
    int selectedRow = -1;  // For tracking the selected row for editing/deleting

    void refreshTable();  // Function to refresh the table
};

#endif // MAINWINDOW_H
