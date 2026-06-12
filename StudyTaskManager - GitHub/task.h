#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>

struct Task {
    QString title;
    QString description;
    QString category;
    QDate deadline;
    bool completed = false;
};

#endif // TASK_H
