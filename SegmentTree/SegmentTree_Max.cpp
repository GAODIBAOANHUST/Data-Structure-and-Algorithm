//利用线段树求区间最值

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

class SegmentTree{
public:
    SegmentTree(int n):MAXN(n){
        Max.resize(MAXN<<2);
        lazy.resize(MAXN<<2);
    }

    void pushup(int rt){
        Max[rt]=max(Max[rt<<1],Max[rt<<1|1]);
    }

    void pushdown(int rt){
        if(lazy[rt]){
            lazy[rt<<1]=max(lazy[rt],lazy[rt<<1]);
            lazy[rt<<1|1]=max(lazy[rt],lazy[rt<<1|1]);
            Max[rt<<1]=max(Max[rt<<1],lazy[rt<<1]);
            Max[rt<<1|1]=max(Max[rt<<1|1],lazy[rt<<1|1]);
            lazy[rt]=0;
        }
    }

    void update(int L,int R,int val,int l,int r,int rt){
        if(L<=l&&R>=r){
            //懒住了
            Max[rt]=max(Max[rt],val);
            lazy[rt]=max(lazy[rt],val);
            return;
        }
        //没懒住,下放任务
        pushdown(rt);
        int mid=l+(r-l>>1);
        if(mid>=L){
            //左子树有任务
            update(L,R,val,l,mid,rt<<1);
        }
        if(mid<R){
            //右子树有任务
            update(L,R,val,mid+1,r,rt<<1|1);
        }
        //更新自己
        pushup(rt);
    }

    int query(int L,int R,int l,int r,int rt){
        if(L<=l&&R>=r){
            return Max[rt];
        }
        //懒不住,下放任务
        pushdown(rt);
        int mid=l+(r-l>>1);
        int res=0;
        if(mid>=L){
            res=max(res,query(L,R,l,mid,rt<<1));
        }
        if(mid<R){
            res=max(res,query(L,R,mid+1,r,rt<<1|1));
        }
        return res;
    }

private:
    int MAXN;
    vector<int> Max;
    vector<int> lazy;
};

//leetcode 699 掉落的方块
class Solution699 {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions){
        set<int> st;
        //找出边界
        for(const vector<int>& p:positions){
            st.insert(p[0]);
            st.insert(p[0]+p[1]-1);
        }
        //离散化,对应坐标
        unordered_map<int,int> indexes;
        int rank=0;
        for(int i:st){
            indexes[i]=rank++;
        }
        SegmentTree Tree(indexes.size());
        vector<int> res;
        int temp=0;
        for(int i=0;i<positions.size();++i){
            int left=positions[i][0];
            int right=positions[i][0]+positions[i][1]-1;
            int left_index=indexes[left];
            int right_index=indexes[right];
            int curr=Tree.query(left_index,right_index,0,indexes.size()-1,1);
            temp=max(temp,curr+positions[i][1]);
            res.push_back(temp);
            Tree.update(left_index,right_index,curr+positions[i][1],0,indexes.size()-1,1);
        }
        return res;
    }
};

//leetcode 218 天际线问题
class Solution218 {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        set<int> st;
        //去重并排序
        for(const vector<int>& b:buildings){
            st.insert(b[0]);
            st.insert(b[1]-1);
            st.insert(b[1]);
        }
        //离散化,对应坐标
        unordered_map<int,int> indexes,rindexes;
        int rank=0;
        for(int i:st){
            indexes[i]=rank;
            rindexes[rank]=i;
            rank++;
        }
        SegmentTree Tree(indexes.size());
        for(const vector<int>& b:buildings){
            Tree.update(indexes[b[0]],indexes[b[1]-1],b[2],0,indexes.size()-1,1);
        }
        int last=0;
        vector<vector<int>> res;
        for(int i=0;i<indexes.size();++i){
            int curr=Tree.query(i,i,0,indexes.size()-1,1);
            if(curr!=last){
                res.push_back({rindexes[i],curr});
                last=curr;
            }
        }
        return res;
    }
};

int main(){
    vector<vector<int>> buildings{{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    vector<vector<int>> res=Solution218().getSkyline(buildings);
    system("pause");
    return 0;
}