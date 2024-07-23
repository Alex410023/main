#pragma once

#include "table.h"
#include "rack.h"
#include "bookitem.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class ViewWidget : public QGraphicsView {
    Q_OBJECT

    QGraphicsScene* scene;
    Table* table;
    Rack* rack;

    bool moveToStackMode;
    bool moveToShelfMode;
    bool readMode;

public:
    explicit ViewWidget(QWidget* parent = nullptr);

    void setTable(Table* table);
    void setRack(Rack* rack, int tableWidth);

    void setMoveToStackMode(bool mode);
    void setMoveToShelfMode(bool mode);
    void setReadMode(bool mode);

    bool getMoveToStackMode() ;
    bool getMoveToShelfMode() ;
    bool getReadMode() ;

protected:
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void bookItemSelected(BookItem* bookItem);
};
