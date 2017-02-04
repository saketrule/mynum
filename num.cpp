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
    string str;
    num(string str){
        auto ll = getll(str,0,NULL);
        head = ll.first;
        tail = ll.second;
        this->str = str;
    }
    num(digit* beg, digit* fin){
        this-> head = beg;
        this-> tail = fin;
    }
    void printnum();
    pair<digit*,digit*> getll(string str,int beg,digit* prev);
    digit* getdigit(int val,digit* prev,digit* next);
    void adddigit(int val);
    void multiply(int mul);
    void multiply(num* b);
    void add(num* b);
    num operator+(num& b){
        num ans("0");
        ans.add(this);
        ans.add(&b);
        return ans;
    }
    num operator*(int& b){
        this->multiply(b);
    }
};
void num::add(num* b){
    digit *aptr = this->tail;
    digit* bptr = b->tail;
    int carry=0,temp=0;
    for(;bptr!=NULL or carry;aptr = aptr->prev){
        temp=carry + ((aptr==NULL)?0:aptr->val) + ((bptr==NULL)?0:bptr->val);
        if(aptr==NULL)
            aptr = this->head = this->head->prev = getdigit(temp%10,NULL,this->head);
        else
            aptr->val = temp%10;
        carry = temp/10;
        if(bptr!=NULL)
            bptr=bptr->prev;
    }
}
void num::multiply(int mul){
    int carry=0,temp=0;
    for(digit* ptr = this->tail;ptr!=NULL or carry;ptr = ptr->prev){
        if(ptr==NULL)
            this->head = ptr = getdigit(0,NULL,this->head);
        temp = ptr->val * mul + carry;
        ptr->val = temp%10;
        carry = temp/10;
    }
}

void num::add(num* a){
    struct digit *c;
    struct digit *n1=this->tail,*n2=a->tail;
    int d=0;
    while(true)
    {
        n1->val=n1->val + n2->val+d;
        d=n1->val /10;
        n1->val=n1->val %10;
        if(n2->prev==NULL)
        break;
        else if(n1->prev==NULL)
        {
            n1->prev=new(struct digit);
            c=n1;
            n1=n1->prev;
            n1->next=c;
            n2=n2->prev;
            continue;
        }
        n1=n1->prev;
        n2=n2->prev;
    }
    if(d!=0)
    {
        if(n1->prev==NULL)
        {
            n1->prev=new(struct digit);
            c=n1;
            n1=n1->prev;
            n1->next=c;
            n1->val=d;
        }
        else
        {
            n1=n1->prev;
            n1->val=n1->val + 10*d;
        }
    }
    while(n1->prev!=NULL)
        n1=n1->prev;
    this->head=n1;
}
void num::sub(num* a){
    struct digit *n1=this->tail,*n2=a->tail;
    int d=0;
    while(true)
    {
        n1->val=n1->val - n2->val+d;
        if((n1->val)<0)
        {
            d=-1;
            n1->val = (n1->val)+10;
        }
        else
            d=0;
        if(n2->prev==NULL)
            break;
        n2=n2->prev;
        n1=n1->prev;
    }
    while(n1->next!=NULL)
    {
        if(n1->val!=0)
        {
            break;
        }
        else
        {
            n1->next->prev=NULL;
            n1=n1->next;
        }
    }
    this->head=n1;
}

void sub(digit* n1,digit* n2){
    int d=0;
    while(true)
    {
        n1->val=n1->val - n2->val+d;
        if((n1->val)<0)
        {
            d=-1;
            n1->val = (n1->val)+10;
        }
        else
            d=0;
        if(n2->prev==NULL)
            break;
        n2=n2->prev;
        n1=n1->prev;
    }
    while(n1->next!=NULL)
    {
        if(n1->val!=0)
        {
            break;
        }
        else
        {
            n1->next->prev=NULL;
            n1=n1->next;
        }
    }
}

int cmp(struct digit *t1,struct digit *t2){
    int c=0;
    while(true)
    {
        if(t1->val > t2->val)
            c=1;
        if(t1->val < t2->val)
            c=2;
        if((t1->prev==NULL)&&(t2->prev==NULL))
        {
            return c;
        }
        if((t1->prev==NULL))
        {
            return 2;
        }
        if((t2->prev==NULL))
        {
            return 1;
        }
    }
}

num num::divide(num* a){
    struct digit *n1,*n2,*qh,*qt;//n1 will be divided by n2 and q will have quotient
    int c,t=0;
    qh=new(struct digit);
    qt=qh;
    n1=this->head;
    n2=a->tail;
    //n1=head and n2=tail
    while(n1!=NULL)
    {
        c=cmp(n1,n2);
        if(c==1||c==0)
        {
            sub(n1,n2);
            qt->val++;
            t=1;
        }
        else
        {
            if(n1->next==NULL)
                 break;
            n1=n1->next;
            if(t==1){
                qt->next=new(struct digit);
                qt->next->prev=qt;
                qt=qt->next;
            }
        }
    }
    num ans = new num(qh,qt);
    return ans;
    //qt will have tail of quotient
    //qh will have head of quotient
    //and the remainder will be in this;
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
    num var("20"),var2("440");
    num var3 = var+var2;
    var3.multiply(2);
    var3.printnum();
    cout<<endl;
    //var.multiply(12);
}
