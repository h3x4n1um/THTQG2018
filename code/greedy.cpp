#include <bits/stdc++.h>

using namespace std;

ifstream inp("stdin.inp");
ofstream out("stdout.out");

struct quaplet{
    int first;
    int second;
    int third;
    int forth;
};

int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
string dir = "NESW";
int a[100][100], b[100][100];
int n, k;
vector <quaplet> ans;
bool vis[100][100];

struct node{
    int val, x, y, x_, y_;
};

bool valid(pair<int, int> state){
    //out<<state.first<<" * "<<state.second<<endl;
    //out<<vis[state.first][state.second]<<" "<<vis[state.first][state.second]<<endl;
    if(state.first >= 1 && state.first <= n && state.second >= 1 && state.second <= n
       && vis[state.first][state.second] == 0 && a[state.first][state.second] == 0){
        return 1;
    }
    return 0;
}

int bfs(int x, int y, int t, bool process){
    if(process){
        out<<x<<" * "<<y<<endl;
    }
    queue<pair<int, pair<int, int> > > q;
    int p[100][100];
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j) vis[i][j] = 0;
    }
    bool found = 0;
    q.push({0, {x, y}});
    while(q.size() != 0){
        pair<int, pair<int, int> > temp = q.front(); q.pop();
        pair<int, int> cur = temp.second;
        for(int i = 0; i < 4; ++i){
            pair<int, int> new_cur = {cur.first + dx[i], cur.second + dy[i]};
            if(valid(new_cur)){
                q.push({temp.first + 1, new_cur});
                vis[cur.first][cur.second] = 1;
                p[cur.first][cur.second] = i;
                if(process){
                    //out<<cur.first<<" "<<cur.second<<" "<<i<<endl;
                    //out<<new_cur.first<<" "<<new_cur.second<<endl;
                }
                if(b[new_cur.first][new_cur.second] == t) {
                    if(process) break;
                    found = 1;
                    return temp.first + 1;
                }
            }
        }
        if(found) break;
    }
    if(process){
        a[x][y] = 0;
        while(b[x][y] != t){
            out<<1<<" "<<x<<" "<<y<<" ";
            out<<dir[p[x][y]]<<endl;
            int cp = p[x][y];
            x += dx[cp];
            y += dy[cp];
        }
        a[x][y] = t;
    }
    return 0;
}

pair<int, pair<int, int> > mDist(int x, int y){
    int need = a[x][y];
    //out<<need<<endl;
    pair<int, int> loc = {0, 0};
    int minDist = 1<<30;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(b[i][j] == need){
                if(abs(i - x) + abs(j - y) < minDist){
                    minDist = abs(i - x) + abs(j - y);
                    loc.first = i;
                    loc.second = j;
                }
            }
        }
    }
    pair<int, pair<int, int> > temp;
    temp.first = minDist;
    temp.second = loc;
    //out<<minDist<<" : "<<loc.first<<" "<<loc.second<<endl;
    return temp;
}

void printOut(){
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            out<<a[i][j]<<" ";
        }
        out<<endl;
    }
}

int main(){
    int cnt = 1;
    //for (int cnt = 1; cnt <= 25; ++cnt){
        /*var*/
        /*read*/
        inp>> n >> k;
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= n; ++j){
                inp >> a[i][j];
            }
        }
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= n; ++j){
                inp >> b[i][j];
            }
        }
        int m = n * n;
        while((m)--){
            vector<pair<int, pair<int, int> > > bans;
            for(int i = 1; i <= n; ++i){
                for(int j = 1; j <= n; ++j){
                    if(a[i][j] != 0 && a[i][j] != -1){
                        int temp = bfs(i, j, a[i][j], 0);
                        //out<<i<<" "<<j<<" "<<temp<<endl;
                        if(temp){
                            bans.push_back({temp, {i, j}});
                        }
                    }
                }
            }
            //out<<bans.size();
            if(bans.size() != 0){
                sort(bans.begin(), bans.end());
                auto cur = bans[0];
                bfs(cur.second.first, cur.second.second, a[cur.second.first][cur.second.second], 1);
            } else {
                vector<node> mans;
                mans.clear();
                for(int i = 1; i <= n; ++i){
                    for(int j = 1; j <= n; ++j){
                        if(a[i][j] != 0 && a[i][j] != -1) {
                            pair<int, pair<int, int> > temp = mDist(i, j);
                            //out<<i<<" "<<j<<" "<<temp.first<<endl;
                            node mew;
                            mew.val = temp.first;
                            mew.x = i;
                            mew.y = j;
                            mew.x_ = temp.second.first;
                            mew.y_ = temp.second.second;
                            mans.push_back(mew);
                        }
                    }
                }
                sort(mans.begin(), mans.end(), [](node a, node b){
                        return a.val > b.val;
                     });
                node choose = mans[0];
                if(choose.val == 0) break;
                out<<2<<" "<<choose.x<<" "<<choose.y<<" "<<choose.x_<<" "<<choose.y_<<endl;
                swap(a[choose.x][choose.y], a[choose.x_][choose.y_]);
            }

        }
    //}
    return 0;
}

