#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>

class DrawingWidget : public QWidget {
public:
    DrawingWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.fillRect(rect(), Qt::white);
        painter.setPen(Qt::black);
        for (int i = 0; i < lines.size(); ++i) {
//            painter.drawLine();
//            qDebug << "lines.size()";
        }
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            currentLine.clear();
            currentLine.append(event->pos());
            lines.append(currentLine);
            update();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (event->buttons() & Qt::LeftButton) {
            currentLine.append(event->pos());
            lines.removeLast();
            lines.append(currentLine);
            update();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            currentLine.clear();
        }
    }

private:
    QList<QPolygon> lines;
    QPolygon currentLine;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);

    DrawingWidget *drawingWidget = new DrawingWidget(&window);
    layout->addWidget(drawingWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    layout->addLayout(buttonLayout);

    QPushButton *button1 = new QPushButton("Button 1");
    QPushButton *button2 = new QPushButton("Button 2");
    QPushButton *button3 = new QPushButton("Button 3");

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    buttonLayout->addWidget(button3);

    window.setLayout(layout);
    window.resize(800, 600);
    window.show();

    return app.exec();
}
