##
## Build
##
FROM golang:1.16-buster AS build

WORKDIR /app

COPY /src/* ./
RUN go mod download && go build -o /mall


##
## Deploy
##
FROM debian:stable-20210902-slim

WORKDIR /

COPY --from=build /mall /mall

EXPOSE 50051

ENTRYPOINT [ "/mall"]
