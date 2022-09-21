#ifndef HANDLER_H
#define HANDLER_H

#include <QList>
#include <QObject>

class Handler : public QObject {
  Q_OBJECT
public:
  Handler(QList<QList<int>> rules);

public slots:
  void drawGrid(int gridSize);
signals:
  void gridInit(int dimensions);
  void drawTile(int tileIndex);

private:
  QVector<QVector<int>> *tileMap;
  QList<QList<int>> m_rules;

  void test();
};

#endif // HANDLER_H
