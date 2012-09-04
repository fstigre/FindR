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

    loadSettings();// call settings
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Drawing_clicked()
{
    QString fileNumber;
    fileNumber = ui->lineEdit_FindPart->text().trimmed();

    if(fileNumber == "0")
    {
        QMessageBox::information(this, "Enter a valid number", "Enter a number other than 0");
    }
    else if(fileNumber == "")
    {
        QMessageBox::information(this, "Empty", "Enter a number");
    }
    else if(fileNumber.contains("A")|| fileNumber.contains("a"))
    {
        findDrawing("A---/");
    }//IF A ends here

    // B doesnt use custom funtions
    else if(fileNumber.contains("B")|| fileNumber.contains("b"))
    {
        //REMOVE LETERS
        if(fileNumber.contains("B"))
        {
            fileNumber.remove("B");
        }
        else if(fileNumber.contains("b"))
        {
            fileNumber.remove("b");
        }

        // CONVERT TO INT BEFORE CHECKING VALUE
        int partNumber = fileNumber.toInt();

        if (partNumber <= 10000)// if part number is between 1 and 10000 use the static directory AND ADD DASH (-)
        {
            searchingFiles();
            //static directory
            QString directoryRange = "B-0001-B10000";
            // assigned to a variable to be able to check the status
            bool linkToDrawing = QDesktopServices::openUrl(QUrl("file:///N:/SolidWorksDrawing/B---/" + directoryRange + "/B" + fileNumber + ".slddrw") );

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

        else
        {
            int directoryMin = (partNumber /1000)* (1000) + 1;// rounding number
            int directoryMax = directoryMin + 999;
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
    }//IF B ends here
    else if(fileNumber.contains("C")|| fileNumber.contains("c"))
    {
        findDrawing("C---/");
    }//IF C
    else if(fileNumber.contains("D")|| fileNumber.contains("d"))
    {
        findDrawing("D---/");
    }//IF D ends here
    else if(fileNumber.contains("E")|| fileNumber.contains("e"))
    {
        findDrawing("E---/");
    }//IF E ends here
    else if(fileNumber.contains("F")|| fileNumber.contains("f"))
    {
        findDrawing("F---/");
    }//IF F ends here
    else if(fileNumber.contains("G")|| fileNumber.contains("g"))
    {
        findDrawing("G/");// no dashes
    }//IF G ends here
    else if(fileNumber.contains("L")|| fileNumber.contains("l"))
    {
        findDrawing("L---/");
    }//IF L ends here
    else if(fileNumber.contains("N")|| fileNumber.contains("n"))
    {
        findDrawing("N---/");
    }//IF N ends here
    else if(fileNumber.contains("R")|| fileNumber.contains("r"))
    {
        findDrawing("R---/");
    }//IF R ends here
    else if(fileNumber.contains("X")|| fileNumber.contains("x"))
    {
        findDrawing("X---/");
    }//IF X ends here

    else if(fileNumber.contains("750"))
    {
        findDrawing("75XXXX/");
    }//IF 750XXX ends here
    else
    {
        notFound();
         QMessageBox::information(this, "Not Found", "You can only search for A, B, C, D, E, F, G, L, N, R, X or 750xxx numbers!");
    }

}//DRAWING ENDS HERE

void MainWindow::on_pushButton_Pdf_clicked()
{
    QString fileNumber;
    fileNumber = ui->lineEdit_FindPart->text().trimmed();

    if(fileNumber == "" )
    {

        QMessageBox::information(this, "Empty", "Enter a number");
    }

    else if(fileNumber == "0" )
    {

        QMessageBox::information(this, "Enter a valid number", "Enter a number other than 0");
    }

    else if(fileNumber.contains("A")|| fileNumber.contains("a"))
    {
        findPdf("A---/");
    }//IF A ends here

    else if(fileNumber.contains("B")|| fileNumber.contains("b"))
    {
        findPdf("B---/");
    }//IF B ends here


    else if(fileNumber.contains("C")|| fileNumber.contains("c"))
    {
        findPdf("C---/");
    }//IF C ends here

    else if(fileNumber.contains("D")|| fileNumber.contains("d"))
    {
       findPdf("D---/");
    }//IF D ends here

    else if(fileNumber.contains("E")|| fileNumber.contains("e"))
    {
        findPdf("E---/");
    }//IF E ends here

    else if(fileNumber.contains("F")|| fileNumber.contains("f"))
    {
        findPdf("F---/");
    }//IF F ends here

    else if(fileNumber.contains("G")|| fileNumber.contains("g"))
    {
        findPdf("G/");
    }//IF G ends here

    else if(fileNumber.contains("L")|| fileNumber.contains("l"))
    {
        findPdf("L---/");
    }//IF L ends here

    else if(fileNumber.contains("N")|| fileNumber.contains("n"))
    {
        findPdf("N---/");
    }//IF N ends here

    else if(fileNumber.contains("R")|| fileNumber.contains("r"))
    {
        findPdf("R---/");
    }//IF R ends here

    else if(fileNumber.contains("X")|| fileNumber.contains("x"))
    {
        findPdf("X---/");
    }//IF X ends here

    else if(fileNumber.contains("750")|| fileNumber.contains("x"))
    {        
        findPdf("75XXXX/");
    }//IF 750xxx ends here
    else
    {
        notFound();
        QMessageBox::information(this, "Not Found", "You can only search for A, B, C, D, E, F, G, L, N, R, X or 750xxx numbers!");
    }


}//PDF ENDS HERE

//when looking for dxf there are no restrictions on file numbers
void MainWindow::on_pushButton_Dxf_clicked()
{
    QString fileNumber;
    fileNumber = ui->lineEdit_FindPart->text().trimmed();

    if(fileNumber == "" )
    {
        QMessageBox::information(this, "Empty", "Enter a number");
    }
    else if(fileNumber == "0" )
    {        
        QMessageBox::information(this, "Enter a valid number", "Enter a number other than 0");
    }

    else
    {
        searchingFiles();
        // assigned to a variable to be able to check the status
         bool linkToDxf = QDesktopServices::openUrl(QUrl("file:///P:/SW_Track/" + fileNumber + ".dxf") );

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
}//DXF ENDS HERE

void MainWindow::on_pushButton_Check_clicked()
{
    fileNumber = ui->lineEdit_FindPart->text().trimmed();

    // SHOW PART NUMBER
    ui->label_LastChecked->setText(fileNumber);

    if(fileNumber == "0")
    {
        QMessageBox::information(this, "Enter a valid number", "Enter a number other than 0");
    }
    else if(fileNumber == "")
    {
        QMessageBox::information(this, "Empty", "Enter a number");
    }
    else if(fileNumber.contains("A")|| fileNumber.contains("a"))
    {
        doesExists("A---/");
    }// IF A ends here
    // B doesnt use custom funtions
    else if(fileNumber.contains("B")|| fileNumber.contains("b"))
    {
        if(fileNumber.contains("B"))
        {
            fileNumber.remove("B");
        }
        else if(fileNumber.contains("b"))
        {
            fileNumber.remove("b");
        }

        int partNumber = fileNumber.toInt();

     if (partNumber <= 10000)// if part number is between 1 and 10000 use the static directory
            {
                QFile drawing("N:/SolidWorksDrawing/B---/B-0001-B10000/B" + fileNumber + ".slddrw"); // added B since it was removed
                QFile pdf("P:/S_Works-Dwgs/B---/B" + fileNumber + ".pdf");// added B since it was removed
                QFile dxf("P:/SW_Track/B" + fileNumber + ".dxf");// added B since it was removed

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
                int partNumber = fileNumber.toInt();
                int directoryMin = (partNumber /1000)* (1000) + 1;// rounding number
                int directoryMax = directoryMin + 999;

                QString directoryRange = "B" + QString::number(directoryMin)+ "-" +  "B" + QString::number(directoryMax);
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

    }//IF B ends here
    else if(fileNumber.contains("C")|| fileNumber.contains("c"))
    {
        doesExists("C---/");
    }//IF C ends here
    else if(fileNumber.contains("D")|| fileNumber.contains("d"))
    {
        doesExists("D---/");
    }//IF D ends here
    else if(fileNumber.contains("E")|| fileNumber.contains("e"))
    {
         doesExists("E---/");
    }//IF E ends here
    else if(fileNumber.contains("F")|| fileNumber.contains("f"))
    {
         doesExists("F---/");
    }//IF F ends here
    else if(fileNumber.contains("G")|| fileNumber.contains("g"))
    {
        doesExists("G/");
    }//IF G ends here
    else if(fileNumber.contains("L")|| fileNumber.contains("l"))
    {
         doesExists("L---/");
    }//IF L ends here
    else if(fileNumber.contains("N")|| fileNumber.contains("n"))
    {
         doesExists("N---/");
    }//IF N ends here
    else if(fileNumber.contains("R")|| fileNumber.contains("r"))
    {
         doesExists("R---/");
    }//IF R ends here
    else if(fileNumber.contains("X")|| fileNumber.contains("x"))
    {
         doesExists("X---/");
    }//IF X ends here
    else if(fileNumber.contains("750")|| fileNumber.contains("x"))
    {
         doesExists("75XXXX/");
    }//IF 750XXX ends here
    else
    {
        notFound();
        QMessageBox::information(this, "Not Found", "You can only search for A, B, C, D, E, F, G, L, N, R, X or 750xxx numbers!");
    }

}//CHECK ENDS HERE

void MainWindow::foundIt()
{
    QString partNum = "             " + ui->lineEdit_FindPart->text() + ", was successfully found";
    ui->statusBar->showMessage(partNum,10000);
}
void MainWindow::notFound()
{
    QString partNum = "             " + ui->lineEdit_FindPart->text() + ", was not found";
    ui->statusBar->showMessage(partNum,5000);
}
void MainWindow::searchingFiles()
{
    QString partNum = "            Searching for " + ui->lineEdit_FindPart->text()+ "...";
     ui->statusBar->showMessage(partNum);
}

// CUSTOM FUNCTION, this function is used in the check funtion
void MainWindow::doesExists(QString sufix)
{
    QString folder = sufix;
    QFile drawing("N:/SolidWorksDrawing/"+folder + fileNumber + ".slddrw");
    QFile pdf("P:/S_Works-Dwgs/"+folder + fileNumber + ".pdf");
    QFile dxf("P:/SW_Track/" + fileNumber + ".dxf");


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
// CUSTOM FUNCTION, this function is used in the dawing function
void MainWindow::findDrawing(QString partDirectory)
{
   QString partDir = partDirectory;

   // without assigning this here it doesnt capture the part number entered
   fileNumber = ui->lineEdit_FindPart->text().trimmed();
   searchingFiles();
   //converting ints to strings and concatinating them
    bool linkToDrawing = QDesktopServices::openUrl(QUrl("file:///N:/SolidWorksDrawing/" + partDir + fileNumber + ".slddrw") );

   if(linkToDrawing !=true)
   {
       notFound();
       QMessageBox::information(this, "Not Found", "The drawing you are looking for was not found in this directory");
   }
   else
   {
       foundIt();
   }

}// find drawing

void MainWindow::findPdf(QString partDirectoryDxf)
{
    QString partDirDxf   = partDirectoryDxf;

    // without assigning this here it doesnt capture the part number entered
    fileNumber = ui->lineEdit_FindPart->text().trimmed();

    searchingFiles();
    // assigned to a variable to be able to check the status
    bool linkToPdf = QDesktopServices::openUrl(QUrl("file:///P:/S_Works-Dwgs/"+ partDirDxf + fileNumber + ".pdf") );

    if(linkToPdf!= true)
    {
        notFound();
        QMessageBox::information(this, "Not Found", "The PDF you are looking for was not found in this directory");
    }
    else
    {
        foundIt();
    }
} // find pdf

//***********************************************
//************** LOCAL FINDR ********************
//********* DO NOT TRANSFER TO TOOL *************
//***********************************************

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
                           "<p>Version 2.0</p>"
    "<p>Copyright &copy; 2012 tuDesign. All Rights Reserved.</p>"
    "<p>FindR was exclusively designed for the engineers at Kenall Manufacturing!"

      ));
}

