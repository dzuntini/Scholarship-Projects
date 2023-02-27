/usr/bin/mysql_install_db --user=root --basedir=/usr --datadir=/var/lib/mysql

/usr/bin/mysqld --user=root --datadir=/var/lib/mysql &
sleep 10

mysql -e "CREATE DATABASE IF NOT EXISTS \`${MARIADB_DATABASE}\`;"
mysql -e "CREATE USER IF NOT EXISTS \`${MARIADB_USER}\`@'localhost' IDENTIFIED BY '${MARIADB_PASSWORD}';"
mysql -e "GRANT ALL PRIVILEGES ON \`${MARIADB_DATABASE}\`.* TO \`${MARIADB_USER}\`@'%' IDENTIFIED BY '${MARIADB_PASSWORD}';"

mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MARIADB_ROOT_PASSWORD}';"
mysql -e "FLUSH PRIVILEGES;"

pkill mysqld
sleep 1
/usr/bin/mysqld --user=root --datadir=/var/lib/mysql
