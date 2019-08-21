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
 
#ifndef STARTTIMEVALUECHANGECOMMAND_H
#define STARTTIMEVALUECHANGECOMMAND_H

#include <QUndoCommand>

#include "DemoModel.hpp"
#include "Scene.hpp"

class StartTimeValueChangeCommand : public QUndoCommand
{
public:
    StartTimeValueChangeCommand(DemoModel *model, Scene *scene, float t_new);
    virtual ~StartTimeValueChangeCommand();
    
    void redo() override;
    void undo() override;
    
private:
    DemoModel *m_model;
    Scene *m_scene;
    float m_t_old, m_t_new;
};
 
 #endif
