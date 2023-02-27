all:
	sudo docker compose -f ./srcs/docker-compose.yml up --build

clean:
	sudo docker compose -f srcs/docker-compose.yml down --volumes

fclean: clean
	sudo rm -rf /home/user42/data/*
	sudo docker system prune -a --force

re:		fclean all

show: 
	sudo docker images -qa
	sudo docker volume ls -q 
