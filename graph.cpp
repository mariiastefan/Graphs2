#include "graph.h"
#include <QTextStream>
#include <QFile>


std::vector<Arc> Graph::GetArce()
{
    return arce;
}

std::vector<Node> Graph::GetNoduri()
{
    return noduri;
}


void Graph::AddNod(Node n)
{
    n.setNumber(noduri.size());
    noduri.push_back(n);
}

void Graph::AddArc(Arc n)
{
    for(auto index:arce)
    {
        if(index.getFirstPoint().getNumber()==n.getFirstPoint().getNumber()&&index.getSecondPoint().getNumber()==n.getSecondPoint().getNumber())
        {
            return;
           }
    }
    arce.push_back(n);
}

Node Graph::GetLastNode()
{
    return noduri[noduri.size()-1];
}

int Graph::getNumberofNodes()
{
    return noduri.size();
}
void Graph::GenerareMatriceAdiacenta()
{

}

void Graph::GenerareListaAdiacenta()
{
    listaAdiacenta=GetArce();

}
