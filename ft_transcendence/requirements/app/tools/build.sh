#!/bin/bash

# Build Frontend
cd /ft_transcendence/app/frontend
echo $NG_APP_WS_URI
sed -i "s/  ws_host: '.*',/  ws_host: '$NG_APP_WS_URI',/g" ./src/environments/environment.prod.ts
cat ./src/environments/environment.prod.ts
npm install
npx ng build

# Start Backend
cd /ft_transcendence/app/backend
npm install
npx prisma migrate deploy
npx prisma generate
npm run build
npm run start:prod
