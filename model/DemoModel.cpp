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

#include "DemoModel.hpp"
#include "Scene.hpp"

#include <QFont>
#include <QColor>
#include <QPushButton>

DemoModel::DemoModel(Demo* demo, QObject* parent)
    : QAbstractTableModel(parent)
    , m_demo(demo)
{
}

DemoModel::~DemoModel()
{
}

int DemoModel::rowCount(const QModelIndex& parent) const
{
    return m_demo->nScenes();
}

int DemoModel::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QVariant DemoModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(index.column() == 0)
            return QVariant(m_demo->sceneName(index.row()));
        else if(index.column() == 1)
            return QVariant(m_demo->sceneAt(index.row())->tStart());
        else if(index.column() == 2)
            return QVariant(m_demo->sceneAt(index.row())->tEnd());
        else if(index.column() == 3)
            return QVariant(QString("del"));
        else if(index.column() == 4)
            return QVariant(QString("SceneView"));
    }
    else if(role == Qt::BackgroundColorRole)
    {
        if(index.row() % 2 == 0)
        {
            QColor color;
            color.setNamedColor("#f3bf8f");
            return QVariant(color);
        }
        else
        {
            QColor color;
            color.setNamedColor("#f2a27f");
            return QVariant(color);
        }
    }
    else if(role == Qt::TextColorRole)
    {
        return QVariant(QColor::fromRgb(0,0,0));
    }
    else if(role == Qt::FontRole)
    {
        QFont font;
        font.setBold(true);
        font.setPointSize(11.);
        return QVariant(font);
    }
    return QVariant();
}

QVariant DemoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(section == 0)
                return QVariant("Name");
            else if(section == 1)
                return QVariant("tlo");
            else if(section == 2)
                return QVariant("thi");
            else if(section == 3)
                return QVariant("del");
            else if(section == 4)
                return QVariant("Connections");
        }
        else if(orientation == Qt::Vertical)
        {
            return QVariant(section);
        }
    }
    else if(role == Qt::BackgroundColorRole)
    {
            QColor color;
            color.setNamedColor("#3d253b");
            return QVariant(color);
    }
    else if(role == Qt::TextColorRole)
    {
            QColor color;
            color.setNamedColor("#f3bf8f");
            return QVariant(color);
    }
    else if(role == Qt::FontRole)
    {
        QFont font;
        font.setBold(true);
        font.setPointSize(11.);
        return QVariant(font);
    }
    return QVariant();
}

Demo * DemoModel::demo()
{
    return m_demo;
}

void DemoModel::beginInsertRows(const QModelIndex& m, int row, int col)
{
    QAbstractTableModel::beginInsertRows(m, row, col);
}

void DemoModel::beginRemoveRows(const QModelIndex& m, int row, int col)
{
    QAbstractTableModel::beginRemoveRows(m, row, col);
}

void DemoModel::endInsertRows()
{
    QAbstractTableModel::endInsertRows();
}

void DemoModel::endRemoveRows()
{
    QAbstractTableModel::endRemoveRows();
}

void DemoModel::update(int row, int column)
{
    emit dataChanged(index(row,column), index(row, column));
}

void DemoModel::updateAll()
{
    emit dataChanged(index(0,0), index(rowCount(), columnCount()));
}
