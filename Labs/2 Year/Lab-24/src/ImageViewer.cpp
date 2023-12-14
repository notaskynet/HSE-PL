#include "ImageViewer.h"


ImageViewer::ImageViewer(QWidget* parent)
    : QWidget(parent), m_image_name("")
{
    this->show();
}


void ImageViewer::setImage(QString image_name)
{
    m_image_name = image_name;
    this->update();
}


void ImageViewer::paintEvent(QPaintEvent* event)
{
    if(!m_image_name.isEmpty())
    {
        QPainter painter(this);
        painter.drawImage(
            QRectF(
                (qreal) (this->width()) / 2 - (qreal) (this->width()) / 3,
                0,
                (qreal) (this->width()  * 2) / 3,
                (qreal) (this->height() * 2) / 3
            ),
            QImage(m_image_name)
        );
    }
}