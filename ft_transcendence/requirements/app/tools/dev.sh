#!/bin/bash

cd /ft_transcendence/app/backend
npm install
npx prisma migrate deploy
npx prisma generate
npm run start:dev
