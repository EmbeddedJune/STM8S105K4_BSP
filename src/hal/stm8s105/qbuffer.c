#include "qbuffer.h"

bool qbuffer_create(qbuffer_t* new_qbuffer, uint8_t* data, uint32_t length)
{
    bool ret = true;

    new_qbuffer->front = 0;
    new_qbuffer->rear = 0;
    new_qbuffer->length = length;
    new_qbuffer->buffer = data;

    return ret;
}

bool qbuffer_write(qbuffer_t* qbuffer, uint8_t* data, uint32_t length)
{
    bool ret = true;
    uint32_t i, cur_index, next_index;

    for (i = 0; i < length; i++) {
        // 쓰기는 변수 front를 움직입니다.
        cur_index = qbuffer->front;
        next_index = qbuffer->front + 1;
        // 버퍼(배열) 범위를 넘어갈 경우 0으로 돌아갑니다.
        if (next_index == qbuffer->length) next_index = 0;
        if (next_index != qbuffer->rear) {
            qbuffer->buffer[cur_index] = data[i];
            qbuffer->front = next_index;
        } else {
            ret = false;
            break;
        }
    }
    return ret;
}

bool qbuffer_read(qbuffer_t* qbuffer, uint8_t* data, uint32_t length)
{
    bool ret = true;
    uint32_t i, cur_index, next_index;
    
    for (i = 0; i < length; i++) {
        // 읽기는 변수 rear을 움직입니다.
        cur_index = qbuffer->rear;
        next_index = qbuffer->rear + 1;
        // 버퍼(배열) 범위를 벗어난 경우 다시 0으로 돌아갑니다.
        if (next_index == qbuffer->length) next_index = 0;
        if (cur_index != qbuffer->front) {
            data[i] = qbuffer->buffer[cur_index];
            qbuffer->rear = next_index;
        } else {
            ret = false;
            break;
        }
    }
    return ret;
}

uint32_t qbuffer_get_length(qbuffer_t* qbuffer)
{
    uint32_t ret;
    ret = (qbuffer->length + (qbuffer->front - qbuffer->rear)) % qbuffer->length;
    return ret;
}

void qbuffer_flush(qbuffer_t* qbuffer)
{
    qbuffer->front = 0;
    qbuffer->rear = 0;
}

