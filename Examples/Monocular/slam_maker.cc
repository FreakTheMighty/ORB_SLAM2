/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<opencv2/core/core.hpp>

#include<System.h>

using namespace std;

void LoadImages(const string &strFile, vector<string> &vstrImageFilenames,
                vector<double> &vTimestamps);

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        cerr << endl << "Usage: ./slam_maker path_to_vocabulary path_to_settings path_to_sequence" << endl;
        return 1;
    }

    
    cv::VideoCapture cap(argv[3]);
    
    if (!cap.isOpened())
    {
        std::cout << "!!! Failed to open file: " << argv[3] << std::endl;
        return -1;
    }


    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,false);


    cout << endl << "-------" << endl;
    cout << "Start processing sequence ..." << endl;

    // Main loop
    cv::Mat im;
    
    while(cap.read(im))
    {
        
        if(im.empty())
        {
            cerr << endl << "Failed to load frame" << endl;
            return 1;
        }
        
        double tframe = cap.get(CV_CAP_PROP_POS_MSEC) / 1000;
        
        cout << "Second: " << tframe << endl;

        resize(im, im, cv::Size(960, 540), 0, 0, cv::INTER_CUBIC);

        // Pass the image to the SLAM system
        cv::Mat pose = SLAM.TrackMonocular(im,tframe);
    }
    
    // Stop all threads
    SLAM.Shutdown();

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");
    SLAM.SaveTrajectoryTUM("Trajectory.txt");
    SLAM.SavePointCloud("PointCloud.txt");
    return 0;
}
