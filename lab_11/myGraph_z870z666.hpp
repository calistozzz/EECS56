/*
@Author: Zitong Zhang
@Date: Nov. 14 2020
@Homework: EECS560 lab11



*/

#include <typeinfo>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <exception>
#include <fstream>

using namespace std;
class myGraph
{
public:
    myGraph(char *filename)
    {
        edge.resize(0);
        distance.resize(0);
        std::ifstream fin;
        std::vector<std::string> data;
        fin.open(filename); // open file
        if (!fin.is_open()) // fail to open
        {
            std::cout << "Can't open the test instance file!" << endl;
            return;
        }
        else
        {
            std::string line;
            while (std::getline(fin, line))
            {
                parseInstance(line, data);
            }
            for (int i = 0; i < data.size(); i = i + 3)
            {
                if (distance.size() <= stoi(data[i]) || edge.size() <= stoi(data[i]))
                {
                    //cout<<"right now size is"<<edge.size()<<endl;
                    distance.resize(stoi(data[i]) + 1, vector<int>(0));
                    edge.resize(stoi(data[i]) + 1, vector<int>(0));

                    //cout<<"now size is "<<edge.size()<<endl;
                }
                edge[stoi(data[i])].push_back(stoi(data[i + 1]));
                distance[stoi(data[i])].push_back(stoi(data[i + 2]));
            }
            visited.resize(data.size(), 0);
        }
    }
    void parseInstance(const std::string &line, std::vector<std::string> &res)
    {
        int p = 0, q = 0;
        while (q < line.size())
        {
            if (line[q] == ',')
            {
                res.push_back(line.substr(p, q - p));
                p = q + 1;
            }
            q++;
        }
    }

    ~myGraph()
    {
    }

    void print2()
    {
        for (int i = 0; i < distance.size(); i++)
        {

            if (!distance[i].empty())
            {
                cout << i << ": ";
                for (int j = 0; j < distance[i].size(); j++)
                {
                    if (j == distance[i].size() - 1)
                        cout << distance[i][j];
                    else
                        cout << distance[i][j] << " ";
                }
            }
            else
            {
                cout << i << ":";
            }
            cout << endl;
        }
    }

    void dijkstra(int source)
    {
        du.resize(edge.size());
        visited.resize(edge.size());
        path.resize(edge.size());

        int vertex;
        int shortest;
        int check = 1;
        for (int i = 0; i < edge.size(); i++)
        {
            visited[i] = false;
            du[i] = INT_MAX;
            path[i] = to_string(source) + ' ';
        }
        du[source] = 0;
        visited[source] = true;
        
        for (int i = 0; i < edge[source].size(); i++)
        {
            du[edge[source][i]] = distance[source][i];
        }
        while (check != edge.size())
        {

            vertex = 0;
            shortest = INT_MAX;
            for (int i = 0; i < edge.size(); i++)
            {
                if (!visited[i] && du[i] < shortest)
                {
                    vertex = i;
                    shortest = du[i];
                }
            }
            visited[vertex] = true;
            for (int i = 0; i < edge[vertex].size(); i++)
            {
                if (!visited[edge[vertex][i]])
                {
                    int cost = distance[vertex][i];
                    if (cost + du[vertex] < du[edge[vertex][i]])
                    {
                        du[edge[vertex][i]] = cost + du[vertex];
                        path[edge[vertex][i]] = path[vertex] + to_string(vertex) + " ";
                    }
                }
            }

            check++;
        }
    }

    void printPath(int i)
    {
        if (path[i] == to_string(i) + " ")
            cout << i;
        else
            cout << path[i] << i;
    }
    int computePathCost(int i)
    {
        return du[i];
    }

private:
    vector<vector<int>> edge;
    vector<vector<int>> distance;
    vector<bool> visited;
    vector<int> du;
    vector<string> path;
};
