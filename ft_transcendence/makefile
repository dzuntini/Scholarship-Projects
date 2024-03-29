# Colored Text
_BLACK			= \033[0;30m
_RED 			= \033[0;31m
_GREEN			= \033[0;32m
_BROWN			= \033[0;33m
_BLUE			= \033[0;34m
_PURPLE			= \033[0;35m
_CYAN			= \033[0;36m
_LIGHT_GRAY		= \033[0;37m
_DARK_GRAY		= \033[1;30m
_LIGHT_RED		= \033[1;31m
_LIGHT_GREEN	= \033[1;32m
_YELLOW			= \033[1;33m
_LIGHT_BLUE		= \033[1;34m
_LIGHT_PURPLE	= \033[1;35m
_LIGHT_CYAN		= \033[1;36m
_WHITE			= \033[1;37m
_NC 			= \033[0m

# Inverted, i.e. colored backgrounds
_IGREY			= \x1b[40m
_IRED			= \x1b[41m
_IGREEN			= \x1b[42m
_IYELLOW		= \x1b[43m
_IBLUE			= \x1b[44m
_IPURPLE		= \x1b[45
_ICYAN			= \x1b[46m
_IWHITE			= \x1b[47m

# Color reset
_COLOR_RESET	= \033[0m

all: build up

build_env: .env
	@./project_utils.sh "initialize .env"
	@cp .env ./srcs/app/backend/.env
	@cp .env ./srcs/app/frontend/.env

transdata:
	@mkdir -p ./srcs/transbase

up: transdata build_env
	@docker-compose up

build: build_env
	@docker-compose build

build_app: build_env
	@docker-compose build app

dev: build_app up_app
	@./project_utils.sh "run dev server"

build_postgres: build_env transdata
	@docker-compose build postgres

up_app: build_env
	@docker-compose up -d app

up_postgres: build_env transdata
	@docker-compose up -d postgres

rm: rm_app rm_postgres

rm_app:
	@echo "y" | docker-compose rm -s -v app

rm_postgres:
	@rm -rf ./srcs/transbase
	@echo "y" | docker-compose rm -s -v postgres

app: build_app up_app

postgres: build_postgres up_postgres

down:
	@docker-compose down

.PHONY: transdata no_build all up down build build_app build_postgres up_app up_postgres app postgres rm_app rm_postgres

