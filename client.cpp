#include "mongoose.h"
#include <stdio.h>

static void ev_handler(mg_connection* nc, int ev, void* ev_data)
{
    (void)nc;
    websocket_message* ws_msg = (websocket_message*)ev_data;

    switch(ev)
    {
    case MG_EV_CONNECT:
        printf("connected to server\n");
        break;

    case MG_EV_WEBSOCKET_HANDSHAKE_DONE:
        printf("Websocket connection established.\n");
        break;

    case MG_EV_WEBSOCKET_FRAME:
        printf("received message: %.*s\n", int(ws_msg->size), ws_msg->data);
        break;

    case MG_EV_CLOSE:
        printf("disconnected\n");
        break;

    default:;
    }
}

int main()
{
    mg_mgr mgr;
    mg_mgr_init(&mgr, nullptr);

    const char* err;

    // remember about zeroing a struct; it does not have a default constructor
    mg_connect_opts connect_opts = {};
    connect_opts.error_string = &err;
    connect_opts.ssl_ca_cert = "authority-crypt/auth.crt";

    mg_connection* conn = mg_connect_ws_opt(&mgr, ev_handler, connect_opts, "wss://localhost:1234",
                                            nullptr, nullptr);

    if(conn == nullptr)
    {
        printf("mg_coonect_ws_opt failed: %s\n", err);
        return 1;
    }

    for(;;)
    {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}
