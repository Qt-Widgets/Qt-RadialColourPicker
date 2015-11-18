#ifndef RADIALCOLOURPICKER_H
#define RADIALCOLOURPICKER_H

#include <QWidget>

class RadialColourPicker : public QWidget
{
    Q_OBJECT
public:
    explicit RadialColourPicker(QWidget *parent = 0);

    QPointF m_centre;

    bool inCircle(QPointF point);

private:

    int m_whiteLevel;
    int m_blackLevel;

signals:
    void colourPicked(QColor colourPicked);

public slots:
    void paintEvent(QPaintEvent *paintEvent);
    void mousePressEvent(QMouseEvent *pressEvent);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    void setWhiteLevel(int level);
    void setBlackLevel(int level);
};

#endif // RADIALCOLOURPICKER_H
