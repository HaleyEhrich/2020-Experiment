# StackCharaNode类Api

## 1：主体

#### 1：作用

底层数据存储，是StackChara的数据使用的类;

## 2:接口&数据&函数

#### 1：数据

| 数据类型        | 名称     | 权限    | 作用                           |
| --------------- | -------- | ------- | ------------------------------ |
| double          | CharaNum | Private | 存储数字操作数数据             |
| chara           | Chara    | Private | 存储存储操作符数据             |
| int             | Type     | Private | 存储该节点存储的为何种数据类型 |
| StackCharaNode* | Next     | Private | 存储下一节点地址               |

#### 2：函数

##### 1：函数列表

|     函数名称      |           说明           |                参数                 |     返回值      |
| :---------------: | :----------------------: | :---------------------------------: | :-------------: |
|      GetNum       |   获取该节点的数字数据   |                 无                  |     double      |
|     GetChara      |   获取该节点的字符数据   |                 无                  |      char       |
|      GetType      | 获取该节点存储的数据类型 |                 无                  |       int       |
|    SetThisNode    |    设置该节点数据内容    | const double&/char&/StackCharaNode& |      bool       |
| SetNextNodeAdress |    设置下一节点的地址    |             StackChara*             |      bool       |
|      SetType      |   设置该节点的数据类型   |                 int                 |      bool       |
|      PopNext      |       弹出下一节点       |                 无                  |      bool       |
|   ThisPriority    |    获取该节点的优先级    |                 无                  |       int       |
|      GetNext      |     获取下一节点地址     |                 无                  | StackCharaNode* |

##### 2：函数详情

- double GetNum()

  获取该节点的数字数据

  若存在数字数据返回数据，若不存在返回-1；

- char GetChara()

  同上

- int GetType()

  返回该节点的数据类型：

  ​		**数字类型(NUMTYPE)--1**       

  ​		**字符类型(CHARATYPE)--2**     

  ​		**空(EMPTYTYPE)--3**

- bool SetThisNode(Const double&/char&/StackCharaNode)

  设置该节点数据

  根据函数参数决定设置数据，并且更新该节点的数据类型

- bool SetNextNdoeAdresss(StackChara*)

  设置下一节点的地址，地址为函数参数

- bool SetType(int)

  设置该节点的数据类型，类型设置为函数参数

- bool PopNext()

  弹出下一节点，更为准确为删除下一节点数据（注意内存泄露问题）

- int ThisPriority()

  获取改节点的数据优先级：

  ​	数字返回1：代表1优先级

  ​	‘+’、‘-’返回2：代表2优先级

  ​	‘*’、‘/‘返回3：代表3优先级

  ​	其它返回-1

  ​	**优先级数字越大该数据优先级越高；**

- StackCharaNode* GetNext()

  返回下一节点地址



------



# StackChara 类Api

## 1:主体

#### 1：作用

使用类用于存储两种不同数据（此处为`double` 以及 `char`），便于在进行前缀后缀转换时的数据存储、移动；

### 2：接口&数据&函数

#### 1：数据

| 数据类型        | 名称 | 权限    | 作用                     |
| --------------- | ---- | ------- | ------------------------ |
| StackCharaNode* | Data | Private | 存储链表第一个节点地址   |
| StackCharaNode* | Top  | Private | 存储链表最后一个节点地址 |

#### 2：函数

##### 1：函数列表

|    函数名称     |              说明              |                参数                 |        返回值         |
| :-------------: | :----------------------------: | :---------------------------------: | :-------------------: |
|  StackChara()   |          类的构造函数          |                 无                  |       无返回值        |
|     AddData     |         添加数据到链表         | const double&/char&/StackCharaNode& |         bool          |
|   StackEmpty    |          链表是否为空          |                 无                  |         bool          |
|   PopTopData    |      弹出最后（最新元素）      |                 无                  |         bool          |
|  PopFirstData   |      弹出最底（最早元素）      |                 无                  |         bool          |
| GetTopPriority  |   获取最后一个的数据的优先级   |                 无                  |          int          |
|  GetFirstType   |      获取第一个数据的类型      |                 无                  |          int          |
|  GetTopNumData  | 获取最后一个的数字类型节点数据 |                 无                  |        double         |
| GetFirstNumData | 获取第一个的数字类型节点的数据 |                 无                  |        double         |
|  GetFirstChara  |   获取第一个字符类型节点数据   |                 无                  |         char          |
|     GetTop      |        获取最后一个数据        |                 无                  | const StackCharaNode& |
|       out       |          输出链表数据          |                 无                  |         void          |

##### 2：函数详情

- void StackChara()

  构造函数

- bool AddData(const double&/char&/StackNode&)

  判定是否为空节点，为空数据填入该节点，否则建立下一节点填入数据

- bool StackEmpty()

  数据是否为空，为空返回1

- bool PopTopData()

  弹出第一个节点，确切而言是删除顶上元素

- bool PopFirstData()

  同上，但是弹出最底下节点

- int GetTopPriority()

  获取节点的数据优先级：

  ​	数字返回1：代表1优先级

  ​	‘+’、‘-’返回2：代表2优先级

  ​	‘*’、‘/‘返回3：代表3优先级

  ​	其它返回-1

- int GetFirstType()

  获取节点数据类型

- double GetTopNumData()

  获取顶上的数字类型数据

- double GetFirstNumData()

  同上获取最底下

- char GetFirstChara()

  获取顶上字符数据

- const StackCharaNode& GetTop()

  获取顶上的节点地址

- void out()

  输出数据

