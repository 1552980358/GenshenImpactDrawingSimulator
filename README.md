# GenshenImpactDrawingSimulator

```
////////////////////////////////////////////////////////////////////
//                          _ooOoo_                               //
//                         o8888888o                              //
//                         88" . "88                              //
//                         (| ^_^ |)                              //
//                         O\  =  /O                             //
//                      ____/`---'\____                         //
//                    .'  \\|     |//  `.                      //
//                   /  \\|||  :  |||//  \                     //
//                  /  _||||| -:- |||||-  \                      //
//                  |   | \\\  -  /// |   |                    //
//                  | \_|  ''\---/''  |   |                     //
//                  \  .-\__  `-`  ___/-. /                   //
//                ___`. .'  /--.--\  `. . ___                  //
//              ."" '<  `.___\_<|>_/___.'  >'"".                //
//            | | :  `- \`.;`\ _ /`;.`/ - ` : | |         //
//            \  \ `-.   \_ __\ /__ _/   .-` /  /           //
//      ========`-.____`-.___\_____/___.-`____.-'========     //
//                           `=---='                             //
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        //
//               佛祖保佑       永无BUG     永不修改                //
////////////////////////////////////////////////////////////////////
```

## 抽卡概率
- 与官服[天空岛]一致
- 5*
    - 总概率 0.6%
    - UP: 占5*中的50%
    - 剩余5*角色共享剩余50%
- 4*
    - 总概率 5.1%
    - UP: UP角色共享50%
    - 剩余4*角色/武器共享剩余50%
- 3*
    - 总概率 94.3%
    - 全为武器

## 常数
- 不建议自行, 否则会打乱算法
- 若有问题请提issue

### `main.h`
- `FLAG_EXIT` -1
   - 退出指令
- `FLAG_CLEAR_ALL` -2
   - 清除全部记录指令
- `FLAG_DRAW_10` -3
   - 10连指令
- `FLAG_HELP` -999
   - 显示帮助信息

### `record.h`
- `TYPE_5` 5
   - 5* 总类型
- `TYPE_4` 4
   - 4* 总类型
- `TYPE_3` 3
   - 3* 类型
    
- `TYPE_5_UP` 55
   - 5* UP
- `TYPE_5_NON_UP` 50
   - 5* 非UP
- `TYPE_4_UP` 48
   - 4 * UP
- `TYPE_4_NON_UP` 44
   - 4* 非UP
    
### `draw.h`
- `LIST_SIZE`: 1000
   - `draw_list` 以及 `safety_match`的大小, 根据5* 概率 `0.6%`, 4* 概率 `5.1%` 成大后个位数不为0得出
- `SIZE_5_STAR_NON_UP` 5
   - 5 个非UP 5*角色
- `SIZE_4_STAR_UP` 3
   - 3 个UP 4*角色
- `SIZE_4_STAR_NON_UP` 28
   - 28 个非UP 4*角色

### 抽卡算法
1. 利用时间种子生成 `default_random_engine` 类
2. 利用 `uniform_int_distribution` 配合 `default_random_engine` 生成指定大小的数组
    - `draw_list` 以及 `safety_match`
        - 根据官方概率小数点, 一直*10, 直到和为整数 (1000)
        - `draw_list`
            - 为总池, 用于获取4*/5*, 且未知是否UP
            - 利用 `uniform_int_distribution` 配合 `default_random_engine` 获取 `TYPE_3` / `TYPE_4` / `TYPE_5`
        - `safety_match`
            - 为保底池, 用于获取4*/5*, 且未知是否UP
            - 利用 `uniform_int_distribution` 配合 `default_random_engine` 获取 `TYPE_4` / `TYPE_5`
    - `draw_5_star`
        - 大小为 `SIZE_5_STAR_NON_UP` * 2
        - 用于抽取5*是否为UP
        - 利用 `uniform_int_distribution` 配合 `default_random_engine` 获取 `TYPE_5_UP` / `TYPE_5_NON_UP`
    - `draw_4_star`
        - 大小为 `SIZE_4_STAR_UP` * `SIZE_4_STAR_NON_UP` * 2
        - 用于抽取4*是否为UP
        - 利用 `uniform_int_distribution` 配合 `default_random_engine` 获取 `TYPE_5_UP` / `TYPE_5_NON_UP`
3. 检查保底
    1. 大保底 (180抽)
        - `check_has_safety_match_180()`
    2. 小保底 (90抽)
        - `check_has_safety_match_90()`
    3. 10抽保底
        - `check_has_safety_match_10()`
4. 抽卡
    - 根据检查保底返回结果进行抽取
    1. 大保底
        - 直接返回UP
    2. 小保底
        - `draw_safety_match_90()`
    3. 10抽保底
        - `draw_safety_match_10()`
    4. 非保底抽
        - `draw_normal()`

## 内存占用
- 由于整个程序记录将会报错于内存中, 内存占用有机会变大
- 占用过大请及时输入`-2` 进行清理
- 有需要保存记录, 请入 `-4` 保存于执行目录中 [开发中, 敬请期待]