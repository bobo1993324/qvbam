#include <QObject>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QDebug>
class FilesModel : public QObject{
    Q_OBJECT
    Q_PROPERTY(QStringList files READ files NOTIFY modelChanged)
public:
    QStringList files();
signals:
    void modelChanged();
};
