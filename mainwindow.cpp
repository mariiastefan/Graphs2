#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include "graph.h"
#include "arc.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFile>
#include <QWidget>
#include <QRadioButton>
#include <QTextStream>
#include <QMessageBox>
#include <QPainter>
#include <QtMath>
#include <random>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::paths(std::vector<bool> pathnode, int n, std::vector<std::vector<int>>& matrix)
{
    srand(time(NULL));
    pathnode.resize(n);
    int s = 0;
    int t = n - 1;
    int k, l, v;
    for (int index = 1; index <= t; index++)
    {
        pathnode[index] = false;
    }
    pathnode[s] = true;
    int u = s;
    for (int j = 1; j < n ; j++)
    {
        k = rand() % (n - j);

        l = 0;
        for (v = 0; v < n; v++)
        {
            if (pathnode[v])
                continue;
            if (l == k)
                break;
            l++;
        }
        matrix[u][v] = 1;
        pathnode[v] = true;
        if (v == t)
            break;
        u = v;
    }

}

void MainWindow::cycles(std::vector<bool> cyclenode, int n, std::vector<std::vector<int>>& matrix)
{
    srand(time(NULL));
    int s = 0, t = n - 1;
    cyclenode.resize(n);
    for (int index = 0; index < n; ++index)
        cyclenode[index] = 0;

    int u0 = rand() % t;

    cyclenode[s] = 1;
    int u = u0;
    int l;
    for (int index = 0; index < n - 1; ++index)
    {
        int k = rand() % (n - index - 1);
        l = 0;
        int v = 0;
        for (v = 0; v < n; ++v)
        {
            if (cyclenode[v])
                continue;
            if (l == k)
                break;
            l++;
        }
        if (u == v)
            index--;
        else
        {
            matrix[u][v] = 1;
            cyclenode[v] = 1;
        }
        if (v == u0)
            break;
        u = v;
    }
}
void Sageata(QPainter& painter, QPoint start, QPoint end) {

  painter.setRenderHint(QPainter::Antialiasing, true);

  qreal arrowSize = 20;
  painter.setPen(QColor(0, 0, 255, 127));
  painter.setBrush(QColor(0, 0, 255, 127));

  QLineF line(end, start);

  double angle = std::atan2(-line.dy(), line.dx());
  QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
  QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);

  QPolygonF arrowHead;
  arrowHead.clear();
  arrowHead << line.p1() << arrowP1 << arrowP2;
  painter.drawLine(line);
  painter.drawPolygon(arrowHead);

}
MainWindow::~MainWindow()
{
    /*QPainter p(this);
    for(int index=0;index<5;index++)
    {
        QRect r;
        p.drawEllipse(r);
        p.drawText(index, QString::number(index));
    }*/
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    int n=10;
    int npaths=0;
    int ncycles=1;
    std::vector<bool> vector;
    std::vector<std::pair<int, int>> adiac;
    std::vector<std::vector<int>> matrix;
    std::vector<Node> noduri;
    std::vector<Arc> arce;

        for (int ind1 = 0; ind1 < n; ind1++)
        {
            std::vector <int> row;
            for (int ind2 = 0; ind2 < n; ind2++)
            {
                row.push_back(0);
            }
            matrix.push_back(row);
        }
        vector.resize(n);
        for (int index = 0; index < npaths; index++)
        {
            paths(vector, n, matrix);
        }
           for (int index = 0; index < ncycles; index++)
           {
               cycles(vector, n, matrix);
           }
  int a=150,b=200;

  QPainter ellipsePainter(this);

      QRect x(a,b,25,25);
      for(int index=0;index<n;index++)
        {
         if(index>0 && index%2==0)
         {

             a+=75;
             b-=50;
              QRect y(a,b,25,25);
              QPoint point(a,b);
              Node nod(point);
              noduri.push_back(nod);
             /* QPoint point(a,b);
              g.AddNod(point);*/
             ellipsePainter.setPen(QPen(Qt::black));
             ellipsePainter.drawEllipse(y);
              ellipsePainter.setBrush(Qt::magenta);
             ellipsePainter.drawText(y,Qt::AlignCenter,QString::number(index));
         }
         if(index>0 && index%2==1)
         {
             a+=50;
             b+=100;
              QRect z(a,b,25,25);
              QPoint point(a,b);
              Node nod(point);
              noduri.push_back(nod);
              /*QPoint point(a,b);
              g.AddNod(point);*/
              ellipsePainter.setBrush(Qt::magenta);
         ellipsePainter.setPen(QPen(Qt::black));
         ellipsePainter.drawEllipse(z);
         ellipsePainter.drawText(z,Qt::AlignCenter,QString::number(index));}


         if(index==0)
         {
             ellipsePainter.setBrush(Qt::magenta);
             ellipsePainter.setPen(QPen(Qt::black));
             ellipsePainter.drawEllipse(x);
             ellipsePainter.drawText(x,Qt::AlignCenter,QString::number(index));
             QPoint point(a,b);
             Node nod(point);
             noduri.push_back(nod);
             /*QPoint point(a,b);
             g.AddNod(point);*/
         }
         }

   QFile file("D:/AG/tema2/adiacenta.txt");
         if(file.open(QIODevice::WriteOnly | QIODevice::Text))
         {
             QTextStream gr(&file);
             gr << n;
                 gr << '\n';
                 for (int ind1 = 0; ind1 < n; ind1++)
                 {
                     for (int ind2 = 0; ind2 < n; ind2++)
                     {
                         if (matrix[ind1][ind2] == 1)
                         {
                             Arc arc(noduri[ind1],noduri[ind2]);
                                arce.push_back(arc);
                             gr << ind1 << " " << ind2;
                             gr << '\n';
                         }

                     }
                 }
             /*std::vector<Arc> gf;
             gf=g.GetArce();
             for(auto index:gf)
                stream<<index.getFirstPoint().getNumber()<<" "<<index.getSecondPoint().getNumber()<<"\n";*/
             file.close();
         }
         QPainter p(this);
                for(auto& ind: arce)
                {
                    int x1 = ind.getFirstPoint().getPoint().x()+10;
                    int x2 = ind.getFirstPoint().getPoint().y()+10;
                    int y1 = ind.getSecondPoint().getPoint().x();
                    int y2 = ind.getSecondPoint().getPoint().y();
                    QPoint x(x1, x2);
                    QPoint y(y1, y2);
                   Sageata(p,x,y);
                }


}
