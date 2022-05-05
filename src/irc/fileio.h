/**
 * 处理json ini文件
 * @date 22.5.5
 */
#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

class FileIO : public QObject
{
    Q_OBJECT
public:
    explicit FileIO(QObject *parent = nullptr);

signals:

};

#endif // FILEIO_H
