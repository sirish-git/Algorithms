#include "../inc/cp_contests.hpp"
  
void print_vec_elements(vector<int> v1){
    cout<<"\n";
    for(auto i:v1){
        cout<<i<<", ";
    } 
    cout<<"\n";    
}

void vector_basics(){
    cout<<"\n";
    cout<<"\nVector initialization with array: v={1,2,..}\n"; {
        vector<int> v1={1,2,3,4};

        cout<<"\naccess as array elements v[0]\n";
        cout2(v1[0], v1[1]);

        cout<<"\naccess elements with auto\n";
        for(auto i:v1){
            cout<<i<<", ";
        }

        cout<<"\n\naccess elements with iterator(pointer)\n";
        for(auto ptr=v1.begin(); ptr!=v1.end(); ptr++){
            cout<<ptr[0]<<", ";
        }        
    }

    cout<<"\nVector initialization with elements: v(cnt, initial)"; {        
        vector<int> v1(5,10);
        print_vec_elements(v1);   
    }

    cout<<"\nVector insert elements"; {        
        vector<int> v1;
        cout<<"insert elements with emplace_back, push_back";
        v1.emplace_back(1);
        v1.push_back(2);
        v1.push_back(5);
        print_vec_elements(v1);

        cout<<"insert single element";
        v1.insert(v1.begin()+2, 4);
        print_vec_elements(v1);   

        cout<<"insert group of elements (same value)";
        v1.insert(v1.begin()+3, 3, 6);
        print_vec_elements(v1);      

        cout<<"insert other vector in to current vecotr";
        vector<int> v2, v3;
        v2.emplace_back(1);
        v2.emplace_back(5);
        v3.emplace_back(2);
        v3.emplace_back(3);
        v3.emplace_back(4);
        v2.insert(v2.begin()+1, v3.begin(), v3.end());
        print_vec_elements(v2);              
    }     

    cout<<"\nVector erase(delete) elements"; {        
        vector<int> v1;
        v1.emplace_back(1);
        v1.push_back(2);
        v1.push_back(3);
        v1.push_back(4);
        v1.push_back(5);
        v1.push_back(6);
        print_vec_elements(v1);

        cout<<"delete single element";
        v1.erase(v1.begin()+1);
        print_vec_elements(v1);    

        cout<<"delete group of elements";
        v1.erase(v1.begin()+1, v1.begin()+3);
        print_vec_elements(v1);         
    } 

    coutm("\nVector of vectors"){
        vvi vvi1;
        vi vi1{1,2,3}, vi2{4,5};
        pb(vvi1, vi1);
        pb(vvi1, vi2);
        loop(i,0,vvi1.size()){
            loop(j,0,vvi1[i].size()){
                cout1(vvi1[i][j]);
            }
        }
    }

    coutm("\nVector of vectors with initialization"){
        vvi vvi1(4, vi(3,-1));
        loop(i,0,vvi1.size()){
            loop(j,0,vvi1[i].size()){
                cout<<vvi1[i][j]<<",";
            }
        }
    }    

    cout<<"\nVector with pair type, access as .first, .second"; {        
        vector<pair<int, int>> v1;
        coutm("insert pair with {element1, element2}");
        v1.push_back({1,2});
        v1.push_back({3,4});
        for(auto i:v1){
            cout2(i.fi, i.se);
        }    

        coutm("vector pair of pairs");
        vpipii vpipii1;
        vpipii1.push_back({1, {1,2}});
        vpipii1.push_back({2, {3,4}});
        for(auto i:vpipii1){
            cout3(i.fi, i.se.fi, i.se.se);
        }          
    }  

    cout<<"\nVector with pair type, access as .first, .second"; {        
        vector<pair<int, int>> v1;
        coutm("insert pair with {element1, element2}");
        v1.push_back({1,2});
        v1.push_back({3,4});
        for(auto i:v1){
            cout2(i.fi, i.se);
        }    
    }     

    cout<<"\n";       
}

void set_basics(){
    cout<<"\n";
    cout<<"\nSet elements are UNIQUE and SORTED\n";
    cout<<"\nSet initialization with array: v={1,2,..}\n"; {
        set<int> s1={2,2,4,1,4,3};

        coutm("Add elements to set using insert");
        s1.insert(5);

        coutm("access set elements using iteration on set")
        for(auto i:s1){
            cout<<i<<", ";
        }  

        coutm("set elements can't be accessed using index, since its a BST");
        coutm("use next function to get element at an index");
        cout2(*next(s1.begin(), 1), *next(s1.begin(), 3));


        cout<<"\nfind element in set, returns pointer\n";
        auto it=s1.find(4); 
        cout1(*s1.find(4)) ;        

        cout<<"\nerase element in set, returns pointer\n";  
        s1.erase(2);   
        for(auto i:s1){
            cout<<i<<", ";
        }    

        cout<<"\nerase element by pointer in set, returns pointer\n";  
        s1.erase(it);   
        for(auto i:s1){
            cout<<i<<", ";
        }                 
    }   
    cout<<"\n";       
}

void multiset_basics(){
    cout<<"\n";
    cout<<"\nmultiset elements stores DUPLICATES and SORTED\n";
    cout<<"\nmultiset initialization with array: v={1,2,..}\n"; {
        multiset<int> ms1={2,2,4,1,4,3};

        coutm("Add elements to multiset using insert");
        ms1.insert(5);
        
        cout<<"\nMultiSet elements accessed using iteration\n";
        for(auto i:ms1){
            cout<<i<<", ";
        }  

        cout<<"\nerase element in set, Deletes ALL occurances\n";  
        ms1.erase(2);   
        for(auto i:ms1){
            cout<<i<<", ";
        }    

        cout<<"\nerase element by pointer in set, deletes ONLY 1 element\n";  
        auto it=ms1.find(4);
        ms1.erase(it);   
        for(auto i:ms1){
            cout<<i<<", ";
        }                 
    }   
    cout<<"\n";       
}

void map_basics(){
    cout<<"\n";
    cout<<"\nMap KEYs are UNIQUE and SORTED\n";
    cout<<"\nMap set values as Array, insert, emplace \n"; {
        map<int, int> m1;
        m1[50]=2;
        m1[20]=5;
        coutm("add values to map with insert");
        m1.insert({100,8});
        coutm("--Note: insert doesn't NOT overwrite existing key, use direct assignment if overwrite needed");
        m1.insert({100,33});
        //m1[100]=22;
        m1.insert({10,1});

        cout<<"Map iteration with auto\n";
        for(auto i:m1){
            cout<<i.first<<", "<<i.second<<"\n";
        }
    }   
    cout<<"\nMap also support Find, Erase functions\n"; {

    }
    cout<<"\n";       
}

void multimap_basics(){
    cout<<"\n";
    cout<<"\nMultiMap set values as Array, insert, emplace \n"; {
        multimap<int, int> m1;
        //m1[50]=2;
        m1.insert({100,8});
        m1.insert({100,8});
        m1.insert({10,1});

        cout<<"\nMultiMap KEYs can have DUPLICATES  and SORTED\n";
        for(auto i:m1){
            cout<<i.first<<", "<<i.second<<"\n";
        }  

        cout<<"\nMultiMap also support Find, Erase functions\n";             
    }      
    cout<<"\n";       
}

void memset_test(){
    int R=2,C=2;
    ll ll2d[R][C], ll1d[R];
    int i2d[R][C], i1d[R];
    //mset(i2d,127);
    msetll(ll2d,INFLL);
    msetll(ll1d,INFLL);
    mseti(i2d,INF);
    mseti(i1d,INF);
    loop(i,0,R){
        loop(j,0,C){            
            cout6(i,j,ll2d[i][j], i2d[i][j], ll1d[i], i1d[i]);
        }
    }    
}

int main(){
    vector_basics();
    set_basics();
    multiset_basics();
    map_basics();
    multimap_basics();
    memset_test();
    return 0;
}