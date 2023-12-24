#include "../inc/cp_contests.hpp"

/* --Important utility functions-- */
/* Find all substrings */
void all_substrings(string str){
    loop(i,0,str.size()){
        string sub;
        loop(j,i,str.size()){            
            pb(sub, str[j]);
            cout1(sub);
        }
    }
}
/* Monotonic stack: Find next larget/smallest element*/
void nextLargestElement(vi &vec){
    stack<int> stk;
    loopr(i,vec.size()){
        int val=-1;
        while(!stk.empty()){
            if(stk.top()>vec[i]){
                val=stk.top();
                break;
            }
            stk.pop();
        }
        stk.push(vec[i]);
        cout2(vec[i], val);
    }
}




int main(){            
    string str1="abcd";
    coutm("all substings: "+str1);
    all_substrings(str1);

    coutm("next largest element with monotonic stack");
    vi vec1={3,1,5,6,2,4};
    coutvec(vec1);
    nextLargestElement(vec1);

    coutm("tests on lower_bound, upper_bound");
    vector vec{1,2,4,8,9};
    auto id1=lb(vec, 3);
    auto id2=ub(vec, 4);
    cout2(*id1,*id2);

    coutm("tests on sortr, loop, cout macros");
    vi v1{4,6,1,3};
    sortr(v1);
    loop(i,0,v1.size()){
        cout3(i, v1[i], maxe(v1));
    }
    return 0;
}