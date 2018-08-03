/*
 * Copyright 2018 Bonn-Rhein-Sieg University
 *
 * Author: Mohammad Wasil, Santosh Thoduka
 *
 */
#ifndef MCR_SCENE_SEGMENTATION_SCENE_SEGMENTATION_NODE_H
#define MCR_SCENE_SEGMENTATION_SCENE_SEGMENTATION_NODE_H

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_listener.h>
#include "mcr_scene_segmentation/clustered_point_cloud_visualizer.h"
#include "mcr_scene_segmentation/bounding_box_visualizer.h"
#include <mcr_scene_segmentation/label_visualizer.h>
#include "mcr_scene_segmentation/cloud_accumulation.h"

#include <dynamic_reconfigure/server.h>
#include <mcr_scene_segmentation/SceneSegmentationConfig.h>
#include <string>

using mcr::visualization::BoundingBoxVisualizer;
using mcr::visualization::ClusteredPointCloudVisualizer;
using mcr::visualization::LabelVisualizer;
using mcr::visualization::Color;

class SceneSegmentationNode
{
    private:
        ros::NodeHandle nh_;
        ros::Publisher pub_debug_;
        ros::Publisher pub_boxes_;
        ros::Publisher pub_object_list_;
        ros::Publisher pub_event_out_;
        ros::Publisher pub_workspace_height_;
        ros::Publisher pub_input_for_debug_;

        ros::Subscriber sub_cloud_;
        ros::Subscriber sub_event_in_;

        ros::ServiceClient recognize_service;

        dynamic_reconfigure::Server<mcr_scene_segmentation::SceneSegmentationConfig> server_;

        tf::TransformListener transform_listener_;

        SceneSegmentation scene_segmentation_;
        CloudAccumulation::UPtr cloud_accumulation_;

        BoundingBoxVisualizer bounding_box_visualizer_;
        ClusteredPointCloudVisualizer cluster_visualizer_;
        LabelVisualizer label_visualizer_;

        bool add_to_octree_;
        std::string frame_id_;
        int object_id_;
        double octree_resolution_;
        double object_height_above_workspace_;
        bool dataset_collection_;
        bool debug_mode_;
        std::string pcd_file_path_;
        std::string pcd_file_name_;        

    private:
        void pointcloudCallback(const sensor_msgs::PointCloud2::Ptr &msg);
        void eventCallback(const std_msgs::String::ConstPtr &msg);
        void config_callback(mcr_scene_segmentation::SceneSegmentationConfig &config, uint32_t level);
        void segment();
        void findPlane();
        geometry_msgs::PoseStamped getPose(const BoundingBox &box);

    public:
        SceneSegmentationNode();
        virtual ~SceneSegmentationNode();
};

#endif  // MCR_SCENE_SEGMENTATION_SCENE_SEGMENTATION_NODE_H
