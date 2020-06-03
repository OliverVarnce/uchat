#include "uchat.h"

void onopen(int fd) {
    char *cli;
    cli = ws_getaddress(fd);
    printf("Connection opened, client: %d | addr: %s\n", fd, cli);
    free(cli);
}

void onclose(int fd) {
    char *cli;
    cli = ws_getaddress(fd);
    printf("Connection closed, client: %d | addr: %s\n", fd, cli);
    free(cli);
}

void onmessage(int fd, const unsigned char *msg) {
    char *cli;
    cli = ws_getaddress(fd);
    printf("I receive a message: %s, from: %s/%d\n", msg, cli, fd);
    ws_sendframe(fd, (char *)msg, true);
    free(cli);
}

void mx_init_sqli() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB_SOURCE, &db);

    if (rc) {
        mx_printerr("Can't open database \n");
        exit(1);
    }
    else {
        mx_printstr("Opened database successfully\n");
    }
    //sqlite3_close(db);
}

int main() {
    mx_init_sqli();
    struct ws_events evs;
    evs.onopen = &onopen;
    evs.onclose = &onclose;
    evs.onmessage = &onmessage;
    ws_socket(&evs, TCP_PORT);
    return 0;
}
