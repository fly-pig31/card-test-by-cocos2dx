# card-test-by-cocos2dx
card test demo
## 1.目录结构
Classes/
├── configs/    # 所有静态配置相关类
├── models/    # 运行时动态数据模型
├── views/     # 视图层，包含所有的UI展示组件
├── controllers/  # 控制器层，协调模型和视图
├── managers/  # 管理器层，提供全局性的服务和功能（作为controllers的成员；可持有model数据，禁止单例）
├── services/  # 服务层,提供无状态的服务，处理业务逻辑，不管理数据生命周期；（禁止持有model数据，可单例可静态方法）
└── utils/  # 工具类，提供通用功能
## 2.运行流程
MVC架构，对应的控制器初始化所有游戏对象，通过model渲染View层。view层再设置回调来调用Controller层接口
~~~mermaid
graph LR
Controller -->|操作数据| Model
View -->|通过回调操作| Controller
Model -->|数据渲染| View
~~~
