#include<bits/stdc++.h>
#include "Num.h"
using namespace std;

int main(){
    num var2,var;
    cin>>var>>var2;
    cout<<(var+var2)<<endl<<var-var2<<endl<<var*var2<<endl<<var/var2<<endl<<var%var2<<endl
    <<"comparison "<<endl;
    cout<<((var>var2)?"yes":"no")<<endl
    <<((var>=var2)?"yes":"no")<<endl
    <<((var==var2)?"yes":"no")<<endl
    <<((var<=var2)?"yes":"no")<<endl
    <<((var<var2)?"yes":"no")<<endl;
}
