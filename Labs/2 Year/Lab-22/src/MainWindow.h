#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMessageBox>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QMenu>
#include <QAction>

#include <QDebug>

enum class FigureType { CIRCLE, SQUARE };

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent=nullptr);
    ~MainWindow() = default;

protected slots:
    void customContextMenuShow(QPoint pos);

    void drawSquare();
    void drawCircle();

    void reducePixels();
    void addPixels();
    void rotateFigure();
    void deleteFigure();

protected:

    bool isPointInside(QPoint point);

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    const int WINDOW_HEIGHT = 600;
    const int WINDOW_WIDTH  = 600;
    const int PIXEL_CHANGE  = 100;

    FigureType m_type;
    int        m_angle;
    int        m_side;

    QPoint m_pos;    
    QRect* m_figure;
    
    bool is_moving;
    bool is_figure_created;

    QMenu* context_menu;
    QMenu* figure_actions;
};

#endif // __MAIN_WINDOW_H__