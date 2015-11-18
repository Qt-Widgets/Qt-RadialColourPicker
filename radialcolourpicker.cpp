#ifndef DEBUG_BORADIALCOLOURPICKER
#define QT_NO_DEBUG_OUTPUT
#endif

#include "radialcolourpicker.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>

#include <cstdlib>
#include <cmath>

RadialColourPicker::RadialColourPicker(QWidget *parent) :
    QWidget(parent)
{
    m_whiteLevel = m_blackLevel = 255;
}

QSize RadialColourPicker::minimumSizeHint() const
{
    return QSize(50, 150);
}

QSize RadialColourPicker::sizeHint() const
{
    return QSize(50, 150);
}

void RadialColourPicker::paintEvent(QPaintEvent *event)
{
    QConicalGradient gradient;

    float lastStop = 0.0;
    float incrementPoint;
    incrementPoint = 1.0/320;
    for (int x = 0; x < 320; x++)
    {
        gradient.setColorAt(lastStop, QColor::fromHsv(x, m_whiteLevel, m_blackLevel));
        lastStop += incrementPoint;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    m_centre.setX((this->width()/2));
    m_centre.setY((this->height()/2));
    gradient.setCenter(m_centre);
    painter.setBrush(QBrush(gradient));
    painter.drawEllipse(m_centre, this->height()/2,this->height()/2);

    event->accept();
}

void RadialColourPicker::mousePressEvent(QMouseEvent *pressEvent)
{
    QPoint clickPoint(pressEvent->x(), pressEvent->y());

    QPixmap gradientMap;
    gradientMap = this->grab();
    QImage gradImage = gradientMap.toImage();
    QRgb pixel = gradImage.pixel(clickPoint);

    if(pow((clickPoint.x() - m_centre.x()), 2) + pow((clickPoint.y() - m_centre.y()), 2) < pow(this->height()/2, 2))
    {
        emit colourPicked(QColor::fromRgb(pixel));
    }
}

void RadialColourPicker::setWhiteLevel(int level)
{
    m_whiteLevel = level;
    update();
}

void RadialColourPicker::setBlackLevel(int level)
{
    m_blackLevel = level;
    update();
}
