FROM node:18-bullseye-slim

WORKDIR /ft_transcendence

RUN apt-get update
RUN apt-get install -y procps openssl
RUN rm -rf /var/lib/apt/lists/*

RUN npm update -g npm

RUN npm install -g @nestjs/cli
RUN npm install -g @angular/cli

RUN mkdir -p /ft_transcendence/app/backend
RUN mkdir -p /ft_transcendence/app/frontend
RUN chmod 777 app

COPY ./tools/build.sh /ft_transcendence/build.sh
RUN chmod +x /ft_transcendence/build.sh

COPY ./tools/dev.sh /ft_transcendence/dev.sh
RUN chmod +x /ft_transcendence/dev.sh

ENTRYPOINT ["bash", "/ft_transcendence/build.sh"]
# ENTRYPOINT ["bash", "/ft_transcendence/dev.sh"]