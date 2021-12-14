package main

import (
    "flag"
    "fmt"
    "log"
    "net/http"
    "os"
    "time"
)


func main() {
    version := os.Getenv("SECKILL_VERSION")
    var count int64  // 计数器
    var appName string
    flag.StringVar(&appName, "app_name", "seckill", "set app name")
    flag.Parse()

    http.DefaultServeMux.HandleFunc("/",  func(resp http.ResponseWriter, req *http.Request) {
        count++
        // 构造响应
        result := []byte(fmt.Sprintf(`{"Code":0,"MSG":"success","Data":{"Time":"%s","Count":%d,"ServiceName":"%s","Version":"%s"}}`,
            time.Now().Format("2006-01-02 15:04:05"), count, appName, version))

        _, _ = os.Stdout.Write(result)
        _, _ = resp.Write(result)
    })
    log.Println("Server starting")
    http.ListenAndServe(":50051", http.DefaultServeMux)
}

