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

private slots:
    //LOCAL
    void on_actionSave_Location_triggered();
    void on_actionAbout_Finder_triggered();

    //COPY AND PASTE
    void on_pushButton_Dxf_clicked();
    void on_pushButton_Pdf_clicked();
    void on_pushButton_Drawing_clicked();
    void on_pushButton_Check_clicked();

private:
    //LOCAL
    Ui::MainWindow *ui;    
    QLabel *statusLabel;
    void loadSettings();

    //COPY AND PASTE
    void foundIt();
    void notFound();
    void searchingFiles();
    void doesExists(QString);
    void findDrawing(QString);
    void findPdf(QString);
    QString fileNumber;
};

#endif // MAINWINDOW_H
