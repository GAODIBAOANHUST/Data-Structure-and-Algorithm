//tarjinǿ��ͨ�����㷨
//��ͨ:����ͼ��,�������i�ɵ��������j
//ǿ��ͨ:����ͼ��,�������i�ɵ��������j
//����ͨ:������ͼ��������ͼ,......ͬ��

//����DFS�����ķ�ʽ
//1. �ȷ��ʵ�ǰ�ڵ�,�ٵݹ����ڽڵ�
//2. �ȵݹ����ڽڵ�,�ٷ��ʵ�ǰ�ڵ�
//tarjin�㷨ʹ�õı�����ʽ��DFS2
//����һ���ڵ�x,��������(i,j),����i��ʾ��DFS��x�㱻���ʵ�ʱ���,j��ʾxͨ������߿ɻ��ݵ��������ʱ���

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

using namespace std;

class Solution1{
private:
    vector<vector<int>> res;
    vector<bool> visited;

    //ʱ���
    int curr_time;
    //��¼ÿһ�β���ǿ��ͨ������ʱ��ĳ���ڵ��Ƿ���ջ��
    unordered_set<int> instack;
    stack<int> S;
    vector<int> times;
    vector<int> origin_times;

    void DFS(const vector<vector<int>>& edges,const vector<vector<int>>& next_points,int index){
        visited[index]=true;
        S.push(index);
        instack.insert(index);
        //��¼���ʵ���ʱ��
        origin_times[index]=times[index]=curr_time++;
        //�����ӽڵ�
        for(int next_pnt:next_points[index]){
            if(!visited[next_pnt]){
                DFS(edges,next_points,next_pnt);
                times[index]=min(times[index],times[next_pnt]);
            }else if(instack.find(next_pnt)!=instack.end()){
                //�Ѿ���������δ��ջ
                times[index]=min(times[index],times[next_pnt]);
            }
        }
        //����ǿ��ͨ����
        if(origin_times[index]==times[index]){
            int Size=res.size();
            res.push_back(vector<int>());
            while(S.top()!=index){
                res[Size].push_back(S.top());
                instack.erase(S.top());
                S.pop();
            }
            res[Size].push_back(S.top());
            instack.erase(S.top());
            S.pop();
        }
    }

public:
    //����vectorÿһ��edge��ʾ��edge[0]->edge[1],�ܹ���n������
    vector<vector<int>> targin(vector<vector<int>>& edges,int n){
        vector<vector<int>> next_points(n,vector<int>());
        visited.resize(n);
        origin_times.resize(n);
        times.resize(n);
        curr_time=0;
        for(auto& edge:edges){
            next_points[edge[0]].push_back(edge[1]);
        }
        //���ܳ���ĳ���������ಿ��δ���ӵ����
        for(int i=0;i<n;++i){
            if(!visited[i]){
                DFS(edges,next_points,i);
            }
        }
        return res;
    }
};


//tarjin����㷨��������
//���:������ͨͼ��,ĳ������ӵ�ı�ȥ����ͼ������ͨ
//��:������ͨͼ��,ĳ����ȥ����ͼ������ͨ 
//���һ�����Ǹ��,���������������֮һ
//case1:x��root�ڵ�&&x���ӽڵ�&&time[x���ӽڵ�]>=original_time[x]
//case2:xΪroot�ڵ�&&x�д��ڵ���2���ӽڵ�
//x->y����:time[y]>original_time[x]

//���ؽ�������ݽṹ
struct PointAndEdge{
    vector<int> points;
    vector<pair<int,int>> edges;
};

class Solution2{
private:
    vector<int> origin_times,times;
    int time;
    //��Ҫ��¼ÿһ���ڵ�ĸ��׽ڵ�,����ʼ��Ϊ-1��ʾһ��ʼ��û�и��ڵ�,DFSʱ���и���,�Ӷ��ж�root�ڵ�
    vector<int> parent;
    //���ܳ����ظ���������,��¼ĳ�����ǲ��Ǹ��
    unordered_set<int> tarjinpnts;
    //�洢���
    vector<pair<int,int>> res_edges;

    void DFS(const vector<vector<int>>& edges,int curr,const int n){
        //��������ǰ�ڵ�,����ʱ��
        origin_times[curr]=times[curr]=time++;
        //��¼�ӽڵ������
        int child=0;
        //�����������ڵĽڵ�
        for(int next_pnt=0;next_pnt<n;++next_pnt){
            if(edges[curr][next_pnt]){
                //��ʱnext_pnt������curr���ӽڵ�,����Ҳ�п���֮ǰ�ͷ��ʹ�
                if(origin_times[next_pnt]==0){
                    child++;
                    parent[next_pnt]=curr;
                    DFS(edges,next_pnt,n);
                    //�ж�curr�ǲ��Ǹ��,����case
                    if(parent[curr]==-1&&child>=2){
                        tarjinpnts.insert(curr);
                    }
                    if(parent[curr]!=-1&&times[next_pnt]>origin_times[curr]){
                        tarjinpnts.insert(curr);
                    }
                    //�ж�curr->next_pnt�������ǲ�����
                    if(times[next_pnt]>origin_times[curr]){
                        res_edges.emplace_back(curr,next_pnt);
                    }
                    //!!!����ͼ�϶����Ի���,��Ҫ����times[curr]
                    times[curr]=min(times[curr],times[next_pnt]);
                }else if(next_pnt!=parent[curr]){
                    //��Ȼ�Ѿ����ʹ�next_pnt,����next_pnt����curr�ĸ��ڵ�,��curr�����Ƚڵ�
                    //����times
                    times[curr]=min(times[curr],times[next_pnt]);
                }
            }
        }
    }

public:
    //�ܹ�n���ڵ�,�ڵ���Ϊ0-n
    //�����edgesΪ�ڽӾ�����ʽ
    PointAndEdge findtargin(vector<vector<int>>& edges,int n){
        origin_times.resize(n,0);
        times.resize(n,0);
        time=1;
        parent.resize(n,-1);
        //��ʵ������˵ͼ����ͨ��,ֻ��Ҫ������һ���ڵ�Ϳ���
        for(int i=0;i<n;++i){
            if(!origin_times[i]){
                DFS(edges,i,n);
            }
        }
        vector<int> res_points(tarjinpnts.begin(),tarjinpnts.end());
        return PointAndEdge{res_points,res_edges};
    }
};

//Solution1����
// int main(){
//     vector<vector<int>> edges{{0,1},{1,2},{2,3},{2,4},{3,4},{3,1},{0,5},{5,6},{6,0}};
//     vector<vector<int>> res=Solution1().targin(edges,7);
//     for(auto& v:res){
//         cout<<"{"<<" ";
//         for(int x:v){
//             cout<<x<<" ";
//         }
//         cout<<"}\n";
//     }
//     system("pause");
//     return 0;
// }

//Solution2����
int main(){
    vector<vector<int>> edges{{0,1,1,0,0,0,0,0},
                                {1,0,1,1,0,0,0,0},
                                {1,1,0,1,0,0,0,0},
                                {0,1,1,0,1,0,0,0},
                                {0,0,0,1,0,0,1,1},
                                {0,0,0,0,0,0,0,1},
                                {0,0,0,0,1,0,0,0},
                                {0,0,0,0,1,1,0,0}};
    PointAndEdge res=Solution2().findtargin(edges,8);
    //������
    cout<<"�������:"<<endl;
    for(int i:res.points){
        cout<<i<<",";
    }
    cout<<endl;
    cout<<"������:"<<endl;
    for(auto& p:res.edges){
        cout<<p.first<<"--"<<p.second<<endl;
    }
    system("pause");
    return 0;
}