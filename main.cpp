#include <iostream>
#include <vector>
#include <algorithm>

const std::vector<std::vector<int>> matrix{{
                                                   { 1 , 8 , 7 , 19, 3 , 7 , 5 , 11, 5 , 4 },
                                                   { 1 , 3 , 2 , 1 , 13, 6 , 25, 8 , 9 , 15},
                                                   { 1 , 1 , 1 , 4 , 6 , 3 , 17, 6 , 10, 13},
                                                   { 13, 4 , 1 , 1 , 9 , 7 , 12, 11, 5 , 15},
                                                   { 17, 12, 8 , 1 , 3 , 1 , 1 , 1 , 10, 4 },
                                                   { 7 , 4 , 19, 1 , 11, 1 , 6 , 1 , 2 , 7 },
                                                   { 9 , 10, 12, 1 , 1 , 1 , 13, 1 , 17, 5 },
                                                   { 3 , 5 , 9 , 14, 10, 18, 5 , 1 , 3 , 10},
                                                   { 14, 2 , 15, 8 , 19, 17, 4 , 1 , 5 , 4 },
                                                   { 13, 8 , 6 , 3 , 3 , 7 , 5 , 1 , 1 , 1 }
                                            }};

struct node{
    int key;
    int i;
    int j;
    bool visited;
    int mass;
};


std::vector<std::vector<node>> InitGraph(std::vector<std::vector<int>> m){
    std::vector<std::vector<node>> Graph;
    auto N = m.size();
    for(auto i=0;i<N;i++){
        Graph.emplace_back(std::vector<node>{m[i].size()});
        for(auto j=0;j<m[i].size();j++){
            Graph[i][j] =node{m[i][j], i, j, false, 100000};
        }
    }
    Graph[0][0].mass = matrix[0][0];
    return Graph;
}

std::vector<node> FindSortedNeighbours(std::vector<std::vector<node>>& G, node& g, int m, int n){
    std::vector<node> val;
    auto i = g.i;
    auto j = g.j;
    //std::cout<<i<<j<<" ";
    if(i+1<m){if(!G[i+1][j].visited){val.emplace_back(G[i+1][j]);}}
    if(i-1>=0){if(!G[i-1][j].visited){val.emplace_back(G[i-1][j]);}}
    if(j+1<n){if(!G[i][j+1].visited){val.emplace_back(G[i][j+1]);}}
    if(j-1>=0){if(!G[i][j-1].visited){val.emplace_back(G[i][j-1]);}}
    struct {
        bool operator()(node a, node b) const { return a.key < b.key; }
    } customLessKey;
    std::sort(val.begin(), val.end(), customLessKey);
    return val;
}

std::vector<node> CreateSortedLine(std::vector<std::vector<node>>& G, node& g, int m){
    std::vector<node> val;
    auto i = g.i;
    auto j = g.j;
    while(i < m && j >= 0){
        val.emplace_back(G[i][j]);
        ++i, --j;
    }
    //std::cout<<std::endl;
    struct {
        bool operator()(node a, node b) const { return a.mass < b.mass; }
    } customLessMass;
    std::sort(val.begin(), val.end(), customLessMass);
    return val;
}

int Deijkstra(std::vector<std::vector<node>>& G){
    auto m = G.size();
    auto n = G[0].size();

    int i=0,j=0;
    while(i!=m && j!=n){
        if(j<n-1){
            auto v = CreateSortedLine(G, G[i][j], m);
            for(auto it:v){
                auto neigbours = FindSortedNeighbours(G, it, m, n);
                for(auto jt:neigbours){
                    if(it.mass+jt.key<jt.mass){G[jt.i][jt.j].mass=it.mass+jt.key;}
                }
                G[it.i][it.j].visited=true;
            }
            j++;
        }
        else{
            auto v = CreateSortedLine(G, G[i][j],m);
            for(auto it:v){
                auto neigbours = FindSortedNeighbours(G, it, m, n);
                for(auto jt:neigbours){
                    if(it.mass+jt.key<jt.mass){G[jt.i][jt.j].mass=it.mass+jt.key;}
                }
                G[it.i][it.j].visited=true;
            }
            i++;
        }
    }
    return 0;
};

int main() {
    auto G = InitGraph(matrix);
    Deijkstra(G);
    for(auto i:G){
        for(auto j:i){
            if(j.mass>9){std::cout<<j.mass<<" ";}
            else{std::cout<<j.mass<<"  ";}
        }
        std::cout<<std::endl;
    }
    
    return 0;
}
