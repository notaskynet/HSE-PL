#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <cmath>
#include <random>

#include <QMessageBox>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QMenu>
#include <QAction>

#define EPS 10

enum class FigureType { CIRCLE, SQUARE };

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent=nullptr);
    ~MainWindow() = default;

protected slots:
    void customContextMenuShow(QPoint pos);

    void addSquare();
    void addCircle();

    void reducePixels();
    void addPixels();
    void rotateFigure();
    void deleteFigure();

protected:
    bool isPointInsideFigure(QPoint point);
    bool isPointOnTheCorner(QPoint point);

    void paintEvent(QPaintEvent* event);
    
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    const int WINDOW_HEIGHT = 600;
    const int WINDOW_WIDTH  = 600;
    const int PIXEL_CHANGE  = 100;

    FigureType m_type;

    int m_angle = 0;
    int m_side  = 100;

    QPoint m_pos;    
    QRect* m_figure;
    
    bool is_glowing = false;
    bool is_moving = false;
    bool is_figure_created = false;

    QMenu* context_menu;
    QMenu* figure_actions;
};

#endif // __MAIN_WINDOW_H__