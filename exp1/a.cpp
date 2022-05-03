#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<stack>



#define MAX 100000000
#define OUT output_file

using namespace std;
void A_h1(const int start[5][5], const int target[5][5]);
void A_h2(const int start[5][5], const int target[5][5]);
void IDA_h1(const int start[5][5], const int target[5][5]);
void IDA_h2(const int start[5][5], const int target[5][5]);
ifstream start_file, target_file;
ofstream output_file;
struct status {
    int zero;
    int now[5][5];
    int h;
    int depth;
    char path[50];
};
struct cmp {
    bool operator()(status* a, status* b)
    {
        return ((a->h + a->depth) > (b->h + b->depth));
    }

};
struct status* status_init(status* p)
{
    p = (struct status*)malloc(sizeof(status));
    p->zero = -1;
    p->h = MAX;
    p->depth = -1;
    return p;
}
int h_1(const int now[5][5], const int target[5][5])
{
    int result = 0;
    for (int i = 0;i < 5;i++)
    {
        for (int j = 0;j < 5;j++)
        {
            if (now[i][j] > 0 && now[i][j] != target[i][j]) result++;
        }
    }
    return result;
}
int h_2(const int now[5][5], const int target[5][5])
{
    int result = 0;
    for(int i = 0;i < 5;i++)
    {
        for(int j = 0;j < 5;j++)
        {
            bool check = false;
            for(int m = 0;m < 5;m++)
            {
                if(now[i][j] == target[i][m])
                    check = true;
            }
            if(!check) 
                result++;
            check = false;
            for(int m = 0;m < 5;m++)
            {
                if(now[i][j] == target[m][j])
                    check = true;
            }
            if(!check) 
                result++;
        }
    }
    return result;
}
// struct status* move(status *p, )  

status* up(status* p, status* target)
{
    target = status_init(target);
    for (int i = 0;i < 5;i++)
    {
        for (int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    for (int i = 0;i < target->depth - 1;i++)
    {
        target->path[i] = p->path[i];
    }
    target->path[target->depth - 1] = 'U';
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if (target->zero == 2)
    {
        if (target->now[4][2] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[4][2];
            target->now[4][2] = 0;
            target->zero = 22;
        }
        else return NULL;
    }
    else if (target->zero < 5)
        return NULL;
    else
    {
        if (target->now[target->zero / 5 - 1][target->zero % 5] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[target->zero / 5 - 1][target->zero % 5];
            target->now[target->zero / 5 - 1][target->zero % 5] = 0;
            target->zero = target->zero - 5;
        }
        else return NULL;
    }
    return target;
}

// bool down(status* p)
// {
//     if(p->zero == 22)
//     {
//         if(p->now[0][2] > 0)
//             return true;
//         else return false;
//     }
//     else if(p->zero >= 20)
//         return false;
//     else
//     {
//         if(p->now[p->zero/5 + 1][p->zero%5] > 0)
//             return true;
//         else return false;
//     }
// }
status* down(status* p, status* target)
{
    target = status_init(target);
    for (int i = 0;i < 5;i++)
    {
        for (int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    for (int i = 0;i < target->depth - 1;i++)
    {
        target->path[i] = p->path[i];
    }
    target->path[target->depth - 1] = 'D';
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if (target->zero == 22)
    {
        if (target->now[0][2] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[0][2];
            target->now[0][2] = 0;
            target->zero = 2;
        }
        else return NULL;
    }
    else if (target->zero >= 20)
        return NULL;
    else
    {
        if (target->now[target->zero / 5 + 1][target->zero % 5] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[target->zero / 5 + 1][target->zero % 5];
            target->now[target->zero / 5 + 1][target->zero % 5] = 0;
            target->zero = target->zero + 5;
        }
        else return NULL;
    }
    return target;
}

status* right(status* p, status* target)
{
    target = status_init(target);
    for (int i = 0;i < 5;i++)
    {
        for (int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    for (int i = 0;i < target->depth - 1;i++)
    {
        target->path[i] = p->path[i];
    }
    target->path[target->depth - 1] = 'R';
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if (target->zero == 14)
    {
        if (target->now[2][0] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[2][0];
            target->now[2][0] = 0;
            target->zero = 10;
        }
        else return NULL;
    }
    else if (target->zero % 5 == 4)
        return NULL;
    else
    {
        if (target->now[target->zero / 5][target->zero % 5 + 1] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[target->zero / 5][target->zero % 5 + 1];
            target->now[target->zero / 5][target->zero % 5 + 1] = 0;
            target->zero = target->zero + 1;
        }
        else return NULL;
    }
    return target;
}

status* left(status* p, status* target)
{
    target = status_init(target);
    for (int i = 0;i < 5;i++)
    {
        for (int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    for (int i = 0;i < target->depth - 1;i++)
    {
        target->path[i] = p->path[i];
    }
    target->path[target->depth - 1] = 'L';
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if (target->zero == 10)
    {
        if (target->now[2][4] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[2][4];
            target->now[2][4] = 0;
            target->zero = 14;
        }
        else return NULL;
    }
    else if (target->zero % 5 == 0)
        return NULL;
    else
    {
        if (target->now[target->zero / 5][target->zero % 5 - 1] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[target->zero / 5][target->zero % 5 - 1];
            target->now[target->zero / 5][target->zero % 5 - 1] = 0;
            target->zero = target->zero - 1;
        }
        else return NULL;
    }
    return target;
}



void A_h1(const int start[5][5], const int target[5][5])
{
    priority_queue<status*, vector<status*>, cmp> Q;
    status* start_status = NULL;
    // status* target_status = NULL;
    start_status = status_init(start_status);
    start_status->depth = 0;
    // target_status = status_init(target_status);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5;j++)
        {
            start_status->now[i][j] = start[i][j];
            // target_status->now[i][j] = target[i][j];
            if (start_status->now[i][j] == 0) start_status->zero = i * 5 + j;
            // if (target_status->now[i][j] == 0) target_status->zero = i + j * 5;
        }
    }
    start_status->h = h_1(start_status->now, target);
    start_status->depth = 0;
    Q.push(start_status);
    while (!Q.empty())
    {
        status* next = Q.top();
        Q.pop();

        bool check = true;
        for (int i = 0;i < 5;i++)
        {
            for (int j = 0;j < 5;j++)
            {
                if (next->now[i][j] != target[i][j])
                {
                    check = false;
                    break;
                }
            }
            if (!check) break;
        }

        if (check)
        {
            next->path[next->depth] = '\0';
            OUT << next->path;
            OUT << ",";
            break;
        }
        status* U, * D, * L, * R;

        U = D = L = R = NULL;
        if (U = up(next, U))
        {
            U->h = h_1(U->now, target);
            Q.push(U);
        }
        if (R = right(next, R))
        {
            R->h = h_1(R->now, target);
            Q.push(R);
        }
        if (D = down(next, D))
        {
            D->h = h_1(D->now, target);
            Q.push(D);
        }

        if (L = left(next, L))
        {
            L->h = h_1(L->now, target);
            Q.push(L);
        }

    }
    return;
}
void A_h2(const int start[5][5], const int target[5][5])
{
    priority_queue<status*, vector<status*>, cmp> Q;
    status* start_status = NULL;
    // status* target_status = NULL;
    start_status = status_init(start_status);
    start_status->depth = 0;
    // target_status = status_init(target_status);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5;j++)
        {
            start_status->now[i][j] = start[i][j];
            // target_status->now[i][j] = target[i][j];
            if (start_status->now[i][j] == 0) start_status->zero = i * 5 + j;
            // if (target_status->now[i][j] == 0) target_status->zero = i + j * 5;
        }
    }
    start_status->h = h_2(start_status->now, target);
    start_status->depth = 0;
    Q.push(start_status);
    while (!Q.empty())
    {
        status* next = Q.top();
        Q.pop();

        bool check = true;
        for (int i = 0;i < 5;i++)
        {
            for (int j = 0;j < 5;j++)
            {
                if (next->now[i][j] != target[i][j])
                {
                    check = false;
                    break;
                }
            }
            if (!check) break;
        }

        if (check)
        {
            next->path[next->depth] = '\0';
            OUT << next->path;
            OUT << ",";
            break;
        }
        status* U, * D, * L, * R;

        U = D = L = R = NULL;
        if (U = up(next, U))
        {
            U->h = h_2(U->now, target);
            Q.push(U);
        }
        if (R = right(next, R))
        {
            R->h = h_2(R->now, target);
            Q.push(R);
        }
        if (D = down(next, D))
        {
            D->h = h_2(D->now, target);
            Q.push(D);
        }

        if (L = left(next, L))
        {
            L->h = h_2(L->now, target);
            Q.push(L);
        }

    }
    return;
}

void IDA_h1(const int start[5][5], const int target[5][5])
{
    status* start_status = NULL;
    // status* target_status = NULL;
    start_status = status_init(start_status);
    start_status->depth = 0;
    // target_status = status_init(target_status);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5;j++)
        {
            start_status->now[i][j] = start[i][j];
            // target_status->now[i][j] = target[i][j];
            if (start_status->now[i][j] == 0) start_status->zero = i * 5 + j;
            // if (target_status->now[i][j] == 0) target_status->zero = i + j * 5;
        }
    }
    start_status->h = h_1(start_status->now, target);
    start_status->depth = 0;
    stack<status*> S;
    int f_limit = start_status->h + start_status->depth;
    while(f_limit < MAX)
    {
        int next_f_limit = MAX;
        S.push(start_status);
        while(!S.empty())
        {
            status * next;
            next = S.top();
            S.pop();
            if(next->depth + next->h > f_limit)
                next_f_limit = min(next_f_limit, next->depth + next->h);
            else
            {
                bool check = true;
                for (int i = 0;i < 5;i++)
                {
                    for (int j = 0;j < 5;j++)
                    {
                        if (next->now[i][j] != target[i][j])
                        {
                            check = false;
                            break;
                        }
                    }
                    if (!check) break;    
                }
                if (check)
                {
                    next->path[next->depth] = '\0';
                    OUT << next->path;
                    OUT << ",";
                    return;
                }
                status* U, * D, * L, * R;
                U = D = L = R = NULL;
                if (U = up(next, U))
                {
                    U->h = h_1(U->now, target);
                    S.push(U);
                }
                if (R = right(next, R))
                {
                    R->h = h_1(R->now, target);
                    S.push(R);
                }
                if (D = down(next, D))
                {
                    D->h = h_1(D->now, target);
                    S.push(D);
                }

                if (L = left(next, L))
                {
                    L->h = h_1(L->now, target);
                    S.push(L);
                }
            }
        }
        f_limit = next_f_limit;
    }
    return;
}
void IDA_h2(const int start[5][5], const int target[5][5])
{
    status* start_status = NULL;
    // status* target_status = NULL;
    start_status = status_init(start_status);
    start_status->depth = 0;
    // target_status = status_init(target_status);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5;j++)
        {
            start_status->now[i][j] = start[i][j];
            // target_status->now[i][j] = target[i][j];
            if (start_status->now[i][j] == 0) start_status->zero = i * 5 + j;
            // if (target_status->now[i][j] == 0) target_status->zero = i + j * 5;
        }
    }
    start_status->h = h_2(start_status->now, target);
    start_status->depth = 0;
    stack<status*> S;
    int f_limit = start_status->h + start_status->depth;
    while(f_limit < MAX)
    {
        int next_f_limit = MAX;
        S.push(start_status);
        while(!S.empty())
        {
            status * next;
            next = S.top();
            S.pop();
            if(next->depth + next->h > f_limit)
                next_f_limit = min(next_f_limit, next->depth + next->h);
            else
            {
                bool check = true;
                for (int i = 0;i < 5;i++)
                {
                    for (int j = 0;j < 5;j++)
                    {
                        if (next->now[i][j] != target[i][j])
                        {
                            check = false;
                            break;
                        }
                    }
                    if (!check) break;    
                }
                if (check)
                {
                    next->path[next->depth] = '\0';
                    OUT << next->path;
                    OUT << ",";
                    return;
                }
                status* U, * D, * L, * R;
                U = D = L = R = NULL;
                if (U = up(next, U))
                {
                    U->h = h_2(U->now, target);
                    S.push(U);
                }
                if (R = right(next, R))
                {
                    R->h = h_2(R->now, target);
                    S.push(R);
                }
                if (D = down(next, D))
                {
                    D->h = h_2(D->now, target);
                    S.push(D);
                }

                if (L = left(next, L))
                {
                    L->h = h_2(L->now, target);
                    S.push(L);
                }
            }
        }
        f_limit = next_f_limit;
    }
    return;
}
int main(int argc, char *argv[])
{
    LARGE_INTEGER t1, t2, tc;
    double time;
    if(argc != 4)
    {
        cout << "argument number error!" << endl; 
        return 0;
    }

    int mode = -1;
    if(strcmp(argv[1], "A_h1") == 0)
        mode = 0;
    else if(strcmp(argv[1], "A_h2") == 0)
        mode = 1;
    else if(strcmp(argv[1], "IDA_h1") == 0)
        mode = 2;
    else if(strcmp(argv[1], "IDA_h2") == 0)
        mode = 3;
    else
    {
        cout << "wrong argument!" << endl;
        return 0;
    }
        
    char start_path[50];
    char target_path[50];
    char output_path[50];
    strcpy(start_path, "./data/");
    strcat(start_path, argv[2]);
    strcpy(target_path, "./data/");
    strcat(target_path, argv[3]);
    strcpy(output_path, "./data/output_");
    strcat(output_path, argv[1]);
    strcat(output_path, ".txt");


    start_file.open(start_path);
    target_file.open(target_path);
    output_file.open(output_path, ofstream::app);
    // if (start_file.is_open()) OUT << "success\n";

    // if(start_file)
    //     OUT << "unable to open the file" << endl;
    int start[5][5];
    int target[5][5];
    // start = status_init(start);
    // start->depth = 0;
    // target = status_init(target);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5;j++)
        {
            start_file >> start[i][j];
            target_file >> target[i][j];
        }
    }
    for(int times = 0; times < 12; times++)
    {
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        switch (mode)
        {
            case 0:A_h1(start, target); break;
            case 1:A_h2(start, target); break;
            case 2:IDA_h1(start, target); break;
            case 3:IDA_h2(start, target); break;    
            default: return 0;
            break;
        }
        QueryPerformanceCounter(&t2);
        double time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
        OUT << time << endl;
    }
    // A_h1(start, target);
    // A_h2(start, target);
    // IDA_h1(start, target);
    start_file.close();
    target_file.close();
    output_file.close();
    return 0;
}