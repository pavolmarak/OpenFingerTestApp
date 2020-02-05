#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "preprocessing.h"
#include "extraction.h"
#include "matcher.h"
#include "zoomlabel.h"

#define IMG_WIDTH 600

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Preprocessing p;
    Extraction e;
    Matcher m;
    cv::Mat img1,img2;
    QString path1,path2;
    PREPROCESSING_RESULTS pr1,pr2;
    unsigned char* template1,*template2;
    int counter{0};

private slots:
    void preprocessingDoneSlot(PREPROCESSING_RESULTS);
    void preprocessingErrorSlot(int);

    void extractionDoneSlot(EXTRACTION_RESULTS);
    void extractionDoneSlot(QVector<MINUTIA>);
    void extractionDoneSlot(unsigned char*);
    void extractionErrorSlot(int);

    void verificationDoneSlot(bool);
    void matcherErrorSlot(int);

    void zoomImgSlot(double,QString);

    void on_pushButton_clicked();
    void on_list2_itemClicked(QListWidgetItem *item);
    void on_list1_itemClicked(QListWidgetItem *item);
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
