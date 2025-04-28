/*
 * Copyright (c) 2025 Matvii Jarosh
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/
#include "mainwindow.h"
#include "utils.h"

#include <string>
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QFrame>
#include <QSplitter>
#include <QHeaderView>

MainWindow::~MainWindow() {}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("REPL");
    setMinimumSize(640, 480);

    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal, this);
    mainSplitter->setHandleWidth(1);

    QSplitter *rightVerticalSplitter = new QSplitter(Qt::Vertical);
    rightVerticalSplitter->setHandleWidth(1);

    topRightWidget = new QTextEdit;
    topRightWidget->setTabStopDistance(20);
    topRightWidget->setReadOnly(true);
    topRightWidget->setFont(QFont("Consolas", 10));
    topRightWidget->setStyleSheet("border-radius: 0");

    QWidget *central = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    input = new CodeEditor();
    input->setTabStopDistance(20);
    input->setFont(QFont("Consolas", 10));
    input->setPlaceholderText("Enter Scheme code");
    input->setStyleSheet("border-radius: 0");

    QPushButton *evalButton = new QPushButton("Eval");
    evalButton->setStyleSheet("border-radius: 0; height: 30px;");
    evalButton->setCursor(Qt::PointingHandCursor);

    table = new QTableView(this);
    model = new QStandardItemModel(this);
    table->setModel(model);
    model->setHorizontalHeaderLabels({"Name", "Value"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->verticalHeader()->setVisible(false);


    layout->addWidget(input);
    layout->addWidget(evalButton);
    rightVerticalSplitter->addWidget(topRightWidget);
    rightVerticalSplitter->addWidget(central);
    mainSplitter->addWidget(table);
    mainSplitter->addWidget(rightVerticalSplitter);

    setCentralWidget(mainSplitter);

    env0 = std::make_shared<Environment>();
    interp = Evaluator();

    updateTable();
    connect(evalButton, &QPushButton::clicked, this, &MainWindow::evalButtonClick);
}

void MainWindow::updateTable() {
    model->clear();
    model->setHorizontalHeaderLabels({"Name", "Value"});

    for (const auto& [name, value] : env0->map) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(QString::fromStdString(name))
                 << new QStandardItem(QString::fromStdString(value.str()));
        model->appendRow(rowItems);
    }

    table->resizeColumnsToContents();
}

void MainWindow::evalButtonClick() {
    QString inputText = input->toPlainText();
    topRightWidget->append("> " + inputText);
    std::string inputStr = inputText.toStdString();

    if (!areParenthesesBalanced(inputStr)) {
        topRightWidget->append("Error: Unbalanced parentheses");
        return;
    }

    try {
        auto tokens = tokenizeLisp(inputStr);
        TokenStream ts(tokens);
        auto exp = ListObject::parse_tokens(ts);
        Value result = interp.Eval(exp, env0);
        topRightWidget->append(QString::fromStdString(result.str()));
        updateTable();
    } catch (const std::exception& e) {
        topRightWidget->append("Error: " + QString::fromStdString(e.what()));
    } catch (...) {
        topRightWidget->append("Error: " + QString::fromStdString("Unknown error occurred"));
    }
}
