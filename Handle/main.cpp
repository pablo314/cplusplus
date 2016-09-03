#include <iostream>                         //客户端


using namespace std;
template <class T> class Handle{
public:
    Handle(T* p=0):ptr(p),use(new size_t(1)){}
    Handle(const Handle& h):ptr(h.ptr),use(h.use)
    {
        (*use)++;
    }
    Handle&operator=(const Handle& h)
    {
        ++(*h.use);
        check();
        ptr = h.ptr;
        use=h.use;
        return *this;
    }
    T& operator*(){
        if(ptr)
            return *ptr;
        throw runtime_error ("unbound Handle");
    }
    T* operator&(){
        if(ptr)
            return ptr;
        throw runtime_error ("unbound Handle");
    }
    const T &operator*() const
    {
        if(ptr)
            return *ptr;
        throw runtime_error ("unbound Handle");
    }
    const T *operator&() const
    {
        if(ptr)
            return ptr;
        throw runtime_error ("unbound Handle");
    }
    ~Handle()
    {
        check();
    }
private:
    T * ptr;
    size_t *use;
    void check(){
        --(*use);
        if(*use==0)
        {
            delete use;
            delete ptr;

        }
    }
};
class test{

public:
    test(int a=0):val(a){}
    int val;
};
int main(){
    test *ptr = new test(2);

    Handle<test> p(ptr);
    cout<<(*p).val<<endl;





    return 0;
}