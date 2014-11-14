#ifndef CSHAPECHOOSER_H
#define CSHAPECHOOSER_H

#include <QMenu>
#include <QIcon>
#include <QToolButton>

class CShapeChooser : public QToolButton
{
    Q_OBJECT
public:
    CShapeChooser(QWidget *parent = 0);
    ~CShapeChooser();

private:
    QMenu* createLineMenu();
    QIcon createLineIcon(int shapeType);
    QString createLineText(int shapeType);

signals:
    void signalShapeChanged(int shapeType);

private slots:
    void onTypeChanged();
};

#endif // CSHAPECHOOSER_H
