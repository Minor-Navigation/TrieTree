#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#define ll long long
#define node_size 256


fstream file;

vector <string> prefix;

class node{
public:
	ll ptr[256];
	ll nodePtr;
    char longitude[25], latitude[25];
    char id[15];
    node()
	{
		for(int i=0;i<256;i++)
			ptr[i]=-1;
            nodePtr=-1;
    }
};


void display_prefix(string s,int ind,ll curr_root){
    if( ind>0 ){
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
            //cout<<curr_root<<"  ";
        }

    }
    file.seekp(curr_root);file.seekg(curr_root);
    node root;
    file.read((char*)&root,sizeof(node));

    if(root.nodePtr==1){
        prefix.push_back(s);
    }

    for(int i=0;i<node_size;i++){

        if(root.ptr[i]==-1 ){
            //return ;
        }
        else{
            string si=s;
            si+=(0+i);
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

int main(){
	long long curr_child=0,curr_root=0,m=0;
    file.open("trie.txt",ios::app|ios::in|ios::out);

    curr_root=0;
    file.seekp(0,ios::end);
    curr_child=file.tellp();
    file.seekp(curr_root);file.seekg(curr_root);

   

    // search
    cout<<endl<<endl;
    node x= search_trie("sikandarabad");
    
    cout<<x.nodePtr<<endl;

    cout<<x.id<<endl;
    cout<<x.latitude<<endl;
    cout<<x.longitude<<endl;

    string temp="new"; //prefix search
    display_prefix(temp,temp.length(),0);
    for(int i=0;i<prefix.size();i++){
        cout<<prefix[i]<<" "<<endl;
    }
    file.close();
    
	return 0;
}
