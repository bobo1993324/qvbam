#include "FilesModel.h"

QStringList FilesModel::files(){
    QDir qdir(QDir::homePath() + "/.local/share/com.ubuntu.developer.bobo1993324.qvbam/roms");
    if (!qdir.exists()) {
        qdir.mkpath(qdir.absolutePath());
        return QStringList();
    } else {
        QStringList qsl = qdir.entryList();
        int i = 0;
        while (i < qsl.length()) {
            if (qsl[i] == "." || qsl[i] == "..") {
                qsl.removeAt(i);
            } else {
                i++;
            }
        }
        qDebug() << "return " << qsl;
        return qsl;
    }

}
