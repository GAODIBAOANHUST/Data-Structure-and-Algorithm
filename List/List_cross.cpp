#include <iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x):val(x),next(nullptr) {}
};

//给定两个单链表的头结点head1和head2,这两个链表可能相交也可能不相交。实现一个函数,如果两个链表相交则返回相交的第一个节点,如果不想交则返回null
ListNode* check_cross_noloop(ListNode* head1,ListNode* head2){
    if(head1==nullptr||head2==nullptr){
        return nullptr;
    }
    ListNode* temp1=head1;
    ListNode* temp2=head2;
    while(temp1!=temp2){
        temp1=temp1?temp1->next:head2;
        temp2=temp2?temp2->next:head1;
    }
    return temp1;
}

//上述情况是链表无环的情况,可是如果链表有环呢?
//如果一个链表有环而另一个链表无环,那么他们是不可能相交的
//step1:如何判断一个链表是否有环?如果有则返回第一个进入环的节点,没有则返回nullptr
ListNode* getLoopNode(ListNode* head){
    if(!head||!head->next){
        return nullptr;
    }
    //快慢指针,如果有环的话快慢指针一定会相遇
    ListNode* slow=head->next;
    ListNode* fast=head->next->next;
    while(slow!=fast&&fast&&fast->next){
        slow=slow->next;
        fast=fast->next->next;
    }
    if(slow==fast){
        //有环
        fast=head;
        while(slow!=fast){
            slow=slow->next;
            fast=fast->next;
        }
        return slow;
    }
    return nullptr;
}

//如果是两个链表都有环的情况,通过上述方法求得了两个有环链表的入口点
ListNode* check_cross_loop(ListNode* head1,ListNode* head2){
    ListNode* loop1=getLoopNode(head1);
    ListNode* loop2=getLoopNode(head2);
    //两个环形链表入口处是否相同?
    if(loop1==loop2){
        ListNode* temp1=head1;
        ListNode* temp2=head2;
        while(temp1!=temp2){
            temp1=temp1!=loop1?temp1->next:head2;
            temp2=temp2!=loop2?temp2->next:head1;
        }
        return temp1;
    }else{
        //从loop1出发,再回到loop1之前查看是否经过了loop2
        ListNode* temp1=loop1->next;
        while(temp1!=loop1){
            if(temp1==loop2){
                return temp1;
            }
            temp1=temp1->next;
        }
    }
    return nullptr;
}

//讨论上述情况之后,总的方法
ListNode* getIntersectNode(ListNode* head1,ListNode*head2){
    ListNode* loop1=getLoopNode(head1);
    ListNode* loop2=getLoopNode(head2);
    if(loop1==nullptr&&loop2==nullptr){
        return check_cross_noloop(head1,head2);
    }else if(loop1&&loop2){
        return check_cross_loop(head1,head2);
    }
    return nullptr;
}

int main(){
    system("pause");
    return 0;
}