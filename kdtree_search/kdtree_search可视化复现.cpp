#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
using namespace pcl;
int main(int argc,char** argv)
{

    srand (time (NULL));

    PointCloud<PointXYZRGB>::Ptr cloud(new PointCloud<PointXYZRGB>);
    PointCloud<PointXYZRGB>::Ptr cloudColor(new PointCloud<PointXYZRGB>);
    cloud->width = 5000;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    std::uint8_t r = 255, g = 255, b = 255;    // Example: Red color
    std::uint32_t rgb = ((std::uint32_t)r << 16 | (std::uint32_t)g << 8 | (std::uint32_t)b);




    for(std::size_t i =0;i<cloud->size();++i)
    {
        (*cloud)[i].x = 10.0f * rand () / (RAND_MAX + 1.0f);
        (*cloud)[i].y = 10.0f * rand () / (RAND_MAX + 1.0f);
        (*cloud)[i].z = 10.0f * rand () / (RAND_MAX + 1.0f);
        (*cloud)[i].rgb = *reinterpret_cast<float*>(&rgb);

    }
    KdTreeFLANN<PointXYZRGB> kdtree;

    kdtree.setInputCloud(cloud);

    PointXYZRGB searchPoint;


    searchPoint.x = 10.0f * rand () / (RAND_MAX + 1.0f);
    searchPoint.y = 10.0f * rand () / (RAND_MAX + 1.0f);
    searchPoint.z = 10.0f * rand () / (RAND_MAX + 1.0f);


    int K = 100;
    std::vector<int> pointIdxNKNSearch(K);
    std::vector<float> pointNKNSquaredDistance(K);

    std::cout << "K nearest neighbor search at (" << searchPoint.x
              << " " << searchPoint.y
              << " " << searchPoint.z
              << ") with K=" << K << std::endl;

    if ( kdtree.nearestKSearch (searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0 )
    {
        for (std::size_t i = 0; i < pointIdxNKNSearch.size (); ++i)
            std::cout << "    "  <<   (*cloud)[ pointIdxNKNSearch[i] ].x
                      << " " << (*cloud)[ pointIdxNKNSearch[i] ].y
                      << " " << (*cloud)[ pointIdxNKNSearch[i] ].z
                      << " (squared distance: " << pointNKNSquaredDistance[i] << ")" << std::endl;
    }
     r = 0, g = 255, b = 0;    // Example: Red color
     rgb = ((std::uint32_t)r << 16 | (std::uint32_t)g << 8 | (std::uint32_t)b);
    for(std::size_t i =0;i<pointIdxNKNSearch.size ();++i)
    {

        (*cloud)[pointIdxNKNSearch[i]].rgb = *reinterpret_cast<float*>(&rgb);

    }


    std::vector<int> pointIdxRadiusSearch;
    std::vector<float> pointRadiusSquaredDistance;

    float radius = 2.0f * rand () / (RAND_MAX + 1.0f);

    std::cout << "Neighbors within radius search at (" << searchPoint.x
              << " " << searchPoint.y
              << " " << searchPoint.z
              << ") with radius=" << radius << std::endl;


    if ( kdtree.radiusSearch (searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0 )
    {
        for (std::size_t i = 0; i < pointIdxRadiusSearch.size (); ++i)
            std::cout << "    "  <<   (*cloud)[ pointIdxRadiusSearch[i] ].x
                      << " " << (*cloud)[ pointIdxRadiusSearch[i] ].y
                      << " " << (*cloud)[ pointIdxRadiusSearch[i] ].z
                      << " (squared distance: " << pointRadiusSquaredDistance[i] << ")" << std::endl;
    }
    r = 255, g = 0, b = 0;    // Example: Red color
    rgb = ((std::uint32_t)r << 16 | (std::uint32_t)g << 8 | (std::uint32_t)b);
    for(std::size_t i =0;i<pointIdxRadiusSearch.size();++i)
    {

        (*cloud)[pointIdxRadiusSearch[i]].rgb = *reinterpret_cast<float*>(&rgb);

    }


    pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");

    viewer.showCloud (cloud);
    while (!viewer.wasStopped())
    {

    }

    return 0;
}
