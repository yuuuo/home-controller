FROM node:18 as build
COPY . /app
WORKDIR /app
RUN npm ci && npm run build

FROM nginx:latest
COPY --from=build /app/dist /usr/share/nginx/html
