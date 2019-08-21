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

#include <QDebug>

Demo::Demo()
    : m_scenes(new QList<Scene *>)
    , m_demo_name("unnamed-demo")
{
}

Demo::Demo(QVariant serial)
    : m_scenes(new QList<Scene *>)
    , m_demo_name("unnamed-demo")
{
    QList<QVariant> data = serial.toList();
    
    m_demo_name = data.at(0).toString();
    for(int i=0; i<data.size(); ++i)
    {
        QVariant scene_serial = data.at(i);
        m_scenes->push_back(new Scene(scene_serial));
    }
}

Demo::~Demo()
{
    delete m_scenes;
}


QVariant Demo::serialize()
{
    QList<QVariant> data;
    
    data.push_back(QVariant(m_demo_name));
    for(int i=0; i<m_scenes->size(); ++i)
        data.push_back(m_scenes->at(i)->serialize());
    
    return QVariant(data);
}

Scene * Demo::sceneAt(int index)
{
    if(index < 0 || index >= m_scenes->size()) return 0;
    return m_scenes->at(index);
}

Scene * Demo::sceneWithName(QString name)
{
    for(int i=0; i<m_scenes->size(); ++i)
    {
        if(m_scenes->at(i)->name() == name)
            return m_scenes->at(i);
    }
    return 0;
}

bool Demo::addScene(QString name)
{
    for(int i=0; i<m_scenes->size(); ++i)
    {
        if(m_scenes->at(i)->name() == name)
            return false;
    }
    
    if(name == "")
        m_scenes->push_back(new Scene(QString("Scene ")+QString::number(m_scenes->size())+QString(" (Unnamed)")));
    else 
        m_scenes->push_back(new Scene(name));
    
    return true;
}

bool Demo::removeScene(QString name)
{
    Scene *scene = sceneWithName(name);
    if(scene == 0) return false;
    delete scene;
    return true;
}

int Demo::nScenes() const
{
    return m_scenes->size();
}

QString Demo::sceneName(int index) const
{
    return m_scenes->at(index)->name();
}

static bool compareScenes(const Scene* first, const Scene* second)
{
    if(first->tEnd() < second->tStart()) return true;
    return false;
}

void Demo::sortChronologically()
{
    std::sort(m_scenes->begin(), m_scenes->end(), compareScenes);
}

bool Demo::addScene(Scene* scene)
{
    if(!m_scenes->contains(scene))
        m_scenes->push_back(scene);
    else return false;
    
    sortChronologically();
    return true;
}

bool Demo::removeScene(Scene* scene)
{
    if(m_scenes->contains(scene))
        m_scenes->removeOne(scene);
    else return false;
    
    return true;
}

int Demo::sceneIndex(Scene* scene)
{
    return m_scenes->indexOf(scene);
}

