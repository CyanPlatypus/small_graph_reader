#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include <QObject>
#include <set>

class GraphManager
{
public:
    GraphManager();
    GraphManager(const QString& input);
    ~GraphManager();

    std::map<QString, QString> FindConnectedComponents();
    QString Export();

private:
    std::map<QString, std::set<QString>> graphMap;
    QString graphText;
    void CreateGraph(const QString& input);
};

#endif // GRAPHMANAGER_H
