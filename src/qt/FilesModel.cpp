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


void FilesModel::importFiles(QString fullPath) {
    QFile file(fullPath);
    QFileInfo fileInfo(file.fileName());
    QString target = QDir::homePath() + "/.local/share/com.ubuntu.developer.bobo1993324.qvbam/roms/" + fileInfo.fileName();
    if (file.exists()) {
        file.copy(target);
    }
    emit filesChanged();
}

void FilesModel::removeFile(QString fileName) {
    QFile f(QDir::homePath() + "/.local/share/com.ubuntu.developer.bobo1993324.qvbam/roms/" + fileName);
    qDebug() << "remove " << fileName << " " << f.exists();
    if (f.exists()) {
        f.remove();
        emit filesChanged();
    }
}
