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

#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <QVariant>
#include <QList>

class Scene
{
public:
    Scene(QString name = "");
    Scene(QVariant serial);
    QVariant serialize();
    QString name();
    float tStart() const;
    float tEnd() const;
    void setTStart(float tstart);
    void setTEnd(float tend);
    void rename(QString name);
    
private:
    QString m_name;
    float m_t_start,
        m_t_end;
};

#endif
