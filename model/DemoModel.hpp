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
 
 #ifndef DEMOMODEL_H
 #define DEMOMODEL_H
 
#include <QAbstractTableModel>
#include <QUndoStack>
#include <QTableView>

#include "Demo.hpp"

 class DemoModel : public QAbstractTableModel
 {
 public:
     explicit DemoModel(Demo *demo, QUndoStack *undo_stack, QObject *parent = nullptr);
     ~DemoModel();
     
     // Show
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    
    // Edit
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    
    void beginInsertRows(const QModelIndex &m, int row, int col);
    void beginRemoveRows(const QModelIndex &m, int row, int col);
    void endInsertRows();
    void endRemoveRows();
    void updateAll();
    void update(int row, int column);
    
    Demo *demo();
    
    void setView(QTableView *view);
    QTableView *view();
    
 private:
     Demo *m_demo;
     QUndoStack *m_undo_stack;
     QTableView *m_view;
 };
 
 #endif
