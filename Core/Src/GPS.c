/*
 * GPS.c
 *
 *  Created on: Apr 6, 2025
 *      Author: zhang
 */
#include "GPS.h"
// 解析GNRMC语句
int parse_gnrmc(const char* sentence, GNRMC* data) {
    char checksum;
    char calculated_checksum = 0;
    char buffer[256];
    char* token;
    int i;

    // 验证校验和
    const char* p = strchr(sentence, '*');
    if (p != NULL) {
        sscanf(p + 1, "%2hhx", &checksum);

        for (i = 1; sentence[i] != '*' && sentence[i] != '\0'; i++) {
            calculated_checksum ^= sentence[i];
        }

        if (calculated_checksum != checksum) {
            return 0;
        }
    }

    // 复制句子到缓冲区进行处理
    strncpy(buffer, sentence, sizeof(buffer));

    // 分割字段
    token = strtok(buffer, ",");
    if (token == NULL || strcmp(token, "$GNRMC") != 0) {
        return 0;
    }

    // 时间
    token = strtok(NULL, ",");
    if (token) strncpy(data->time, token, sizeof(data->time));

    // 状态
    token = strtok(NULL, ",");
    if (token) data->status = *token;

    // 纬度
    token = strtok(NULL, ",");
    if (token) data->latitude = atof(token);

    // 纬度方向
    token = strtok(NULL, ",");
    if (token) data->lat_dir = *token;

    // 经度
    token = strtok(NULL, ",");
    if (token) data->longitude = atof(token);

    // 经度方向
    token = strtok(NULL, ",");
    if (token) data->lon_dir = *token;

    // 速度
    token = strtok(NULL, ",");
    if (token) data->speed = atof(token);

    // 航向
    token = strtok(NULL, ",");
    if (token) data->course = atof(token);

    // 日期
    token = strtok(NULL, ",");
    if (token) strncpy(data->date, token, sizeof(data->date));

    // 模式
    token = strtok(NULL, "*");
    if (token) data->mode = *token;

    return 1;
}
