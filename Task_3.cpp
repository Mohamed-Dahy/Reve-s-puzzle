#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

//////////////////////// Global Variables //////////////////
int disks;
int moves = 0;
vector<int> s;  // Source Peg
vector<int> a1; // Aux Peg 1
vector<int> a2; // Aux Peg 2
vector<int> d;  // Destination Peg
///////////////////////////////////////////
void print_tower();
void move(vector<int> &src, vector<int> &dest);
void task_3(int n, vector<int> &src, vector<int> &dest, vector<int> &aux1, vector<int> &aux2);
int optimal_k(int n);
void task_2(int n, vector<int> &src, vector<int> &dest, vector<int> &aux);
int T(int n, int p);
/////////////////////////////////////////////////////////

int main()
{
    cout << "Enter number of disks: ";
    cin >> disks;

    s.resize(disks);
    a1.resize(disks, 0);
    a2.resize(disks, 0);
    d.resize(disks, 0);

    for (int i = 0; i < disks; i++)
    {
        s[i] = i + 1;
    }

    print_tower();
    task_3(disks, s, d, a1, a2);

    cout << "\nTotal Moves: " << moves << endl;
    return 0;
}

int T(int n, int p)
{
    if (n == 1)
        return 1;
    if (p == 3)
        return pow(2, n) - 1; // Tower of Hanoi for 3 pegs

    int min_moves = INT_MAX;
    for (int k = 1; k < n; k++)
    {
        int moves = 2 * T(k, p) + T(n - k, p - 1);
        if (moves < min_moves)
        {
            min_moves = moves;
        }
    }
    return min_moves;
}

int optimal_k(int n)
{
    int best_k = 1;
    int min_moves = INT_MAX;

    for (int k = 1; k < n; k++)
    {
        int moves = 2 * T(k, 4) + T(n - k, 3);
        if (moves < min_moves)
        {
            min_moves = moves;
            best_k = k;
        }
    }
    return best_k;
}

void task_2(int n, vector<int> &src, vector<int> &dest, vector<int> &aux)
{
    if (n == 1)
    {
        move(src, dest);
        return;
    }
    task_2(n - 1, src, aux, dest);
    move(src, dest);
    task_2(n - 1, aux, dest, src);
}

void task_3(int n, vector<int> &src, vector<int> &dest, vector<int> &aux1, vector<int> &aux2)
{
    if (n == 1)
    {
        move(src, dest);
        return;
    }
    int k = optimal_k(n);

    task_3(k, src, aux1, aux2, dest);
    task_2(n - k, src, dest, aux2);
    task_3(k, aux1, dest, src, aux2);
}

void move(vector<int> &src, vector<int> &dest)
{
    int from = -1;
    int to = -1;

    for (int i = 0; i < disks; i++)
    {
        if (src[i] != 0)
        {
            from = i;
            break;
        }
    }

    for (int i = disks - 1; i >= 0; i--)
    {
        if (dest[i] == 0)
        {
            to = i;
            break;
        }
    }

    if (from != -1 && to != -1)
    {
        dest[to] = src[from];
        src[from] = 0;
        moves++;
        print_tower();
    }
}

void print_tower()
{
    cout << "---------------------------------" << endl;
    for (int i = 0; i < disks; i++)
    {
        cout << (s[i] != 0 ? s[i] : 0) << "\t";
        cout << (a1[i] != 0 ? a1[i] : 0) << "\t";
        cout << (a2[i] != 0 ? a2[i] : 0) << "\t";
        cout << (d[i] != 0 ? d[i] : 0) << endl;
    }
    cout << "---------------------------------" << endl;
}