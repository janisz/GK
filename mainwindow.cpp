#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    //Set constans and variables
    shapeList.append("Line");
    shapeList.append("Circle");
    shapeList.append("AACircle");
    shapeList.append("Ellipse");
    shapeList.append("Polygon");
    shapeList.append("StrongLine");
    shapeList.append("StrongCircle");

    //Create UI
    setFixedSize(1000, 620);
    setWindowTitle("Grafika Komputerowa");

    paintArea = new PaintArea(this);
    paintArea->show();

    leftPanelWidget = new QWidget(this);
    leftPanelWidget->setGeometry(800, 0, 200, 600);
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

    connect (showGridCheckBox, SIGNAL(clicked()), this, SLOT(ShowGrid()));
    connect (gapSizeSpinBox, SIGNAL(editingFinished()), this, SLOT(ShowGrid()));
    connect (gapSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ShowGrid()));
    connect (colorChooseButton, SIGNAL(clicked()), this, SLOT(ChangeColor()));
    connect (testButton, SIGNAL(clicked()), this, SLOT(RunTest()));
    connect (newLineButton, SIGNAL(clicked()), this, SLOT(NewLine()));
    connect (shapeChooserComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeShape()));
    connect (filledCheckBox, SIGNAL(clicked()), this, SLOT(SetFill()));
    connect (textureChooseButton, SIGNAL(clicked()), this, SLOT(ChangeFillTexture()));

    connect (colorIntensivitySlider, SIGNAL(valueChanged(int)), this, SLOT(MoveSlider()));


    setMouseTracking(true);
}

QImage setRgbPalete(int r)
{
    QImage img(200, 200, QImage::Format_RGB16);
    for (int i=0;i<200;i++)
    {
        for (int j=0;j<200;j++)
        {
            QColor c(r, i*2.55/2, j*2.55/2);
            img.setPixel(i, j, c.rgb());
        }
    }
    return img;
}

void MainWindow::RunTest()
{
    paintArea->RunTest();
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

void MainWindow::ChangeColor()
{

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
    QColor c = QColor(colorValueEdit[0]->value() * 2.55,
                      colorValueEdit[1]->value() * 2.55,
                      colorValueEdit[2]->value() * 2.55);
    qDebug() << c;
    QImage img(1, 1, QImage::Format_ARGB32);
    img.fill(c);
    colorMapImage = setRgbPalete(c.red());
    for (int i=0;i<5;i++)
    {
        colorMapImage.setPixel(colorValueEdit[1]->value()*2+i+2, colorValueEdit[2]->value() *2, 0);
        colorMapImage.setPixel(colorValueEdit[1]->value()*2-i-2, colorValueEdit[2]->value() *2, 0);
        colorMapImage.setPixel(colorValueEdit[1]->value()*2,   colorValueEdit[2]->value() *2+i+2, 0);
        colorMapImage.setPixel(colorValueEdit[1]->value()*2,   colorValueEdit[2]->value() *2-i-2, 0);
    }
    colorMap->setPixmap(QPixmap::fromImage(colorMapImage));
    paintArea->ChangeTexture(img);
}

void MainWindow::ChangeFillTexture()
{
    QImage img;
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Image"), "", tr("Image Files (*.bmp)"));
    if (!img.load(fileName))
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
