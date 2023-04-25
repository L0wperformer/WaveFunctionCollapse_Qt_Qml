#include "handler.h"
#include "definitions.h"
#include <QGuiApplication>
#include <QList>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);

  //    QQmlApplicationEngine engine;
  //    const QUrl url(QStringLiteral("qrc:/main.qml"));
  //    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
  //                     &app, [url](QObject *obj, const QUrl &objUrl) {
  //        if (!obj && url == objUrl)
  //            QCoreApplication::exit(-1);
  //    }, Qt::QueuedConnection);
  //    engine.load(url);

  // RULES
  QList<QList<int>> sockets = {
      //            INDEX
      {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}, // 0
      {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // 1
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0}, // 2
      {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, // 3
      {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0}, // 4
      {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0}, // 5
      {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}, // 6
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0}, // 7
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // 8
      {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // 9
      {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, // 10
      {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1}, // 11
      {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0}, // 12
      {0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0}, // 13
      {0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0}, // 14
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1}, // 15
      {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0}, // 16
      {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // 17
      {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, // 18
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, // 19
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 20
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // 21
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // 22
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // 23
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 24
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 25

  };

        QList<int> disadvantageWeightsNormalizedNoStop = {
            1,  // 0
            2,  // 1
            2,  // 2
            4,  // 3
            4,  // 4        These weights were chosen "normalized"
            4,  // 5        So x pieces of similar type get
            4,  // 6        a disadvantage of x
            4,  // 7        Tiles that stop a line are
            4,  // 8        10x times as unlikely
            4,  // 9
            4,  // 10
            4,  // 11
            4,  // 12
            4,  // 13
            4,  // 14
            2,  // 15
            2,  // 16
            80, // 17
            80, // 18
            80, // 19
            80, // 20
            80, // 21
            80, // 22
            80, // 23
            80, // 24
            1   // 25
        };
    QList<int> disadvantageWeightsAllEquallyLikely = {
        1, // 0
        1, // 1
        1, // 2
        1, // 3
        1, // 4        All equally likely
        1, // 5
        1, // 6
        1, // 7
        1, // 8
        1, // 9
        1, // 10
        1, // 11
        1, // 12
        1, // 13
        1, // 14
        1, // 15
        1, // 16
        1, // 17
        1, // 18
        1, // 19
        1, // 20
        1, // 21
        1, // 22
        1, // 23
        1, // 24
        1  // 25
    };
    QList<int> disadvantageWeightsClusters = {
        2,   // 0
        1,   // 1
        1,   // 2
        10,  // 3
        10,  // 4        These weights make connections
        10,  // 5        between diagonal and horizontal
        10,  // 6        unlikely
        10,  // 7        resulting in long diagonals
        10,  // 8        and clusters
        10,  // 9
        10,  // 10
        100, // 11
        100, // 12
        100, // 13
        100, // 14
        5,   // 15
        5,   // 16
        80,  // 17
        80,  // 18
        80,  // 19
        80,  // 20
        80,  // 21
        80,  // 22
        80,  // 23
        80,  // 24
        20   // 25
    };
    QList<int> disadvantageWeightsLongDiagonals = {
        1,  // 0
        2,  // 1
        2,  // 2
        20, // 3
        20, // 4        These weights were chosen to
        20, // 5        encourage long diagonals
        20, // 6        All pieces that end a diagonal
        30, // 7        or arent diagonal
        30, // 8        got a much higher weight
        30, // 9
        30, // 10
        10, // 11
        10, // 12
        10, // 13
        10, // 14
        1,  // 15
        1,  // 16
        80, // 17
        80, // 18
        80, // 19
        80, // 20
        80, // 21
        80, // 22
        80, // 23
        80, // 24
        20   // 25
    };

      QList<int> disadvantageWeightsNormalized = {
          5, // 0
          2, // 1
          2, // 2
          5, // 3
          5, // 4        These weights were chosen "normalized"
          5, // 5        So x pieces of similar type get
          5, // 6        a disadvantage of x
          4, // 7
          4, // 8
          4, // 9
          4, // 10
          4, // 11
          4, // 12
          4, // 13
          4, // 14
          2, // 15
          2, // 16
          8, // 17
          8, // 18
          8, // 19
          8, // 20
          8, // 21
          8, // 22
          8, // 23
          8, // 24
          1  // 25
      };

      QList<int> disadvantageWeightsVerticals = {
          100, // 0
          1, // 1
          100, // 2
          1, // 3
          100, // 4
          1, // 5
          100, // 6
          100, // 7
          100, // 8
          100, // 9
          100, // 10
          100, // 11
          100, // 12
          100, // 13
          100, // 14
          100, // 15
          100, // 16
          100, // 17
          100, // 18
          100, // 19
          100, // 20
          100, // 21
          5, // 22
          100, // 23
          5, // 24
          100  // 25

      };

      QList<int> disadvantageWeightsHorizontals = {
          100, // 0
          100, // 1
          1, // 2-
          100, // 3
          1, // 4-
          100, // 5
          1, // 6-
          100, // 7
          100, // 8
          100, // 9
          100, // 10
          100, // 11
          100, // 12
          100, // 13
          100, // 14
          100, // 15
          100, // 16
          100, // 17
          100, // 18
          100, // 19
          100, // 20
          50, // 21-
          100, // 22
          50, // 23-
          100, // 24
          100  // 25

      };

      QList<int> disadvantageWeightsWhiteout = {//mostly for testing
                                               1000, // 0
                                               1000, // 1
                                               1000, // 2-
                                               1000, // 3
                                               1000, // 4-
                                               1000, // 5
                                               1000, // 6-
                                               1000, // 7
                                               1000, // 8
                                               1000, // 9
                                               1000, // 10
                                               1000, // 11
                                               1000, // 12
                                               1000, // 13
                                               1000, // 14
                                               1000, // 15
                                               1000, // 16
                                               1000, // 17
                                               1000, // 18
                                               1000, // 19
                                               1000, // 20
                                               1000, // 21-
                                               1000, // 22
                                               1000, // 23-
                                               1000, // 24
                                               1  // 25

      };




//All avaiblae weightlists. Default at index 0
 QList<QList<int>> availableDisadvantageWeightlist;
 availableDisadvantageWeightlist
         //<<disadvantageWeightsAllEquallyLikely//DEFAULT //0
       << disadvantageWeightsWhiteout//0
       << disadvantageWeightsNormalizedNoStop//1

       << disadvantageWeightsClusters//2
       << disadvantageWeightsLongDiagonals//3
       << disadvantageWeightsNormalized//4
       << disadvantageWeightsVerticals//5
       << disadvantageWeightsHorizontals;//6
//Weightmap: What index uses what weightlist?
//All that are not specified have the standard weightlist (index 0 in  availableDisadvantageWeightlist)
//If the rangepair has -1 as second value, it will apply the pair until the end.
 //Will not work if not on last range (index-wise)

//QList<constructWeightMapParameters> disadvantageWeightmap;

//for  (int i = 0; i< 10; i++){
//    disadvantageWeightmap.insert(Rangepair(0+i*60,31+i*60),5);
//}
//disadvantageWeightmap.insert(Rangepair(400,500),5);

 //long names are.... long
 typedef constructionStartIndexType csit;
 typedef constructionDirection cd;
 QList<constructParameters> numberWeightmapOne{
     constructParameters(csit::tileStartIndex,
                         425,10,6,false,5,cd::horizontal),
     constructParameters(csit::tileStartIndex,
                         430,30,5,false,5,cd::vertical)
 };
// QList<constructParameters> disadvantageWeightmapConstructionInstructions{
//     constructParameters(constructionStartIndexType::columnStartIndex,
//                         0,-1,5,false,60,constructionDirection::vertical),
//     constructParameters(constructionStartIndexType::lineStartIndex,
//                         8,-1,6,false,16,constructionDirection::horizontal )

// };
 QList<constructParameters> disadvantageWeightmapConstructionInstructions = numberWeightmapOne;

 QList<constructParameters> precollapedTilesConstructionInstructions;


 Handler h(sockets,100 ,50, sockets.length(),precollapedTilesConstructionInstructions ,disadvantageWeightmapConstructionInstructions,availableDisadvantageWeightlist);





 auto view = new QQuickView;


  view->rootContext()->setContextProperty("handler", &h);
  view->setSource(QUrl("qrc:/main.qml"));
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  view->show();

  return app.exec();
}
