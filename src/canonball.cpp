//
//  canonball.cpp
//
//  Created by Jon Christopher on 9/23/14.
//  Copyright (c) 2014 hoot. All rights reserved.
//

#include "headers/canonball.h"

int inialize_sdk() {
    return EdsInitializeSDK();
}

int terminate_sdk() {
    return EdsTerminateSDK();
}

int open_camera_session(int camera_index) {
    EdsError error = EDS_ERR_OK;
    EdsCameraRef camera = NULL;
    EdsCameraListRef camera_list = NULL;
    if (error == EDS_ERR_OK) error = EdsGetCameraList(&camera_list);
    if (error == EDS_ERR_OK) error = EdsGetChildAtIndex(camera_list, camera_index, &camera);
    if (error == EDS_ERR_OK) error = EdsOpenSession(camera);
    return error;
}

int close_camera_session(int camera_index) {
    EdsError error = EDS_ERR_OK;
    EdsCameraRef camera = NULL;
    EdsCameraListRef camera_list = NULL;
    if (error == EDS_ERR_OK) error = EdsGetCameraList(&camera_list);
    if (error == EDS_ERR_OK) error = EdsGetChildAtIndex(camera_list, camera_index, &camera);
    if (error == EDS_ERR_OK) error = EdsCloseSession(camera);
    if (error == EDS_ERR_OK) error = EdsRelease(camera);
    if (error == EDS_ERR_OK) error = EdsRelease(camera_list);
    return error;
}

int take_picture(int camera_index) {
    EdsError error = EDS_ERR_OK;
    EdsCameraRef camera = NULL;
    EdsCameraListRef camera_list = NULL;
    if (error == EDS_ERR_OK) error = EdsGetCameraList(&camera_list);
    if (error == EDS_ERR_OK) error = EdsGetChildAtIndex(camera_list, camera_index, &camera);
    if (error == EDS_ERR_OK) error = EdsSendCommand(camera , kEdsCameraCommand_TakePicture, 0);  
    return error;
}

int download_file(EdsDirectoryItemRef file_pointer, std::string folder){
    EdsError error = EDS_ERR_OK;
    EdsStreamRef stream = NULL;
    EdsDirectoryItemInfo file;
    if (error == EDS_ERR_OK) error = EdsGetDirectoryItemInfo(file_pointer, &file);
    if (error == EDS_ERR_OK) error = EdsCreateFileStream( ( folder + file.szFileName ).c_str(), kEdsFileCreateDisposition_CreateAlways, kEdsAccess_ReadWrite, &stream);
    if (error == EDS_ERR_OK) error = EdsDownload( file_pointer, file.size, stream);
    if (error == EDS_ERR_OK) error = EdsDownloadComplete(file_pointer);
    if (error == EDS_ERR_OK) error = EdsDeleteDirectoryItem(file_pointer);
    if (error == EDS_ERR_OK) error = EdsRelease(stream);
    return error;
}

int download_files(int camera_index, const char* folder) {
    EdsError error = EDS_ERR_OK;
    EdsCameraRef camera = NULL;
    EdsCameraListRef camera_list = NULL;

    EdsUInt32 folder_count = 0;    
    EdsVolumeRef sd_card = NULL;
    EdsDirectoryItemRef dcim_folder = NULL;
    EdsDirectoryItemInfo folder_info;

    // Get DCIM folder
    if (error == EDS_ERR_OK) error = EdsGetCameraList(&camera_list);
    if (error == EDS_ERR_OK) error = EdsGetChildAtIndex(camera_list, camera_index, &camera);
    if (error == EDS_ERR_OK) error = EdsGetChildAtIndex(camera, 0, &sd_card);

    if (error == EDS_ERR_OK) error = EdsGetChildCount( sd_card, &folder_count);
    for(int i = 0; i < folder_count; i++){
        if (error == EDS_ERR_OK) error = EdsGetChildAtIndex( sd_card, i, &dcim_folder ) ;
        if (error == EDS_ERR_OK) error = EdsGetDirectoryItemInfo( dcim_folder, &folder_info );
        std::string folderName = folder_info.szFileName;
        if( folderName == "DCIM" ) break;
        if (error == EDS_ERR_OK) error = EdsRelease(dcim_folder);
    } 
    if (error == EDS_ERR_OK) error = EdsRelease(sd_card);

    // Iterate directories 
    EdsDirectoryItemRef images_folder = NULL;
    EdsDirectoryItemRef file = NULL;
    EdsUInt32 sub_folder_count = 0;

    if (error == EDS_ERR_OK) error = EdsGetChildCount(dcim_folder, &sub_folder_count);
    int lastIndex = sub_folder_count-1;
    EdsDirectoryItemInfo dirItemInfo_Sub;
    if (error == EDS_ERR_OK) error = EdsGetChildAtIndex(dcim_folder, lastIndex, &images_folder ) ;
    if (error == EDS_ERR_OK) error = EdsGetDirectoryItemInfo( images_folder, &dirItemInfo_Sub);  
    EdsUInt32 jpgCount = 0;
    if (error == EDS_ERR_OK) error = EdsGetChildCount(images_folder, &jpgCount );
    for(int i = 0; i < jpgCount; i++){
        if (error == EDS_ERR_OK) error = EdsGetChildAtIndex(images_folder, i, &file ) ;
        if (error == EDS_ERR_OK) error = download_file(file , folder);
    }

    if (error == EDS_ERR_OK) error = EdsRelease(dcim_folder);
    if (error == EDS_ERR_OK) error = EdsRelease(images_folder);
    if (error == EDS_ERR_OK) error = EdsRelease(file);
    return error;
}