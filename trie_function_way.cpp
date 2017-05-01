#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#define ll long long
#define way_size 256

fstream file,file_link;

vector <string> prefix;


class way_link{
public:

    char id[15];
    char longitude[25], latitude[25];
    ll next;
    int delimiter;
    way_link()
    {
        next=-1;
        delimiter=-1;
    }

};


class way{
public :
    ll ptr[256];
    ll wayPtr,wayPtr_end;
    char admin_level[3];
    char way_id[15];

    way()
    {
        for(int i=0;i<256;i++)
            {ptr[i]=-1;}
            wayPtr=-1;
            wayPtr_end=-1;
    }


};
    vector <string> id_list;
    vector <string> long_list;
    vector <string> lat_list;
    vector <int> delimiter_list;

void node_with_wayid(ll curr_root){
    id_list.clear();
    lat_list.clear();
    file_link.seekp(curr_root);file_link.seekg(curr_root);

    way_link link_list;
    //cout<<root.nodePtr<<" "<<root.nodePtr_end<<endl;
    while(1){

        file_link.read((char*)&link_list,sizeof(way_link));
        string s(link_list.id);
        id_list.push_back(s);
        string lo(link_list.longitude);
        string la(link_list.latitude);
        lat_list.push_back(la);
        lat_list.push_back(lo);

        delimiter_list.push_back(link_list.delimiter);

        if( link_list.next==-1){break;}
        //cout<<link_list.id<<endl;
        file_link.seekp(link_list.next);file_link.seekg(link_list.next);

    }

    return ;

}


void display_prefix(string s,int ind,ll curr_root){

    if( ind>0 ){
        ll curr_child=0;
        for(int i=0;i<s.length();i++){
            file.seekp(curr_root);file.seekg(curr_root);
            way root;
            file.read((char*)&root,sizeof(way));

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
    way root;
    file.read((char*)&root,sizeof(way));

    if(root.wayPtr!=-1){
       prefix.push_back(s);
    }

    for(int i=0;i<way_size;i++){

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

way search_trie(string s){
    ll curr_child=0,curr_root=0;
    for(int i=0;i<s.length();i++){
        file.seekp(curr_root);file.seekg(curr_root);
        way root;
        file.read((char*)&root,sizeof(way));

        if(root.ptr[s[i]-0]==-1 ){
            way x;
            return x;
        }
        else{
            curr_child=root.ptr[s[i]-0];
            if(i==s.length()-1){
                way child;
                file.seekp(curr_child);file.seekg(curr_child);
                file.read((char*)&child,sizeof(way));
                return child;
            }
        }

        curr_root=curr_child;
        //cout<<curr_root<<endl;
    }
}

int main(){
	long long curr_child=0,curr_root=0,m=0;
    file.open("trie_way.txt",ios::app|ios::in|ios::out);
    file_link.open("trie_link_way.txt",ios::app|ios::in|ios::out);

    curr_root=0;
    file.seekp(0,ios::end);
    curr_child=file.tellp();
    file.seekp(curr_root);file.seekg(curr_root);

    // search
    cout<<endl<<endl;
    way x= search_trie("Hapur Road");

    cout<<x.wayPtr<<"   "<<x.wayPtr_end<<endl;

    string temp="B"; //prefix search
    display_prefix(temp,temp.length(),0);
    for(int i=0;i<prefix.size();i++){
   //     cout<<prefix[i]<<" "<<prefix.size()<<endl;
    }
    file.close();

    node_with_wayid(x.wayPtr);

    for(int i=0;i<id_list.size();i++){
        cout<<id_list[i]<<"  "<<delimiter_list[i]<<endl;
    }



	return 0;
}
