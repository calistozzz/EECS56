/*
@Author: Zitong Zhang
@Date: Nov. 8 2020
@Homework: EECS560 lab10



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
        std::ifstream fin;
        std::vector<std::string> data;
        fin.open(filename); // open file
        if (!fin.is_open()) // fail to open
        {
            std::cout << "Can't open the test instance file!\n";
            return;
        }
        else
        {
            std::string line;
            while (std::getline(fin, line))
            {
                parseInstance(line, data);
            }
            for (int i = 0; i < data.size(); i = i + 2)
            {
                if (edge.size() <= stoi(data[i]))
                {
                    // cout<<"right now size is"<<edge.size()<<endl;
                    edge.resize(stoi(data[i])+1, vector<int>(0));
                    // cout<<"now size is "<<edge.size()<<endl;
                }
                // edge[stoi(data[i])].push_back(stoi(data[i + 1]));
                edge[stoi(data[i])].push_back(stoi(data[i + 1]));
            }
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

    void print()
    {
        for (int i = 0; i < edge.size(); i++)
        {
            
            if (!edge[i].empty())
            {
                cout << i << ": ";
                for (int j = 0; j < edge[i].size(); j++)
                {
                    if(j== edge[i].size()-1)
                    {
                        cout << edge[i][j];
                    }
                    else
                    {
                        cout << edge[i][j] << " ";
                    }
                }
               
            }
            else
            {
                cout<<i<<":";
            }
            cout<<"\n";
        }
    }
    void BFS( int source )
    {
        vector<int> queue;
        vector<bool> visited(edge.size()); 
        queue.push_back(source);
        visited[source]= 1;
       BFS_help(queue, visited);

    }

    void BFS_help(vector<int> m_queue, vector<bool> m_visited)
    {
        int count = m_queue.size();
        for(int i=0; i<m_queue.size();i++)
        {
            for(int j=0; j <edge[m_queue[i]].size();j++)
            {
                if(m_visited[edge[m_queue[i]][j]] ==false)
                {
                    m_visited[edge[m_queue[i]][j]]=1;
                    m_queue.push_back(edge[m_queue[i]][j]);
                }
            }
        }
        while (count !=0)
        {
            cout<<m_queue[0]<<endl;
            m_queue.erase(m_queue.begin());
            count--;
        }
        if(!m_queue.empty())
            BFS_help(m_queue, m_visited);

    }
    
    void DFS( int source ) 
    {
        vector<int> stack;
        vector<bool> visited(edge.size()); 
        stack.push_back(source);
        visited[source]= 1;
       DFS_help(stack, visited);

       for(int i=0;i<stack.size();i++)
       {
           cout<<stack[i]<<endl;
       }
    }
    void DFS_help(vector<int>& m_stack , vector<bool>& m_visited)
    {
        int count = m_stack.back();
        for(int i=0; i<edge[count].size();i++)
        {
           if(m_visited[edge[count][i]] ==false)
           {
               m_stack.push_back(edge[count][i]);
               m_visited[edge[count][i]] =true;
               DFS_help(m_stack, m_visited);
           }
        }
    }

private:
    vector<vector<int>> edge;
   
};
