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
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>

MainWindow::MainWindow(QApplication *app)
    : QMainWindow()
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    
    m_demo = new Demo();
    m_demo_model = new DemoModel(m_demo, &m_undo_stack);
    m_demo_model->setView(m_ui->tableView);

    m_ui->tableView->setModel(m_demo_model);
    m_ui->tableView->setStyleSheet("QToolbar { background:#3d253b; } QHeaderView::section { background-color:#3d253b; color:#f3bf8f; }");
    m_ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    m_ui->tableView->update();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::newDemo()
{
    delete m_demo;
    delete m_demo_model;
    m_undo_stack.clear();
    m_demo = new Demo();
    m_demo_model = new DemoModel(m_demo, &m_undo_stack);
    m_demo_model->setView(m_ui->tableView);
    m_ui->tableView->setModel(m_demo_model);
    m_ui->tableView->update();
}

void MainWindow::saveDemo()
{
    QVariant data = m_demo->serialize();
    QJsonDocument demo_document = QJsonDocument(data.toJsonObject());
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Demo"), "C:\\Demo", tr("JSON files (*.json)"));
    QFile demo_file(filename);
    demo_file.open(QFile::WriteOnly);
    demo_file.write(demo_document.toJson());
    demo_file.close();
}

void MainWindow::generateCode()
{
    QStringList filenames;
    QFileDialog d(this);
    d.setFileMode(QFileDialog::DirectoryOnly);
    d.setOption(QFileDialog::ShowDirsOnly);
    if(d.exec())
        filenames = d.selectedFiles();
    QString filename = filenames.at(0);
    
    QFile scenes_header(filename + "\\scenes.h");
    scenes_header.open(QFile::WriteOnly);
    
    QTextStream ts1(&scenes_header);
    
    ts1 << "#ifndef SCENES_HEADER\n";
    ts1 << "#define SCENES_HEADER\n";

    ts1 << "const int nscenes = " + QVariant(m_demo->nScenes()).toString() + ";\n";
    ts1 << "const double start_times[" + QVariant(m_demo->nScenes()).toString() + "] = {";
    if(m_demo->nScenes() > 0)
    {
        for(int i=0; i<m_demo->nScenes()-1; ++i)
            ts1 << QVariant(m_demo->sceneAt(i)->tStart()).toString() + ",";
        ts1 << QVariant(m_demo->sceneAt(m_demo->nScenes()-1)->tStart()).toString();
    }
    ts1 << "};\n";
    ts1 << "const char *scene_names[" + QVariant(m_demo->nScenes()).toString() + "] = {";
    if(m_demo->nScenes() > 0)
    {
        for(int i=0; i<m_demo->nScenes()-1; ++i)
            ts1 << "\"" + QVariant(m_demo->sceneAt(i)->name()).toString() + "\",";
        ts1 << "\"" + QVariant(m_demo->sceneAt(m_demo->nScenes()-1)->name()).toString() + "\"";
    }
    ts1 << "};\n";
    
    ts1 << "#endif\n";
    scenes_header.close();
    
    QFile draw_header(filename + "\\draw.h");
    draw_header.open(QFile::WriteOnly);
    
    QTextStream ts(&draw_header);
    
    ts << "#ifndef DRAW_HEADER\n";
    ts << "#define DRAW_HEADER\n";
    ts << "if(scene_override)\n";
    ts << "{\n";
    ts << "    if(override_index == 1) t = t_now;\n";
    ts << "    else t = t_now + start_times[override_index - 2];\n";
    ts << "}\n\n";
    
    for(int i=0; i<m_demo->nScenes(); ++i)
    {
        ts << (i==0?"":"else ");
        ts << "if(t < " << QVariant(m_demo->sceneAt(i)->tStart()).toString() + ")\n";
        ts << "{\n";
        ts << "    glUseProgram(" + QVariant(m_demo->sceneAt(i)->prefix()).toString() + "_program);\n";
        ts << "    glUniform1f(" + QVariant(m_demo->sceneAt(i)->prefix()).toString() + "_iTime_location, t);\n";
        ts << "    glUniform2f(" + QVariant(m_demo->sceneAt(i)->prefix()).toString() + "_iResolution_location, w, h);\n";
        ts << "#ifdef MIDI\n";
        for(int j=0; j<8; ++j)
            ts << "    glUniform1f(" + QVariant(m_demo->sceneAt(i)->prefix()).toString() + "_iFader" + QVariant(j).toString() + "_location, fader" + QVariant(j).toString() + ");\n";
        ts << "    if(override_index == " + QVariant(i).toString() + ")\n";
        ts << "    {\n";
        ts << "        select_button(override_index);\n";
        ts << "        override_index = " + QVariant(0).toString() + ";\n";
        ts << "    }\n";
        ts << "#endif\n";
        ts << "}\n";
    }
    
    ts << "#endif\n";
    
    draw_header.close();
}

void MainWindow::openDemo()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Save Demo"), "C:\\Demo", tr("JSON files (*.json)"));
    QFile demo_file(filename);
    demo_file.open(QFile::ReadOnly);
    QTextStream in(&demo_file);
    QString data = in.readAll();
    demo_file.close();
    QJsonDocument demo_document = QJsonDocument::fromJson(data.toUtf8());
    
    delete m_demo;
    delete m_demo_model;
    m_undo_stack.clear();
    m_demo = new Demo();
    
    QVariant vdata = demo_document.object();
    m_demo->deserialize(vdata);
    
    m_demo_model = new DemoModel(m_demo, &m_undo_stack);
    m_demo_model->setView(m_ui->tableView);
    m_ui->tableView->setModel(m_demo_model);
    m_ui->tableView->update();
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

void MainWindow::sortScenes()
{
    qDebug() << "Sorting.";
    m_demo->sortChronologically();
    m_demo_model->updateAll();
}


