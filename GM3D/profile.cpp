#include "profile.h"
#include "ui_profile.h"
#include "qcustomplot.h"
Profile::Profile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);
    this->setWindowTitle("Profile View");
    QIcon Icon(":/icon/myicon/profile.png");
    this->setWindowIcon(Icon);
    originalSize=this->size();
    storeInitialGeometries(this);

    connect(ui->ComfirmBtn,SIGNAL(clicked(bool)),this,SLOT(GetProfileData()));
    connect(ui->OutputBtn,SIGNAL(clicked(bool)),this,SLOT(OutputData()));
    connect(ui->datacomboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(DataChanged(int)));
}

Profile::~Profile()
{
    delete ui;
}

void Profile::GetModelMsg(QVector<QVector<QVector<double> > > density,QVector<QVector<QVector<double> > > magnatization,QVector<float> FieldParam)
{
   // Spacedata=spacedata;
    Density=density;
    Magnatization=magnatization;
    xMin=FieldParam[0];
    xMax=FieldParam[1];
    yMin=FieldParam[2];
    yMax=FieldParam[3];
    zMin=FieldParam[4];
    zMax=FieldParam[5];
    xMesh=FieldParam[6];
    yMesh=FieldParam[7];
    zMesh=FieldParam[8];
    xSize = static_cast<int>((xMax - xMin) / xMesh);
    ySize = static_cast<int>((yMax - yMin) / yMesh);
    zSize = static_cast<int>((zMax - zMin) / zMesh);
    if (ui->datacomboBox->currentIndex()==0) {
        Spacedata=Density;
    }else{
        Spacedata=Magnatization;
    }


}

void Profile::PlotProfile(QVector<QVector<double> > profiledata, int rows, int cols)
{
    QCustomPlot *customPlot = new QCustomPlot(this);

    // 创建一个二维网格数据
    QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    colorMap->data()->setSize(cols, rows);
    colorMap->data()->setRange(QCPRange(0, cols - 1), QCPRange(0, rows - 1));

    // 填充数据
    for (int xIndex = 0; xIndex < cols; ++xIndex) {
        for (int yIndex = 0; yIndex < rows; ++yIndex) {
            colorMap->data()->setCell(xIndex, yIndex, profiledata[yIndex][xIndex]);
        }
    }
    // 设置颜色渐变
    QCPColorScale *colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale);
    colorMap->setColorScale(colorScale);
    colorScale->setType(QCPAxis::atRight);

    // 设置颜色映射
    QCPColorGradient gradient;
    gradient.setColorStopAt(0, Qt::blue);
    gradient.setColorStopAt(0.5, Qt::yellow);
    gradient.setColorStopAt(1, Qt::red);
    colorMap->setGradient(gradient);

    // 自动缩放颜色范围
    colorMap->rescaleDataRange(true);

    // 设置坐标轴范围
    customPlot->xAxis->setRange(0, cols - 1);
    customPlot->yAxis->setRange(0, rows - 1);
    customPlot->setGeometry(ProfileAxis.toRect());

    // 绘制
    customPlot->replot();
    customPlot->show();
}

void Profile::PlotProfileChoose()
{
    update();
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(ChooseProfileAxis);
    int index = ui->comboBox->currentIndex();
    QString xLabel, yLabel;
    double xStart=0, xEnd=0, yStart=0, yEnd=0;

    switch (index) {
    case 0: // X剖面
        yLabel = "Y";
        xLabel = "Z";
        yStart = yMin;
        yEnd = yMax;
        xStart = zMin;
        xEnd = zMax;
        break;
    case 1: // Y剖面
        xLabel = "X";
        yLabel = "Z";
        xStart = xMin;
        xEnd = xMax;
        yStart = zMin;
        yEnd = zMax;
        break;
    case 2: // Z剖面
        xLabel = "X";
        yLabel = "Y";
        xStart = xMin;
        xEnd = xMax;
        yStart = yMin;
        yEnd = yMax;
        break;
    }

    // 在横纵轴中间写上标号
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);
    QRectF xLabelRect(ChooseProfileAxis.x() + ChooseProfileAxis.width() / 2 - 10, ChooseProfileAxis.y() + ChooseProfileAxis.height() + 10, 20, 20);
    QRectF yLabelRect(ChooseProfileAxis.x() - 20, ChooseProfileAxis.y() + ChooseProfileAxis.height() / 2 - 10, 20, 20);
    painter.drawText(xLabelRect, Qt::AlignCenter, xLabel);
    painter.drawText(yLabelRect, Qt::AlignCenter, yLabel);

    // 在坐标区的四个角标注横纵轴的范围
    QString topLeftText = QString("%1").arg(yEnd);
    QString bottomLeftText = QString("%1, %2").arg(xStart).arg(yStart);
    QString bottomRightText = QString("%1").arg(xEnd);
    QRectF topLeftRect(ChooseProfileAxis.x()-20, ChooseProfileAxis.y() - 20, 80, 20);
    QRectF bottomLeftRect(ChooseProfileAxis.x()-20, ChooseProfileAxis.y() + ChooseProfileAxis.height(), 80, 20);
    QRectF bottomRightRect(ChooseProfileAxis.x() + ChooseProfileAxis.width() - 70, ChooseProfileAxis.y() + ChooseProfileAxis.height(), 80, 20);
    painter.drawText(topLeftRect, Qt::AlignLeft, topLeftText);
    painter.drawText(bottomLeftRect, Qt::AlignLeft, bottomLeftText);
    painter.drawText(bottomRightRect, Qt::AlignRight, bottomRightText);

    // 在坐标区内用透明度比较低的虚线画上网格
    QPen gridPen(Qt::gray, 1, Qt::DashLine);
    gridPen.setColor(QColor(128, 128, 128, 128)); // 设置透明度为 128
    painter.setPen(gridPen);
    double xStep = (xEnd - xStart) / 10;
    double yStep = (yEnd - yStart) / 10;
    for (int i = 0; i <= 10; ++i) {
        double xValue = xStart + i * xStep;
        double yValue = yStart + i * yStep;

        // 计算网格线在坐标区的像素位置
        double xPixel = ChooseProfileAxis.x() + (xValue - xStart) * ChooseProfileAxis.width() / (xEnd - xStart);
        double yPixel = ChooseProfileAxis.y() + (yEnd - yValue) * ChooseProfileAxis.height() / (yEnd - yStart);

        painter.drawLine(xPixel, ChooseProfileAxis.y(), xPixel, ChooseProfileAxis.y() + ChooseProfileAxis.height());
        painter.drawLine(ChooseProfileAxis.x(), yPixel, ChooseProfileAxis.x() + ChooseProfileAxis.width(), yPixel);
    }

    // 从 lineEdit 中获取坐标
    QString text1 = ui->StartPointEdit->text();
    QString text2 = ui->EndPointEdit->text();
    QPointF point1Model, point2Model;

    if (!text1.isEmpty()) {
        QStringList values1 = text1.mid(1, text1.length() - 2).split(',');
        if (values1.size() == 2) {
            point1Model.setX(values1[0].toDouble());
            point1Model.setY(values1[1].toDouble());
        }
    }

    if (!text2.isEmpty()) {
        QStringList values2 = text2.mid(1, text2.length() - 2).split(',');
        if (values2.size() == 2) {
            point2Model.setX(values2[0].toDouble());
            point2Model.setY(values2[1].toDouble());
        }
    }

    // 将模型坐标转换为像素坐标
    auto modelToPixel = [&](const QPointF& modelPoint) {
        double xPixel = ChooseProfileAxis.x() + (modelPoint.x() - xStart) * ChooseProfileAxis.width() / (xEnd - xStart);
        double yPixel = ChooseProfileAxis.y() + (yEnd - modelPoint.y()) * ChooseProfileAxis.height() / (yEnd - yStart);
        return QPointF(xPixel, yPixel);
    };

    QPointF point1Pixel = modelToPixel(point1Model);
    QPointF point2Pixel = modelToPixel(point2Model);

    // 绘制点和连线
    QPen redPen(Qt::red, 2);
    painter.setPen(redPen);
    painter.setBrush(Qt::red);

    if (!text1.isEmpty()) {
        painter.drawEllipse(point1Pixel, 5, 5);
    }
    if (!text1.isEmpty() && !text2.isEmpty()) {
        painter.drawEllipse(point2Pixel, 5, 5);
        painter.drawLine(point1Pixel, point2Pixel);
    }

}

void Profile::storeInitialGeometries(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            m_initialGeometries[childWidget] = childWidget->geometry();
            storeInitialGeometries(childWidget);
        }
    }
}

QPoint Profile::convertToModelCoordinates(QPoint &point)
{
    int index = ui->comboBox->currentIndex();
    double xModel=0, yModel=0;
    int xPixel = point.x() - ChooseProfileAxis.x();
    int yPixel = point.y() - ChooseProfileAxis.y();

    switch (index) {
    case 0: // X剖面
        xModel = zMin + (zMax - zMin)* xPixel / ChooseProfileAxis.width();
        yModel = yMin + (yMax - yMin) * (ChooseProfileAxis.height() - yPixel) / ChooseProfileAxis.height();
        break;
    case 1: // Y剖面
        xModel = xMin + (xMax - xMin) * xPixel / ChooseProfileAxis.width();
        yModel = zMin + (zMax - zMin) * (ChooseProfileAxis.height() - yPixel) / ChooseProfileAxis.height();
        break;
    case 2: // Z剖面
        xModel = xMin + (xMax - xMin) * xPixel / ChooseProfileAxis.width();
        yModel = yMin + (yMax - yMin)* (ChooseProfileAxis.height() - yPixel) / ChooseProfileAxis.height();
        break;
    }
    return QPoint(xModel, yModel);
}

QVector<QVector<double> > Profile::getProfileData(const QPointF &p1, const QPointF &p2)
{
    QVector<QVector<double>> profile;
    int index = ui->comboBox->currentIndex();
    int startX, startY, endX, endY;


    switch (index) {
    case 0: // X剖面
        startX = static_cast<int>((p1.x() - yMin) / yMesh);
        startY = static_cast<int>((p1.y() - zMin) / zMesh);
        endX = static_cast<int>((p2.x() - yMin) / yMesh);
        endY = static_cast<int>((p2.y() - zMin) / zMesh);
        break;
    case 1: // Y剖面
        startX = static_cast<int>((p1.x() - xMin) / xMesh);
        startY = static_cast<int>((p1.y() - zMin) / zMesh);
        endX = static_cast<int>((p2.x() - xMin) / xMesh);
        endY = static_cast<int>((p2.y() - zMin) / zMesh);
        break;
    case 2: // Z剖面
        startX = static_cast<int>((p1.x() - xMin) / xMesh);
        startY = static_cast<int>((p1.y() - yMin) / yMesh);
        endX = static_cast<int>((p2.x() - xMin) / xMesh);
        endY = static_cast<int>((p2.y() - yMin) / yMesh);
        break;
    }

    int dx = endX - startX;
    int dy = endY - startY;
    int steps = std::max(std::abs(dx), std::abs(dy));

    if (steps == 0) {
        // 如果两点重合，返回一个包含单个点在对应方向上所有值的剖面
        QVector<double> row;
        switch (index) {
        case 0:
            for (int x = 0; x < xSize; ++x) {
                if (startX >= 0 && startX < ySize && startY >= 0 && startY < zSize) {
                    row.push_back(Spacedata[x][startX][startY]);
                }
            }
            break;
        case 1:
            for (int y = 0; y < ySize; ++y) {
                if (startX >= 0 && startX < xSize && startY >= 0 && startY < zSize) {
                    row.push_back(Spacedata[startX][y][startY]);
                }
            }
            break;
        case 2:
            for (int z = 0; z < zSize; ++z) {
                if (startX >= 0 && startX < xSize && startY >= 0 && startY < ySize) {
                    row.push_back(Spacedata[startX][startY][z]);
                }
            }
            break;
        }
        profile.push_back(row);
        return profile;
    }

    double xIncrement = static_cast<double>(dx) / steps;
    double yIncrement = static_cast<double>(dy) / steps;

    for (int i = 0; i <= steps; ++i) {
        int x = static_cast<int>(startX + i * xIncrement);
        int y = static_cast<int>(startY + i * yIncrement);
        QVector<double> row;
        switch (index) {
        case 0:
            for (int fixed = 0; fixed < xSize; ++fixed) {
                if (x >= 0 && x < ySize && y >= 0 && y < zSize) {
                    row.push_back(Spacedata[fixed][x][y]);
                }
            }

            break;
        case 1:
            for (int fixed = 0; fixed < ySize; ++fixed) {
                if (x >= 0 && x < xSize && y >= 0 && y < zSize) {
                    row.push_back(Spacedata[x][fixed][y]);
                }
            }

            break;
        case 2:
            for (int fixed = 0; fixed < zSize; ++fixed) {
                if (x >= 0 && x < xSize && y >= 0 && y < ySize) {
                    row.push_back(Spacedata[x][y][fixed]);
                }
            }

            break;
        }
        if (!row.isEmpty()) {
            profile.push_back(row);
        }
    }

    return profile;
}

void Profile::GetProfileData()
{
    QString text1 = ui->StartPointEdit->text();
    QString text2 = ui->EndPointEdit->text();
    QPointF point1Model, point2Model;
    update();
    if (!text1.isEmpty()) {
        QStringList values1 = text1.mid(1, text1.length() - 2).split(',');
        if (values1.size() == 2) {
            point1Model.setX(values1[0].toDouble());
            point1Model.setY(values1[1].toDouble());
        }
    }

    if (!text2.isEmpty()) {
        QStringList values2 = text2.mid(1, text2.length() - 2).split(',');
        if (values2.size() == 2) {
            point2Model.setX(values2[0].toDouble());
            point2Model.setY(values2[1].toDouble());
        }
    }
    profileData = getProfileData(point1Model, point2Model);
    int rows = profileData.size();

    // 获取列数，假设每一行的列数相同，取第一行的列数
    int cols = 0;
    if (!profileData.isEmpty()) {
        cols = profileData[0].size();
    }
    PlotProfile(profileData,rows,cols);
}

void Profile::OutputData()
{
    if (profileData.isEmpty()) {
        QMessageBox::warning(this, "Error", "There is no available data.");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "保存文件", "", "文本文件 (*.txt)");
    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open the file");
        return;
    }

    QTextStream out(&file);
    for (const auto& row : profileData) {
        for (double value : row) {
            out << value << " ";
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(this, "Notice", "The data has been saved successfully!");
}

void Profile::DataChanged(int index)
{
    if (index==0) {
        Spacedata=Density;
    }else{
        Spacedata=Magnatization;
    }
}

void Profile::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    qreal scaleX = (qreal)width() /originalSize.width();
    qreal scaleY = (qreal)height()/originalSize.height();
    for (auto it = m_initialGeometries.begin(); it != m_initialGeometries.end(); ++it) {
        QWidget *widget = it.key();
        QRect geom = it.value();
        int newX = geom.x() * scaleX;
        int newY = geom.y() * scaleY;
        int newWidth = geom.width() * scaleX;
        int newHeight = geom.height() * scaleY;
        widget->setGeometry(newX, newY, newWidth, newHeight);
    }
    ProfileAxis=QRect(InitProfileAxis.x()*scaleX,InitProfileAxis.y()*scaleY,InitProfileAxis.width()*scaleX,InitProfileAxis.height()*scaleY);
    ChooseProfileAxis=QRect(InitChooseProfileAxis.x()*scaleX,InitChooseProfileAxis.y()*scaleY,InitChooseProfileAxis.width()*scaleX,InitChooseProfileAxis.height()*scaleY);
}

void Profile::paintEvent(QPaintEvent *)
{
    PlotProfileChoose();
}

void Profile::mousePressEvent(QMouseEvent *event)
{
    if (ChooseProfileAxis.contains(event->pos())) {
        if (!firstPointSelected) {
            StartPoint = event->pos();
            firstPointSelected = true;
            QPointF modelPoint1 = convertToModelCoordinates(StartPoint);
            ui->StartPointEdit->setText(QString("[%1, %2]").arg(modelPoint1.x()).arg(modelPoint1.y()));
        } else {
            EndPoint = event->pos();
            QPointF modelPoint2 = convertToModelCoordinates(EndPoint);
            ui->EndPointEdit->setText(QString("[%1, %2]").arg(modelPoint2.x()).arg(modelPoint2.y()));
            firstPointSelected = false;
        }
        update();
    }
}
