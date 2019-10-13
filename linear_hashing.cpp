#include<iostream>
#include<vector>

std::vector <std::vector<int> > hash_table;

int hash(int n)
{
    if(n<0)
        return -n;
    return n;
}
void split(int iter,int size)
{
    std::vector <int> a;
    std::vector <int> splitted;
    for(auto i:hash_table[iter])
        if((hash(i)&((size<<1)-1)) == iter)
            a.push_back(i);
        else
            splitted.push_back(i);
    hash_table[iter] = a;
    hash_table.push_back(splitted);
    // std::cout<<hash_table[iter].size()<<' '<<hash_table[iter+size].size();
}
bool check(int a,int index)
{
    for(auto i:hash_table[index])
        if(i==a)
            return true;
    return false;
}
int main()
{
    int n,a,index;
    std::cin>>n;
    int iter = 0;
    int size = 1;
    int capacity = 2;
    std::vector<int> v;
    hash_table.push_back(v);
    for(int i=0;i<n;i++)
    {
        std::cin>>a;
        index = hash(a)&((size<<1)-1);
        // std::cout<<"Original "<<index;
        if(index>=iter+size)
            index = index - size;
        // std::cout<<" New Index "<<index;
        if(check(a,index))
            continue;
        hash_table[index].push_back(a);
        if(hash_table[index].size() > capacity)
        {
            // std::cout<<" Overflow ";
            split(iter,size);
            iter++;
            if(iter==size)
            {
                size=size<<1;
                iter = 0;
            }
        }
        // std::cout<<'\n';
    }
    for(int i=0;i<iter+size;i++)
    {
        // std::cout<<i<<':';
        for(auto &j:hash_table[i])
            std::cout<<j<<' ';
    }
    std::cout<<'\n';
    return 0;
}
