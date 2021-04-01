FROM debian:buster
COPY ./srcs/* /
RUN	apt-get update -y \
&&	apt-get upgrade -y \
&&	apt-get install wget \
					gnupg \
					lsb-release \
					openssl \
					nginx \
					mysql-common \
					default-mysql-server \
					php7.3 \
					php7.3-xml \
					php7.3-fpm \
					php7.3-mysql \
					php-common \
					php7.3-cli \
					php7.3-common \
					php7.3-json \
					php7.3-opcache \
					php7.3-readline \
					php7.3-mbstring -y \
&&	rm -rf /etc/nginx/sites-available/default \
&&	mv default /etc/nginx/sites-available/ \
&&	ln -sf /etc/nginx/sites-available/default /etc/nginx/sites-enabled \
&&	wget -P /var/www/html $(wget -P /var/www/html https://www.phpmyadmin.net/\
home_page/version.txt -q -O- | tail -1 | sed 's/zip/tar.gz/g') \
&&	tar xvf /var/www/html/phpMyAdmin-*-all-languages.tar.gz \
&&	mv phpMyAdmin-*-all-languages /var/www/html/PHPMyAdmin \
&&	rm -rf	/var/www/html/version.txt \
			/var/www/html/phpMyAdmin-*-all-languages.tar.gz \
&&	wget -P /var/www/html https://wordpress.org/latest.tar.gz \
&&	tar xvf /var/www/html/latest.tar.gz \
&&	mv wordpress /var/www/html/ \
&&	rm -rf /var/www/html/latest.tar.gz \
&&	chmod -R 755 /var/www/* \
&&	chown -R www-data:www-data /var/www/* \
#Wordpress
&&	mv wp-config.php /var/www/html/wordpress/ \
#Nginx
&&	mkdir /etc/nginx/ssl \
&&	openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
-out /etc/nginx/ssl/localhost.pem -keyout /etc/nginx/ssl/localhost.key \
-subj "/C=FR/ST=PACA/L=Nice/O=42Nice/OU=David/CN=localhost" \
&&	rm -rf /var/www/html/index.nginx-debian.html \
#PHPMyAdmin
&&	mv config.inc.php /var/www/html/PHPMyAdmin/ \
&&	service mysql start \
&&	mysql -u root -e "CREATE USER 'thor'@'localhost' IDENTIFIED BY 'thor';" \
&&	mysql -u root -e "GRANT ALL PRIVILEGES ON * . * TO 'thor'@'localhost';" \
&&	mysql -u root -e "FLUSH PRIVILEGES;" \
&&	mysql --user=thor --password=thor -e "CREATE DATABASE valhalla;" \
&&	service mysql stop
VOLUME /etc/nginx /var/www /var/lib/mysql
CMD bash start.sh
EXPOSE 80
EXPOSE 443