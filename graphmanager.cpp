#include "graphmanager.h"
#include <map>
#include <queue>
#include <set>

using namespace std;

GraphManager::GraphManager(){
}

GraphManager::GraphManager(const QString& input){
    CreateGraph(input);
    graphText = input;
}

GraphManager::~GraphManager(){
}

QString GraphManager::Export(){
    return graphText;
}

void GraphManager::CreateGraph(const QString& input){
    QStringList stringList = input.split('\n', QString::SkipEmptyParts);

    //parse input into map
    for (int i = 0; i < stringList.count(); i++){
        QStringList vertexList = stringList.at(i).split(' ', QString::SkipEmptyParts);

        if(vertexList.count() > 0){
            for (int ii = 1; ii < vertexList.count(); ii++){
                graphMap[vertexList.at(0)]
                        .insert(vertexList.at(ii));
                //make map full
                graphMap[vertexList.at(ii)].insert(vertexList.at(0));
            }
        }
        if(vertexList.count() == 1){
            graphMap.insert(make_pair(vertexList.at(0), set<QString>()));
        }
    }
}

map<QString, QString> GraphManager::FindConnectedComponents(){

    //for vertexes that have already been added to components map
    vector<QString> addedVertexes;

    //map<componentName, set<vertexName>>
    map<QString, set<QString>> componentsMap;

    queue<QString> vertexQueue;

    int componentCount = 0;

    //traverse
    for(auto& mapPair : graphMap){
        if(find(addedVertexes.begin(), addedVertexes.end(), mapPair.first)
                == addedVertexes.end()){

            vertexQueue.push(mapPair.first);

            while (!vertexQueue.empty()) {
                QString vertex = vertexQueue.front();
                vertexQueue.pop();

                if(find(addedVertexes.begin(), addedVertexes.end(), vertex)
                        == addedVertexes.end()){
                    addedVertexes.push_back(vertex);

                    componentsMap["comp"+(QString::number(componentCount))]
                            .insert(vertex);

                    //add all adjacent vertexes
                    if(graphMap.find(vertex)!= graphMap.end()){
                        for(auto& mateVertex : graphMap[vertex]){
                            vertexQueue.push(mateVertex);
                        }
                    }
                }
            }
            componentCount++;
        }

    }

    map<QString, QString> components;

    for(auto& component : componentsMap){
        QStringList fileGraph;
        //far all vertexes from one component
        for(auto& componVertex: component.second){
            QStringList fileGraphLine;
            fileGraphLine.append(componVertex);
            //far all adjacent vertexes of curr vertex
            for(auto& adjacentVert : graphMap[componVertex]){
                fileGraphLine.append(adjacentVert);
            }
            fileGraph.append(fileGraphLine.join(' '));
        }
        components[component.first]=fileGraph.join('\n');
    }
    return components;


//    QStringList result;

//    for(auto& component : componentsMap){
//        QString componentStr;
//        componentStr.append(component.first + " ");
//        for(auto& vert : component.second){
//            componentStr.append(vert + " ");
//        }
//        result.append(componentStr);
//    }

//    return result.join("\n");
}

const std::map<QString, std::set<QString>>& GraphManager::GetInnerRepresentation(){
    return graphMap;
}
