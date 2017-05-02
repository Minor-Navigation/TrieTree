#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<long long >);
PYBIND11_MAKE_OPAQUE(std::vector<string>);
PYBIND11_MAKE_OPAQUE(std::vector<double>);

int add(int i, int j) {
    return i + j;
}

int subtract(int i, int j) {
    return i - j;
}



#define ll long long
#define way_size 256
#define node_size 256
// ----way trieeee  #####################################################

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

    string getlevel(){
        string s(admin_level);
        return s;
    }

    string getid(){
        string s(way_id);
        return s;
    }

    vector<long long> getptr(){
        vector<long long> v;
        for(int i=0;i<way_size;i++){
            v.push_back(ptr[i]);
        }
        return v;

    }

};


class node_link_trie{
public:

    char longitude[25], latitude[25];
    char id[15];
    char admin_level[3];
    ll next;

    node_link_trie()
    {
        next=-1;
    }

};

class node_trie{
public :
    ll ptr[256];
    ll nodePtr,nodePtr_end;

    node_trie()
    {
        for(int i=0;i<256;i++)
            {ptr[i]=-1;}
            nodePtr=-1;
            nodePtr_end=-1;
    }


    vector<long long> getptr(){
        vector<long long> v;
        for(int i=0;i<way_size;i++){
            v.push_back(ptr[i]);
        }
        return v;

    }


};



class trie{
public:

    fstream file,file_link,file_node,file_link_node;
    vector <string> prefix,list;
    vector <string> id_list;
    vector <string> long_list;
    vector <string> lat_list;
    vector <ll> delimiter_list;
    
     trie(){
        file.open("C:\\Users\\akansh\\python_example\\trie_way.txt",ios::app|ios::in|ios::out|ios::binary);
        file_link.open("C:\\Users\\akansh\\python_example\\trie_link_way.txt",ios::app|ios::in|ios::out|ios::binary);
        file_node.open("C:\\Users\\akansh\\python_example\\trie.txt",ios::app|ios::in|ios::out|ios::binary);
        file_link_node.open("C:\\Users\\akansh\\python_example\\trie_link.txt",ios::app|ios::in|ios::out|ios::binary);
    }

    void close(){
        file.close();
        file_link.close();
        file_node.close();
        file_link_node.close();
    }



    void display_prefix(string s,int ind,ll curr_root){

        if( ind>0 ){

            prefix.clear();
            list.clear();
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
           string str(root.way_id);
           list.push_back(str);
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

        }
    }


    void display_prefix_node(string s,int ind,ll curr_root){

        if( ind>0 ){
            prefix.clear();
            list.clear();

            ll curr_child=0;
            for(int i=0;i<s.length();i++){
                file_node.seekp(curr_root);file_node.seekg(curr_root);
                node_trie root;
                file_node.read((char*)&root,sizeof(node_trie));

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

        file_node.seekp(curr_root);file_node.seekg(curr_root);
        node_trie root;
        file_node.read((char*)&root,sizeof(node_trie));

        if(root.nodePtr!=-1){
           // prefix.push_back(s);
            file_link_node.seekp(root.nodePtr);file_link_node.seekg(root.nodePtr);

            node_link_trie link_list;

            while(1){
                file_link_node.read((char*)&link_list,sizeof(node_link_trie));

                prefix.push_back(s);
                string str(link_list.id);
                list.push_back(str);
                if(link_list.next==-1){break;}
                file_link_node.seekp(link_list.next);file_link_node.seekg(link_list.next);

            }

        }

        for(int i=0;i<node_size;i++){

            if(root.ptr[i]==-1 ){
                //return ;
            }
            else{
                string si=s;
                si+=(0+i);
                display_prefix_node(si,0,root.ptr[i] );
            }

        }

        return;

    }

    node_trie search_trie_node(string s){


        ll curr_child=0,curr_root=0;
        for(int i=0;i<s.length();i++){
            file_node.seekp(curr_root);file_node.seekg(curr_root);
            node_trie root;
            file_node.read((char*)&root,sizeof(node_trie));

            if(root.ptr[s[i]-0]==-1 ){
                node_trie x;
                return x;
            }
            else{
                curr_child=root.ptr[s[i]-0];
                if(i==s.length()-1){
                    node_trie child;
                    file_node.seekp(curr_child);file_node.seekg(curr_child);
                    file_node.read((char*)&child,sizeof(node_trie));
                    return child;
                }
            }

            curr_root=curr_child;

        }
    }


    void node_with_wayid(ll curr_root){
        id_list.clear();
        lat_list.clear();
        file_link.seekp(curr_root);file_link.seekg(curr_root);
        delimiter_list.clear();
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



    void node_with_nodeid(ll curr_root){
        id_list.clear();
        lat_list.clear();
        file_link_node.seekp(curr_root);file_link_node.seekg(curr_root);

        node_link_trie link_list;
        //cout<<root.nodePtr<<" "<<root.nodePtr_end<<endl;
        while(1){

            file_link_node.read((char*)&link_list,sizeof(node_link_trie));
            string s(link_list.id);
            id_list.push_back(s);
            string lo(link_list.longitude);
            string la(link_list.latitude);
            lat_list.push_back(la);
            lat_list.push_back(lo);


            if( link_list.next==-1){break;}
            //cout<<link_list.next<<endl;
            file_link_node.seekp(link_list.next);file_link_node.seekg(link_list.next);

        }

        return ;

    }
    

};


////R----- treee ##########################################################

#define min(a,b) ((a<b) ? (a) : (b))
#define max(a,b) ((a>b) ? (a) : (b))
#define abs(a) ((a>0) ? (a) : ((-1)*a))
#define ll long long
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORL(i,n) for(long long i=0;i<n;i++)
#define MOD 1000000007
#define PI 3.141592653589
#define pb push_back
#define mp make_pair
#define fastio ios_base::sync_with_stdio(false); cin.tie(0);
#define fileio freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#define MAX_CHILD 10
#define null NULL
#define square(a) a*a

typedef struct node{
public:
    bool isLeaf,isParentLeaf;
    long long id;
    int level;
    double lon1,lat1,lon2,lat2;
    //struct node *child[MAX_CHILD+1];
    long long child[MAX_CHILD+1];
    int no_child;
    node()
    {

    }
    node(double lo1,double la1, double lo2,double la2)
    {
        isLeaf=false;
        lon1=lo1;
        lat1=la1;
        lon2=lo2;
        lat2=la2;
        id=-1;
        level=-1;
        no_child=0;
        for (int i=0;i<=MAX_CHILD;i++)
            child[i]=-1;
    }
    node(double lo, double la,long long i, int l)
    {
        isLeaf=true;
        id=i;
        level=l;
        isParentLeaf=false;
        lon1=lon2=lo;
        lat1=lat2=la;
        no_child=0;
        for (int i=0;i<=MAX_CHILD;i++)
            child[i]=-1;
    }
} node;


class nodeInd{
public:
    ll id,ptr,adjPtr;
    int size;
};

class nodeData {
public:
    ll id;
    double lon,lat;
    vector<ll> adj,adjPtr;
    char* otherData;
    nodeData(){

    }
};

class rtree{


public:
    fstream f,f1,f2;
    vector<ll> nodes_in_box;
    ll root;
    fstream file_rtree;
    ll value;
    rtree(ll r)
    {
        f.open("C:\\Users\\akansh\\python_example\\NodeIndexNew.ind",ios::in | ios::out | ios::binary); 
        f1.open("C:\\Users\\akansh\\python_example\\CompleteNodeData.dat",ios::in | ios::out | ios::binary); 
        f2.open("C:\\Users\\akansh\\python_example\\adjacency.dat",ios::in | ios::out | ios::binary); 
        root=r;
        value=0;
        if(r!=-1)
            file_rtree.open("C:\\Users\\akansh\\python_example\\test.txt",ios::in | ios::out | ios::binary);
        else
            file_rtree.open("C:\\Users\\akansh\\python_example\\test.txt",ios::in | ios::out | ios::trunc | ios::binary);

    }

    void close(){
        f.close();
        f1.close();
        f2.close();
        file_rtree.close();
    }

    void boundingBox_(double lo1,double lo2, double la1, double la2, int level, ll ptr)
    {   value+=5;
        if(ptr==-1)
            return;

        node n;
        file_rtree.seekp(ptr);file_rtree.seekg(ptr);
        file_rtree.read((char*)&n , sizeof(node));
        value=n.id;
       // cout<<n.id<endl<<endl;
        if ( n.lon2>=lo1 && lo2>=n.lon1 && n.lat2>=la1 && la2>=n.lat1)
        {
        }
        else
            return;

        if(n.level>level)
            return;

        if(n.isLeaf)
        {   value=n.id;

            nodes_in_box.pb(n.id);
           // cout<<n.id<<" "<<n.level<<endl;
        }

        for(int i=0;i<n.no_child;i++)
        {
            boundingBox_(lo1,lo2,la1,la2,level,n.child[i]);
        }

    }



    void boundingBox(double lo1,double lo2, double la1, double la2, int level)
    {
        nodes_in_box.clear();
        double t;
        if(lo1>lo2)
        {
            t=lo1;
            lo1=lo2;
            lo2=t;
        }

        if(la1>la2)
        {
            t=la1;
            la1=la2;
            la2=t;
        }
        boundingBox_(lo1,lo2,la1,la2,level,root);
    }


    nodeData queryNode(ll id)
    {

        nodeData nd;

        char *res = NULL;

        f.seekg(0,ios::end);
        ll no_nodes=f.tellg();
        nodeInd in;
        no_nodes/=sizeof(nodeInd);
        int size;
        ll temp;
        ll s=0,e=no_nodes-1,m;
        while(s<=e)
        {
            m=(s+e)/2;
            f.seekg(m*sizeof(nodeInd));f.seekp(m*sizeof(nodeInd));
            f.read((char*)&in,sizeof(nodeInd));
            if(in.id==id)
            {
                //cout<<"Found";
                nd.otherData= new char[in.size];
                f1.seekg(in.ptr);f1.seekp(in.ptr);
                f1.read(nd.otherData,in.size);

                f2.seekg(in.adjPtr);f2.seekp(in.adjPtr);
                f2>>nd.id>>nd.lon>>nd.lat>>size;
                while(size--)
                {
                    f2>>temp;
                    nd.adj.pb(temp);
                    f2>>temp;
                    nd.adjPtr.pb(temp);
                }

                return nd;
            }
            if(in.id<id)
                s=m+1;
            else
                e=m-1;

        }
        nd.id=-1;
        
        return nd;

    }

    nodeData queryNode2(ll id ,ll ptr)
    {

        nodeData nd;
        char *res = NULL;

        nodeInd in;
        int size;
        ll temp;

    
        f.seekg(ptr);f.seekp(ptr);
        f.read((char*)&in,sizeof(nodeInd));
        if(in.id==id)
        {
            //cout<<"Found";
            nd.otherData= new char[in.size];
            f1.seekg(in.ptr);f1.seekp(in.ptr);
            f1.read(nd.otherData,in.size);

            f2.seekg(in.adjPtr);f2.seekp(in.adjPtr);
            f2>>nd.id>>nd.lon>>nd.lat>>size;
            while(size--)
            {
                f2>>temp;
                nd.adj.pb(temp);
                f2>>temp;
                nd.adjPtr.pb(temp);
            }

            return nd;
        }
        nd.id=-1;
        
        return nd;

    }




};



PYBIND11_PLUGIN(python_example) {
    py::module m("python_example", R"pbdoc(
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: python_example
        .. autosummary::
           :toctree: _generate
           add
           subtract
    )pbdoc");


    m.def("add", &add, R"pbdoc(
        Add two numbers
        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", &subtract, R"pbdoc(
        Subtract two numbers
        Some other explanation about the subtract function.
    )pbdoc");
    
    py::bind_vector<std::vector<long long>>(m, "Vectorll");
    py::bind_vector<std::vector<string>>(m, "Vectorstring");
    py::bind_vector<std::vector<double>>(m, "Vectord");

    py::class_<trie>(m,"trie")
    .def(py::init<>())
    .def("close", &trie::close)
    .def_readwrite("prefix", &trie::prefix)
    .def_readwrite("list", &trie::list)
    .def_readwrite("id_list", &trie::id_list)
    .def_readwrite("long_list", &trie::long_list)
    .def_readwrite("lat_list", &trie::lat_list)
    .def_readwrite("delimiter_list", &trie::delimiter_list)
    .def("display_prefix", &trie::display_prefix)
    .def("search_trie", &trie::search_trie)
    .def("display_prefix_node", &trie::display_prefix_node)
    .def("search_trie_node", &trie::search_trie_node)
    .def("node_with_wayid", &trie::node_with_wayid)
    .def("node_with_nodeid", &trie::node_with_nodeid);

    py::class_<node_trie>(m,"node_trie")
    .def(py::init<>())
    .def("getptr", &node_trie::getptr)
    .def_readwrite("nodeptr", &node_trie::nodePtr)
    .def_readwrite("nodeptr_end", &node_trie::nodePtr_end);

    py::class_<way>(m,"way_trie")
    .def(py::init<>())
    .def("getptr", &way::getptr)
    .def("getid", &way::getid)
    .def_readwrite("wayptr", &way::wayPtr)
    .def_readwrite("wayptr_end", &way::wayPtr_end)
    .def("getlevel", &way::getlevel);
    
    py::class_<rtree>(m,"rtree")
    .def(py::init<long long >())
    .def("boundingBox", &rtree::boundingBox)
    .def("queryNode", &rtree::queryNode)
    .def("queryNode2", &rtree::queryNode2)
    .def("close", &rtree::close)
    .def_readwrite("nodes_in_box", &rtree::nodes_in_box)
    .def_readwrite("root", &rtree::root)
    .def_readwrite("value", &rtree::value);

    py::class_<nodeData>(m,"nodeData")
    .def(py::init<>())
    .def_readwrite("id", &nodeData::id)
    .def_readwrite("lon", &nodeData::lon)
    .def_readwrite("lat", &nodeData::lat)
    .def_readwrite("adj", &nodeData::adj)
    .def_readwrite("adjPtr", &nodeData::adjPtr);


#ifdef VERSION_INFO
    m.attr("__version__") = py::str(VERSION_INFO);
#else
    m.attr("__version__") = py::str("dev");
#endif

    return m.ptr();
}