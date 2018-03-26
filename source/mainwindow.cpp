/* -------------------------------------------------
*
* ClipboardManager is a lightweight tool to analyze and modify the content of the clipboard.
* Copyright © 2018 remileduc
* remi.ducceschi@gmail.com
*
* This file is part of ClipboardManager.
*
* ClipboardManager is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* ------------------------------------------------- */

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <utility>

#include <QApplication>
#include <QClipboard>
#include <QLineEdit>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->combo->lineEdit()->setPlaceholderText("Add MIME type...");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::copy()
{
    auto* mimedata = new QMimeData();
    for (const auto& p : content)
        mimedata->setData(p.first.c_str(), p.second.c_str());
    QApplication::clipboard()->setMimeData(mimedata);
}

void MainWindow::paste()
{
    clear();

    const auto& clip = QApplication::clipboard()->mimeData();
    content.reserve(clip->formats().size());
    for (const auto& format : clip->formats())
    {
        content.emplace(format.toStdString(), clip->data(format));
    }
    if (!content.empty())
    {
        ui->combo->blockSignals(true);
        ui->combo->addItems(clip->formats());
        ui->combo->setCurrentText(std::cbegin(content)->first.c_str());
        ui->combo->blockSignals(false);
        ui->textArea->blockSignals(true);
        ui->textArea->setPlainText(std::cbegin(content)->second.c_str());
        ui->textArea->blockSignals(false);
    }
}

void MainWindow::clear()
{
    ui->combo->clear();
    ui->textArea->clear();
    content.clear();
}

void MainWindow::mimeTypeChanged(const QString &type)
{
    if (content.find(type.toStdString()) != std::end(content))
        ui->textArea->setPlainText(content[type.toStdString()].c_str());
    else
        content[type.toStdString()] = ui->textArea->toPlainText().toStdString();
}

void MainWindow::contentChanged()
{
    const QString& type = ui->combo->currentText();
    if (!type.isEmpty() && ui->combo->findText(type) == -1)
        ui->combo->addItem(type);
    content[type.toStdString()] = ui->textArea->toPlainText().toStdString();
}

void MainWindow::removeMimeType()
{
    content.erase(ui->combo->currentText().toStdString());
    ui->combo->removeItem(ui->combo->currentIndex());
    ui->textArea->setPlainText(content[ui->combo->currentText().toStdString()].c_str());
}
