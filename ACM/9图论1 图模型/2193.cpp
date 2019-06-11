#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

void tidy(string& x) {
    int j = 0;
    for(int i = 0; i < x.size(); ++i)
        if(x[i] != ' ')
            x[j++] = x[i];
    x.erase(j);
}

int main() {
    string x;
    string P[4];
    bool G[9][9];
    vector<int> H[4][4];
    //将每个格子里面可能出现的值存放在H[4][4]中
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            H[i][j].push_back(i*3+j);
            H[i][j+1].push_back(i*3+j);
            H[i+1][j].push_back(i*3+j);
            H[i+1][j+1].push_back(i*3+j);
        }
    }
    while(getline(cin, x) && x == "START") {
        //将第i行的数据存储在P[i]中，并去除其中的空格
        for(int i = 0; i < 4; ++i) {
            getline(cin, P[i]);
            tidy(P[i]);
        }
        getline(cin, x);//把"END"处理掉
        memset(G, 0, sizeof(G));
        //构建有向图
        //对快照中每一个格子中的值，如果H中有可覆盖的值，
        //就将有向图G[P[i][j] - '1'][H[i][j][k]]的值改为true，表示可以覆盖的值
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                for(int k = 0; k < H[i][j].size(); ++k)
                    if(H[i][j][k] != P[i][j] - '1')
                        G[P[i][j] - '1'][H[i][j][k]] = true;
        //判断是否有环
        for(int i = 0; i < 9; ++i)
            for(int j = 0; j < 9; ++j)
                for(int k = 0; k < 9; ++k)
                    if(G[j][i] && G[i][k])
                        G[j][k] = true;
        bool ans = false;
        for(int i = 0; i < 9; ++i)
            if(G[i][i] == true)
                ans = true;
        puts(
            ans ?
            "THESE WINDOWS ARE BROKEN" :
            "THESE WINDOWS ARE CLEAN"
        );
    }

}