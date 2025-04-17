/*
 * GPS.h
 *
 *  Created on: Apr 6, 2025
 *      Author: zhang
 */

#ifndef SRC_GPS_H_
#define SRC_GPS_H_
#include "main.h"

#define max_gps_data 256

typedef struct {
    char time[10];      // UTC时间 (162039.000)
    char status;        // 状态 (A=有效，V=无效)
    double latitude;    // 纬度 (3411.74331)
    char lat_dir;       // 纬度方向 (N/S)
    double longitude;   // 经度 (11717.94501)
    char lon_dir;       // 经度方向 (E/W)
    double speed;       // 地面速度 (0.00节)
    double course;      // 地面航向 (352.42度)
    char date[10];      // UTC日期 (060425)
    char mode;          // 定位模式 (A=自主，D=差分，E=估算，N=无效)
} GNRMC;

int parse_gnrmc(const char* sentence, GNRMC* data) ;

#endif /* SRC_GPS_H_ */
