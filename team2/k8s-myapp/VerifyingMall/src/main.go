package main

import (
    "encoding/json"
    "io"
    "log"
    "net/http"
)

type RetObj struct {
    Code int
    Msg string
    Data interface{}
}

func main()  {
    var err error
    resp, err := http.Get("http://mall-service:50051")
    if err != nil {
        log.Panicf("HTTP GET http://mall-service:50051 Failed! err: %v", err)
    }
    content, err := io.ReadAll(resp.Body)
    defer resp.Body.Close()
    if err != nil {
        log.Panicf("Get http://mall-service:50051 response failed! err: %v", err)
    }

    retObj := &RetObj{}
    err = json.Unmarshal(content, retObj)
    if err != nil {
        log.Panicf("Parse http://mall-service:50051 response to object failed! err: %v", err)
    }

    if retObj.Code != 0 {
        log.Panicf("http://mall-service:50051 response code is not success! err: %v", err)
    }

    log.Println("http://mall-service:50051 response success!")
}