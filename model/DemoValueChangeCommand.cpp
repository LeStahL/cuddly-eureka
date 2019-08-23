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
 
 #include "DemoValueChangeCommand.hpp"

DemoValueChangeCommand::DemoValueChangeCommand(const QModelIndex &index, const QVariant value, DemoModel *model)
    : QUndoCommand()
{
    m_model = model;
    m_old = index.data(Qt::DisplayRole);
    m_new = value;
    m_row = index.row();
    m_col = index.column();
    setText(QString("Value change at (%1, %2) from %3 to %4").arg(m_row).arg(m_col).arg(m_old.toInt()).arg(m_new.toInt()));
}

void DemoValueChangeCommand::redo()
{
    if(m_col == 0)
        m_model->demo()->sceneAt(m_row)->rename(m_new.toString());
    else if(m_col == 1)
        m_model->demo()->sceneAt(m_row)->setTStart(m_new.toFloat());
    else if(m_col == 2)
        m_model->demo()->sceneAt(m_row)->setTEnd(m_new.toFloat());
    m_model->update(m_row, m_col);
    m_model->demo()->sortChronologically();
}

void DemoValueChangeCommand::undo()
{
    if(m_col == 0)
        m_model->demo()->sceneAt(m_row)->rename(m_old.toString());
    else if(m_col == 1)
        m_model->demo()->sceneAt(m_row)->setTStart(m_old.toFloat());
    else if(m_col == 2)
        m_model->demo()->sceneAt(m_row)->setTEnd(m_old.toFloat());
    m_model->update(m_row, m_col);
    m_model->demo()->sortChronologically();
}

DemoValueChangeCommand::~DemoValueChangeCommand()
{
}
