#include <iostream>
#include <stack>
#include <stdio.h>
using namespace std;

int main()
{
    int n, count, i;
    int tar[1000];
    stack<int> st;
    while (scanf("%d", &n) != EOF && n != 0)
    {
        while (scanf("%d", &tar[0]) && tar[0] != 0)
        {
            for (i = 1; i < n; i++)
                scanf("%d", &tar[i]);
            i = 0;
            count = 1;
            while (i < n)
            {
                if (count == tar[i])
                {
                    count++;
                    i++;
                }
                else if (!st.empty() && (st.top() == tar[i]))
                {
                    st.pop();
                    i++;
                }
                else if (count <= tar[i])
                {
                    st.push(count++);
                }
                else
                    break;
            }
            if (i == n)
                printf("Yes\n");
            else
                printf("No\n");
            while(!st.empty())st.pop();
        }
        printf("\n");
    }
    //system("pause");
    return 0;
}