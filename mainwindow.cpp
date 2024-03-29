#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtGui>
#include <QtCore>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QClipboard>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView_Drawing->setStyleSheet("background-color:#FFD700");
    ui->graphicsView_Pdf->setStyleSheet("background-color:#FFD700");
    ui->graphicsView_Dxf->setStyleSheet("background-color:#FFD700");
     // statusbar label
    statusLabel = new QLabel(this);
    statusLabel->setText("            Status");
    ui->statusBar->addWidget(statusLabel);
    ui->statusBar->setStyleSheet("color:#333");

    ui->lineEdit_Sufix->setReadOnly(true);

    loadSettings();// call settings
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::foundIt()
{
    QString partNum = "            B" + ui->lineEdit_FindPart->text() + ", was successfully found";
    ui->statusBar->showMessage(partNum,10000);
}
void MainWindow::foundItLessThan()
{
    QString partNum = "            B-" + ui->lineEdit_FindPart->text() + ", was successfully found";
    ui->statusBar->showMessage(partNum,10000);
}

void MainWindow::notFound()
{
    QString partNum = "            B" + ui->lineEdit_FindPart->text() + ", was not found";
    ui->statusBar->showMessage(partNum,5000);
}
void MainWindow::notFoundLessThan()
{
    QString partNum = "            B-" + ui->lineEdit_FindPart->text() + ", was not found";
    ui->statusBar->showMessage(partNum,5000);
}

void MainWindow::searchingFiles()
{
    QString partNum = "            Searching for B" + ui->lineEdit_FindPart->text()+ "...";
     ui->statusBar->showMessage(partNum);
}

void MainWindow::on_pushButton_Dxf_clicked()
{
    QString fileNumber;
    fileNumber = ui->lineEdit_FindPart->text();

    int partNumber = fileNumber.toInt();

    if(fileNumber == "" )
    {
        QMessageBox::information(this, "Empty", "Enter a number");
    }
    else if(fileNumber == "0" )
    {        
        QMessageBox::information(this, "Enter a valid number", "Enter a number other than 0");
    }
    else if (partNumber <= 10000)// IF PART LESS THAN 10000, ADD DASH (-)
    {
         searchingFiles();
         // assigned to a variable to be able to check the status
         bool linkToDxf = QDesktopServices::openUrl(QUrl("file:///P:/SW_Track/B-" + fileNumber + ".dxf") );

         if(linkToDxf !=true)
         {
             notFoundLessThan();
             QMessageBox::information(this, "Not Found", "The DXF you are looking for was not found in this directory");
         }
         else
         {
             foundItLessThan();
         }

    }
    else
    {
        searchingFiles();
        // assigned to a variable to be able to check the status
         bool linkToDxf = QDesktopServices::openUrl(QUrl("file:///P:/SW_Track/B" + fileNumber + ".dxf") );

         if(linkToDxf !=true)
         {
             notFound();
             QMessageBox::information(this, "Not Found", "The DXF you are looking for was not found in this directory");
         }
         else
         {
             foundIt();
         }
    }
}


void MainWindow::on_pushButton_Pdf_clicked()
{
    QString fileNumber;
    fileNumber = ui->lineEdit_FindPart->text();

    int partNumber = fileNumber.toInt();

    if(fileNumber == "" )
    {

        QMessageBox::information(this, "Empty", "Enter a number");
    }

    else if(fileNumber == "0" )
    {

        QMessageBox::information(this, "Enter a valid number", "Enter a number other than 0");
    }
    else if (partNumber <= 10000) // IF PART LESS THAN 10000, ADD DASH (-)
    {
        searchingFiles();
        // assigned to a variable to be able to check the status
        bool linkToPdf = QDesktopServices::openUrl(QUrl("file:///P:/S_Works-Dwgs/B---/B-" + fileNumber + ".pdf") );

        if(linkToPdf!= true)
        {
            notFoundLessThan();
            QMessageBox::information(this, "Not Found", "The PDF you are looking for was not found in this directory");
        }
        else
        {
            foundItLessThan();
        }

    }

    else
    {
        searchingFiles();
        // assigned to a variable to be able to check the status
        bool linkToPdf = QDesktopServices::openUrl(QUrl("file:///P:/S_Works-Dwgs/B---/B" + fileNumber + ".pdf") );

        if(linkToPdf!= true)
        {
            notFound();
            QMessageBox::information(this, "Not Found", "The PDF you are looking for was not found in this directory");
        }
        else
        {
            foundIt();
        }
    }

}

void MainWindow::on_pushButton_Drawing_clicked()
{
    QString fileNumber;
    fileNumber = ui->lineEdit_FindPart->text();

    int partNumber = fileNumber.toInt();
    int directoryMin = (partNumber /1000)* (1000) + 1;// rounding number
    int directoryMax = directoryMin + 999;

    if(fileNumber == "0")
    {

        QMessageBox::information(this, "Enter a valid number", "Enter a number other than 0");
    }
    else if(fileNumber == "")
    {

        QMessageBox::information(this, "Empty", "Enter a number");
    }
    else if (partNumber <= 10000)// if part number is between 1 and 10000 use the static directory AND ADD DASH (-)
    {
        searchingFiles();
        //static directory
        QString directoryRange = "B-0001-B10000";
        // assigned to a variable to be able to check the status
        bool linkToDrawing = QDesktopServices::openUrl(QUrl("file:///N:/SolidWorksDrawing/B---/" + directoryRange + "/B-" + fileNumber + ".slddrw") );

        if(linkToDrawing !=true)
        {
            notFoundLessThan();
            QMessageBox::information(this, "Not Found", "The drawing you are looking for was not found in this directory");
        }
        else
        {
             foundItLessThan();
        }

    }

    else
    {
        searchingFiles();
        //converting ints to strings and concatinating them
        QString directoryRange = "B"+ QString::number(directoryMin)+ "-" + "B" + QString::number(directoryMax);
        bool linkToDrawing = QDesktopServices::openUrl(QUrl("file:///N:/SolidWorksDrawing/B---/" + directoryRange + "/b" + fileNumber + ".slddrw") );

        if(linkToDrawing !=true)
        {
            notFound();
            QMessageBox::information(this, "Not Found", "The drawing you are looking for was not found in this directory");
        }
        else
        {
             foundIt();
        }

    }

}


void MainWindow::on_pushButton_Check_clicked()
{
    QString fileNumber;
    fileNumber = ui->lineEdit_FindPart->text();


    int partNumber = fileNumber.toInt();
    int directoryMin = (partNumber /1000)* (1000) + 1;// rounding number
    int directoryMax = directoryMin + 999;

    if(fileNumber == "0")
    {
        QMessageBox::information(this, "Enter a valid number", "Enter a number other than 0");
    }
    else if(fileNumber == "")
    {
        QMessageBox::information(this, "Empty", "Enter a number");
    }
    else if (partNumber <= 10000)// if part number is between 1 and 10000 use the static directory AND ADD DASH (-)
    {
        //SHOW PART NUMBER
        ui->label_LastChecked->setText("B-"+fileNumber);

        //static directory
        QString directoryRange = "B-0001-B10000";

        QFile drawing("N:/SolidWorksDrawing/B---/" + directoryRange + "/B-" + fileNumber + ".slddrw");
        QFile pdf("P:/S_Works-Dwgs/B---/B-" + fileNumber + ".pdf");
        QFile dxf("P:/SW_Track/B-" + fileNumber + ".dxf");

        if(drawing.exists())
        {
           ui->graphicsView_Drawing->setStyleSheet("background-color:#00ff00");
        }
        else
        {
          ui->graphicsView_Drawing->setStyleSheet("background-color:#ff0000");
        }

        // PDF
        if(pdf.exists())
        {
           ui->graphicsView_Pdf->setStyleSheet("background-color:#00ff00");
        }
        else
        {
          ui->graphicsView_Pdf->setStyleSheet("background-color:#ff0000");
        }

        // DXF
        if(dxf.exists())
        {
           ui->graphicsView_Dxf->setStyleSheet("background-color:#00ff00");
        }
        else
        {
          ui->graphicsView_Dxf->setStyleSheet("background-color:#ff0000");
        }
    }

    else
    {
        //SHOW PART NUMBER
        ui->label_LastChecked->setText("B"+fileNumber);

        //converting ints to strings and concatinating them
        QString directoryRange = "B"+ QString::number(directoryMin)+ "-" + "B" + QString::number(directoryMax);
        QFile drawing("N:/SolidWorksDrawing/B---/" + directoryRange + "/B" + fileNumber + ".slddrw");
        QFile pdf("P:/S_Works-Dwgs/B---/B" + fileNumber + ".pdf");
        QFile dxf("P:/SW_Track/B" + fileNumber + ".dxf");

        if(drawing.exists())
        {
           ui->graphicsView_Drawing->setStyleSheet("background-color:#00ff00");
        }
        else
        {
          ui->graphicsView_Drawing->setStyleSheet("background-color:#ff0000");
        }

        // PDF
        if(pdf.exists())
        {
           ui->graphicsView_Pdf->setStyleSheet("background-color:#00ff00");
        }
        else
        {
          ui->graphicsView_Pdf->setStyleSheet("background-color:#ff0000");
        }

        // DXF
        if(dxf.exists())
        {
           ui->graphicsView_Dxf->setStyleSheet("background-color:#00ff00");
        }
        else
        {
          ui->graphicsView_Dxf->setStyleSheet("background-color:#ff0000");
        }

    }

}//CHECK ENDS HERE
void MainWindow::on_actionSave_Location_triggered()
{
    ui->statusBar->showMessage("         Saving layout...", 400);
    QSettings settings("tuDesign", "FindR");
    settings.setValue("geometry", saveGeometry());
    QMessageBox::information(this,"Save Layout","Layout has been saved");
}

void MainWindow::loadSettings()
{
    QSettings settings("tuDesign", "FindR");
    restoreGeometry(settings.value("geometry").toByteArray());

}

void MainWindow::on_actionAbout_Finder_triggered()
{
    QMessageBox::about(this, tr("About FindR"),
                       tr( "<img src=':/icons/images/FindRLogo-80x256.png'/>"
                           "<h2>FindR</h2>"
                           "<p>Version 1.0</p>"
    "<p>Copyright &copy; 2012 tuDesign. All Rights Reserved.</p>"
    "<p>FindR was exclusively designed for the engineers at Kenall Manufacturing!"

      ));
}

