#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "taskmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// Main application window controlling all UI logic
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    TaskManager taskManager; // stores active & completed tasks
    int editingIndex = -1; // -1 means not editing anything

    // UI refresh
    void refreshTaskLists();
    void showCompletedContextMenu(const QPoint& pos);
    void toggleCompletedVisibility(bool checked);
    void toggleDarkMode(bool enabled);

    // Task operations
    void deleteTask();
    void completeTaskBox(QListWidgetItem *item);
    void editTask();
    void saveEdit();

    // Persistance
    void saveTasks();
    void loadTasks();

protected:
     void closeEvent(QCloseEvent *event) override; // save tasks when window closes
};
#endif // MAINWINDOW_H
