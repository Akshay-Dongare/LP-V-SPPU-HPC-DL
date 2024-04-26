#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>
using namespace std;

struct Graph{
    int V;
    vector<vector<int>> adj;
    
    Graph(int V){
        this->V=V;
        adj.resize(V);
    }
    
    void add_edges(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void BFS(int start){
        vector<bool> visited(V,false);
        queue<int> q;
        visited[start]=true;
        q.push(start);
        
        while(!q.empty()){
            int u=q.front();
            q.pop();
            cout<<u<<" ";
            
            #pragma omp parallel for
            for(int i=0;i<adj[u].size();i++){
                int v=adj[u][i];
                if(!visited[v]){
                    #pragma omp critical
                    visited[v]=true;
                    q.push(v);
                }
            }
        }
        
        
    }
    
    void DFS(int start){
        vector<bool> visited(V,false);
        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                DFSUtil(start,visited);
            }
        }
    }
    
    
    void DFSUtil(int u , vector<bool>& visited ){
       visited[u]=true;                                     //visited[u]=true and cout
       cout<<u<<" ";
       
       #pragma omp parallel for
        {
            for(int i=0;i<adj[u].size();i++){
                int v=adj[u][i];
                if(!visited[v]){
                    DFSUtil(v,visited);
                }
            }
        }
        
        cout<<endl;
    }
};

int main(){
    int V;
    cout<<"Enter vertices=";
    cin>>V;
    
    Graph g(V);
    
    int edgecount;
    cout<<"Enter no of edges= ";
    cin>>edgecount;
    
    cout<<"ENter edged= ";
    for(int i=0;i<edgecount;i++){
        int u,v;
        cin>>u>>v;
        g.add_edges(u,v);
    }
    
    cout<<"BFS= ";
    g.BFS(0);
    
    cout<<"DFS= ";
    g.DFS(0);
}