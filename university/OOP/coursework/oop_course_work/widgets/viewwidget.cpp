#include "viewwidget.h"
#include "bookitem.h"

#include <QGraphicsRectItem>
#include <QPen>
#include <QMessageBox>
#include <QMouseEvent>


ViewWidget::ViewWidget(QWidget* parent)
    : QGraphicsView(parent)
    , scene(new QGraphicsScene(this))
    , moveToStackMode(false)
    , moveToShelfMode(false)
    , readMode(false) {
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(800, 480);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void ViewWidget::setTable(Table* table) {
        this->table = table;
        scene->clear();
        const QVector<Stack>& stacks = table->getStacks();

        int maxStackThickness = 0;
        int bookMargin = 10;

        for (const Stack& stack : stacks) {
            int curStackThickness = stack.getStackThickness();
            if (maxStackThickness < curStackThickness) {
                maxStackThickness = curStackThickness;
            }
        }

        const Book firstBook = table->getStacks().at(0).getBooks().at(0);
        int width = firstBook.getWidth();
        int tableWidth = width * stacks.size() +
                            bookMargin * (stacks.size() - 1);
        table->setWidth(tableWidth);

        int tableHeight = 20;
        int xPos = 0;
        int yPos = maxStackThickness;

        QGraphicsRectItem* item = new QGraphicsRectItem(xPos, yPos, tableWidth, tableHeight);
        item->setBrush(Qt::darkRed);
        item->setPen(QPen(Qt::black));
        scene->addItem(item);

        for (const Stack& stack : stacks) {
            yPos = maxStackThickness;
            for (const Book& book : stack.getBooks()) {
                yPos -= book.getThickness();
                BookItem* item = new BookItem(book, xPos, yPos,
                                              book.getWidth(), book.getThickness());

                bool isOnTop = book == stack.getBooks().back();
                item->setOnTop(isOnTop);

                scene->addItem(item);
            }
            xPos += width + bookMargin;
        }
}

void ViewWidget::setRack(Rack* rack, int tableWidth) {
    if (this->rack == nullptr) {
        this->rack = rack;
    } else {
        QVector<Shelf> shelves = rack->getShelves();

        int shelfBorderThickness = 2;
        qreal width = shelves.at(0).getWidth();
        int height = shelves.at(0).getHeight();
        int xPos = tableWidth + 30;
        int yPos = 0;

        for (const Shelf& shelf : shelves) {
            QGraphicsRectItem* item = new QGraphicsRectItem(xPos, yPos, width, height);
            item->setPen(QPen(Qt::black, shelfBorderThickness));
            scene->addItem(item);
            yPos += height;
        }

        yPos = 0;

        for (const Shelf& shelf : shelves) {
            xPos = tableWidth + 30;
            for (const Book& book : shelf.getBooks()) {
                BookItem* item = new BookItem(book, xPos, yPos,
                                              book.getWidth(), book.getHeight());

                item->setOnTop(true);
                item->setBrush(Qt::gray);

                scene->addItem(item);
                xPos += book.getWidth();
            }
            yPos += height;
        }
    }
}

void ViewWidget::mousePressEvent(QMouseEvent* event) {
    QGraphicsView::mousePressEvent(event);

    QPointF scenePos = mapToScene(event->pos());
    QGraphicsItem* item = scene->itemAt(scenePos, QTransform());
    if (item && item->type() == BookItem::Type) {
        BookItem* bookItem = static_cast<BookItem*>(item);
        if (bookItem->getIsAccessible()) {
            emit bookItemSelected(bookItem);
        } else {
            QMessageBox::information(nullptr, "Book", "Cannot access non-top objects");
        }
    }
}


bool ViewWidget::getMoveToStackMode()  {
    return moveToStackMode;
}

bool ViewWidget::getMoveToShelfMode()  {
    return moveToShelfMode;
}

bool ViewWidget::getReadMode()  {
    return readMode;
}

void ViewWidget::setMoveToStackMode(bool mode) {
    moveToStackMode = mode;
}

void ViewWidget::setMoveToShelfMode(bool mode) {
    moveToShelfMode = mode;
}

void ViewWidget::setReadMode(bool mode) {
    readMode = mode;
}
