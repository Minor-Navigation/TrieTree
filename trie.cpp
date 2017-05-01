#define ll long long
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#define ll long long

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

fstream file,file_link;

ll c=0;

void link_last_node(node& child,string name, string id, string longi, string lati, string lev){
    ll curr_link=0,curr_end=0;
           // cout<<child.nodePtr<<" ";
c++;
    if(child.nodePtr==-1){
        file_link.seekp(0,ios::end);file_link.seekg(0,ios::end);
        child.nodePtr=file_link.tellp();
        child.nodePtr_end=file_link.tellp();

        //cout<<"-1:"<<child.nodePtr_end;
        node_link last;
        last.next=-1;
        //cout<<last.next<<endl;
        (id).copy(last.id, id.length());
        last.id[id.length()]='\0';

        (longi).copy(last.longitude, longi.length());
        last.longitude[longi.length()]='\0';

        (lati).copy(last.latitude, lati.length());
        last.latitude[lati.length()]='\0';

        (lev).copy(last.admin_level, lev.length());
        last.admin_level[lev.length()]='\0';
        last.next=-1;

        file_link.write((char*)&last,sizeof(node_link));
    cout<<last.next<<" :next -1:"<<file_link.tellp()<<endl;

    }
    else{
        file_link.seekp(0,ios::end);file_link.seekg(0,ios::end);
        curr_link=child.nodePtr_end;

        child.nodePtr_end=file_link.tellp();
        //cout<<child.nodePtr_end<<endl;

        curr_end=file_link.tellp();

        node_link last;
        //cout<<"  "<<last.next;

        (id).copy(last.id, id.length() );
        last.id[id.length()]='\0';

        (longi).copy(last.longitude, longi.length());
        last.longitude[longi.length()]='\0';

        (lati).copy(last.latitude, lati.length());
        last.latitude[lati.length()]='\0';

        (lev).copy(last.admin_level, lev.length());
        last.admin_level[lev.length()]='\0';
        last.next=-1;
        file_link.write((char*)&last,sizeof(node_link));

        //linking list end pointer to new pointer
        file_link.seekp(curr_link);file_link.seekg(curr_link);
    cout<<last.next<<" up:next "<<file_link.tellp()<<endl;

        file_link.read((char*)&last,sizeof(node_link));

        //cout<<"      "<<last.next<<endl;
        file_link.seekp(curr_link);file_link.seekg(curr_link);
        last.next=curr_end;
    cout<<last.next<<" :next "<<file_link.tellp()<<endl;

        file_link.write((char*)&last,sizeof(node_link));

    }

    //cout<<"  "<<file_link.tellp()<<endl;

}

void trie(string name, string id, string longi, string lati, string lev){
         ll curr_child=0, curr_root=0;
         
        for(int i=0;i<name.length();i++){
            file.seekp(curr_root);file.seekg(curr_root);
            node root;
            file.read((char*)&root,sizeof(node));
            
            cout<<" if  "<<root.ptr[name[i]-0]<<endl;

            if(root.ptr[name[i]-0]==-1 ){
                file.seekp(0,ios::end);file.seekg(0,ios::end);
                node child;

                if(i==name.length()-1){

                    link_last_node(child, name, id, longi, lati,lev);

                }

                root.ptr[name[i]-0]=file.tellp();
                curr_child=file.tellg();
                file.write((char*)&child,sizeof(node));

                file.seekp(curr_root);file.seekg(curr_root);
                file.write((char*)&root,sizeof(node));

            }

            else{

                node child;
                curr_child=root.ptr[name[i]-0];
            cout<<"  else "<<root.ptr[name[i]-0]<<endl;

                file.seekp(curr_child);file.seekg(curr_child);
                file.read((char*)&child,sizeof(node));

                if(i==name.length()-1){

                    link_last_node(child, name, id, longi, lati,lev);

                }

                file.seekp(curr_child);file.seekg(curr_child);
                file.write((char*)&child,sizeof(node));
            }

            curr_root=curr_child;
            cout<<curr_root<<endl;

        }

}


string delimiter;
string longitude, latitude;
string id, name,level;

void read_file(string str){
        string::size_type sz = 0;
        size_t pos = 0;
        string token;
        int ii=0;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            if(ii==0){
                ii++;
                name=token;
            }
            else if(ii==1){
                ii++;
                id = token;
            }
            else if(ii==2){
                ii++;
                level = token;
            }
            else if(ii==3){
                ii++;
                longitude= token;
            }
            else if(ii==4){
                ii++;
                latitude = token;
            }
            str.erase(0, pos + delimiter.length());
        }
}

string space2underscore(string text)
{
    for(int i = 0; i < text.length(); i++)
    {
        if(text[i] == ' ')
            text[i] = '_';
    }
    return text;
}

int main(){

    ll curr_child=0,curr_root=0,m=0;
    string filename="trie.txt";
    file.open("trie.txt",ios::trunc|ios::in|ios::out|ios::binary);
    file_link.open("trie_link.txt",ios::trunc|ios::in|ios::out|ios::binary);

    node root;
    file.seekp(0);file.seekg(0);
    file.write((char*)&root,sizeof(node));

//abcd 1 2.2 3.3 2
    std::ifstream node_file("NodeDataForTrieNew.txt");
    delimiter = "$";
    string str;
    while(!node_file.eof()) // To get you all the lines.
    {
        //name= space2underscore(name);
        getline(node_file,str); // Saves the line in STRING.
        read_file(str);
        cout<<str<<endl;
        trie(name, id,level, longitude, latitude);
        //cout<<name<<endl;
    }
    cout<<endl<<c<<endl;

    node_file.close();
    file_link.close();
    file.close();

    return 0;
}