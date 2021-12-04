// 线段树应用场景:区间和，区间最值，区间乘积(共同点：左右两个区间可以合并)
// 线段树每个节点代表一个区间，叶子节点是单独的点，编号lson=2*fa,rson=2*fa+1,fa=lson/2=rson/2,父亲节点的信息等于左右两个孩子信息的合并
// 建树，以递归的形式，每一次分割成两半，边界是叶子节点(l==r) 
// 线段树可以进行区间更新,例如有一段区间[1,n],每一次要替换区间[x,y]为一个固定值c，也会不停的查询某段区间的和
// 如果使用单点更新，时间复杂度O(nlogn),但是当查询次数过多的时候时间复杂度不满足条件
// 每次更新一个区间，不需要把所有的叶子节点更新，只需要更新到能把这段区间覆盖的节点就可以

//实现某个区间的值全部加val,某个区间的值全部变为val,对某个区间求和
//左神算法
#include <iostream>
#include <vector>

using namespace std;

class SegmentTree{
public:
    SegmentTree(vector<int>& origin):MAXN(origin.size()+1){
        arr.resize(MAXN);
        for(int i=1;i<MAXN;++i){
            arr[i]=origin[i-1];
        }
        sum.resize(MAXN<<2);
        lazy.resize(MAXN<<2);
        change.resize(MAXN<<2);
        update.resize(MAXN<<2);
        build(1,MAXN-1,1);
    }

    void add(int L,int R,int val){
        add(L,R,val,1,MAXN-1,1);
    }

    void Update(int L,int R,int val){
        Update(L,R,val,1,MAXN-1,1);
    }

    long long query(int L,int R){
        return query(L,R,1,MAXN-1,1);
    }

private:
    void pushup(int rt){
        sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    }

    void pushdown(int ln,int rn,int rt){
        if(update[rt]){
            update[rt<<1]=true;
            update[rt<<1|1]=true;
            update[rt]=false;
            lazy[rt<<1]=0;
            lazy[rt<<1|1]=0;
            change[rt<<1]=change[rt];
            change[rt<<1|1]=change[rt];
            sum[rt<<1]=ln*change[rt];
            sum[rt<<1|1]=rn*change[rt];
            change[rt]=0;
        }
        if(lazy[rt]){
            lazy[rt<<1]+=lazy[rt];
            lazy[rt<<1|1]+=lazy[rt];
            sum[rt<<1]+=ln*lazy[rt];
            sum[rt<<1|1]+=rn*lazy[rt];
            lazy[rt]=0;
        }
    }

    void build(int l,int r,int rt){
        if(l==r){
            sum[rt]=arr[l];
            return;
        }
        //下放到左右子节点
        int mid=l+(r-l>>1);
        build(l,mid,rt<<1);
        build(mid+1,r,rt<<1|1);
        //更新自己
        pushup(rt);
    }

    //将区间arr[L...R]的数都增加val
    void add(int L,int R,int val,int l,int r,int rt){
        if(L<=l&&R>=r){
            //该区间懒住了
            sum[rt]+=(r-l+1)*val;
            lazy[rt]+=val;
            return;
        }
        //懒不住下放子任务
        int mid=l+(r-l>>1);
        pushdown(mid-l+1,r-mid,rt);
        if(mid>=L){
            //左子树有任务
            add(L,R,val,l,mid,rt<<1);
        }
        if(mid<R){
            //右子树有任务
            add(L,R,val,mid+1,r,rt<<1|1);
        }
        //更新自己的信息
        pushup(rt);
    }

    //将区间arr[L...R]的数都变成val
    void Update(int L,int R,int val,int l,int r,int rt){
        if(L<=l&&R>=r){
            //该区间懒住了
            sum[rt]=(r-l+1)*val;
            change[rt]=val;
            lazy[rt]=0;
            update[rt]=true;
            return;
        }
        //没懒住,下放子任务
        int mid=l+(r-l>>1);
        pushdown(mid-l+1,r-mid,rt);
        if(L<=mid){
            //左子树有任务
            Update(L,R,val,l,mid,rt<<1);
        }
        if(mid<R){
            //右子树有任务
            Update(L,R,val,mid+1,r,rt<<1|1);
        }
        //更新自己的信息
        pushup(rt);
    }

    //查询区间arr[L...R]的累加和
    long long query(int L,int R,int l,int r,int rt){
        if(L<=l&&R>=r){
            //懒住了
            return sum[rt];
        }
        //懒不住，下放子任务
        int mid=l+(r-l>>1);
        pushdown(mid-l+1,r-mid,rt);
        long long res=0;
        if(L<=mid){
            res+=query(L,R,l,mid,rt<<1);
        }
        if(mid<R){
            res+=query(L,R,mid+1,r,rt<<1|1);
        }
        return res;
    }

    int MAXN;
    vector<int> arr;
    vector<int> sum;
    vector<int> lazy;
    vector<int> change;
    vector<bool> update;
};

//测试
int main(){
    //初始数组
    vector<int> origin{1,5,4,2,3};
    SegmentTree Tree(origin);
    //查询[2...4]的和
    long long sum1=Tree.query(2,4);
    cout<<sum1<<endl;
    //[2...3]区间+2
    Tree.add(2,3,2);
    //查询区间[3...4]的和
    long long sum2=Tree.query(3,4);
    cout<<sum2<<endl;
    //[1...5]区间+1
    Tree.add(1,5,1);
    //查询[1...4]的和
    long long sum3=Tree.query(1,4);
    cout<<sum3<<endl;
    //区间[2...4]都变为5;
    Tree.Update(2,4,5);
    //查询区间[2...5]的和
    long long sum4=Tree.query(2,5);
    cout<<sum4<<endl;
    system("pause");
    return 0;
}