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

#ifndef STYLE_H
#define STYLE_H

#include <QProxyStyle>
#include <QPrimitiveElemet>
#include <QStyleOption>
#include <QPainter>
#include <QWidget>

class Style : public QProxyStyle
{
    Q_OBJECT
    
public:
    Style();
    ~Style();
    
    void drawPrimitive(QStyle::QPrimitiveElemet element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const override;
};

#endif
