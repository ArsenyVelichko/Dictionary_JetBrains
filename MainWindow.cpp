#include <QFileDialog>

#include "MainWindow.h"
#include "ui_MainWindow.h"

constexpr int searchLen = 1000;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->inputLineEdit, &QLineEdit::textEdited, this, &MainWindow::onQueryChanged);
    connect(ui->openAction, &QAction::triggered, this, &MainWindow::onOpenFile);
}

MainWindow::~MainWindow() {
    if (mProducer) {
        mProducer->cancel();
        mProducer->wait();
    }

    delete ui;
}

void MainWindow::onOpenFile() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "./",
                                                    tr("Text files (*.txt)"));

    if (filePath.isNull()) { return; }

    ui->inputLineEdit->setEnabled(true);
    ui->outputTextEdit->clear();

    delete mDictionary;

    mDictionary = new Dictionary(filePath, this);
    mProducer = new SearchProducer(mDictionary, searchLen, this);

    connect(mProducer, &SearchProducer::chunkReady,
            this, &MainWindow::onChunkReady);
    connect(mProducer, &SearchProducer::finished,
            this, &MainWindow::onSearchFinished);
}

void MainWindow::onQueryChanged(const QString& query)
{
    mNextQuery = query;

    if (!mProducer->isRunning()) {
        onSearchFinished();
    } else {
        mProducer->cancel();
    }
}

void MainWindow::onSearchFinished()
{
    if (mNextQuery.isNull()) { return; }

    ui->outputTextEdit->clear();

    if (mNextQuery.isEmpty()) { return; }

    mProducer->setPattern(mNextQuery);

    mProducer->start();
    mNextQuery = QString();
}

void MainWindow::onChunkReady()
{
    QString chunk = mProducer->getChunk();
    ui->outputTextEdit->append(chunk);
}
