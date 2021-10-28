/*
*initialization notice
*REP(i,0,maxn-1) REP(j,0,V) dp[i][j] = -inf;dp[0][0] = 0, when volume needs exactly right.
*otherwise, dp[][] = 0;
*/

//01 pack

void zero_one_pack() {
    REP(i, 1, n) {
        _REP(j, V, c[i]) {
            f[j] = max(f[j], f[j - c[i]] + w[i]);
        }
    }
}

//complete pack

void complete_pack() {
    REP(i, 1, n) {
        REP(j, c[i], V) {
            f[j] = max(f[j], f[j - c[i]] + w[i]);
        }
    }
}

//multiple pack

void multiple_pack()  //if want to cut logM, use monotonic queue instead of it. The column note it.
{
    REP(i, 1, n) {
        if (k[i] >= V / c[i]) {
            REP(j, c[i], V) {
                f[j] = max(f[j], f[j - c[i]] + w[i]);
            }
            return;
        }
        int t = 1, M = k[i];
        while (t < M) {
            _REP(j, V, t * c[i]) {
                f[j] = max(f[j], f[j - t * c[i]] + t * w[i]);
            }
            M -= t;
            t <<= 1;
        }
        _REP(j, V, M * c[i]) {
            f[j] = max(f[j], f[j - M * c[i]] + M * w[i]);
        }
    }
}

//judge if exact V can reach in multiple pack situation

void available_volume() {
    memset(f, -1, sizeof f);
    f[0][0] = 0;
    REP(i, 1, n) {
        REP(j, 0, V) {
            if (f[i - 1][j] >= 0)
                f[i][j] = k[i];
            REP(j, 0, V - c[i])
            if (f[i][j] > 0)
                f[i][j + c[i]] = max(f[i][j + c[i]], f[i][j] - 1);
        }
    }

    //mixed pack

    void mixed_pack() {
        //make some modification from up context
        REP(i, 1, n) {
            if (01)
                01();
            else if (complete)
                complete();
            else
                multiple();
        }
    }

    //cluster pack, each cluster can only choose one at most.

    vector<int> cluster[maxk];  //don't add the pack whose volume is over V.
    void cluster_pack() {
        REP(i, 1, k) {  //1~k cluster
            REP(j, V, 0) {
                for (int t = 0; t < cluster[i].size(); t++) {
                    k0 = cluster[i][t];
                    if (j >= c[k0]) {
                        f[j] = max(f[j], f[j - c[k0]] + w[k0]);
                    }
                }
            }
        }
    }

    //complete pack or cluster pack can use optimization: when some pack only can choose one, those not replaced can be selected by the following methor:

    vector<int> cluster[maxk];  //don't add the pack whose volume is over V.
    int cntarr[maxV];
    void select(int p) {
        memset(cntarr, 0, sizeof cntarr);
        w[0] = -1;
        for (int i = 0; i < cluster[p].size(); i++) {
            int pac = cluster[p][i];
        cntarr[c[pac]] = (w[cntarr[c[pac]]] < w[pac] ? pac : cntarr[c[pac]);
        }
        cluster[p].clear();
        int idx = 0;
        REP(i, 0, V - 1) {
            if (w[cntarr[i]] > w[idx]) {
                cluster[p].push_back(cntarr[i]);
                idx = cntarr[i];
            }
        }
    }

    //best plan total number:01 pack for exmaple.
    void zero_one_pack_plan() {
        g[0][0] = 1;
        REP(i, 1, n) {
            REP(j, V, c[i]) {
                f[i][j] = max(f[i - 1][j], f[i - 1][j - c[i]] + w[i]);
                if (f[i][j] == f[i - 1][j])
                    g[i][j] += g[i - 1][j];
                if (f[i][j] == f[i - 1][j - c[i]] + w[i])
                    g[i][j] += g[i - 1][j - c[i]];
            }
        }
    }
