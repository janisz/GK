#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    //Set constans and variables
    shapeList.append("Line");
    shapeList.append("Circle");
    shapeList.append("AACircle");
    shapeList.append("Rectangle");
    shapeList.append("Polygon");
    shapeList.append("StrongLine");
    shapeList.append("StrongCircle");

    //Create UI
    setFixedSize(1010, 630);
    setWindowTitle("Grafika Komputerowa");

    paintArea = new PaintArea(this);
    paintArea->show();

    leftPanelWidget = new QWidget(this);
    leftPanelWidget->setGeometry(800, 0, 210, 630);
    leftPanelLayout = new QVBoxLayout();
    leftPanelWidget->setLayout(leftPanelLayout);

    statusBar = new QStatusBar(this);
    statusBar->showMessage("Started working", 5);
    statusBar->setGeometry(0, 600, 100, 20);
    statusBar->show();

    showGridCheckBox = new QCheckBox(this);
    showGridCheckBox->setText("Show Grid");
    leftPanelLayout->addWidget(showGridCheckBox);

    gapSizeSpinBox = new QSpinBox(this);
    gapSizeSpinBox->setMinimum(1);
    gapSizeSpinBox->setMaximum(600);
    gapSizeSpinBox->setValue(100);
    leftPanelLayout->addWidget(gapSizeSpinBox);

    colorChooseButton = new QPushButton("Line color", this);
    leftPanelLayout->addWidget(colorChooseButton);

//    fillColorChooseButton = new QPushButton("Fill Color", this);
//    leftPanelLayout->addWidget(fillColorChooseButton);

    textureChooseButton = new QPushButton("Texture", this);
    leftPanelLayout->addWidget(textureChooseButton);

    filledCheckBox = new QCheckBox("Fill", this);
    leftPanelLayout->addWidget(filledCheckBox);

    shapeChooserComboBox = new QComboBox(this);
    shapeChooserComboBox->addItems(shapeList);
    leftPanelLayout->addWidget(shapeChooserComboBox);

    testButton = new QPushButton("Test",  this);
    leftPanelLayout->addWidget(testButton);

    newLineButton = new QPushButton("Line", this);
    leftPanelLayout->addWidget(newLineButton);

    colorModelComboBox = new QComboBox(this);
    colorModelComboBox->addItem("RGB");
    colorModelComboBox->addItem("HSV");
    colorModelComboBox->addItem("XYZ");
    leftPanelLayout->addWidget(colorModelComboBox);

    colorMap = new QLabel(this);
    colorMap->resize(200, 200);
    colorMapImage = QImage(200, 200, QImage::Format_RGB16);
    colorMapImage.fill(Qt::red);
    colorMap->setPixmap(QPixmap::fromImage(colorMapImage));
    leftPanelLayout->addWidget(colorMap);

    colorIntensivitySlider = new QSlider(Qt::Horizontal, this);
    colorIntensivitySlider->setRange(0, 100);
    leftPanelLayout->addWidget(colorIntensivitySlider);



    colorValueEdit = new QSpinBox*[3];
    for (int i=0;i<3;i++)
    {
        colorValueEdit[i] = new QSpinBox(this);
        colorValueEdit[i]->setRange(0, 100);
        colorValueEdit[i]->setSingleStep(1);
        colorValueEdit[i]->setPrefix("X:\t");
        leftPanelLayout->addWidget(colorValueEdit[i]);
        connect(colorValueEdit[i], SIGNAL(valueChanged(int)), this, SLOT(ChangeColorSpinBox()));
    }
    colorValueEdit[0]->setPrefix("R:\t");
    colorValueEdit[1]->setPrefix("G:\t");
    colorValueEdit[2]->setPrefix("B:\t");

    colorCountSlider = new QSlider(Qt::Horizontal, this);
    colorCountSlider->setRange(2, 512);
    colorCountSlider->setTickInterval(10);
    leftPanelLayout->addWidget(colorCountSlider);

    connect (showGridCheckBox, SIGNAL(clicked()), this, SLOT(ShowGrid()));
    connect (gapSizeSpinBox, SIGNAL(editingFinished()), this, SLOT(ShowGrid()));
    connect (gapSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ShowGrid()));
    connect (colorChooseButton, SIGNAL(clicked()), this, SLOT(ChangeLineColor()));
    connect (testButton, SIGNAL(clicked()), this, SLOT(RunTest()));
    connect (newLineButton, SIGNAL(clicked()), this, SLOT(NewLine()));
    connect (shapeChooserComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeShape()));
    connect (filledCheckBox, SIGNAL(clicked()), this, SLOT(SetFill()));
    connect (textureChooseButton, SIGNAL(clicked()), this, SLOT(ChangeFillTexture()));
    connect (colorCountSlider, SIGNAL(valueChanged(int)), this, SLOT(ChangeFillTextureColors()));
    connect (colorModelComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangePalette()));
    connect (colorIntensivitySlider, SIGNAL(valueChanged(int)), this, SLOT(MoveSlider()));

    setMouseTracking(true);

//    Colors::Quantize("/tmp/tux.ppm", 30);
//    QImage im;
//    im.load("/tmp/t.ppm");
//    qDebug() << im.bits();
//    Colors::Quantize("/tmp/tux.ppm", 3);
//    Colors::Quantize(im.scanLine(0), im.width(), im.height(), 2);
}


QColor Hsv2Rgb(int h, int s, int v)
{
    QColor color;
    float* c = hsv2rgb(h, s/100.0, v/100.0);
    color.setRgb(c[0]*255, c[1]*255, c[2]*255);
    delete c;
    return color;
}

bool validColor = true;

QColor Xyz2Rgb(int x, int y, int z)
{
    QColor color;
    float* c = xyz2rgb(x*0.009, y*0.009, z*0.009);
    validColor = (c[0] < 0 || c[1] < 0 || c[2] < 0) || (c[0] > 1 || c[1] > 1|| c[2] > 1);
//    c[2]= MIN(1.0f,MAX(0.0f,c[2]));
//    c[0]= MIN(1.0f,MAX(0.0f,c[0]));
//    c[1]= MIN(1.0f,MAX(0.0f,c[1]));
    if (validColor) c[0] = c[1] = c[2] = 0;
    color.setRgb(c[0]*255.0, c[1]*255.0, c[2]*255.0);
    delete c;
    return color;
}

QImage setRgbPalete(int r)
{
    QImage img(200, 200, QImage::Format_RGB16);
    for (int i=0;i<200;i++)
    {
        for (int j=0;j<200;j++)
        {
            QColor c(r*2.55, i*2.55/2, j*2.55/2);
            img.setPixel(i, j, c.rgb());
        }
    }
    return img;
}

QImage setHsvPalete(int h)
{
    QImage img(200, 200, QImage::Format_RGB16);
    for (int i=0;i<200;i++)
    {
        for (int j=0;j<200;j++)
        {
            QColor c = Hsv2Rgb(h*3.59, i/2, j/2);
            img.setPixel(i, j, c.rgb());
        }
    }
    return img;
}

QImage setXyzPalete(int x)
{
    QImage img(200, 200, QImage::Format_RGB16);
    for (int i=0;i<200;i++)
    {
        for (int j=0;j<200;j++)
        {
            QColor c = Xyz2Rgb(x, i/2, j/2);
            img.setPixel(i, j, c.rgb());
        }
    }
    return img;
}

QImage MainWindow::setPalete(int x)
{
    if (colorModelComboBox->currentIndex() == 0) //RGB
        return setRgbPalete(x);
    if (colorModelComboBox->currentIndex() == 1) //HSV
        return setHsvPalete(x);
    if (colorModelComboBox->currentIndex() == 2) //XYZ
        return setXyzPalete(x);
}

void MainWindow::RunTest()
{
    paintArea->RunTest();
}

void MainWindow::ChangePalette()
{
    if (colorModelComboBox->currentIndex() == 0) //RGB
    {
        QColor sc = selectedColor;
        colorValueEdit[0]->setValue(round(sc.red()/2.55));
        colorValueEdit[1]->setValue(round(sc.green()/2.55));
        colorValueEdit[2]->setValue(round(sc.blue()/2.55));
        colorValueEdit[0]->setPrefix("R:\t");
        colorValueEdit[1]->setPrefix("G:\t");
        colorValueEdit[2]->setPrefix("B:\t");
    }
    if (colorModelComboBox->currentIndex() == 1) //HSV
    {
        float r = selectedColor.redF();
        float g = selectedColor.greenF();
        float b = selectedColor.blueF();
        float* c = rgb2hsv(r, g, b);
        colorValueEdit[0]->setPrefix("H:\t");
        colorValueEdit[1]->setPrefix("S:\t");
        colorValueEdit[2]->setPrefix("V:\t");
        colorValueEdit[0]->setValue(round(c[0]/3.59));
        colorValueEdit[1]->setValue(round(c[1]*100));
        colorValueEdit[2]->setValue(round(c[2]*100));
        delete c;
    }
    if (colorModelComboBox->currentIndex() == 2) //CIE
    {
        float r = selectedColor.redF();
        float g = selectedColor.greenF();
        float b = selectedColor.blueF();
        float* c = rgb2xyz(r, g, b);
        colorValueEdit[0]->setValue(round(c[0]*100));
        colorValueEdit[1]->setValue(round(c[1]*100));
        colorValueEdit[2]->setValue(round(c[2]*100));
        delete c;
        colorValueEdit[0]->setPrefix("X:\t");
        colorValueEdit[1]->setPrefix("Y:\t");
        colorValueEdit[2]->setPrefix("Z:\t");
    }
    ChangeFillColor();
}

void MainWindow::NewLine()
{
    int x0, y0, x1, y1;
    x0 = y0 = x1 = y1 = 0;

    x0 = QInputDialog::getInteger(this, "Insert value", "X0");
    y0 = QInputDialog::getInteger(this, "Insert value", "Y0");
    x1 = QInputDialog::getInteger(this, "Insert value", "X1");
    y1 = QInputDialog::getInteger(this, "Insert value", "Y1");

    paintArea->AddLine(x0, x1, y0, y1);
}

void MainWindow::ChangeLineColor()
{
    paintArea->SetLineColor(QColorDialog::getColor(Qt::red, this ));
}

void MainWindow::ChangeColor()
{
    if (colorModelComboBox->currentIndex() == 0) //RGB
    {
        selectedColor = QColor(colorValueEdit[0]->value() * 2.55,
                               colorValueEdit[1]->value() * 2.55,
                               colorValueEdit[2]->value() * 2.55);
    }
    if (colorModelComboBox->currentIndex() == 1) //HSV
    {
        selectedColor = Hsv2Rgb(colorValueEdit[0]->value()*3.59,
                                colorValueEdit[1]->value(),
                                colorValueEdit[2]->value());
    }
    if (colorModelComboBox->currentIndex() == 2) //CIE
    {
        selectedColor = Xyz2Rgb(colorValueEdit[0]->value(),
                                colorValueEdit[1]->value(),
                                colorValueEdit[2]->value());
        if (validColor)
        {
            QMessageBox msgBox;
            msgBox.setText("Color errr");
            msgBox.setInformativeText("Not supported color?");
            int ret = msgBox.exec();
        }
    }
}

void MainWindow::ClickOnColorLabel()
{
    ChangeFillColor();
}

void MainWindow::ChangeColorSpinBox()
{
    colorIntensivitySlider->setValue(colorValueEdit[0]->value());
    ChangeFillColor();
}

void MainWindow::MoveSlider()
{
    colorValueEdit[0]->setValue(colorIntensivitySlider->value());
    ChangeFillColor();
}

void MainWindow::ChangeFillColor()
{
    ChangeColor();
    QColor c = selectedColor;
    qDebug() << c;
    QImage img(1, 1, QImage::Format_ARGB32);
    img.fill(c);
    colorMapImage = setPalete(colorValueEdit[0]->value());
    for (int i=0;i<5;i++)
    {
        colorMapImage.setPixel(colorValueEdit[1]->value()*2+i+2, colorValueEdit[2]->value() *2, 0xffffff);
        colorMapImage.setPixel(colorValueEdit[1]->value()*2-i-2, colorValueEdit[2]->value() *2, 0xffffff);
        colorMapImage.setPixel(colorValueEdit[1]->value()*2,   colorValueEdit[2]->value() *2+i+2, 0xffffff);
        colorMapImage.setPixel(colorValueEdit[1]->value()*2,   colorValueEdit[2]->value() *2-i-2, 0xffffff);
    }
    colorMap->setPixmap(QPixmap::fromImage(colorMapImage));
    paintArea->ChangeTexture(img);
}

QString fileName = "tux.ppm";

void MainWindow::ChangeFillTexture()
{
    QImage img;
    fileName = QFileDialog::getOpenFileName(this,
         tr("Open Image"), "", tr("Image Files (*.ppm)"));
    Colors::Quantize(fileName.toStdString().c_str(), colorCountSlider->value());
    if (!img.load("out.ppm"))
        return;
    paintArea->ChangeTexture(img);
}

void MainWindow::ChangeFillTextureColors()
{
    QImage img;
    statusBar->showMessage(QString("Count: %1").arg(colorCountSlider->value()));
    Colors::Quantize(fileName.toStdString().c_str(), colorCountSlider->value());
    if (!img.load("out.ppm"))
        return;
    paintArea->ChangeTexture(img);
}

void MainWindow::SetFill()
{
    paintArea->Fill(filledCheckBox->isChecked());
}

void MainWindow::ChangeShape()
{
    paintArea->SetCurrentShape((Globals::ShapeType)shapeChooserComboBox->currentIndex());
}

void MainWindow::ShowGrid()
{
    paintArea->SetGridVisibility(showGridCheckBox->isChecked());
    paintArea->SetGridGap(gapSizeSpinBox->value());
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    statusBar->showMessage(QString("X:%1 \t Y:%2").arg(event->pos().x()).arg(event->pos().y()));
}

void MainWindow::moveEvent(QMoveEvent *event)
{


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QRect widgetRect = colorMap->geometry();
    widgetRect.moveTopLeft(colorMap->parentWidget()->mapToGlobal(widgetRect.topLeft()));
    if (widgetRect.contains(QCursor::pos()))
    {
        int x = colorMap->rect().right()  - event->pos().x() + leftPanelWidget->pos().x() + colorMap->pos().x()+10;
        int y = colorMap->rect().bottom() - event->pos().y() + colorMap->pos().y() + leftPanelWidget->pos().y()-15;
        if (x <= 200 && x >= 0 && y <= 200 && y >= 0)
        {
            colorValueEdit[1]->setValue(100-x/2);
            colorValueEdit[2]->setValue(100-y/2);
            update();
        }
    }
    event->accept();
}

MainWindow::~MainWindow()
{
    
}
