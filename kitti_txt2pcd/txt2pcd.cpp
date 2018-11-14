#include <iostream>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <fstream>
#include <vector>
#include <sstream>


using namespace std;
typedef pcl::PointXYZI PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

int main(int argc, char** argv){
    fstream txt(argv[1]);
    string lines;
    PointCloudT cloud;
    while(getline(txt,lines)){
        PointT temp; double va;
        stringstream ss;
        ss<<lines;
        ss>>va;temp.x=va;
        ss>>va;temp.y=va;
        ss>>va;temp.z=va;
        ss>>va;temp.intensity=va;
        cloud.push_back(temp);
    }
    
    string file_name(argv[1]);
    int pos=file_name.find('.');
    string file_name_pre=file_name.substr(0,pos);
    cout<<file_name_pre<<endl;
    pcl::io::savePCDFileASCII(file_name_pre+".pcd",cloud);
}