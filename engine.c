// CLEAN FINAL VERSION (MATCHES YOUR ASSIGNMENT)

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include "monitor_ioctl.h"

#define CONTROL_PATH "/tmp/mini_runtime.sock"

typedef struct {
    char id[32];
    pid_t pid;
    char state[16];
} container;

container containers[10];
int count = 0;

/* ================= CLIENT ================= */

int send_request(char *msg)
{
    int sock;
    struct sockaddr_un addr;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, CONTROL_PATH);

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));

    write(sock, msg, strlen(msg));
    close(sock);
    return 0;
}

/* ================= SUPERVISOR ================= */

int run_supervisor()
{
    int server_fd, client_fd;
    struct sockaddr_un addr;

    unlink(CONTROL_PATH);

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, CONTROL_PATH);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 5);

    printf("Supervisor running...\n");

    while (1) {
        char buffer[256];

        client_fd = accept(server_fd, NULL, NULL);
        read(client_fd, buffer, sizeof(buffer));

        if (strncmp(buffer, "start", 5) == 0) {

            char id[32], rootfs[128], cmd[128];
            sscanf(buffer, "start %s %s %s", id, rootfs, cmd);

            mkdir("logs", 0777);

            char logfile[128];
            sprintf(logfile, "logs/%s.log", id);

            int fd = open(logfile, O_CREAT | O_WRONLY | O_APPEND, 0644);

            pid_t pid = fork();

            if (pid == 0) {
                dup2(fd, 1);
                dup2(fd, 2);
                chroot(rootfs);
                chdir("/");
                execl("/bin/sh", "sh", "-c", cmd, NULL);
                exit(1);
            }

            close(fd);

            containers[count].pid = pid;
            strcpy(containers[count].id, id);
            strcpy(containers[count].state, "running");
            count++;


            // register with kernel
            int monitor_fd = open("/dev/container_monitor", O_RDONLY);
            if (monitor_fd >= 0) {
                struct monitor_request req;
                req.pid = pid;
                req.soft_limit_bytes = 40 * 1024 * 1024;
                req.hard_limit_bytes = 64 * 1024 * 1024;
                strcpy(req.container_id, id);

                ioctl(monitor_fd, MONITOR_REGISTER, &req);
                close(monitor_fd);
            }

            printf("Started %s PID %d\n", id, pid);
        }

        close(client_fd);
    }
}

/* ================= MAIN ================= */

int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "supervisor") == 0)
        return run_supervisor();

    else if (strcmp(argv[1], "start") == 0) {
        char cmd[256];
        sprintf(cmd, "start %s %s %s", argv[2], argv[3], argv[4]);
        return send_request(cmd);
    }

    else if (strcmp(argv[1], "ps") == 0) {
        for (int i = 0; i < count; i++)
            printf("%s | PID: %d | %s\n",
                   containers[i].id,
                   containers[i].pid,
                   containers[i].state);
    }

    return 0;
}
