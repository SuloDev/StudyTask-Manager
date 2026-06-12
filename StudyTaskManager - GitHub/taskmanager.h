#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QVector>
#include "task.h"

class TaskManager {
public:
    QVector<Task> active;
    QVector<Task> completed;

    void addTask(const Task& t);
    void deleteActiveTask(int index);
    void deleteCompletedTask(int index);
    void markCompletedTask(int index);

    void save(const QString& filename);
    void load(const QString& filename);
};

#endif // TASKMANAGER_H
