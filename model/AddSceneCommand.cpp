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

#include "AddSceneCommand.hpp"

#include <QDebug>   

AddSceneCommand::AddSceneCommand(DemoModel* model)
    : m_model(model)
{
    ++SCENE_COUNTER;
    
    m_scene = new Scene(QString("Scene ")+QString::number(SCENE_COUNTER));
}

AddSceneCommand::~AddSceneCommand()
{
    delete m_scene;
}

void AddSceneCommand::redo()
{
    m_model->beginInsertRows(QModelIndex(), m_model->rowCount()-1, m_model->rowCount()-1);
    m_model->demo()->addScene(m_scene);
    m_model->endInsertRows();
    m_model->updateAll();
}

void AddSceneCommand::undo()
{
    m_model->beginRemoveRows(QModelIndex(),m_model->demo()->sceneIndex(m_scene), m_model->demo()->sceneIndex(m_scene));
    m_model->demo()->removeScene(m_scene);
    m_model->endRemoveRows();
    m_model->updateAll();
}
