#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QByteArray>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filename("D:/xxxx.pptx");

    QFile f(filename);
    f.open(QFile::ReadOnly);

    int total = f.bytesAvailable();
    qDebug() << total;
    const char* s = new char[total + 1];
    memcpy((void*)s, f.read(f.bytesAvailable()).constData(), total);
    qDebug() << strlen(s);
    f.close();

    QFile f2(filename + "2");
    f2.open(QFile::WriteOnly);
    int i = 0;
    // qDebug() << f2.write(s, total);
    while (true) {
        f2.write(s + i, 500);
        i += 500;
        if (i >= total)
            break;
        qDebug() << i << total;
    }
    f2.close();


    return a.exec();
}
