# zws_logis
物流表达式 logistics expression 


---- 是什么 what is that ----

顾名思义，物流表达式就是用表达式的方式描述物流的运转情况。比如这个表达式：
%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001)， 
就是中通一单6666和圆通两单8888和5641走铁路，京东一单JD0001走空运，基本上能够一眼就看出表达式的意思。

With a form of expression to describe logistics status, e.g.:
%railway(ems6666 + dhl(8888 + 5641)) + %airline(ups0001), 
that is one order of ems with number 6666 and two orders of dhl with numbers 8888 and 5641, they transport using railway, 
and order of ups with number 0001 transport using airline



---- 为什么 why ----

为了用简约而有规律的方式概括物流状态，并为进一步实现物流的数字化和自动化打基础。

Summary logistics status in a simple and regular form, in order to make a solid foundation for furthermore atuomatization and digitization in logstics industry



---- 特性 feature ----

支持中文 Supporting Chinese

关键字可配置 Keyword configurable

表达式可扩展 Expression scalable

自动代码生成 Automatic code generation





---- 用在哪 where to use ----

可广泛用于物流行业各种场景，如转运包裹单清点，包裹跟踪，计算包裹重量，分析包裹内容，物流信息的交互和传递等等。
Can be widely used in all kind of scene fo logistics industry between human and machine or between different machines,
e.g. manifest of packet, tracking system, calculation of packet weight, analyse packet content, and so on.


---- Licensing ----
The source code is licensed under GPL v3.
