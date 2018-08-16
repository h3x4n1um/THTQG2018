#include <bits/stdc++.h>

using namespace std;

int main(){
    for (int cnt = 1; cnt <= 25; ++cnt){
        /*var*/
        ifstream input(R"(..\input\Windows\)" + to_string(cnt) + ".in");
        ofstream output(R"(..\output\bruteforce\)" + to_string(cnt) + ".out");
        int n, k;
        int a[105][105], b[105][105];
        bool correct[105][105];
        vector <pair <pair <int, int>, pair <int, int> > > ans;
        /*read*/
        input >> n >> k;
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= n; ++j){
                input >> a[i][j];
                correct[i][j] = false;
            }
        }
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= n; ++j){
                input >> b[i][j];
                if (a[i][j] == b[i][j] && a[i][j] > 0) correct[i][j] = true;
            }
        }
        /*process*/
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= n; ++j){
                if (!correct[i][j] && b[i][j] > 0){
                    for (int _i = 1; _i <= n; ++_i){
                        bool quit = false;
                        for (int _j = 1; _j <= n; ++_j){
                            if (a[_i][_j] == 0){
                                swap(a[i][j], a[_i][_j]);
                                ans.push_back(make_pair(make_pair(i, j), make_pair(_i, _j)));
                                quit = true;
                                break;
                            }
                        }
                        if (quit) break;
                    }
                    for (int _i = 1; _i <= n; ++_i){
                        bool quit = false;
                        for (int _j = 1; _j <= n; ++_j){
                            if (!correct[_i][_j] && a[_i][_j] == b[i][j] && a[_i][_j] > 0){
                                swap(a[i][j], a[_i][_j]);
                                ans.push_back(make_pair(make_pair(_i, _j), make_pair(i, j)));
                                correct[i][j] = true;
                                quit = true;
                                break;
                            }
                        }
                        if (quit) break;
                    }
                }
            }
        }
        output << ans.size() << endl;
        for (auto i : ans){
            output << 2 << ' ' << i.first.first << ' ' << i.first.second << ' ' << i.second.first << ' ' << i.second.second << endl;
        }
    }
    return 0;
}
