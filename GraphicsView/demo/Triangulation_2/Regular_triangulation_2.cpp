#include <fstream>

// CGAL headers
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Regular_triangulation_euclidean_traits_2.h>
#include <CGAL/Regular_triangulation_2.h>

#include <CGAL/point_generators_2.h>

// Qt headers
#include <QtGui>
#include <QString>
#include <QActionGroup>
#include <QFileDialog>
#include <QInputDialog>

// GraphicsView items and event filters (input classes)

#include "RegularTriangulationRemoveVertex.h"
#include <CGAL/Qt/GraphicsViewCircleInput.h>
#include <CGAL/Qt/RegularTriangulationGraphicsItem.h>
#include <CGAL/Qt/PowerdiagramGraphicsItem.h>
  
// for viewportsBbox
#include <CGAL/Qt/utility.h>
// the two base classes
#include "ui_Regular_triangulation_2.h"
#include <CGAL/Qt/DemosMainWindow.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Point_2 Circle_2;
typedef K::Iso_rectangle_2 Iso_rectangle_2;

typedef double Weight;
typedef CGAL::Regular_triangulation_euclidean_traits_2<K,Weight>  Gt;
typedef CGAL::Regular_triangulation_2<Gt> Regular;

class MainWindow :
  public CGAL::Qt::DemosMainWindow,
  public Ui::Regular_triangulation_2
{
  Q_OBJECT
  
private:  
  Regular dt; 
  QGraphicsScene scene;  

  CGAL::Qt::RegularTriangulationGraphicsItem<Regular> * dgi;
  CGAL::Qt::PowerdiagramGraphicsItem<Regular> * vgi;

  CGAL::Qt::RegularTriangulationRemoveVertex<Regular> * trv;
  CGAL::Qt::GraphicsViewCircleInput<K> * pi;
public:
  MainWindow();

public slots:

  void processInput(CGAL::Object o);

  void on_actionShowRegular_toggled(bool checked);

  void on_actionShowPowerdiagram_toggled(bool checked);

  void on_actionInsertPoint_toggled(bool checked);
  
  void on_actionInsertRandomPoints_triggered();

  void on_actionLoadPoints_triggered();

  void on_actionSavePoints_triggered();

  void on_actionClear_triggered();

  void on_actionRecenter_triggered();


signals:
  void changed();
};


MainWindow::MainWindow()
  : DemosMainWindow()
{
  setupUi(this);

  // Add a GraphicItem for the Regular triangulation
  dgi = new CGAL::Qt::RegularTriangulationGraphicsItem<Regular>(&dt);

  QObject::connect(this, SIGNAL(changed()),
		   dgi, SLOT(modelChanged()));

  dgi->setVerticesPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  scene.addItem(dgi);

  // Add a GraphicItem for the Powerdiagram diagram
  vgi = new CGAL::Qt::PowerdiagramGraphicsItem<Regular>(&dt);

  QObject::connect(this, SIGNAL(changed()),
		   vgi, SLOT(modelChanged()));

  vgi->setEdgesPen(QPen(Qt::blue, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  scene.addItem(vgi);
  vgi->hide();

  // Setup input handlers. They get events before the scene gets them
  // and the input they generate is passed to the triangulation with 
  // the signal/slot mechanism    
  pi = new CGAL::Qt::GraphicsViewCircleInput<K>(this, &scene, 1); // emits center/radius
                                                                           

  QObject::connect(pi, SIGNAL(generate(CGAL::Object)),
		   this, SLOT(processInput(CGAL::Object)));

  trv = new CGAL::Qt::RegularTriangulationRemoveVertex<Regular>(&dt, this);
  QObject::connect(trv, SIGNAL(modelChanged()),
		   this, SIGNAL(changed()));

  // 
  // Manual handling of actions
  //
  QObject::connect(this->actionQuit, SIGNAL(triggered()), 
		   this, SLOT(close()));

  // We put mutually exclusive actions in an QActionGroup
  QActionGroup* ag = new QActionGroup(this);
  ag->addAction(this->actionInsertPoint);

  // Check two actions 
  this->actionInsertPoint->setChecked(true);
  this->actionShowRegular->setChecked(true);

  //
  // Setup the scene and the view
  //
  scene.setItemIndexMethod(QGraphicsScene::NoIndex);
  scene.setSceneRect(-100, -100, 100, 100);
  this->graphicsView->setScene(&scene);
  this->graphicsView->setMouseTracking(true);

  // Turn the vertical axis upside down
  this->graphicsView->matrix().scale(1, -1);
                                                      
  // The navigation adds zooming and translation functionality to the
  // QGraphicsView
  this->addNavigation(this->graphicsView);

  this->setupStatusBar();
  this->setupOptionsMenu();
  this->addAboutDemo(":/cgal/help/about_Regular_triangulation_2.html");
  this->addAboutCGAL();
}


void
MainWindow::processInput(CGAL::Object o)
{
  std::pair<Point_2, K::FT > center_sqr;
  if(CGAL::assign(center_sqr, o)){
    Regular::Point wp(center_sqr.first, center_sqr.second);
    dt.insert(wp);
  }

  emit(changed());
}


/* 
 *  Qt Automatic Connections
 *  http://doc.trolltech.com/4.4/designer-using-a-component.html#automatic-connections
 * 
 *  setupUi(this) generates connections to the slots named
 *  "on_<action_name>_<signal_name>"
 */
void
MainWindow::on_actionInsertPoint_toggled(bool checked)
{
  if(checked){
    scene.installEventFilter(pi);
    scene.installEventFilter(trv);
  } else {
    scene.removeEventFilter(pi);
    scene.removeEventFilter(trv);
  }
}



void
MainWindow::on_actionShowRegular_toggled(bool checked)
{
  dgi->setVisibleEdges(checked);
}


void
MainWindow::on_actionShowPowerdiagram_toggled(bool checked)
{
  vgi->setVisible(checked);
}


void
MainWindow::on_actionClear_triggered()
{
  dt.clear();
  emit(changed());
}


void
MainWindow::on_actionInsertRandomPoints_triggered()
{
  QRectF rect = CGAL::Qt::viewportsBbox(&scene);
  CGAL::Qt::Converter<K> convert;
  Iso_rectangle_2 isor = convert(rect);
  CGAL::Random_points_in_iso_rectangle_2<Point_2> pg(isor.min(), isor.max());
  const int number_of_points = 
    QInputDialog::getInteger(this, 
                             tr("Number of random points"),
                             tr("Enter number of random points"), 100, 0);

  // wait cursor
  QApplication::setOverrideCursor(Qt::WaitCursor);
  std::vector<Point_2> points;
  points.reserve(number_of_points);
  for(int i = 0; i < number_of_points; ++i){
    points.push_back(*pg++);
  }
  dt.insert(points.begin(), points.end());
  // default cursor
  QApplication::setOverrideCursor(Qt::ArrowCursor);
  emit(changed());
}


void
MainWindow::on_actionLoadPoints_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this,
						  tr("Open Points file"),
						  ".");
  if(! fileName.isEmpty()){
    std::ifstream ifs(qPrintable(fileName));

    K::Point_2 p;
    std::vector<K::Point_2> points;
    while(ifs >> p) {
      points.push_back(p);
    }
    dt.insert(points.begin(), points.end());

    actionRecenter->trigger();
    emit(changed());
  }
}


void
MainWindow::on_actionSavePoints_triggered()
{
  QString fileName = QFileDialog::getSaveFileName(this,
						  tr("Save points"),
						  ".");
  if(! fileName.isEmpty()){
    std::ofstream ofs(qPrintable(fileName));
    for(Regular::Finite_vertices_iterator 
          vit = dt.finite_vertices_begin(),
          end = dt.finite_vertices_end();
        vit!= end; ++vit)
    {
      ofs << vit->point() << std::endl;
    }
  }
}


void
MainWindow::on_actionRecenter_triggered()
{
  this->graphicsView->setSceneRect(dgi->boundingRect());
  this->graphicsView->fitInView(dgi->boundingRect(), Qt::KeepAspectRatio);  
}


#include "Regular_triangulation_2.moc"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  // Import resources from libCGALQt4.
  // See http://doc.trolltech.com/4.4/qdir.html#Q_INIT_RESOURCE
  Q_INIT_RESOURCE(File);
  Q_INIT_RESOURCE(Triangulation_2);
  Q_INIT_RESOURCE(Input);
  Q_INIT_RESOURCE(CGAL);

  MainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
