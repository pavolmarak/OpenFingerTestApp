#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

static inline QImage Mat2QImage(cv::Mat const &mat,
                         QImage::Format format)
{
    return QImage(mat.data, mat.cols, mat.rows,
                  mat.step, format).copy();
}

static inline  cv::Mat QImage2Mat(QImage const &img, int format)
{
    return cv::Mat(img.height(), img.width(), format,
                   const_cast<uchar*>(img.bits()),
                   img.bytesPerLine()).clone();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // preprocessor setup
    // default settings

    // extraction setup
    e.setFeatures(true,true); // enables ISO format export and orientation fixing

    // matcher setup
    m.setMatcher(MATCHER::suprema);

    // signals/slots

    qRegisterMetaType<PREPROCESSING_RESULTS >("PREPROCESSING_RESULTS");
    qRegisterMetaType<EXTRACTION_RESULTS >("EXTRACTION_RESULTS");
    qRegisterMetaType<QVector<MINUTIA> >("QVector<MINUTIA>");

    QObject::connect(&p, SIGNAL(preprocessingDoneSignal(PREPROCESSING_RESULTS)),this,SLOT(preprocessingDoneSlot(PREPROCESSING_RESULTS)));
    QObject::connect(&p, SIGNAL(preprocessingErrorSignal(int)),this,SLOT(preprocessingErrorSlot(int)));

    QObject::connect(&e, SIGNAL(extractionDoneSignal(EXTRACTION_RESULTS)),this,SLOT(extractionDoneSlot(EXTRACTION_RESULTS)));
    QObject::connect(&e, SIGNAL(extractionDoneSignal(QVector<MINUTIA>)),this,SLOT(extractionDoneSlot(QVector<MINUTIA>)));
    QObject::connect(&e, SIGNAL(extractionDoneSignal(unsigned char*)),this,SLOT(extractionDoneSlot(unsigned char*)));
    QObject::connect(&e, SIGNAL(extractionErrorSignal(int)),this,SLOT(extractionErrorSlot(int)));

    QObject::connect(&m, SIGNAL(verificationDoneSignal(bool)),this,SLOT(verificationDoneSlot(bool)));
    QObject::connect(&m, SIGNAL(matcherErrorSignal(int)),this,SLOT(matcherErrorSlot(int)));

    // image zooming
    QObject::connect(ui->img1, SIGNAL(zoomImgSignal(double,QString)),this,SLOT(zoomImgSlot(double,QString)));
    QObject::connect(ui->img2, SIGNAL(zoomImgSignal(double,QString)),this,SLOT(zoomImgSlot(double,QString)));

    // image loading
    path1 = PRO_PWD+QString("/db/")+"8_4.tif";
    path2 = PRO_PWD+QString("/db/")+"15_4.tif";
    this->img1 = cv::imread(path1.toStdString(),cv::IMREAD_GRAYSCALE);
    this->img2 = cv::imread(path2.toStdString(),cv::IMREAD_GRAYSCALE);

    ui->img1->setPixmap(QPixmap(path1).scaledToWidth(IMG_WIDTH));
    ui->img2->setPixmap(QPixmap(path2).scaledToWidth(IMG_WIDTH));

    // load image lists
    QDir dir(PRO_PWD+QString("/db"));
    QFileInfoList ilist = dir.entryInfoList(QStringList() << "*.tif" << "*.png" << "*.jpg" << "*.bmp");
    for(QFileInfo& i : ilist){
        ui->list1->addItem(i.fileName());
        ui->list2->addItem(i.fileName());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::preprocessingDoneSlot(PREPROCESSING_RESULTS pr)
{
//    counter++;
//    if(counter==1){
//        pr1 = pr;
//    }
//    else if(counter==2){
//        pr2 = pr;
//    }
//    e.loadInput(pr);
//    e.start();
}

void MainWindow::preprocessingErrorSlot(int)
{
    qDebug() << "ERROR";
}

void MainWindow::extractionDoneSlot(EXTRACTION_RESULTS er)
{
//    QImage img;
//    if(counter==1){
//       img = Mat2QImage(img1,QImage::Format_Grayscale8);
//    }
//    else{
//       img = Mat2QImage(img2,QImage::Format_Grayscale8);
//    }

//    img = img.convertToFormat(QImage::Format_RGB888);
//    QPainter pnt(&img);

//    pnt.setBrush(Qt::NoBrush);
//    pnt.setPen(QPen(QBrush(QColor(255,0,0)),2));

//    for(MINUTIA& m : er.minutiaePredictedFixed){

//        if(m.type==0){
//            pnt.setPen(QPen(QBrush(QColor(0,255,0)),2));

//        }
//        else{
//            pnt.setPen(QPen(QBrush(QColor(255,0,0)),2));

//        }pnt.drawEllipse(QPoint(m.xy.x(),m.xy.y()),5,5);
//        pnt.drawLine(QPoint(m.xy),QPoint(m.xy.x()+qCos(m.angle)*12,m.xy.y() -qSin(m.angle)*12));
//    }
//    pnt.end();

//    img = img.scaledToWidth(IMG_WIDTH);
//    if(counter==1){
//        ui->img1->setPixmap(QPixmap::fromImage(img));
//    }
//    else{
//        ui->img2->setPixmap(QPixmap::fromImage(img));
//    }

}

void MainWindow::extractionDoneSlot(QVector<MINUTIA>)
{

}

void MainWindow::extractionDoneSlot(unsigned char * iso)
{
//    if(counter==1){
//        template1 = iso;
//    }
//    else{
//        template2 = iso;
//        QVector<unsigned char*> templates2{template2};

//        m.verify(template1,templates2);
//    }
}

void MainWindow::extractionErrorSlot(int)
{
    qDebug() << "ERROR";
}

void MainWindow::verificationDoneSlot(bool vr)
{
    qDebug() << "RESULT: " << vr;
    qDebug() << "Score: " << m.getSupremaMatcher().scores.last();
    if(m.getSupremaMatcher().scores.last() > 0.01){
        ui->score->setText("TRUE");
    }
    else{
        ui->score->setText("FALSE");
    }

}

void MainWindow::matcherErrorSlot(int)
{
    qDebug() << "ERROR";
}

void MainWindow::zoomImgSlot(double scaleFactor, QString imgName)
{
    if(imgName == "img1"){
        ui->img1->setPixmap(QPixmap(path1).scaledToWidth(ui->img1->pixmap()->width()*scaleFactor));
    }
    else if (imgName == "img2"){
        ui->img2->setPixmap(QPixmap(path2).scaledToWidth(ui->img2->pixmap()->width()*scaleFactor));
    }
}

void MainWindow::on_pushButton_clicked()
{
    counter = 0;
    p.loadInput(path1);
    p.start();
    p.loadInput(path2);
    p.start();
}

void MainWindow::on_list2_itemClicked(QListWidgetItem *item)
{
    path2 = PRO_PWD+QString("/db/")+item->text();
    this->img2 = cv::imread(path2.toStdString(),cv::IMREAD_GRAYSCALE);
    ui->img2->setPixmap(QPixmap(path2).scaledToWidth(IMG_WIDTH));
}

void MainWindow::on_list1_itemClicked(QListWidgetItem *item)
{
    path1 = PRO_PWD+QString("/db/")+item->text();
    this->img1 = cv::imread(path1.toStdString(),cv::IMREAD_GRAYSCALE);
    ui->img1->setPixmap(QPixmap(path1).scaledToWidth(IMG_WIDTH));

}

void MainWindow::on_pushButton_2_clicked()
{
    QMap<QString, unsigned char *> fmap;
    QDir dir(PRO_PWD+QString("/db"));
    QFileInfoList ilist = dir.entryInfoList(QStringList() << "*.tif" << "*.png" << "*.jpg" << "*.bmp");
    int ii=0;
    for(QFileInfo& i : ilist){
        p.loadInput(i.absoluteFilePath());
        p.start();
        e.loadInput(p.getBasicResults());
        e.start();
        fmap.insert(i.fileName(), e.getResults().minutiaeISO);
        qDebug() << ii++;
    }
    m.setDBTestParams(100,8);
    m.testDatabase(fmap);
    for(double i: m.getDbtestResult().fmrY){
         std::cout << i;
    }


}
