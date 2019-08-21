/* cuddly-eureka - Storyboard editor by Team210
 * Copyright (C) 2019  Alexander Kraus <nr4@z10.info>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "model/AddSceneCommand.hpp"
#include "model/RemoveSceneCommand.hpp"

#include <QDebug>
#include <QModelIndexList>
#include <QItemSelectionModel>

MainWindow::MainWindow(QApplication *app)
    : QMainWindow()
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    
    m_demo = new Demo();
    m_demo_model = new DemoModel(m_demo, &m_undo_stack);

    m_ui->tableView->setModel(m_demo_model);
    m_ui->tableView->setStyleSheet("QHeaderView::section { background-color:#3d253b; color:#f3bf8f; }");
    m_ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    m_ui->tableView->update();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::newDemo()
{
}

void MainWindow::saveDemo()
{
}

void MainWindow::openDemo()
{
}

void MainWindow::addScene()
{
    m_undo_stack.push(new AddSceneCommand(m_demo_model));
    m_ui->actionUndo->setEnabled(true);
}

void MainWindow::removeScene()
{
    // Find selected rows
    QItemSelectionModel *select = m_ui->tableView->selectionModel();

    if(!select->hasSelection()) return;
    QModelIndexList rows = select->selectedRows();
    for(int i=0; i<rows.size(); ++i)
    {
        QModelIndex index = rows.at(i);
        m_undo_stack.push(new RemoveSceneCommand(m_demo_model, m_demo->sceneAt(index.row())));
    }
    m_ui->actionUndo->setEnabled(true);
}

void MainWindow::redo()
{
    m_undo_stack.redo();
    if(!m_undo_stack.canRedo())
        m_ui->actionRedo->setEnabled(false);
    m_ui->actionUndo->setEnabled(true);
}

void MainWindow::undo()
{
    m_undo_stack.undo();
    if(!m_undo_stack.canUndo())
        m_ui->actionUndo->setEnabled(false);
    m_ui->actionRedo->setEnabled(true);
}


