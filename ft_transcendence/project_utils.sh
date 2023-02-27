#!/bin/bash
POST=$(ifconfig | grep "inet " | grep -Fv 127.0.0.1 | awk '{print $2}' | cut -d " " -f 2  | sed "s/10.//" | sed 's/./c/1' | sed 's/./r/3' | rev | sed 's/./p/2' | rev )
if [ "$1" == "initialize .env" ]; then
	echo "initialize .env"
	echo POST=$POST | cat - .env > tmp && mv tmp .env
	python post.py $POST
elif [ "$1" == "run dev server" ]; then
	echo "run dev server"
	cd ./srcs/app/frontend && npx ng serve --port 8000 --host $POST.42nice.fr
fi