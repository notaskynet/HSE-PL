#ifndef __IMAGE_VIEWER_H__
#define __IMAGE_VIEWER_H__

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QtGlobal>
#include <QString>

class ImageViewer : public QWidget
{
public:
    ImageViewer(QWidget* parent=nullptr);
    void setImage(QString image_name);
    void paintEvent(QPaintEvent* event=nullptr);
private:
    QString m_image_name;
};

#endif // __IMAGE_VIEWER_H__