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
 
 #include "Scene.hpp"
 
Scene::Scene(QString name)
    : m_name(name)
    , m_t_start(0)
    , m_t_end(0)
{
}

QVariant Scene::serialize()
{
    QList<QVariant> data;
    
    data.push_back(QVariant(m_name));
    
    return QVariant(data);
}

Scene::Scene(QVariant serial)
{
    QList<QVariant> data = serial.toList();
    
    m_name = data.at(0).toString();
}

QString Scene::name()
{
    return m_name;
}

void Scene::setTEnd(float tend)
{
    m_t_end = tend;
}

float Scene::tEnd() const
{
    return m_t_end;
}

void Scene::setTStart(float tstart)
{
    m_t_start = tstart;
}

float Scene::tStart() const
{
    return m_t_start;
}

void Scene::rename(QString name)
{
    m_name = name;
}
