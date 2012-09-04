#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtGui>
#include <QtCore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadSettings();
    void foundIt();
    void foundItLessThan();
    void searchingFiles();
    void notFound();
    void notFoundLessThan();

private slots:
    void on_pushButton_Dxf_clicked();
    void on_pushButton_Pdf_clicked();
    void on_pushButton_Drawing_clicked();
    
    void on_actionSave_Location_triggered();

    void on_actionAbout_Finder_triggered();

    void on_pushButton_Check_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;
};

#endif // MAINWINDOW_H
