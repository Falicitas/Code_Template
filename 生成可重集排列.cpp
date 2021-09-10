void print_permulation(int n,int *P,int *A,int cur)
{
    if(cur==n+1){
        for(int i=1;i<=n;i++) printf("%d ",A[i]);
        printf("\n");
    }
    else for(int i=1;i<=n;i++) if(i==1||P[i]!=P[i-1]){  //P[i]代表可重集的元素
        int c1 = 0;int c2 = 0;
        for(int j=1;j<cur;j++) if(A[j]==P[i]) c1++;
        for(int j=1;j<=n;j++) if(P[j]==P[i]) c2++;
        if(c1<c2){
            A[cur] = P[i];
            print_permulation(n,P,A,cur+1);
        }
    }
}
