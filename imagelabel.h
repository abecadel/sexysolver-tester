#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPoint>

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    ImageLabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

signals:
    void mouseClicked(QPoint location);
    void mouseHovered(QPoint location);

};

#endif // IMAGELABEL_H
