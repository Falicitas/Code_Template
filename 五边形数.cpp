namespace five_number
{
    const int maxn = 100000;
    int p[maxn+10];
    void init(){
        int i, j, k, l;
        long long sum;
        p[0] = 1;
        for(i = 1; i <= maxn; i++){
            sum = 0;
            for(j = 1, k = 1, l = 1; j > 0; k++, l = -l){
                j = i - (3*k*k - k) / 2;
                if(j >= 0) sum += l * p[j];
                j = i - (3*k*k + k) / 2;
                if(j >= 0) sum += l * p[j];
                sum = (sum % mod + mod) % mod;
            }
            p[i] = sum;
        }
    }
}
