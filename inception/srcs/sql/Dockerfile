FROM alpine:3.14

RUN apk update
RUN apk upgrade

RUN apk add mariadb mariadb-common mariadb-client mariadb-server-utils

RUN rm -f /etc/my.cnf.d/mariadb-server.cnf
RUN rm -f /etc/my.cnf.d/my.cnf
COPY my.cnf /etc/my.cnf.d/mly.cnf
COPY my.cnf /etc/mysql/my.cnf


RUN mkdir -p /run/mysqld /var/lib/mysql
RUN chown -R mysql /var/lib/mysql

COPY start.sh start.sh
CMD ["sh", "start.sh"]
EXPOSE 3306

