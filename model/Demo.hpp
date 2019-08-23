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
 
#ifndef DEMO_H
#define DEMO_H

#include <QString>
#include <QList>
#include <QVariant>

class Scene;

static bool compareScenes(const Scene* first, const Scene* second);

class Demo
{
public:
    Demo();
    virtual ~Demo();
    QVariant serialize();
    void deserialize(QVariant data);
    
    bool addScene(QString name = "");
    bool addScene(Scene *scene);
    bool removeScene(Scene *scene);
    bool removeScene(QString name);
    bool renameScene(QString name);
    Scene *sceneAt(int index);
    Scene *sceneWithName(QString name);
    int nScenes() const;
    QString sceneName(int index) const;
    void sortChronologically();
    int sceneIndex(Scene *scene);
    
private:
    QString m_demo_name;
    QList<Scene *> *m_scenes;
};

#endif
