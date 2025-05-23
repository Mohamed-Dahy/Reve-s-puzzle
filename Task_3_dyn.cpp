#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

//////////////////////// Global Variables //////////////////
int disks;
int moves = 0;
vector<int> s;               // Source Peg
vector<int> a1;              // Aux Peg 1
vector<int> a2;              // Aux Peg 2
vector<int> d;               // Destination Peg
int dp[100][5];              // DP Table 

void print_tower();
void move(vector<int>& src, vector<int>& dest);
void task_3(int n, vector<int>& src, vector<int>& dest, vector<int>& aux1, vector<int>& aux2);
int optimal_k(int n);
void task_2(int n, vector<int>& src, vector<int>& dest, vector<int>& aux);
void fill_table(int max_disks);
int T(int n, int p);

int main() {
    cout << "Enter number of disks: ";
    cin >> disks;

    s.resize(disks);
    a1.resize(disks, 0);
    a2.resize(disks, 0);
    d.resize(disks, 0);

    for (int i = 0; i < disks; i++) {
        s[i] = i + 1;
    }

    fill_table(disks);
    print_tower();
    task_3(disks, s, d, a1, a2);

    cout << "\nTotal Moves: " << moves << endl;
    return 0;
}

void fill_table(int max_disks) {
    for (int p = 3; p <= 4; p++) {
        for (int n = 1; n <= max_disks; n++) {
            if (n == 1) dp[n][p] = 1;
            else if (p == 3) dp[n][p] = pow(2, n) - 1;
            else {
                dp[n][p] = INT_MAX;
                for (int k = 1; k < n; k++) {
                    int moves = 2 * dp[k][p] + dp[n - k][p - 1];
                    if (moves < dp[n][p]) {
                        dp[n][p] = moves;
                    }
                }
            }
        }
    }
}

int T(int n, int p) {
    return dp[n][p];
}

int optimal_k(int n) {
    for (int k = 1; k < n; k++) {
        if (dp[n][4] == 2 * dp[k][4] + dp[n - k][3]) {
            return k;
        }
    }
    return 1;
}

void task_2(int n, vector<int>& src, vector<int>& dest, vector<int>& aux) {
    if (n == 1) {
        move(src, dest);
        return;
    }
    task_2(n - 1, src, aux, dest);
    move(src, dest);
    task_2(n - 1, aux, dest, src);
}

void task_3(int n, vector<int>& src, vector<int>& dest, vector<int>& aux1, vector<int>& aux2) {
    if (n == 1) {
        move(src, dest);
        return;
    }
    int k = optimal_k(n);
    task_3(k, src, aux1, aux2, dest);
    task_2(n - k, src, dest, aux2);
    task_3(k, aux1, dest, src, aux2);
}

void move(vector<int>& src, vector<int>& dest) {
    int from = -1, to = -1;

    for (int i = 0; i < src.size(); i++) {
        if (src[i] != 0) {
            from = i;
            break;
        }
    }

    for (int i = dest.size() - 1; i >= 0; i--) {
        if (dest[i] == 0) {
            to = i;
            break;
        }
    }

    if (from != -1 && to != -1) {
        dest[to] = src[from];
        src[from] = 0;
        moves++;
        print_tower();
    }
}

void print_tower() {
    cout << "---------------------------------\n";
    for (int i = 0; i < disks; i++) {
        cout << (i < s.size() ? s[i] : 0) << "\t"
            << (i < a1.size() ? a1[i] : 0) << "\t"
            << (i < a2.size() ? a2[i] : 0) << "\t"
            << (i < d.size() ? d[i] : 0) << endl;
    }
    cout << "---------------------------------\n";
}
