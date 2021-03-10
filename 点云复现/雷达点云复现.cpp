#include <iostream>
#include <unistd.h>
#include <ctime>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
using namespace std;
void Delay(int   time)//time*1000为秒数
{
    clock_t now =clock();
    while(clock()-now< time);
}
int main (int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);


    /*std::cout << "Loaded "
              << cloud->width * cloud->height
              << " data points from test_pcd.pcd with the following fields: "
              << std::endl;
    for (const auto& point: *cloud)
        std::cout << "    " << point.x
                  << " "    << point.y
                  << " "    << point.z << std::endl;*/
    pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");

    viewer.showCloud (cloud);
    int number=0;
    //string dir="//home//chenjianlin//桌面//pcl_test//test//PointCloud//PointCloud_";
    string dir="//home//chenjianlin//桌面//pcl_test//点云复现//PointCloud//PointCloud_";
    while (!viewer.wasStopped ())
    {

        string filename = dir + to_string(number) + ".pcd";
        pcl::io::loadPCDFile(filename, *cloud);
        pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color(cloud, 0, 255, 0);
        viewer.showCloud(cloud);
        //sleep(1);
        Delay(1500);
        number++;
        cout<<number<<endl;
        if(number ==700)
        {
           number=0;
        }

    }

    return (0);
}


