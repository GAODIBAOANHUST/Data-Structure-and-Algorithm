//��С�������㷨,����̰�ĵ�˼��
//��Kruskal�㷨��ͬ,���㷨���ڶ��㣬����ѡ������������������б߼��ϵ���Сֵ
//ͼ�з�Ϊ�����ӵĲ��ֺ�δ���ӵĲ���,ѡ�����������ֵ�Ȩֵ��С�ı�
//Prim�㷨���ϸ��������б�
//�б�1:�洢��ѡ�������Ϣ
//�б�2:�洢��ǰʱ����ѡ���㼯�ϵ��ö������СȨֵ�ߵ�Ȩֵ��С,��ʼ״̬��ΪINF 
//�б�3:�洢��Ӧ�б�2ÿһ������,��˵��<�б�3[i],i>ΪMST��һ����,����λ��Ϊ0��ʾ��λ���Ѽ���MST

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

struct Result{
    vector<int> res;
    int cost;
    Result(vector<int>& edges,int cost):res(edges),cost(cost) {}
};

//��ȡһ����ʼ��,������ȡ0Ϊ��ʼ��
//ʱ�临�Ӷ�O(n^2)
class Solution{
public:
    Result Prim(vector<vector<int>>& graph,int n){
        //��Ҫ�����ڽӾ���
        vector<vector<int>> Graph(n+1,vector<int>(n+1,INF));
        for(int i=0;i<=n;++i){
            Graph[i][i]=0;
        }
        for(const vector<int>& g:graph){
            Graph[g[0]][g[1]]=g[2];
            Graph[g[1]][g[0]]=g[2];
        }
        vector<int> visited(n+1);
        vector<int> lowcost(n+1,INF);
        vector<int> MST(n+1,0);
        lowcost[0]=0;
        for(int i=1;i<n;++i){
            int index=-1;
            int dis_temp=INF;
            for(int i=0;i<=n;++i){
                if(!visited[i]&&lowcost[i]<dis_temp){
                    index=i;
                    dis_temp=lowcost[i];
                }
            }
            if(index==-1){
                break;
            }
            visited[index]=true;
            lowcost[index]=0;
            //ÿ����һ������Ҫ����lowcost����
            for(int i=0;i<=n;++i){
                if(!visited[i]&&Graph[index][i]<lowcost[i]){
                    lowcost[i]=Graph[index][i];
                    MST[i]=index;
                }
            }
        }
        int cost=0;
        for(int i=1;i<=n;++i){
            cost+=Graph[MST[i]][i];
        }
        return {MST,cost};
    }
};

int main(){
    vector<vector<int>> graph{{0,1,10},{0,5,11},{1,2,18},{1,6,16},{1,8,12},{2,3,22},{2,8,8},{3,4,20},{3,6,24},{3,7,16},{3,8,21},{4,5,26},{4,7,7},{5,6,17},{6,7,19}};
    Result Res=Solution().Prim(graph,8);
    cout<<"�ܻ���:"<<Res.cost<<endl;
    cout<<"ÿһ����-------------------------------------"<<endl;
    for(int i=1;i<=8;++i){
        cout<<"���:"<<Res.res[i]<<"<-->"<<"�յ�:"<<i<<endl;
    }
    system("pause");
    return 0;
}