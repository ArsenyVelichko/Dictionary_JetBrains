#ifndef DICTIONARY_JETBRAINS_MAINWINDOW_H
#define DICTIONARY_JETBRAINS_MAINWINDOW_H

#include <QMainWindow>

#include "Dictionary.h"
#include "SearchProducer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow() override;

private slots:
    void onOpenFile();
    void onQueryChanged(const QString& query);
    void onSearchFinished();
    void onChunkReady();

private:
    Ui::MainWindow* ui;

    QString mNextQuery;
    SearchProducer* mProducer = nullptr;
    Dictionary* mDictionary = nullptr;
};

#endif //DICTIONARY_JETBRAINS_MAINWINDOW_H
