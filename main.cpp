#include "mongoose.h"
#include <stdio.h>

mg_serve_http_opts http_opts;

static void ev_handler(mg_connection* nc, int ev, void* ev_data)
{
    switch(ev)
    {
    case MG_EV_HTTP_REQUEST:
    {
        http_message* ht = (http_message*)ev_data;
        mg_serve_http(nc, ht, http_opts);
        break;
    }
    case MG_EV_WEBSOCKET_HANDSHAKE_DONE:
    {
        const char* buf = "welcome";
        mg_send_websocket_frame(nc, WEBSOCKET_OP_TEXT, buf, strlen(buf));
        break;
    }
    case MG_EV_WEBSOCKET_FRAME:
    {
        websocket_message* wm = (websocket_message*)ev_data;
        printf("received msg: %.*s\n", wm->size, wm->data);
        static int count = 0;
        ++count;
        char buf[256];
        snprintf(buf, sizeof(buf), "counter: %d", count);
        mg_send_websocket_frame(nc, WEBSOCKET_OP_TEXT, buf, strlen(buf));
        break;
    }
    case MG_EV_CLOSE:
    {
        break;
    }
    default:;
    }
}

int main()
{
    mg_mgr mgr;
    mg_mgr_init(&mgr, nullptr);

    const char* err;
    mg_bind_opts bind_opts = {};
    bind_opts.ssl_key = "server.key";
    bind_opts.ssl_cert = "server.crt";
    bind_opts.error_string = &err;

    mg_connection* conn = mg_bind_opt(&mgr, "1234", ev_handler, bind_opts);

    if(conn == nullptr)
    {
        printf("mg_bind_opt failed: %s\n", err);
        return 1;
    }

    http_opts.document_root = ".";
    http_opts.enable_directory_listing = "yes";

    mg_set_protocol_http_websocket(conn);

    for(;;)
    {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}
