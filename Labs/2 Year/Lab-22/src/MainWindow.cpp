#include "MainWindow.h"



MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
{
    qDebug("MainWindow::MainWindow(QWidget* parent)");

    this->setWindowTitle(tr("QPainter Test"));
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    m_angle = 0;
    m_side = 100;
    is_moving = false;
    is_figure_created = false;
    m_pos = QPoint(
        (WINDOW_WIDTH - m_side)/2,
        (WINDOW_HEIGHT - m_side)/2
    );
    m_figure = new QRect(m_pos.x(), m_pos.y(), m_side, m_side);

    context_menu = new QMenu(this);

    QAction* drawSquareAction = new QAction(tr("Нарисовать квадрат"), this);
    QAction* drawCircleAction = new QAction(tr("Нарисовать круг"), this);

    connect(drawSquareAction, &QAction::triggered, this, &MainWindow::drawSquare);
    connect(drawCircleAction, &QAction::triggered, this, &MainWindow::drawCircle);

    context_menu->addAction(drawSquareAction);
    context_menu->addAction(drawCircleAction);

    figure_actions = new QMenu(this);

    QAction* reducePixelsAction = new QAction(tr("Уменьшить на 100 пикселей"), this);
    QAction* addPixelsAction = new QAction(tr("Увеличить на 100 пикселей"), this);
    QAction* rotateFigureAction = new QAction(tr("Повернуть фигуру на 30 градусов"), this);
    QAction* deleteFigureAction = new QAction(tr("Удалить фигуру"), this);

    connect(reducePixelsAction, SIGNAL(triggered()), this, SLOT(reducePixels()));
    connect(addPixelsAction,    SIGNAL(triggered()), this, SLOT(addPixels()));
    connect(rotateFigureAction, SIGNAL(triggered()), this, SLOT(rotateFigure()));
    connect(deleteFigureAction, SIGNAL(triggered()), this, SLOT(deleteFigure()));

    figure_actions->addAction(reducePixelsAction);
    figure_actions->addAction(addPixelsAction);
    figure_actions->addAction(rotateFigureAction);
    figure_actions->addAction(deleteFigureAction);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenuShow(QPoint)));
}


void MainWindow::drawSquare()
{
    qDebug("MainWindow::drawSquare(QPaintEvent* event)\n");

    QPainter painter(this);

    is_figure_created = true;
    m_type = FigureType::SQUARE;
    this->update();
}

void MainWindow::drawCircle()
{
    qDebug("MainWindow::drawCircle(QPaintEvent* event)\n");

    is_figure_created = true;
    m_type = FigureType::CIRCLE;
    this->update();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    qDebug("MainWindow::paintEvent(QPaintEvent* event)\n");
    if(is_figure_created)
    {
        QPainter painter(this);

        painter.setRenderHint(QPainter::Antialiasing);

        if(m_type == FigureType::CIRCLE)
        {
            painter.translate(m_figure->center());
            painter.rotate(m_angle);
            painter.translate(-m_figure->center());

            painter.setBrush(Qt::blue);
            painter.setPen(Qt::black);
            painter.drawEllipse(*m_figure);
        }
        else if(m_type == FigureType::SQUARE)
        {
            painter.translate(m_figure->center());
            painter.rotate(m_angle);
            painter.translate(-m_figure->center());

            painter.setBrush(Qt::green);
            painter.setPen(Qt::black);
            painter.drawRect(*m_figure);
        }
    }
}


bool MainWindow::isPointInside(QPoint point)
{
    qDebug("MainWindow::isPointInside(QPoint point)");

    if(m_type == FigureType::CIRCLE) {
        return ((point.x() >= m_figure->x()) &&
                (point.y() >= m_figure->y()) &&
                (point.x() <= m_figure->x() + m_side) &&
                (point.y() <= m_figure->y() + m_side)); 
    }
    else {            
        return (abs(m_figure->center().x() - point.x()) <=  m_side/2 &&
                abs(m_figure->center().y() - point.y()) <=  m_side/2);
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(is_figure_created && isPointInside(event->pos()) &&  (event->button() & Qt::LeftButton))
    {
        is_moving = true;
        m_pos = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    qDebug("void MainWindow::mouseMoveEvent(QMouseEvent* event)");
    
    if(is_moving) {
        int x_shift = event->pos().x() - m_pos.x();
        int y_shift = event->pos().y() - m_pos.y();
        m_pos = event->pos();

        m_figure->moveTo(m_figure->x() + x_shift,
                         m_figure->y() + y_shift);
        this->update();        
    }
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() & Qt::LeftButton) && is_moving) {
        is_moving = false;
    }
}

void MainWindow::customContextMenuShow(QPoint pos)
{
    QPoint globalPos = mapToGlobal(pos);

    qDebug("void MainWindow::customMenuRequested(QPoint pos)");

    if(!is_figure_created) {
        context_menu->exec(globalPos);
    }
    else if(is_figure_created && isPointInside(pos)){
        figure_actions->exec(globalPos);
    }
}


void MainWindow::reducePixels()
{
    qDebug("void MainWindow::reducePixels()");

    if(m_side >= 2 * PIXEL_CHANGE) {
        m_side -= PIXEL_CHANGE;
        m_figure->setWidth(m_side);
        m_figure->setHeight(m_side);
    }
    else {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning,
                                               "Предупреждение!",
                                               "Фигуру нельзя сделать еще меньше!",
                                               QMessageBox::NoButton);
        warning->exec();
    }
    this->update();        
}


void MainWindow::addPixels()
{ 
    qDebug("void MainWindow::addPixels()");

    if(m_side < WINDOW_HEIGHT / 2 - PIXEL_CHANGE) {
        m_side += PIXEL_CHANGE;
    }
    else {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning,
                                               "Предупреждение!",
                                               "Фигуру нельзя сделать еще больше!",
                                               QMessageBox::NoButton);
        warning->exec();
    }
    m_figure->setWidth(m_side);
    m_figure->setHeight(m_side);
    this->update();       
}


void MainWindow::rotateFigure()
{
    qDebug("void MainWindow::rotate()");

    m_angle = (m_angle + 30) % 360;
    this->update();
}


void MainWindow::deleteFigure()
{
    qDebug("void MainWindow::deleteFigure()");

    is_figure_created = false;
    m_angle = 0;
    this->update();       
}
