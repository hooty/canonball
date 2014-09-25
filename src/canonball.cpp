//
//  canonball.cpp
//
//  Created by Jon Christopher on 9/23/14.
//  Copyright (c) 2014 hoot. All rights reserved.
//

#include "headers/canonball.h"

EdsError _error = EDS_ERR_OK;
EdsCameraRef _camera = NULL;
EdsCameraListRef _camera_list = NULL;

void inialize_sdk() {
    _error = EdsInitializeSDK();
    if (_error != EDS_ERR_OK) printf("No framework detected\n");
}

void terminate_sdk() {
    _error = EdsTerminateSDK();
    if (_error != EDS_ERR_OK) printf("Failed terminating framework\n");
}

void open_camera_session(int camera_index) {
    if (_error == EDS_ERR_OK) _error = EdsGetCameraList(&_camera_list);
    if (_error == EDS_ERR_OK) _error = EdsGetChildAtIndex(_camera_list, camera_index, &_camera);
    if (_error == EDS_ERR_OK) _error = EdsOpenSession(_camera);
    if (_error != EDS_ERR_OK) printf("No camera detected\n");
}

void close_camera_session() {
    if (_error == EDS_ERR_OK) _error = EdsCloseSession(_camera);
    if (_error == EDS_ERR_OK) _error = EdsRelease(_camera);
    if (_error == EDS_ERR_OK) _error = EdsRelease(_camera_list);
    if (_error != EDS_ERR_OK && _camera != NULL) printf("Error releasing camera\n");
}

int take_picture(int camera_index) {
    inialize_sdk();
    open_camera_session(camera_index); 
    EdsSendCommand(_camera , kEdsCameraCommand_TakePicture, 0);  
    close_camera_session(); 
    terminate_sdk();        
    return _error;
}

EdsDirectoryItemRef DCIM_folder() {
    EdsUInt32 folder_count = 0;    
    EdsVolumeRef sd_card = NULL;
    EdsDirectoryItemRef dcim_folder = NULL;
    EdsDirectoryItemInfo folder_info;
    if (_error == EDS_ERR_OK) _error = EdsGetChildAtIndex( _camera, 0, &sd_card);
    if (_error == EDS_ERR_OK) _error = EdsGetChildCount( sd_card, &folder_count);
    for(int i = 0; i < folder_count; i++){
        if (_error == EDS_ERR_OK) _error = EdsGetChildAtIndex( sd_card, i, &dcim_folder ) ;
        if (_error == EDS_ERR_OK) _error = EdsGetDirectoryItemInfo( dcim_folder, &folder_info );
        std::string folderName = folder_info.szFileName;
        if( folderName == "DCIM" ) break;
        if (_error == EDS_ERR_OK) _error = EdsRelease(dcim_folder);
    } 
    if (_error == EDS_ERR_OK) _error = EdsRelease(sd_card);
    return dcim_folder;
}

void download_file(EdsDirectoryItemRef file_pointer, std::string folder){
    EdsStreamRef stream = NULL;
    EdsDirectoryItemInfo file;
    if (_error == EDS_ERR_OK) _error = EdsGetDirectoryItemInfo(file_pointer, &file);
    if (_error == EDS_ERR_OK) _error = EdsCreateFileStream( ( folder + file.szFileName ).c_str(), kEdsFileCreateDisposition_CreateAlways, kEdsAccess_ReadWrite, &stream);
    if (_error == EDS_ERR_OK) _error = EdsDownload( file_pointer, file.size, stream);
    if (_error == EDS_ERR_OK) _error = EdsDownloadComplete(file_pointer);
    if (_error == EDS_ERR_OK) _error = EdsDeleteDirectoryItem(file_pointer);
    if (_error == EDS_ERR_OK) _error = EdsRelease(stream);
    if (_error != EDS_ERR_OK) printf("Error downloading file\n");
}

int download_files(int camera_index, const char* folder) {
    inialize_sdk();
    open_camera_session(camera_index); 

    EdsDirectoryItemRef images_folder = NULL;
    EdsDirectoryItemRef file = NULL;
    EdsUInt32 sub_folder_count = 0;
    EdsDirectoryItemRef dcim_folder = DCIM_folder();

    EdsGetChildCount(dcim_folder, &sub_folder_count);
    int lastIndex = sub_folder_count-1;
    EdsDirectoryItemInfo dirItemInfo_Sub;
    _error = EdsGetChildAtIndex(dcim_folder, lastIndex, &images_folder ) ;
    _error = EdsGetDirectoryItemInfo( images_folder, &dirItemInfo_Sub);  
    EdsUInt32 jpgCount = 0;
    _error = EdsGetChildCount(images_folder, &jpgCount );
    for(int i = 0; i < jpgCount; i++){
        EdsGetChildAtIndex(images_folder, i, &file ) ;
        download_file(file , folder);
    }

    EdsRelease(dcim_folder);
    EdsRelease(images_folder);
    EdsRelease(file);

    close_camera_session(); 
    terminate_sdk();        

    return _error;
}