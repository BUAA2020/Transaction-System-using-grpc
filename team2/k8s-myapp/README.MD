# K8S 示例工程

### 说明
1. [AppX](./AppX) 示例服务
   1. 如何构建服务容器镜像
   2. 如何运行服务容器镜像
   3. 使用K8S Deployment 部署 AppX 至K8S
   4. 使用K8S Service 使 AppX 对集群内提供服务
2. [VerifyingAppX](./VerifyingAppX) 示例验证任务 K8S Job

### 环境
1. 安装 [kubectl](https://kubernetes.io/docs/tasks/tools/#kubectl)
2. 使用[./kube/config](./kube/config) 覆盖 `~/.kube/config`
3. 确认K8S运行状态 `kubectl cluster-info`

### 注意是想
1. 注意使用各自小组的namespace与镜像仓库。  比如队伍1使用 namespace team1。
2. kube config 信息不要外传
3. `docker login -u k8s-example-1636115017127 -p fa3336efbf25a63e269ad765ebf064eae12712f9 yinli2020-docker.pkg.coding.net` 登陆后，才可以推送容器镜像
