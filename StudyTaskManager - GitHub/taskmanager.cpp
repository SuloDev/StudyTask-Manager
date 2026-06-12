#include "taskmanager.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

void TaskManager::addTask(const Task& t) {
    active.append(t);
}

void TaskManager::deleteActiveTask(int index) {
    if (index >= 0 && index < active.size())
        active.removeAt(index);
}

void TaskManager::deleteCompletedTask(int index) {
    if (index >= 0 && index < completed.size())
        completed.removeAt(index);
}

void TaskManager::markCompletedTask(int index) {
    if (index >= 0 && index < active.size()) {
        Task t = active[index];
        t.completed = true;
        completed.append(t);
        active.removeAt(index);
    }
}

void TaskManager::save(const QString& filename) {
    QJsonObject root;

    QJsonArray activeArray;
    for (const Task& t : active) {
        QJsonObject obj;
        obj["title"] = t.title;
        obj["description"] = t.description;
        obj["category"] = t.category;
        obj["deadline"] = t.deadline.toString("yyyy-MM-dd");
        obj["completed"] = false;
        activeArray.append(obj);
    }

    QJsonArray completedArray;
    for (const Task& t : completed) {
        QJsonObject obj;
        obj["title"] = t.title;
        obj["description"] = t.description;
        obj["category"] = t.category;
        obj["deadline"] = t.deadline.toString("yyyy-MM-dd");
        obj["completed"] = true;
        completedArray.append(obj);
    }

    root["active"] = activeArray;
    root["completed"] = completedArray;

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
        file.close();
    }
}

void TaskManager::load(const QString& filename) {
    active.clear();
    completed.clear();

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject root = doc.object();

    QJsonArray activeArray = root["active"].toArray();
    for (const QJsonValue& v : activeArray) {
        QJsonObject o = v.toObject();
        Task t;
        t.title = o["title"].toString();
        t.description = o["description"].toString();
        t.category = o["category"].toString();
        t.deadline = QDate::fromString(o["deadline"].toString(), "yyyy-MM-dd");
        t.completed = false;
        active.append(t);
    }

    QJsonArray completedArray = root["completed"].toArray();
    for (const QJsonValue& v : completedArray) {
        QJsonObject o = v.toObject();
        Task t;
        t.title = o["title"].toString();
        t.description = o["description"].toString();
        t.category = o["category"].toString();
        t.deadline = QDate::fromString(o["deadline"].toString(), "yyyy-MM-dd");
        t.completed = true;
        completed.append(t);
    }
}