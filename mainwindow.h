#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
   void handleButton();
private:
    Ui::MainWindow *ui;
    QPushButton *m_button;
    QTextEdit *m_textEdit;
};

#endif // MAINWINDOW_H
