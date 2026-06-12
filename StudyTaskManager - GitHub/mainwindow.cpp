#include "mainwindow.h"
#include "ui_mainwindow.h" // auto-generated header file (connects UI design to code)
#include <QJsonArray> // JSON arrays support (list of tasks)
#include <QJsonDocument> // JSON document wrapper (for saving/loading)
#include <QJsonObject> // JSON object support (single task data)
#include <qevent.h> 
#include <QFile>
#include <QRandomGenerator>
#include <QApplication>
#include <QIcon>
#include <QMenu>
#include <QMessageBox> // lets you show popup dialogs/messages/warnings

const QString LIGHT_MODE = R"(
QWidget {
    background-color: #f5f7fb;
    color: #222;
    font-size: 14px;
}

QLineEdit, QComboBox, QDateEdit {
    background-color: #ffffff;
    border: 2px solid #9eacb3;
    border-radius: 8px;
    padding: 4px 8px;
    color: #222;
}

QLineEdit:focus, QComboBox:focus, QDateEdit:focus {
    border: 2px solid #4CAF50;
}

QComboBox::drop-down, QDateEdit::drop-down {
    border: none;
    background: transparent;
    width: 24px;
    padding-right: 6px;
}

QComboBox::down-arrow, QDateEdit::down-arrow {
    width: 10px;
    height: 10px;
    border: solid #4CAF50;
    border-width: 0 2px 2px 0;
    transform: rotate(45deg);
    margin-right: 6px;
}

QDateEdit::up-button, QDateEdit::down-button {
    width: 0px;
    height: 0px;
    border: none;
}

QComboBox, QDateEdit {
    padding-right: 28px;
}

QListWidget {
    border: 2px solid #b0bec5;
    background-color: #ffffff;
    border-radius: 12px;
    padding: 8px;
}

QListWidget::item {
    padding: 8px;
    margin-bottom: 4px;
    border-radius: 8px;
    background: #ffffff;
    border: 1px solid #d0d0d0;
}

QListWidget::item:selected {
    background-color: #a5d6a7;
    border: 1px solid #4CAF50;
    color: #1b5e20;
}

QListWidget::indicator {
    width: 16px;
    height: 16px;
}

QListWidget::indicator:unchecked {
    border: 2px solid #4CAF50;
    background: white;
    border-radius: 4px;
}

QListWidget::indicator:checked {
    background: #4CAF50;
    border-radius: 4px;
}

QListWidget::item:hover {
    background-color: #f1f8f4;
}

QListWidget::item:selected:!active {
    background: none;
    color: inherit;
}

QPushButton {
    background-color: #4CAF50;
    color: white;
    border-radius: 10px;
    padding: 6px 10px;
}

QPushButton#btnDelete {
    background-color: #f44336;
}

QPushButton#btnEdit {
    background-color: #2196F3;
}

#frameEditor {
    background-color: #ffffff;
    border: 2px solid #b0bec5;
    border-radius: 12px;
    padding: 12px;
}

QLabel {
    background: transparent;
    color: #333;
    font-weight: bold;
}
QLabel#activeTaskLabel {
    font-size: 20px;
    font-weight: bold;
    margin-bottom: 6px;
    background: transparent;
}

QMenu#completedMenu {
    background-color: #ffffff;
    border: 1px solid #ccc;
    border-radius: 6px;
    padding: 4px;
}

QMenu#completedMenu::item {
    padding: 6px 12px;
    border-radius: 4px;
}

QMenu#completedMenu::item:selected {
    background-color: #f44336; /* red */
    color: white;
}

)";

const QString DARK_MODE = R"(
QWidget {
    background-color: #1e1f22;
    color: #e6e6e6;
    font-size: 14px;
}

QLineEdit, QComboBox, QDateEdit {
    background-color: #2b2d31;
    border: 2px solid #3a3d42;
    border-radius: 8px;
    padding: 4px 8px;
    color: #e6e6e6;
}

QLineEdit:focus, QComboBox:focus, QDateEdit:focus {
    border: 2px solid #4CAF50;
}

QComboBox::drop-down, QDateEdit::drop-down {
    border: none;
    background: transparent;
    width: 24px;
    padding-right: 6px;
}

QComboBox::down-arrow, QDateEdit::down-arrow {
    width: 10px;
    height: 10px;
    border: solid #4CAF50;
    border-width: 0 2px 2px 0;
    transform: rotate(45deg);
    margin-right: 6px;
}

QDateEdit::up-button, QDateEdit::down-button {
    width: 0px;
    height: 0px;
    border: none;
}

QComboBox, QDateEdit {
    padding-right: 28px;
}

QListWidget {
    background-color: #2b2d31;
    border-radius: 12px;
    padding: 8px;
    border: 2px solid #3a3d42;
}

QListWidget::item:selected:!active {
    background: none;
    color: inherit;
}

QListWidget::item {
    padding: 8px;
    margin-bottom: 4px;
    border-radius: 8px;
    background: #2b2d31;
    border: 1px solid #3a3d42;
}

QListWidget::item:selected {
    background-color: #4CAF50;
    border: 1px solid #4CAF50;
    color: white;
}

QListWidget::indicator {
    width: 16px;
    height: 16px;
}

QListWidget::indicator:unchecked {
    border: 2px solid #4CAF50;
    background: #1e1f22;
    border-radius: 4px;
}

QListWidget::indicator:checked {
    background: #4CAF50;
    border-radius: 4px;
}

QPushButton {
    background-color: #4CAF50;
    color: white;
    border-radius: 10px;
    padding: 6px 10px;
}

QPushButton#btnDelete {
    background-color: #e53935;
}

QPushButton#btnEdit {
    background-color: #1e88e5;
}

#frameEditor {
    background-color: #2b2d31;
    border: 2px solid #3a3d42;
    border-radius: 12px;
    padding: 12px;
}

QLabel {
    background: transparent;
    color: #e6e6e6;
    font-weight: bold;
}
QLabel#activeTaskLabel {
    font-size: 20px;
    font-weight: bold;
    margin-bottom: 6px;
    background: transparent;
}

QMenu#completedMenu {
    background-color: #ffffff;
    border: 1px solid #ccc;
    border-radius: 6px;
    padding: 4px;
}

QMenu#completedMenu::item {
    padding: 6px 12px;
    border-radius: 4px;
}

QMenu#completedMenu::item:selected {
    background-color: #f44336; /* red */
    color: white;
}
)";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icons/icon/appicon.ico"));
    this->resize(900, 900);
    this->setMinimumSize(800, 600);

    ui->tasksLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    ui->dateDeadline->setCalendarPopup(true);
    ui->dateDeadline->setMinimumDate(QDate::currentDate());

    ui->listEditTasks->setFont(QFont("Segoe UI", 10));
    ui->listCompletedTasks->setFont(QFont("Segoe UI", 10));
    ui->listEditTasks->setSpacing(4);
    ui->listCompletedTasks->setSpacing(4);

    ui->listCompletedTasks->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listCompletedTasks->setSelectionBehavior(QAbstractItemView::SelectItems);

    loadTasks();

    connect(ui->lineEditTitle, &QLineEdit::returnPressed, this, &MainWindow::saveEdit);
    connect(ui->lineEditDescription, &QLineEdit::returnPressed, this, &MainWindow::saveEdit);
    connect(ui->btnDelete, &QPushButton::clicked, this, &MainWindow::deleteTask);
    connect(ui->btnEdit, &QPushButton::clicked, this, &MainWindow::editTask);
    connect(ui->btnSave, &QPushButton::clicked, this, &MainWindow::saveEdit);
    connect(ui->listEditTasks, &QListWidget::itemChanged, this, &MainWindow::completeTaskBox);

    ui->listCompletedTasks->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listCompletedTasks, &QListWidget::customContextMenuRequested,
            this, &MainWindow::showCompletedContextMenu);

    QAction* toggleCompletedAction = new QAction("Show Completed", this);
    toggleCompletedAction->setCheckable(true);
    toggleCompletedAction->setChecked(false);
    connect(toggleCompletedAction, &QAction::toggled,
            this, &MainWindow::toggleCompletedVisibility);
    ui->menuView->addAction(toggleCompletedAction);

    QAction* darkMode = new QAction("Dark Mode", this);
    darkMode->setCheckable(true);
    darkMode->setChecked(false);
    connect(darkMode, &QAction::toggled, this, &MainWindow::toggleDarkMode);
    ui->menuView->addAction(darkMode);

    qApp->setStyleSheet(LIGHT_MODE);
}

MainWindow::~MainWindow()
{
    delete ui; // cleans up UI object to free memory
}

void MainWindow::refreshTaskLists() {
    ui->listEditTasks->clear(); // clears active&completed tasks in UI
    ui->listCompletedTasks->clear();

    // display active tasks
    for (const Task& t : taskManager.active) {
        QString text = "[" + t.category + "]"
                       + t.title + " - "
                       + t.description + " ( Due: " + t.deadline.toString("yyyy-MM-dd") + " )";

        QListWidgetItem *item = new QListWidgetItem(text);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(t.completed ? Qt::Checked : Qt::Unchecked);

        ui->listEditTasks->addItem(item); // shows in the active list
    }

    // display completed tasks
    for (const Task& t : taskManager.completed) {
        QString text = "[" + t.category + "]"
                       + t.title + " - "
                       + t.description + " ( Due: " + t.deadline.toString("yyyy-MM-dd") + " ) ✔";

        QListWidgetItem * item = new QListWidgetItem(text); //creats UI item
        item->setData(Qt::UserRole, "completed");
        item->setForeground(QColor("#4CAF50"));
        item->setFont(QFont("Segoe UI", 10, QFont::Bold)); //bold font
        item->setData(Qt::UserRole + 1, true);

        ui->listCompletedTasks->addItem(item); // shows in the completed list
    }
}

void MainWindow::toggleCompletedVisibility(bool checked) {
    if (checked) {
        // switching to completed
        ui->listEditTasks->clearSelection();
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        // switching to active
        ui->listCompletedTasks->clearSelection();
        ui->stackedWidget->setCurrentIndex(0);
    }

    // reset editing state
    editingIndex = -1;
    ui->btnSave->setText("Save Task");

    QAction* action = qobject_cast<QAction*>(sender());
    if (action)
        action->setText(checked ? "Show Active" : "Show Completed");
}

void MainWindow::toggleDarkMode(bool enabled) {
    if (enabled) {
        qApp->setStyleSheet(DARK_MODE);
    } else {
        qApp->setStyleSheet(LIGHT_MODE);
    }
}

void MainWindow::showCompletedContextMenu(const QPoint& pos) {
    QModelIndex index = ui->listCompletedTasks->indexAt(pos);
    if (index.isValid()) {
        if (!ui->listCompletedTasks->item(index.row())->isSelected()) {
            ui->listCompletedTasks->clearSelection();
            ui->listCompletedTasks->setCurrentRow(index.row());
        }
    }

    QList<QListWidgetItem*> selected = ui->listCompletedTasks->selectedItems();
    int count = selected.size();
    if (count == 0) return;

    QMenu menu;
    menu.setObjectName("completedMenu");
    QAction* deleteOne = nullptr;
    QAction* deleteSelected = nullptr;

    if (count == 1) {
        deleteOne = menu.addAction("Delete Task");
    }
    else if (count > 1) {
        deleteSelected = menu.addAction("Delete All Selected");
    }

    QAction* chosen = menu.exec(ui->listCompletedTasks->viewport()->mapToGlobal(pos));
    if (!chosen) return;

    if (chosen == deleteOne) {
        int row = ui->listCompletedTasks->row(selected[0]);
        taskManager.deleteCompletedTask(row);
        refreshTaskLists();
    }
    else if (chosen == deleteSelected) {
        if(QMessageBox::question(this, "Confirm Delete",
                                  "Delete ALL selected tasks?",
                                  QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes)
        {
            // Collect row numbers BEFORE deleting anything
            QList<int> rows;
            for (auto* item : selected)
                rows << ui->listCompletedTasks->row(item);

            // Sort descending
            std::sort(rows.begin(), rows.end(), std::greater<int>());

            // Delete safely
            for (int row : rows)
                taskManager.deleteCompletedTask(row);

            refreshTaskLists();

        }
    }
}

void MainWindow::completeTaskBox(QListWidgetItem *item) {
    if (!(item->flags() & Qt::ItemIsUserCheckable))
        return;

    if (item->checkState() == Qt::Checked) {
        int row = ui->listEditTasks->row(item);
        taskManager.markCompletedTask(row);

        refreshTaskLists();
    }
}

void MainWindow::deleteTask() {
    int activeRow = ui->listEditTasks->currentRow();
    int completedRow = ui->listCompletedTasks->currentRow();

    // If active page is visible, only delete from active
    if (ui->stackedWidget->currentIndex() == 0) {
        if (activeRow >= 0) {
            taskManager.deleteActiveTask(activeRow);
            refreshTaskLists();
            return;
        }
    }

    // If completed page is visible, only delete from completed
    if (ui->stackedWidget->currentIndex() == 1) {
        if (completedRow >= 0) {
            taskManager.deleteCompletedTask(completedRow);
            refreshTaskLists();
            return;
        }
    }

    QMessageBox::information(this, "Info", "Select a task to delete");
}

void MainWindow::editTask() {
    int index = ui->listEditTasks->currentRow();
    if (index < 0) {
        QMessageBox::information(this, "Info", "Select a task to edit");
        return;
    }

    //retrieve the Task object from TaskManager
    const Task& t = taskManager.active[index]; //acces the real data

    //fill the UI fields wiht the task's data, this allows th euser modify the fields
    ui->lineEditTitle->setText(t.title);
    ui->lineEditDescription->setText(t.description);
    ui->comboCategory->setCurrentText(t.category);
    ui->dateDeadline->setDate(t.deadline);

    //remember which task is being edited
    editingIndex = index; //saves index for saveEdit()

    ui->btnSave->setText("Save Edit");
}

void MainWindow::saveEdit() {
    if (editingIndex == -1) {
        QString title = ui->lineEditTitle->text();
        QString description = ui->lineEditDescription->text();
        QString category = ui->comboCategory->currentText();
        QDate deadline = ui->dateDeadline->date();

        if (title.isEmpty()) {
            QMessageBox::warning(this, "Error", "Task title cannot be empty");
            return;
        }

        Task newTask;
        newTask.title = title;
        newTask.description = description;
        newTask.category = category;
        newTask.deadline = deadline;
        newTask.completed = false;

        taskManager.active.append(newTask); //adds deirectly to active list
        refreshTaskLists();

        //reset UI
        ui->lineEditTitle->clear();
        ui->lineEditDescription->clear();
        ui->dateDeadline->setDate(QDate::currentDate());
        return;
    }

    //editing existing task
    QString title = ui->lineEditTitle->text();
    QString description = ui->lineEditDescription->text();
    QString category = ui->comboCategory->currentText();
    QDate deadline = ui->dateDeadline->date();

    if (title.isEmpty()) {
        QMessageBox::warning(this, "Error", "Task title cannot be empty");
        return;
    }

    Task& t = taskManager.active[editingIndex];
    t.title = title;
    t.description = description;
    t.category = category;
    t.deadline = deadline;

    editingIndex = -1;
    ui->btnSave->setText("Save Task");

    refreshTaskLists();
    ui->lineEditTitle->clear();
    ui->lineEditDescription->clear();
    ui->dateDeadline->setDate(QDate::currentDate());
}

void MainWindow::saveTasks() {
    taskManager.save("tasks.json");
}

void MainWindow::loadTasks() {
    taskManager.load("tasks.json");

    refreshTaskLists();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    saveTasks(); //saves tasks before closing the app

    event->accept();
}