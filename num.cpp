#include<bits/stdc++.h>
using namespace std;
struct digit{
    int val=0;
    digit *prev=NULL,*next=NULL;
};

class num{
public:
    digit *head=NULL;
    digit *tail=NULL;
    num(string str){
        auto ll = getll(str,0,NULL);
        head = ll.first;
        tail = ll.second;
        printnum();
    }
    void printnum();
    pair<digit*,digit*> getll(string str,int beg,digit* prev);
    digit* getdigit(int val,digit* prev,digit* next);
    void adddigit(int val);
    void add(num* a);
    num multiply(num a,num b);
};
num num::multiply(num* a,num* b){

}

void num::add(num* a){
    struct digit *c;
    struct digit *n1=this.tail,*n2=a->tail;
    int d=0;
    while(true)
    {
        n1->val=n1->val + n2->val+d;
        d=n1->val /10;
        n1->val=n1->val %10;
        if(n2->next==NULL)
        break;
        else if(n1->next==NULL)
        {
            n1->next=new(struct digit);
            c=n1;
            n1=n1->next;
            n1->prev=c;
            n1->val=0;
            n2=n2->next;
            continue;
        }
        n1=n1->next;
        n2=n2->next;
        
    }
    n1->val=n1->val + 10*d;
    this.head=n1;
}

void num::printnum(){
    for(digit* ptr = this->head;ptr!=NULL;ptr=ptr->next)
        cout<<ptr->val;
    return;
}
void num::adddigit(int val){
    this->tail->next = getdigit(val,this->tail,NULL);
    tail = tail->next;
}
pair<digit*,digit*> num::getll(string str,int beg,digit* prev){
    if(beg==str.length())   return make_pair((digit*)NULL,(digit*)NULL);
    digit* newdigit = getdigit(str[beg]-'0',prev,NULL);
    auto rest = getll(str,beg+1,newdigit);
    newdigit->next = rest.first;
    return make_pair(newdigit,((beg==str.length()-1)?newdigit:rest.second));
}
digit* num::getdigit(int val,digit* prev,digit* next){
    digit* ans = new digit;
    ans->val = val;
    ans->prev = prev;
    ans->next = next;
    return ans;
}

int main(){
    num("4298520");
}
