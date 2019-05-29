#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <boost/algorithm/string.hpp>
#include <vector>

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;


using namespace std;

void read_bin(PointCloudT &out_points_cloud, string& files_dir, string& file_name){
    out_points_cloud.clear();
    string infile = files_dir+file_name+".bin";
    fstream input(infile.c_str(), ios::in | ios::binary);
    if(!input.good()){
        cerr << "Could not read file: " << infile << endl;
        exit(EXIT_FAILURE);
    }
    input.seekg(0, ios::beg);
    float inten;
    for (int i=0; input.good() && !input.eof(); i++) {
        PointT point;
        input.read((char *) &point.x, 3*sizeof(float));
        input.read((char *) &inten, sizeof(float));
        out_points_cloud.push_back(point);
    }
    input.close();
}

void writePointCloud(PointCloudT & pc, string file_name, string path){
    string file_name_path = path+file_name+".pcd";
    pcl::io::savePCDFileASCII(file_name_path, pc);
}

string reBuildPath(vector<string> &elems){
    string path="";
    for(int i=0; i<elems.size()-1; i++){
        path += elems[i]+"/";
    }
    return path;
}


void  filePathParsor(string file_name_path, string & file_path, string & file_name){
    vector<string> elems, file_elems;
    boost::algorithm::split(elems, file_name_path, boost::is_any_of("/"));
    boost::algorithm::split(file_elems, elems[elems.size()-1], boost::is_any_of("."));
    file_path = reBuildPath(elems);
    file_name = file_elems[0];
}

int main(int argc, char ** argv){
    PointCloudT pc;
   
    string file_name_path, file_name, file_path;
    if(argc >= 2){
        file_name_path = string(argv[1]);
        filePathParsor(file_name_path, file_path, file_name);
        read_bin(pc, file_path, file_name);
    }

    writePointCloud(pc, file_name, file_path);
}

