FROM alpine:3.14

RUN apk update
RUN apk upgrade

RUN apk add php7 php7-fpm php7-opcache php7-mysqli \
            php7-session php7-iconv php7-json \
            php7-gd php7-curl php7-xml php7-common \
            php7-imap php7-cgi php7-pdo php7-pdo_mysql \
            php7-soap php7-xmlrpc php7-posix php7-mcrypt php7-redis \
            php7-gettext php7-ldap php7-ctype php7-dom php7-phar curl

COPY ./move/* ./

EXPOSE 9000

RUN adduser -D php-fpm-dzuntini

ENTRYPOINT ["sh", "installation.sh"]

CMD ["php-fpm7", "-F"]

