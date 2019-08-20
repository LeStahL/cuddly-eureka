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

#include "Demo.hpp"
#include "Scene.hpp"

Demo::Demo()
    : m_demo_name("unnamed-demo")
{
}

Demo::Demo(QVariant serial)
{
    QList<QVariant> data = serial.toList();
    
    m_demo_name = data.at(0).toString();
    for(int i=0; i<data.size(); ++i)
    {
        QVariant scene_serial = data.at(i);
        m_scenes.push_back(new Scene(scene_serial));
    }
}

QVariant Demo::serialize()
{
    QList<QVariant> data;
    
    data.push_back(QVariant(m_demo_name));
    for(int i=0; i<m_scenes.size(); ++i)
    {
        data.push_back(m_scenes.at(i)->serialize());
    }
    
    return QVariant(data);
}
