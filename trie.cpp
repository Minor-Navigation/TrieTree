#define ll long long
#include<bits/stdc++.h>
#include<fstream>
#include <iostream> 
#include <string>
using namespace std;
#define ll long long 

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

fstream file;
	
void trie(string name, string id, string longi, string lati){
         ll curr_child=0, curr_root=0;
        
        for(int i=0;i<name.length();i++){
            file.seekp(curr_root);file.seekg(curr_root);
            node root;
            file.read((char*)&root,sizeof(node));

            if(root.ptr[name[i]-0]==-1 ){
                file.seekp(0,ios::end);file.seekg(0,ios::end);
                node child;
               
                if(i==name.length()-1){
                    child.nodePtr=1;
                   
                    (id).copy(child.id, id.length());
                    child.id[id.length()]='\0';
                   
                    (longi).copy(child.longitude, longi.length());
                    child.longitude[longi.length()]='\0';
                   
                    (lati).copy(child.latitude, lati.length());
                    child.longitude[lati.length()]='\0';
                    
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
                file.seekp(curr_child);file.seekg(curr_child);
                file.read((char*)&child,sizeof(node));

                if(i==name.length()-1){
                    child.nodePtr=1;
                   
                    (id).copy(child.id, id.length());
                    child.id[id.length()]='\0';
                   
                    (longi).copy(child.longitude, longi.length());
                    child.longitude[longi.length()]='\0';
                   
                    (lati).copy(child.latitude, lati.length());
                    child.longitude[lati.length()]='\0';
                    
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
string id, name;
	
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
                longitude= token;
            }
            else if(ii==3){
                ii++;
                latitude = token;
            }
            str.erase(0, pos + delimiter.length());
        }
}


int main(){
   
    ll curr_child=0,curr_root=0,m=0;
	string filename="trie.txt";
	file.open("trie.txt",ios::trunc|ios::in|ios::out);
	node root;
	file.seekp(0);file.seekg(0);
    file.write((char*)&root,sizeof(node));

    std::ifstream node_file("node_data1.txt");    
    delimiter = "$";
    string str;
    while(!node_file.eof()) // To get you all the lines.
    {
        getline(node_file,str); // Saves the line in STRING.
        read_file(str);
        trie(name, id, longitude, latitude); 
    }
    node_file.close();
    file.close();

	return 0;
}