FROM alpine:3.14

RUN apk update
RUN apk upgrade

RUN apk add nginx
RUN apk add openssl
RUN		mkdir -p /etc/ssl/private
RUN 	mkdir -p /etc/ssl/certs
RUN		mkdir /var/www/html
RUN 	openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/nginx-selfsigned.key -out /etc/ssl/certs/nginx-selfsigned.crt -subj "/C=FR/ST=PACA/L=NICE/O=42Nice/CN=dzuntini"
COPY	default.conf	/etc/nginx/http.d/default.conf

EXPOSE 443

CMD [ "nginx", "-g", "daemon off;" ]
