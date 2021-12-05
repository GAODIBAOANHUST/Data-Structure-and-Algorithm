//��С�������㷨,����̰�ĵ�˼��
//��ͼ�����б߷ŵ��б�֮��,�����߰���Ȩֵ��С��С��������
//��ÿ���߻�����ÿ�ζ���Ҫ�ж�ͼ���Ƿ���ڻ�,���û���γɻ�,�ñ߾Ϳ��Գ�Ϊ��С��������һ����
//ʹ�����ȶ���+���鼯��ʵ�֣�ÿ�δ����ȶ�����ȡ��һ�����ò��鼯�ж��Ƿ�ɻ�

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

class UF{
public:
    UF(int n):n(n),rank(n,1),parent(n){
        iota(parent.begin(),parent.end(),0);
    }

    void Union(int x,int y){
        int rootX=find(x),rootY=find(y);
        if(rootX==rootY){
            return;
        }
        //С���ӵ�����������ƽ��
        if(rank[rootX]<rank[rootY]){
            parent[rootX]=rootY;
            rank[rootY]+=rank[rootX];
        }else{
            parent[rootY]=rootX;
            rank[rootX]+=rank[rootY];
        }
    }

    bool isConnected(int x,int y){
        return find(x)==find(y);
    }

private:
    int n;
    vector<int> parent;
    vector<int> rank;

    int find(int x){
        // while(x!=parent[x]){
        //     parent[x]=parent[parent[x]];
        //     x=parent[x];
        // }
        // return x;
        return x==parent[x]?x:parent[x]=find(parent[x]);
    }
};

struct Result{
    vector<vector<int>> res;
    int cost;
    Result(vector<vector<int>>& edges,int cost):res(edges),cost(cost) {}
};

class Solution{
public:
    //Ĭ�����ⶥ�������ͨ��ĳ��·�����������ڵ�
    //��������㣬������ʹ�ò��鼯�ж��Ƿ��Ѿ���ͨ
    //�ܹ���n������,graph[i][0],graph[i][1]��ʾÿ���ߵ���������,graph[i][2]��ʾÿ���ߵ�Ȩֵ��С
    Result Kruskal(vector<vector<int>>& graph,int n){
        //��ÿ���߰���Ȩֵ��С����
        auto comp=[&](const vector<int>& a,const vector<int>& b){
            return a[2]>b[2];
        };
        priority_queue<vector<int>,vector<vector<int>>,decltype(comp)> pq(comp);
        //��ͼ�б����
        for(const vector<int>& edge:graph){
            pq.push(edge);
        }
        //�ܹ�ʹ��n-1��������
        //�洢ÿ���ߵĽ��
        vector<vector<int>> res;
        UF uf(n);
        //�����Ҫn-1����
        while(res.size()<n-1){
            //!!!��������������,���ȶ��ж���ɾ��֮���仯
            auto edge=pq.top();
            pq.pop();
            int point1=edge[0],point2=edge[1];
            if(uf.isConnected(point1,point2)){
                continue;
            }
            uf.Union(point1,point2);
            res.push_back(edge);
        }
        int cost=0;
        for(const vector<int>& edges:res){
            cost+=edges[2];
        }
        return Result(res,cost);
    }
};

int main(){
    vector<vector<int>> graph{{0,1,10},{0,5,11},{1,2,18},{1,6,16},{1,8,12},{2,3,22},{2,8,8},{3,4,20},{3,6,24},{3,7,16},{3,8,21},{4,5,26},{4,7,7},{5,6,17},{6,7,19}};
    Result Res=Solution().Kruskal(graph,9);
    cout<<"�ܻ���:"<<Res.cost<<endl;
    cout<<"ÿһ����-------------------------------------"<<endl;
    for(const vector<int>& edge:Res.res){
        cout<<edge[0]<<"<-->"<<edge[1]<<" Ȩֵ:"<<edge[2]<<endl;
    }
    system("pause");
    return 0;
}