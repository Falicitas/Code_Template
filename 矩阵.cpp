struct Matrix
{
    int m[4][4],mod;

    void clear()
    {
        REP(i,0,3){
            REP(i,0,3){
                m[i][j] = 0;
            }
        }
    }

    void unit()
    {
        REP(i,0,3){
            m[i][i] = 1;
        }
    }

    bool empty()
    {
        if(m[1][1]==0&&m[1][2]==1&&m[2][1]==1&&m[2][2]==1) return true;
        else return false;
    }

    Matrix operator*(const matrix &y) const
    {
        matrix z; z.clear();
        REP(i,1,2){
            REP(k,1,2){ //put k in middle, accelerate multipling speed.
                REP(j,1,2){
                    (z.m[i][j] += m[i][k] * y.m[k][j]) %= mod;
                }
            }
        }
        return z;
    }

    friend matrix operator+(matrix a,Matrix b)//notice this.
    {
        matrix c;c.clear();
        REP(i,1,2){
            REP(j,1,2){
                c.m[i][j] = (a.m[i][j] + b.m[i][j]) % mod;
            }
        }
        return c;
    }
};
