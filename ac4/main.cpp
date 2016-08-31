#include <iostream>                         //客户端
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

using namespace std;
template <class type> class List;
template <class type> istream& operator>>(istream&, List<type>&);

template <class type> class QueueItem{
    friend istream&operator>><type>(istream& , List<type>&);
    friend class List<type>;
    QueueItem(const type &t):item(t),next(0){}
    type item;
    QueueItem* next;
};

template <class type> class List{
public:
    List():front(0),end(0){}
    List(const List &q):front(0),end(0){
        copy_element(q);
    }
    List& operator=(const List &l){
        destory();
        front=end=0;
        copy_element(l);
        return *this;
    }
    ~List(){
        destory();
    }

    type begin(){
        return *front;
    }
    type last(){
        return *end;
    }
    void del(QueueItem<type>*index){
        QueueItem<type>*temp = front;
        while(temp!=index && temp!=0 && temp->next!=index)
            temp=temp->next;
        if(temp!=0)
        {
            if(temp==index)
                front=front->next;
            else
            {
                temp->next=index->next;
            }
            if(index == end)
                end = temp->next;
            delete index;
        }
        else
            throw out_of_range("not such node\n");
    }
    bool empty(){
        return front == 0;
    }
    void insert(QueueItem<type> *index,type val)
    {
        QueueItem<type> *p = new QueueItem<type>(val);
        if(empty()){
            front=p;
        }
        else
        {
            p->next=index->next;;
            index->next=p;
        }
        if(index == end)
        {
            end = p;
        }
    }
    template <typename T> void assign(T a,T b){
        destory();
        copy_elements(a,b);
    }

private:
    friend istream&operator>> <type>(istream& , List<type>&);
    QueueItem<type> *front,*end;
    void destory(){
        while(!empty())
            del(front);
    }
    void copy_element(const List &p){
        for(QueueItem<type> *pt=p.front;pt;pt=pt->next)
        {
            insert(end,pt->item);
        }
    }
    template <typename T> void copy_elements(T a,T b){
        while(a!=b)
        {
            insert(end,*a);
            a++;
        }
    }
};
template <class type> istream& operator>>(istream& is, List<type>& l)
{
    type val;
    is>>val;
    l.insert(l.end,val);
    return is;
}
template <typename T>
class CheckPtr{
    CheckPtr(T pt,T pt1):start(pt),end(pt1),curr(pt){}
    CheckPtr&operator++(){
        if(curr == end)
            throw out_of_range("out of end range\n");
        curr++;
        return *this;
    }
    CheckPtr&operator--(){
        if(curr==start)
            throw out_of_range("out of start range\n");
        curr--;
        return *this;
    }
    CheckPtr operator++(int){
        CheckPtr ret(*this);
        ++*this;
        return ret;
    }
    CheckPtr operator--(int){
        CheckPtr ret(*this);
        --*this;
        return ret;
    }

private:
    T* start;
    T* end;
    T* curr;
};
void bubble_sort(int *p,int size)
{
    int i,j;
    int temp;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size-i-1;j++)
        {
            if(p[j]<p[j+1])
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}
int main(){
    List<int> L;


    vector<int> temp={1,2,3,4,5};
    L.assign(temp.begin(),temp.end());



    return 0;
}