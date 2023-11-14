#include <stdio.h>
#include "uv.h"

#define BUFFER_SIZE 1024

typedef struct {
    uv_fs_t req;
    uv_buf_t buf;
} read_req_t;

void on_read(uv_fs_t* req) {
    read_req_t* read_req = (read_req_t*)req->data;

    if (req->result < 0) {
        fprintf(stderr, "Read error: %s\n", uv_strerror(req->result));
    } else if (req->result == 0) {
        printf("End of file reached.\n");
    } else {
        printf("Read %ld bytes: %.*s\n", req->result, req->result, read_req->buf.base);
    }

    uv_fs_req_cleanup(req);
    free(read_req->buf.base);
    free(read_req);
}

void on_open(uv_fs_t* req) {
    if (req->result < 0) {
        fprintf(stderr, "File open error: %s\n", uv_strerror(req->result));
    } else {
        read_req_t* read_req = (read_req_t*)malloc(sizeof(read_req_t));
        read_req->buf = uv_buf_init((char*)malloc(BUFFER_SIZE), BUFFER_SIZE);
        read_req->req.data = read_req;

        uv_fs_read(uv_default_loop(), &read_req->req, req->result, &read_req->buf, 1, -1, on_read);
    }

    uv_fs_req_cleanup(req);
}

int main() {
    uv_loop_t* loop = uv_default_loop();

    uv_fs_t open_req;
    uv_fs_open(loop, &open_req, "123.txt", O_RDONLY, 0, on_open);

    return uv_run(loop, UV_RUN_DEFAULT);
}