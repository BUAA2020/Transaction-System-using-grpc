##
## Build
##
FROM golang:1.16-buster AS build

WORKDIR /app

COPY /src/* ./
RUN go mod download && go build -o /verifying-basic


##
## Deploy
##
FROM debian:stable-20210902-slim

WORKDIR /

COPY --from=build /verifying-basic /verifying-basic

ENTRYPOINT [ "/verifying-basic"]
