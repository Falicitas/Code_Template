struct node
{
    int x,y;
    bool operator ==(const node&rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
};

struct node_hash
{
    size_t operator() (const node& a)const{//利用x的hash值和y的hansh值做异或得到eg的hash值
        return hash<int>()(a.x) ^ hash<int>()(a.y);
    }
};
