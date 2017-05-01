#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#define ll long long
#define node_size 256

fstream file,file_link;

vector <string> prefix;

class node_link{
public:

    char longitude[25], latitude[25];
    char id[15];
    char admin_level[3];
    ll next;

    node_link()
    {
        next=-1;
    }

};

class node{
public :
    ll ptr[256];
    ll nodePtr,nodePtr_end;

    node()
    {
        for(int i=0;i<256;i++)
            {ptr[i]=-1;}
            nodePtr=-1;
            nodePtr_end=-1;
    }


};


void display_prefix(string s,int ind,ll curr_root){

    if( ind>0 ){
        prefix.clear();
        ll curr_child=0;
        for(int i=0;i<s.length();i++){
            file.seekp(curr_root);file.seekg(curr_root);
            node root;
            file.read((char*)&root,sizeof(node));

            if(root.ptr[s[i]-0]==-1 ){
                return ;
            }
            else{
                curr_child=root.ptr[s[i]-0];
            }
            curr_root=curr_child;
            ind--;
          //  cout<<i<<":i "<<root.nodePtr<<"  "<<ind<<endl;;
        }

    }
    //cout<<s<<endl;

    file.seekp(curr_root);file.seekg(curr_root);
    node root;
    file.read((char*)&root,sizeof(node));

    if(root.nodePtr!=-1){
       // prefix.push_back(s);
        file_link.seekp(root.nodePtr);file_link.seekg(root.nodePtr);

        node_link link_list;
       // cout<<root.nodePtr<<" "<<root.nodePtr_end<<endl;;
        while(1){
            file_link.read((char*)&link_list,sizeof(node_link));

            prefix.push_back(s);
            if( link_list.next==-1 || abs(link_list.next)>30000000){break;}
           // cout<<link_list.next<<endl;
            file_link.seekp(link_list.next);file_link.seekg(link_list.next);

        }

    }

    for(int i=0;i<node_size;i++){

        if(root.ptr[i]==-1 ){
            //return ;
        }
        else{
            string si=s;
            si+=(char)(0+i);
            display_prefix(si,0,root.ptr[i] );
        }

    }

    return;
}


node search_trie(string s){
    ll curr_child=0,curr_root=0;
    for(int i=0;i<s.length();i++){
        file.seekp(curr_root);file.seekg(curr_root);
        node root;
        file.read((char*)&root,sizeof(node));
        cout<<root.ptr[s[i]-0]<<endl;

        if(root.ptr[s[i]-0]==-1 ){
            node x;
            return x;
        }
        else{
            curr_child=root.ptr[s[i]-0];
            if(i==s.length()-1){
                node child;
                file.seekp(curr_child);file.seekg(curr_child);
                file.read((char*)&child,sizeof(node));
                return child;
            }
        }

        curr_root=curr_child;

    }
}


vector <string> id_list;
vector <string> long_list;
vector <string> lat_list;

void node_with_nodeid(ll curr_root){
    id_list.clear();
    lat_list.clear();
    file_link.seekp(curr_root);file_link.seekg(curr_root);

    node_link link_list;
    //cout<<root.nodePtr<<" "<<root.nodePtr_end<<endl;
    while(1){

        file_link.read((char*)&link_list,sizeof(node_link));
        string s(link_list.id);
        id_list.push_back(s);
        string lo(link_list.longitude);
        string la(link_list.latitude);
        lat_list.push_back(la);
        lat_list.push_back(lo);


        if( link_list.next==-1){break;}
        cout<<link_list.next<<endl;
        file_link.seekp(link_list.next);file_link.seekg(link_list.next);

    }

    return ;

}


int main(){
    long long curr_child=0,curr_root=0,m=0;
    file.open("trie.txt",ios::app|ios::in|ios::out);
    file_link.open("trie_link.txt",ios::app|ios::in|ios::out);

    curr_root=0;
    file.seekp(0,ios::end);
    curr_child=file.tellp();
    file.seekp(curr_root);file.seekg(curr_root);



    // search
    cout<<endl<<endl;
    node x= search_trie("Modinagar");

    cout<<x.nodePtr<<endl;

    string temp="Mo"; //prefix search

    display_prefix(temp,temp.length(),0);
    for(int i=0;i<prefix.size();i++){
        cout<<prefix[i]<<" "<<endl;
    }
   
     node_with_nodeid(x.nodePtr);

    for(int i=0;i<id_list.size();i++){
        cout<<id_list[i]<<"  "<<endl;
    }

    file.close();
    file_link.close();
    return 0;
}