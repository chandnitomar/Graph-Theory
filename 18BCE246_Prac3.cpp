#include <iostream>
#include<bits/stdc++.h>
using namespace std;
bool graphical_or_not(int degree_seq[], int n)
{
    int sum=0;
    for(int i=0; i<n; i++)
        sum+=degree_seq[i];
    if(sum%2)
        return false;
    int start = 0;
    while(1)
	{
        sort(degree_seq + start, degree_seq + n);
        reverse(degree_seq + start, degree_seq + n);
        if(degree_seq[start] == 0)
            return true;
        if(degree_seq[start]>(n-start-1))
            return false;
        start++;
        for(int i=start; i<(start+degree_seq[start-1]); i++)
		{
            degree_seq[i]--;
            if (degree_seq[i] < 0)
                return false;
        }
    }
}

int main()
{
    int n;
    cin>>n;
    int degree_seq[n];
    for(int i=0; i<n; i++)
        cin>>degree_seq[i];
    int ans = graphical_or_not(degree_seq , n);
    if(ans)
        cout<<endl<<"Is Graphical"<<endl;
    else
        cout<<endl<<"Is not Graphical"<<endl;
}


/*
9
6 6 5 4 4 3 2 2 1
*/
