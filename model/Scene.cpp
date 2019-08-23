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

#include <QVariantMap>
#include <QDebug>
 
Scene::Scene(QString name)
    : m_name(name)
    , m_t_start(0)
    , m_t_end(0)
{
}

QVariant Scene::serialize()
{
    QVariantMap data;
    
    data.insert(QString("name"), QVariant(m_name));
    data.insert(QString("t_start"), QVariant(m_t_start));
    data.insert(QString("t_end"), QVariant(m_t_end));
    
    return QVariant(data);
}

void Scene::deserialize(QVariant data)
{
    QVariantMap mapdata = data.toMap();
    
    m_name = mapdata["name"].toString();
    m_t_start = mapdata["t_start"].toFloat();
    m_t_end = mapdata["m_t_end"].toFloat();
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
