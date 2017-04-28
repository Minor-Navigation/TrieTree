#define ll long long
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#define ll long long

class way_link{
public:

    char id[15];

    ll next;

    way_link()
	{
        next=-1;
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

fstream file,file_link;

void link_last_way(way& child,vector <string > v){
	ll curr_link=0,curr_end=0;
			//cout<<child.wayPtr<<" ";


    for(int i=0;i<v.size();i++){

        if(child.wayPtr==-1){
            file_link.seekp(0,ios::end);file_link.seekg(0,ios::end);
            child.wayPtr=file_link.tellp();
            child.wayPtr_end=file_link.tellp();

            //cout<<child.wayPtr_end<<endl;
            way_link last;

            (v[i]).copy(last.id, v[i].length());
            last.id[v[i].length()]='\0';

            file_link.write((char*)&last,sizeof(way_link));
        }
        else{
            file_link.seekp(0,ios::end);file_link.seekg(0,ios::end);
            curr_link=child.wayPtr_end;

            child.wayPtr_end=file_link.tellp();
            //cout<<child.wayPtr_end<<endl;

            curr_end=file_link.tellp();

            way_link last;
            //cout<<"  "<<last.next;

            (v[i]).copy(last.id, v[i].length() );
            last.id[v[i].length()]='\0';

            file_link.write((char*)&last,sizeof(way_link));

            //linking list end pointer to new pointer
            file_link.seekp(curr_link);file_link.seekg(curr_link);

            file_link.read((char*)&last,sizeof(way_link));
            last.next=curr_end;
            file_link.seekp(curr_link);file_link.seekg(curr_link);

            file_link.write((char*)&last,sizeof(way_link));

        }

    }


}

void trie(string name, string id, string lev ,vector <string> v){
         ll curr_child=0, curr_root=0;

        for(int i=0;i<name.length();i++){
            file.seekp(curr_root);file.seekg(curr_root);
            way root;
            file.read((char*)&root,sizeof(way));

            if(root.ptr[name[i]-0]==-1 ){
                file.seekp(0,ios::end);file.seekg(0,ios::end);
                way child;

                if(i==name.length()-1){

                    (id).copy(child.way_id, id.length());
                    child.way_id[id.length()]='\0';

                    (lev).copy(child.admin_level, lev.length());
                    child.admin_level[lev.length()]='\0';

                	link_last_way(child, v);

                }

                root.ptr[name[i]-0]=file.tellp();
                curr_child=file.tellg();
                file.write((char*)&child,sizeof(way));

                file.seekp(curr_root);file.seekg(curr_root);
                file.write((char*)&root,sizeof(way));

            }
            else{

                way child;
                curr_child=root.ptr[name[i]-0];
                file.seekp(curr_child);file.seekg(curr_child);
                file.read((char*)&child,sizeof(way));

                if(i==name.length()-1){

                    (id).copy(child.way_id, id.length());
                    child.way_id[id.length()]='\0';

                    (lev).copy(child.admin_level, lev.length());
                    child.admin_level[lev.length()]='\0';

                	link_last_way(child,v);

                }

                file.seekp(curr_child);file.seekg(curr_child);
                file.write((char*)&child,sizeof(way));
            }

            curr_root=curr_child;
            //cout<<curr_root<<endl;

        }

}

string delimiter;
string longitude, latitude;
string id, name,lev;
vector<string> ve;

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
                lev= token;
            }
            else if(ii>=3){
                ii++;
                ve.push_back(token);
            }
            str.erase(0, pos + delimiter.length());
        }
}


int main(){

    ll curr_child=0,curr_root=0,m=0;
	string filename="trie.txt";
	file.open("trie_way.txt",ios::trunc|ios::in|ios::out);
	file_link.open("trie_link_way.txt",ios::trunc|ios::in|ios::out);

	way root;
	file.seekp(0);file.seekg(0);
    file.write((char*)&root,sizeof(way));

//abcd 1 2.2 3.3 2
    std::ifstream way_file("waysDataForTrie.txt");
    delimiter = "$";
    string str;
    while(!way_file.eof()) // To get you all the lines.
    {
        getline(way_file,str); // Saves the line in STRING.
        read_file(str);
        cout<<name<<endl;
        trie(name, id, lev, ve);
        ve.clear();
    }



//    way_file.close();
    file_link.close();
    file.close();

	return 0;
}
