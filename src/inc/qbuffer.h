#include "stm8s105k4.h"
#include "stdbool.h"

typedef struct qbuffer_t {
    uint32_t front;
    uint32_t rear;
    uint32_t length;
    uint8_t* buffer;
} qbuffer_t;

bool qbuffer_create(qbuffer_t* new_qbuffer, uint8_t* data, uint32_t length);
bool qbuffer_write(qbuffer_t* qbuffer, uint8_t* data, uint32_t length);
bool qbuffer_read(qbuffer_t* qbuffer, uint8_t* data, uint32_t length);
uint32_t qbuffer_get_length(qbuffer_t* qbuffer);
void qbuffer_flush(qbuffer_t* qbuffer);